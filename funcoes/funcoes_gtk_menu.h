#ifndef FUNCOES_GTK_MENU_H
#define FUNCOES_GTK_MENU_H

#include <gtk/gtk.h>

void on_file_new_activate(GtkMenuItem *menuitem, gpointer data);
void on_file_open_activate(GtkMenuItem *menuitem, gpointer data);
void on_file_quit_activate(GtkMenuItem *menuitem, gpointer data);
void on_edit_cut_activate(GtkMenuItem *menuitem, gpointer data);
void on_edit_copy_activate(GtkMenuItem *menuitem, gpointer data);
void on_edit_paste_activate(GtkMenuItem *menuitem, gpointer data);

#endif