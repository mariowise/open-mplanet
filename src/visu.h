#ifndef VISU_H_
#define VISU_H_

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

Window win;

unsigned int 		width, 
					height, 
					border_width,
					
					display_width, 
					display_height,

					screen;

char * 	window_name = "Planets movement",
	 *  display_name = NULL;

GC gc;

unsigned long valuemask = 0;

XGCValues 		values;

Display 		* display;

XSizeHints 		size_hints;

Pixmap 			bitmap;

XPoint 			points[800];

XSetWindowAttributes attr[1];

Colormap screen_colormap;

XColor grayColor;


void visu_start_window();

void visu_draw_universe();

#endif