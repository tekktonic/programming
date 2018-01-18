#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

/* void notebook_add_webkit_widget(GtkNotebook *nb, GtkWidget *child, guint page, gpointer data) */
/* { */
    
/* } */



struct browser_widget
{
    GtkBox *container; // We don't care about the hbox in the url bar
    GtkButton *back, *forward, *refresh;
    GtkEntry *urlBar;
    WebKitWebView *webview;
};

void browse_browse_cb(GtkWidget *e, gpointer data)
{
    printf("testing %s\n", gtk_entry_get_text(e));
    struct browser_widget *self = (struct browser_widget *)data;

    webkit_web_view_load_uri(self->webview, gtk_entry_get_text(e));
}


struct browser_widget build_browser_widget(char *url)
{
    struct browser_widget ret;
    ret.container = (GtkBox*)gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    GtkBox *hbox = (GtkBox*)gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    ret.back = (GtkButton*)gtk_button_new_with_label("Back");
    ret.forward = (GtkButton*)gtk_button_new_with_label("Forward");
    ret.refresh = (GtkButton*)gtk_button_new_with_label("Refresh");

    ret.urlBar = (GtkEntry*)gtk_entry_new();
    gtk_box_pack_start(hbox, (GtkWidget*)ret.back, FALSE, TRUE, 0);
    gtk_box_pack_start(hbox, (GtkWidget*)ret.forward, FALSE, TRUE, 0);
    gtk_box_pack_start(hbox, (GtkWidget*)ret.urlBar, TRUE, TRUE, 0);
    gtk_box_pack_start(hbox, (GtkWidget*)ret.refresh, FALSE, TRUE, 0);
    
    ret.webview = (WebKitWebView*)webkit_web_view_new();

    gtk_box_pack_start(ret.container, (GtkWidget*)hbox, FALSE, TRUE, 0);
    gtk_box_pack_start(ret.container, (GtkWidget*)ret.webview, TRUE, TRUE, 0);
    gtk_entry_set_text(ret.urlBar, "about:blank");


    webkit_web_view_load_plain_text(ret.webview, "Hello World");

    return ret;
}

int main(int argc, char **argv)
{
    GtkBuilder *builder;

    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("browse.glade");

    GtkWindow *win = (GtkWindow*)gtk_builder_get_object(builder, "mainwindow");
    GtkNotebook *tabView = (GtkNotebook*)gtk_builder_get_object(builder, "tabview");
    // Connecting up gtk signals from glade is broken.
    g_signal_connect((GObject*)win, "destroy", gtk_main_quit, NULL);

    struct browser_widget w = build_browser_widget("");
    g_signal_connect(w.urlBar, "activate", (GCallback)browse_browse_cb, &w);
    gtk_notebook_append_page(tabView, (GtkWidget*)w.container, NULL);

//    gtk_widget_show((GtkWidget*)w.container);
    gtk_widget_show_all((GtkWidget*)win);

    gtk_main();
    return 0;
}
