#ifndef FUNCOES_UTEIS_H
#define FUNCOES_UTEIS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#define MAX_KEY_LENGTH 128
#define MAX_VALUE_LENGTH 128

typedef struct {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} EnvEntry;

void mostrarAviso(const gchar *mensagem);
int loadEnvFile(const char* filename, EnvEntry** envArray);
void freeEnvArray(EnvEntry* envArray, int envCount);

#endif
