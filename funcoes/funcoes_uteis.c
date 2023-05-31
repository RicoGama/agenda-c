#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_uteis.h"

#define MAX_LINE_LENGTH 256
#define MAX_KEY_LENGTH 128
#define MAX_VALUE_LENGTH 128

void mostrarAviso(const gchar *mensagem) {
    // Cria o diálogo de mensagem
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                               GTK_DIALOG_MODAL,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "%s",
                                               mensagem);
    // Executa o diálogo e aguarda a resposta do usuário
    gtk_dialog_run(GTK_DIALOG(dialog));

    // Fecha o diálogo
    gtk_widget_destroy(dialog);
}

int loadEnvFile(const char* filename, EnvEntry** envArray) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", filename);
        return 0;
    }

    EnvEntry* envData = NULL;
    int envCount = 0;

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Verificar se a linha possui o formato chave=valor válido
        char* delimiter = strchr(line, '=');
        if (delimiter == NULL || line[0] == '#' || line[0] == '\n') {
            continue;  // Ignorar linhas inválidas ou comentários
        }

        // Extrair a chave e o valor da linha
        *delimiter = '\0';
        char* key = line;
        char* value = delimiter + 1;
        size_t keyLength = strlen(key);
        size_t valueLength = strlen(value);

        // Remover caracteres de espaço em branco do final da chave e do valor
        while (keyLength > 0 && (key[keyLength - 1] == ' ' || key[keyLength - 1] == '\t' || key[keyLength - 1] == '\n')) {
            key[keyLength - 1] = '\0';
            keyLength--;
        }
        while (valueLength > 0 && (value[valueLength - 1] == ' ' || value[valueLength - 1] == '\t' || value[valueLength - 1] == '\n')) {
            value[valueLength - 1] = '\0';
            valueLength--;
        }

        // Armazenar a chave e o valor no array associativo
        envData = realloc(envData, (envCount + 1) * sizeof(EnvEntry));
        strncpy(envData[envCount].key, key, MAX_KEY_LENGTH - 1);
        strncpy(envData[envCount].value, value, MAX_VALUE_LENGTH - 1);
        envCount++;
    }

    fclose(file);

    *envArray = envData;
    return envCount;
}

void freeEnvArray(EnvEntry* envArray, int envCount) {
    if (envArray == NULL) {
        return;
    }

    for (int i = 0; i < envCount; i++) {
        memset(envArray[i].key, 0, MAX_KEY_LENGTH);
        memset(envArray[i].value, 0, MAX_VALUE_LENGTH);
    }

    free(envArray);
}