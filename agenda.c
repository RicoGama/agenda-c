#include <gtk/gtk.h>
#include "funcoes/funcoes_gtk_menu.h"
#include "funcoes/funcoes_inputs.h"

GtkWidget *labelInicial;

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Criar a janela
    GtkWidget *janela = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(janela), "Agenda de Contatos");
    gtk_container_set_border_width(GTK_CONTAINER(janela), 10);
    gtk_widget_set_size_request(janela, 800, 600);
    g_signal_connect(janela, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(janela), GTK_WIN_POS_CENTER);

    // Criar um GtkGrid como contêiner principal
    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(janela), grid);
    for (int i = 0; i < 20; i++) {
        gtk_grid_insert_column(GTK_GRID(grid), i);
    }
    // Criar a barra de menu
    GtkWidget *menubar = gtk_menu_bar_new();

    // Criar o menu "Arquivo" e seus itens
    GtkWidget *menu_arquivo = gtk_menu_new();
    GtkWidget *menuitem_arquivo = gtk_menu_item_new_with_label("Arquivo");
    GtkWidget *menuitem_novo = gtk_menu_item_new_with_label("Novo");
    GtkWidget *menuitem_abrir = gtk_menu_item_new_with_label("Abrir");
    GtkWidget *menuitem_sair = gtk_menu_item_new_with_label("Sair");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuitem_arquivo), menu_arquivo);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_arquivo), menuitem_novo);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_arquivo), menuitem_abrir);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_arquivo), gtk_separator_menu_item_new());
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_arquivo), menuitem_sair);

    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), menuitem_arquivo);

    // Criar a label para exibir o resultado
    labelInicial = gtk_label_new("Bem-vindo à Agenda de contatos");
    gtk_label_set_justify(GTK_LABEL(labelInicial), GTK_JUSTIFY_CENTER);
    gtk_grid_attach(GTK_GRID(grid), menubar, 0, 0, 1, 1); // Adicionar a menubar ao grid
    gtk_grid_attach(GTK_GRID(grid), labelInicial, 0, 1, 1, 1); // Adicionar a label ao grid

    // Criar o frame "Nome"
    GtkWidget *frameNome = gtk_frame_new("Nome");
    gtk_container_set_border_width(GTK_CONTAINER(frameNome), 10);
    gtk_grid_attach(GTK_GRID(grid), frameNome, 0, 2, 10, 1);

    // Criar a box vertical para organizar os widgets dentro do frame "Nome"
    GtkWidget *caixa_vertical_nome = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(caixa_vertical_nome), 10);
    gtk_container_add(GTK_CONTAINER(frameNome), caixa_vertical_nome);

    // Criar a entrada "Nome"
    GtkWidget *entradaNome = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(caixa_vertical_nome), entradaNome, FALSE, FALSE, 0);

    // Criar o frame "Email"
    GtkWidget *frameEmail = gtk_frame_new("Email");
    gtk_container_set_border_width(GTK_CONTAINER(frameEmail), 10);
    gtk_grid_attach(GTK_GRID(grid), frameEmail, 10, 2, 10, 1);

    // Criar a box vertical para organizar os widgets dentro do frame "Email"
    GtkWidget *caixa_vertical_email = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(caixa_vertical_email), 10);
    gtk_container_add(GTK_CONTAINER(frameEmail), caixa_vertical_email);

    // Criar a entrada "Email"
    GtkWidget *entradaEmail = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(caixa_vertical_email), entradaEmail, FALSE, FALSE, 0);

    // Criar o frame "Email"
    GtkWidget *frameTelefone = gtk_frame_new("Telefone");
    gtk_container_set_border_width(GTK_CONTAINER(frameTelefone), 10);
    gtk_grid_attach(GTK_GRID(grid), frameTelefone, 0, 3, 5, 1);

    // Criar a box vertical para organizar os widgets dentro do frame "Email"
    GtkWidget *caixa_vertical_telefone = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_set_border_width(GTK_CONTAINER(caixa_vertical_telefone), 10);
    gtk_container_add(GTK_CONTAINER(frameTelefone), caixa_vertical_telefone);

    // Criar a entrada "Telefone"
    GtkWidget *entradaTelefone = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(caixa_vertical_telefone), entradaTelefone, FALSE, FALSE, 0);
    g_signal_connect(entradaTelefone, "insert-text", G_CALLBACK(aplicarMascaraTelefone), NULL);
    g_signal_connect(entradaTelefone, "key-press-event", G_CALLBACK(onKeyPress), NULL);

    // Exibir a janela
    gtk_widget_show_all(janela);

    // Executar o loop principal do GTK
    gtk_main();

    return 0;
}
