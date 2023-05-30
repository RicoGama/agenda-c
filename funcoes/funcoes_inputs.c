#include <gtk/gtk.h>
#include <glib.h>
#include "funcoes_inputs.h"

void aplicarMascaraTelefone(GtkWidget *widget, GdkEventKey *event, gpointer user_data) {
    GtkEntry *entradaTelefone = GTK_ENTRY(widget);
    const gchar *texto = gtk_entry_get_text(entradaTelefone);
    gchar *mascara = g_strdup_printf("(%c%c)%c%c%c%c%c-%c%c%c%c", texto[0], texto[1], texto[2], texto[3], texto[4], texto[5], texto[6], texto[7], texto[8], texto[9], texto[10]);
    gtk_entry_set_text(entradaTelefone, mascara);
    g_free(mascara);
}