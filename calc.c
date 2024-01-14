#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "calc.h"

// switch statement
#define DEFAULT -1
#define ADD     '+'
#define SUB     '-'
#define DIVV    '/'
#define MUL     'x'
#define POWW    '^'
#define EQUAL   '='
#define CLEAR   'C'
// Debugging tool
bool debugger = true;
// Macro function to display current running fragment of code
#define LINE_INFO(info) \
    if( debugger ) printf("[%s:%d]: %s\n", __FILE__, __LINE__, info)

int main(int argc, char **argv) {
    /* Pointer to app */
    GtkApplication *app;
    /* Init app */
    gtk_init(&argc, &argv);

    int status;
    app = gtk_application_new("org.gtk.calculator", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

/* FUNCTIONS DELCARATION */
void init_window(GtkApplication *app, calculator_elements * widget) {
    widget->window = gtk_application_window_new(app);
    gtk_window_set_position(GTK_WINDOW(widget->window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(widget->window), "My series calculator");
    gtk_window_set_default_size(GTK_WINDOW(widget->window), 200, 200);
    gtk_container_set_border_width(GTK_CONTAINER(widget->window), 10);
}

void init_grid(calculator_elements * widget) {
    widget->grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(widget->window), widget->grid);

    calculator_window = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(calculator_window), FALSE);
    /* LABELS FOR BUTTONS */
    const char *labels = "0123456789.+-x/C=^";
    /* ASSIGN CHARS TO BUTTONS */
    for (int i = 0; i < NUM_BUTTONS; i++) {
        widget->button[i] = gtk_button_new_with_label(g_strdup_printf("%c", labels[i]));
    }
    /* POSITION AND WIDTH ELEMENTS */
    gtk_grid_attach(GTK_GRID(widget->grid), calculator_window, 0, 0, 4, 1);
    /* ROW 1 */
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[15], 0, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[17], 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[14], 3, 1, 1, 1);
    /* ROW 2 */
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[7], 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[8], 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[9], 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[13], 3, 2, 1, 1);
    /* ROW 3 */
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[4], 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[5], 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[6], 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[12], 3, 3, 1, 1);
    /* ROW 4 */
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[1], 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[2], 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[3], 2, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[11], 3, 4, 1, 1);
    /* ROW 5 */
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[0], 0, 5, 2, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[10], 2, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(widget->grid), widget->button[16], 3, 5, 1, 1);

    for (int i = 0; i < NUM_BUTTONS; i++) {
        g_signal_connect(widget->button[i], "clicked", G_CALLBACK(calculate), NULL);
    }
}

void calculate(GtkButton *button, gpointer data) {
    // logic for buttons and calculation
    // decode pressed button label
	const gchar* text = gtk_button_get_label(button);
    // numbers stored in number_array
    int number_stored;

    switch (text[0]) {
    case POWW:
    case SUB:
    case DIVV:
    case MUL:
    case ADD:
    case EQUAL:
        // if operation button is pressed, collect number string to number_array
        LINE_INFO("SAVE TO number_arrayBER ARRAY");
        if (text[0] != EQUAL) // no overwrite mode operation
            mode = text[0];
        // string number to float number array
        number_array[count++] = atof(input_buffer);
        pt_input_buffer = 0;
        break;
    case CLEAR:
        // reset calculator, clear outputs
        LINE_INFO("CLEAR");
        gtk_entry_set_text(GTK_ENTRY(calculator_window), "");
		memset(input_buffer,0,strlen(input_buffer));
		memset(output_buffer,0,strlen(output_buffer));
        result = 0.0;
		count = 0;
        pt_input_buffer = 0;
		number_stored = sizeof(number_array)/sizeof(number_array[0]);
		
		for(int i=0; i<number_stored; i++) {
				number_array[i] = 0;
		}
        break;
    default:
        // store chars into buffer input
        LINE_INFO(text);
        sprintf(input_buffer+pt_input_buffer++, "%c", text[0]);
        gtk_entry_set_text(GTK_ENTRY(calculator_window), input_buffer);
        break;
    }

    if (text[0] == EQUAL) {
        // MAKE CALCULATION
        number_stored = sizeof(number_array)/sizeof(number_array[0]);
        LINE_INFO("MAKE CALCULATION");
        switch (mode){
        // OPERATION MODE
        case ADD:
            LINE_INFO("ADD");
            for(int i=0; i<number_stored; i++){
				result += number_array[i];
			}
            break;
        case DIVV:
            LINE_INFO("DIVV");
            result = number_array[0]/number_array[1];
            break;
        case SUB:
            LINE_INFO("SUB");
            if(result == 0.0){
					result = number_array[0]*2;
				}
			for(int i=0; i<number_stored; i++){
				result -= number_array[i];
			}
            break;
        case MUL:
            LINE_INFO("MUL");
            result = number_array[0]*number_array[1];
            break;
        case POWW:
            LINE_INFO("POWW");
            result = (float)pow((double)number_array[0],(double)number_array[1]);
            break;
        default:
            LINE_INFO(text);
            break;
        }
        mode = DEFAULT;
		sprintf(output_buffer, "%.6f", result);
        sprintf(input_buffer, "%.6f", result);
        // store result into number_array[0]
        number_array[0] = result;
        count = 0;
        // Display result
		gtk_entry_set_text(GTK_ENTRY(calculator_window), output_buffer);
    }
}

void activate(GtkApplication *app, gpointer user_data) {
    /* SETUP GUI LAYOUT */
    calculator_elements widget;
    /* INIT LAYOUT */
    init_window(app, &widget);
    init_grid(&widget);
    /* SETUP DARK MODE */
    GtkSettings *settings = gtk_settings_get_default();
    g_object_set(settings, "gtk-application-prefer-dark-theme", TRUE, NULL);
    /* DISPLAY APP */
    gtk_widget_show_all(widget.window);
}