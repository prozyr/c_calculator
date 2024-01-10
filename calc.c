#include  <gtk/gtk.h>

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

// Include Flex and Bison generated files
// #include "calc.tab.h"
// #include <FlexLexer.h>

typedef struct {
    GtkWidget *window;
    GtkWidget *widget;
    GtkWidget *grid;
    GtkWidget *button[19];
} calc;

GtkWidget *box;

#define SIZE 10
#define ADD     1
#define SUB     2
#define DIVV    3
#define MUL     4
#define POWW    5
#define CLEAR   0
#define DEFAULT -1

bool clear_buffer = false;
bool add=false;
bool mul = false;
bool divv = false;
bool sub = false;
bool poww = false;

char input_buffer[100] = {0};
char output_buffer[100] = {0};

float result = 0.0;
static float num[SIZE];
int count = 0;
int mode = 0;

static void calculate(GtkButton *button, gpointer data){

	const gchar* text = gtk_button_get_label(button);
    // Update lexer input with the new entry content
    // yyin = fmemopen(input_buffer, strlen(input_buffer), "r");
    // yyparse(); // Parse the updated input

	if( (strcmp("+", text)==0) ||   (strcmp("-", text)==0) ||  (strcmp("/", text)==0) ||  (strcmp("x", text)==0) ||  (strcmp("=", text)==0) || (strcmp("^", text)==0) ){
		
		num[count] = atof(input_buffer);
		count++;
		clear_buffer = true;

		if(strcmp("+",text)==0){
			add = true;
            mode = ADD;
		}
		if(strcmp("-",text)==0){
			sub = true;
            mode = SUB;
		}
		if(strcmp("/",text)==0){
			divv = true;
            mode = DIVV;
		}
		if(strcmp("x",text)==0){
			mul = true;
            mode = MUL;
		}
        if(strcmp("^",text)==0){
			poww = true;
            mode = POWW;
		}
	}

    switch (text[0])
    {
    case '+':
        mode = ADD;
        break;
    case '-':
        mode = SUB;
        break;
    case '/':
        mode = DIVV;
        break;
    case 'x':
        mode = MUL;
        break;
    case '^':
        mode = POWW;
        break;
    
    default:
        break;
    }

	if(strcmp("=",text)==0){
		int x = sizeof(num)/sizeof(num[0]);

        if (count < 1)
        {
            num[1] = result;
            num[0] = result;
            x = 3;
        } else {
            result = 0.0;
        }
        
		
        switch (mode)
        {
        case ADD:
            for(int i=0; i<x; i++){
				result += num[i];
			}
            break;
        case DIVV:
            result = num[0]/num[1];
            break;
        case SUB:
            if(result == 0.0){
					result = num[0]*2;
				}
			for(int i=0; i<x; i++){
				result -= num[i];
			}
            break;
        case MUL:
            result = num[0]*num[1];
            break;
        case POWW:
            result = (float)pow((double)num[0],(double)num[1]);
            break;
        default:
            break;
        }

        mode = DEFAULT;

		add = false;
		mul = false;
		divv = false;
		sub = false;
		
		gtk_entry_set_text(GTK_ENTRY(box), "");
		sprintf(output_buffer, "%.3f", result);
		gtk_entry_set_text(GTK_ENTRY(box), output_buffer);
        memset(input_buffer,0,strlen(input_buffer));
    
        // snprintf(output_buffer, sizeof(output_buffer), "%.3f", result);
		// result = 0.0;
	} else{
		if(clear_buffer){
			memset(input_buffer,0,strlen(input_buffer));
			clear_buffer = false;
		}else{
			strncat(input_buffer,text, 1);
		}
		
			strncat(output_buffer,text, 1);
			gtk_entry_set_text(GTK_ENTRY(box), output_buffer);
	}
		
	if(text[0] == 'C'){
		gtk_entry_set_text(GTK_ENTRY(box), "");
		memset(input_buffer,0,strlen(input_buffer));
		memset(output_buffer,0,strlen(output_buffer));
        result = 0.0;
		count = 0;
		int x = sizeof(num)/sizeof(num[0]);
		
		for(int i=0; i<x; i++){
				num[i] = 0;
		}

		add = false;
		mul = false;
		divv = false;
		sub = false;
        poww = false;
	}
}

static void activate(GtkApplication *app, gpointer user_data) {
    /* SETUP GUI LAYOUT */
    calc widget;

    widget.window = gtk_application_window_new(app);
    gtk_window_set_position(GTK_WINDOW(widget.window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(widget.window), "My series calculator");
    gtk_window_set_default_size(GTK_WINDOW(widget.window), 200, 200);
    gtk_container_set_border_width(GTK_CONTAINER(widget.window), 10);

    widget.grid = gtk_grid_new();

    gtk_container_add(GTK_CONTAINER(widget.window), widget.grid);

    box = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(box), TRUE);

    /* SETUP DARK MODE */
    GtkSettings *settings = gtk_settings_get_default();
    g_object_set(settings, "gtk-application-prefer-dark-theme", TRUE, NULL);


    /* LABELS FOR KEYBOARD */
    char *labels = "0123456789.+-x/C=^";
    /* ASSIGN CHARS TO BUTTONS */
    for (int i = 0; i < 19; i++) {
        widget.button[i] = gtk_button_new_with_label(g_strdup_printf("%c", labels[i]));
    }
    
    /* POSITION AND WIDTH ELEMENTS */
    /* NUMBER SPACE */
    gtk_grid_attach(GTK_GRID(widget.grid), box, 0, 0, 4, 1);
    /* ROW 1 */
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[15], 0, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[17], 2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[14], 3, 1, 1, 1);
    /* ROW 2 */
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[7], 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[8], 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[9], 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[13], 3, 2, 1, 1);
    /* ROW 3 */
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[4], 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[5], 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[6], 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[12], 3, 3, 1, 1);
    /* ROW 4 */
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[1], 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[2], 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[3], 2, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[11], 3, 4, 1, 1);
    /* ROW 5 */
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[0], 0, 5, 2, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[10], 2, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[16], 3, 5, 1, 1);

    for (int i = 0; i < 18; i++) {
        g_signal_connect(widget.button[i], "clicked", G_CALLBACK(calculate), NULL);
    }

    gtk_widget_show_all(widget.window);
}

int main(int argc, char **argv) {
    /* Pointer to app */
    GtkApplication *app;
    /* Init app */
    gtk_init(&argc, &argv);
    // Initialize the Flex and Bison lexer/parser
    // yyin = stdin; // Set the input source to stdin for simplicity
    /* Status variable */
    int status;
    app = gtk_application_new("org.gtk.calculator", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}