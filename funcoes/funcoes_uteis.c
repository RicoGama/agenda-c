#include <gtk/gtk.h>
#include "funcoes_uteis.h"

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