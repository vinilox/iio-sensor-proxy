// gcc -o test-orientation test-orientation.c orientation.c `pkg-config --libs --cflags gtk+-3.0` -lm

#include <gtk/gtk.h>
#include "orientation.h"

static GtkWidget *scale_x, *scale_y, *scale_z;
static GtkWidget *label;

#define ONEG 256

static void
value_changed (GtkSpinButton *spin_button,
	       gpointer       user_data)
{
	int x, y, z;
	OrientationUp o;

	x = gtk_spin_button_get_value (GTK_SPIN_BUTTON (scale_x));
	y = gtk_spin_button_get_value (GTK_SPIN_BUTTON (scale_y));
	z = gtk_spin_button_get_value (GTK_SPIN_BUTTON (scale_z));

	o = orientation_calc (ORIENTATION_UNDEFINED, x, y, z);
	gtk_label_set_text (GTK_LABEL (label), orientation_to_string (o));
}

int main (int argc, char **argv)
{
	GtkWidget *window;
	GtkWidget *box;

	gtk_init (&argc, &argv);

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	scale_x = gtk_spin_button_new_with_range (-ONEG, ONEG, 1);
	scale_y = gtk_spin_button_new_with_range (-ONEG, ONEG, 1);
	scale_z = gtk_spin_button_new_with_range (-ONEG, ONEG, 1);

	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
	gtk_container_add (GTK_CONTAINER (window), box);

	gtk_container_add (GTK_CONTAINER (box), scale_x);
	gtk_container_add (GTK_CONTAINER (box), scale_y);
	gtk_container_add (GTK_CONTAINER (box), scale_z);

	g_signal_connect (G_OBJECT (scale_x), "value-changed",
			  G_CALLBACK (value_changed), NULL);
	g_signal_connect (G_OBJECT (scale_y), "value-changed",
			  G_CALLBACK (value_changed), NULL);
	g_signal_connect (G_OBJECT (scale_y), "value-changed",
			  G_CALLBACK (value_changed), NULL);

	label = gtk_label_new ("");
	gtk_container_add (GTK_CONTAINER (box), label);

	value_changed (NULL, NULL);

	gtk_widget_show_all (window);
	gtk_main ();

	return 0;
}
