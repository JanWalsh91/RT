#include <gtk/gtk.h>

static void
print_hello (GtkWidget *widget,
             gpointer   data)
{
  g_print ("Hello World\n");
}
// #define GTK_BUILDER_ERROR                (gtk_builder_error_quark ())
int
main (int   argc,
      char *argv[])
{
  GtkBuilder *builder;
  GObject *window;
  GObject *button;
//   GtkWidget *app;
	// GError *err = NULL;
  gtk_init (&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new ();
 	gtk_builder_add_from_file (builder, "builder.ui", NULL);
// {
// 	printf("Error adding build from file. Error: %s\n", err->message);
// }
// app = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
// gtk_builder_connect_signals (builder, NULL);
  /* Connect signal handlers to the constructed widgets. */
  window = gtk_builder_get_object (builder, "window");
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  button = gtk_builder_get_object (builder, "button1");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

  button = gtk_builder_get_object (builder, "button2");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

  button = gtk_builder_get_object (builder, "quit");
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

//   gtk_widget_show (app);
gtk_main ();
return 0;
}