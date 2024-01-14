#ifndef CALC_H
#define CALC_H

#include <gtk/gtk.h>
#include <stdbool.h>

#define NUM_BUTTONS 19
#define IO_ARR_SIZE 100
#define NUM_ARR_SIZE 10

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button[NUM_BUTTONS];
} calculator_elements;

GtkWidget *calculator_window;
int mode;
int count;
int pt_input_buffer;
float result;
float number_array[NUM_ARR_SIZE];
char input_buffer[IO_ARR_SIZE];
char output_buffer[IO_ARR_SIZE];

void activate(GtkApplication *app, gpointer user_data);
void init_grid(calculator_elements * widget);
void init_window(GtkApplication *app, calculator_elements * widget);
void calculate(GtkButton *button, gpointer data);

#endif // CALC_H