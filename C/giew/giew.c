#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

static void destroy_window_cb(GtkWidget *widget, GtkWindow *win);
static void web_view_cb(WebKitWebView *wv, WebKitLoadEvent e, gpointer data);

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    
    GtkWindow *w = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(w, 800, 600);

    g_signal_connect(w, "destroy", G_CALLBACK(destroy_window_cb), NULL);
    WebKitWebView *view = (WebKitWebView*)webkit_web_view_new();
    gtk_container_add((GtkContainer*)w, (GtkWidget*)view);
    webkit_web_view_load_uri(view, argv[1]);

    g_signal_connect(view, "notify::title", G_CALLBACK(web_view_cb), w);
    gtk_widget_grab_focus((GtkWidget*)view);
    gtk_widget_show_all((GtkWidget*)w);

    gtk_main();
}

static void destroy_window_cb(GtkWidget *widget, GtkWindow *win) {
    gtk_main_quit();
}

static void web_view_cb(WebKitWebView *wv, WebKitLoadEvent e, gpointer data) {
    GtkWindow *w = (GtkWindow*)data;
    static int boo = 1;
    char blarg[5];
    sprintf(blarg, "%d", boo);
    
    switch (e) {
    case WEBKIT_LOAD_FINISHED:
        gtk_window_set_title(w, blarg);
        break;
    default:
        break;
    }
    boo++;
}
