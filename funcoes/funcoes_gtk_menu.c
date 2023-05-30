#include <gtk/gtk.h>
#include "funcoes_gtk_menu.h"

void on_file_new_activate(GtkMenuItem *menuitem, gpointer data) {
    g_print("Opção 'Novo' selecionada.\n");
}

void on_file_open_activate(GtkMenuItem *menuitem, gpointer data) {
    g_print("Opção 'Abrir' selecionada.\n");
}

void on_file_quit_activate(GtkMenuItem *menuitem, gpointer data) {
    exit(0);
}

void on_edit_cut_activate(GtkMenuItem *menuitem, gpointer data) {
    g_print("Opção 'Recortar' selecionada.\n");
}

void on_edit_copy_activate(GtkMenuItem *menuitem, gpointer data) {
    g_print("Opção 'Copiar' selecionada.\n");
}

void on_edit_paste_activate(GtkMenuItem *menuitem, gpointer data) {
    g_print("Opção 'Colar' selecionada.\n");
}