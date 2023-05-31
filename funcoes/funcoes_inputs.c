#include <gtk/gtk.h>
#include <glib.h>
#include <mysql/mysql.h>
#include "funcoes_inputs.h"
#include "funcoes_uteis.h"

void aplicarMascaraTelefone(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    GtkEntry *entradaTelefone = GTK_ENTRY(widget);
    const gchar *texto = gtk_entry_get_text(entradaTelefone);
    gchar *mascara = g_strdup_printf("(%c%c)%c%c%c%c%c-%c%c%c%c", texto[0], texto[1], texto[2], texto[3], texto[4], texto[5], texto[6], texto[7], texto[8], texto[9], texto[10]);
    gtk_entry_set_text(entradaTelefone, mascara);
    g_free(mascara);
}

void gravarContato(GtkWidget *widget, gpointer data) {
    // Obter os valores digitados nos campos de entrada
    GtkEntry *entradaNome = GTK_ENTRY(gtk_builder_get_object(builder, "entradaNome"));
    GtkEntry *entradaEmail = GTK_ENTRY(gtk_builder_get_object(builder, "entradaEmail")); // Substitua "builder" pelo nome do objeto GtkBuilder usado em seu código
    GtkEntry *entradaTelefone = GTK_ENTRY(gtk_builder_get_object(builder, "entradaTelefone")); // Substitua "builder" pelo nome do objeto GtkBuilder usado em seu código

    const gchar *nome = gtk_entry_get_text(entradaNome);
    const gchar *email = gtk_entry_get_text(entradaEmail);
    const gchar *telefone = gtk_entry_get_text(entradaTelefone);

    // Conectar ao banco de dados MySQL
    MYSQL *conn;
    conn = mysql_init(NULL);
    
    if (conn == NULL) {
        fprintf(stderr, "Erro ao inicializar a conexão com o banco de dados: %s\n", mysql_error(conn));
        return;
    }

    if (mysql_real_connect(conn, "localhost", "usuario", "senha", "nomedobanco", 0, NULL, 0) == NULL) {
        fprintf(stderr, "Erro ao conectar ao banco de dados: %s\n", mysql_error(conn));
        mysql_close(conn);
        return;
    }

    // Montar a consulta SQL para inserir o novo contato na tabela
    char query[1024];
    sprintf(query, "INSERT INTO contatos (nome, email, telefone) VALUES ('%s', '%s', '%s')", nome, email, telefone);

    // Executar a consulta SQL
    if (mysql_query(conn, query) != 0) {
        fprintf(stderr, "Erro ao executar a consulta SQL: %s\n", mysql_error(conn));
    } else {
        printf("Contato gravado com sucesso!\n");
    }

    // Fechar a conexão com o banco de dados
    mysql_close(conn);
}