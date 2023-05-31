#include <gtk/gtk.h>
#include <glib.h>
#include <mysql/mysql.h>
#include <stdio.h>
#include <time.h>
#include "funcoes_inputs.h"
#include "funcoes_uteis.h"

#define MAX_ENV_VARS 100

void aplicarMascaraTelefone(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    GtkEntry *entradaTelefone = GTK_ENTRY(widget);
    const gchar *texto = gtk_entry_get_text(entradaTelefone);
    gchar *mascara = g_strdup_printf("(%c%c)%c%c%c%c%c-%c%c%c%c", texto[0], texto[1], texto[2], texto[3], texto[4], texto[5], texto[6], texto[7], texto[8], texto[9], texto[10]);
    gtk_entry_set_text(entradaTelefone, mascara);
    g_free(mascara);
}

void gravarContato(GtkWidget *widget, gpointer user_data) {

    const char* envFilename = ".env";

    EnvEntry* envArray;
    int envCount = loadEnvFile(envFilename, &envArray);

    char* host = NULL;
    char* username = NULL;
    char* password = NULL;
    char* database = NULL;

    // Conectar ao banco de dados MySQL
    MYSQL *conn;
    conn = mysql_init(NULL);

    for (int i = 0; i < envCount; i++) {
        if (strcmp(envArray[i].key, "USER") == 0) {
            username = envArray[i].value;
        } else if (strcmp(envArray[i].key, "PASSWORD") == 0) {
            password = envArray[i].value;
        } else if (strcmp(envArray[i].key, "HOST") == 0) {
            host = envArray[i].value;
        } else if (strcmp(envArray[i].key, "BD") == 0) {
            database = envArray[i].value;
        }
    }

    if (host == NULL || username == NULL || password == NULL || database == NULL) {
        mostrarAviso("Impossível resgatar os parâmetros de conexão do bd.");
        // Lembre-se de liberar a memória alocada para o envArray antes de retornar
        freeEnvArray(envArray, envCount);
        mysql_close(conn);
        return;
    }

    // Obter os valores digitados nos campos de entrada
    GtkBuilder *builder = GTK_BUILDER(user_data);

    // Obter os valores digitados nos campos de entrada
    GtkEntry *entradaNome = GTK_ENTRY(gtk_builder_get_object(builder, "entradaNome"));
    GtkEntry *entradaEmail = GTK_ENTRY(gtk_builder_get_object(builder, "entradaEmail"));
    GtkEntry *entradaTelefone = GTK_ENTRY(gtk_builder_get_object(builder, "entradaTelefone"));
    
    if (conn == NULL) {
        fprintf(stderr, "Erro ao inicializar a conexão com o banco de dados: %s\n", mysql_error(conn));
        return;
    }

    if (mysql_real_connect(conn, host, username, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Erro ao conectar ao banco de dados: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    const gchar *nome = gtk_entry_get_text(entradaNome);
    const gchar *email = gtk_entry_get_text(entradaEmail);
    const gchar *telefone = gtk_entry_get_text(entradaTelefone);

    if (strlen(nome) == 0 || strlen(email) == 0 || strlen(telefone) == 0) {
        mostrarAviso("Por favor, preencha todos os campos");
        return;
    }

    char nomeCopy[100];
    char emailCopy[100];
    char telefoneCopy[100];
    strcpy(nomeCopy, nome);
    strcpy(emailCopy, email);
    strcpy(telefoneCopy, telefone);
    
    time_t currentTime;
    time(&currentTime);

    // Converter o timestamp para uma string formatada
    char timestampStr[20]; // Tamanho suficiente para armazenar a string formatada
    strftime(timestampStr, sizeof(timestampStr), "%Y-%m-%d %H:%M:%S", localtime(&currentTime));

    // Montar a consulta SQL para inserir o novo contato na tabela
    char query[1024];
    sprintf(query, "INSERT INTO contatos (nome, email, telefone, created_at, updated_at) VALUES ('%s', '%s', '%s', '%s', '%s')", nomeCopy, emailCopy, telefoneCopy, timestampStr, timestampStr);

    // Executar a consulta SQL
    if (mysql_query(conn, query) != 0) {
        fprintf(stderr, "Erro ao executar a consulta SQL: %s\n", mysql_error(conn));
    } else {
        mostrarAviso("Contato gravado com sucesso");
    }

    // Fechar a conexão com o banco de dados
    mysql_close(conn);
}