#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

static void print_hello (GtkWidget *widget, gpointer data)
{
	g_print ("Hello World\n");
}
#include <stdio.h>

static void activate (GtkApplication *app, gpointer user_data)
{
	GtkWidget	*window;
	GtkWidget	*render;
	GdkPixbuf	*pixel;

	guchar	data[1080*720*3];
	memset(data, 255, 1080*720 * 3);
	pixel = gdk_pixbuf_new_from_data(data, GDK_COLORSPACE_RGB, FALSE, 8, 1080, 720, 720*3, NULL, NULL);
	render = gtk_image_new_from_pixbuf(pixel);

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 1080, 720);

	//button = gtk_button_new_with_label ("Hello World");

	//gtk_container_add (GTK_CONTAINER (window), button_box);
	gtk_container_add(GTK_CONTAINER(window), render);

	//g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
	//g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	//gtk_container_add (GTK_CONTAINER (button_box), button);
	gtk_widget_show_all(window);
}

int main (int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	return status;
}
