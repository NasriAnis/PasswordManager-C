#include <gtk/gtk.h>

#include "../include/view_vault.h"
#include "../include/main_window.h"

#include "glib-object.h"

static void main_window(GtkApplication *app, gpointer data);


int show_main_window(int argc, char** argv)
{
  GtkApplication *app;
  app = gtk_application_new("com.lockr.app", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK (main_window), NULL);

  int status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

static void main_window(GtkApplication *app, gpointer data)
{
  GtkWidget *paned, *sidebar, *btn_show_all,
  *scrolled_window, *content_area, *main_window;

  Window *window_ptr = g_malloc(sizeof(Window));

  // Initialize window
  main_window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (main_window), "Lokr vault");
  gtk_window_set_default_size (GTK_WINDOW (main_window), 700, 600);

  // initialize the panned box
  paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_window_set_child(GTK_WINDOW(main_window), paned);

  // create a right sidebar inside the panned box + button inside
  sidebar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_widget_set_size_request(sidebar, 150, -1);
  gtk_paned_set_start_child(GTK_PANED(paned), sidebar);

  btn_show_all = gtk_button_new_with_label("Show All Data");
  g_signal_connect(btn_show_all, "clicked", G_CALLBACK(view_vault), window_ptr);
  gtk_box_append(GTK_BOX(sidebar), btn_show_all);

  // initialize the right scrooled bar for content
  scrolled_window = gtk_scrolled_window_new();
  gtk_paned_set_end_child(GTK_PANED(paned), scrolled_window);

  // Create a box inside the scrolled window to hold password rows
  content_area = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), content_area);

  // save pointers used in other functions
  window_ptr->window = main_window;
  window_ptr->content_area = content_area;

  gtk_window_present (GTK_WINDOW (main_window));
}
