
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <math.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include <point2D.h>
#include <universe.h>
#include <quadtree.h>
#include <visu.h>

void visu_start_window() {

	printf("Iniciando X11 window\n");
	
	if ((display = XOpenDisplay(display_name))==NULL) {
        printf("error al inicializar X11\n");
        exit(-1);
    }

    screen = DefaultScreen (display);
    display_width  = DisplayWidth (display, screen);
    display_height = DisplayHeight(display, screen);


    /* tamaño de la ventana */
    width  = WINDOW_WIDTH;
    height = WINDOW_HEIGHT;
    border_width = 4;
    win = XCreateSimpleWindow (display, RootWindow (display, screen),
                               500, 0, width, height, border_width,
                               BlackPixel (display, screen), WhitePixel (display, screen));
    XStoreName(display, win, window_name);

    gc = XCreateGC (display, win, valuemask, &values);
    XSetBackground (display, gc, WhitePixel (display, screen));
    XSetLineAttributes (display, gc, 1, LineSolid, CapRound, JoinRound);
	    attr[0].backing_store = Always;
	    attr[0].backing_planes = 1;
	    attr[0].backing_pixel = BlackPixel(display, screen);
    XChangeWindowAttributes(display, win, CWBackingStore | CWBackingPlanes | CWBackingPixel, attr);
    XMapWindow (display, win);

    screen_colormap = DefaultColormap(display, DefaultScreen(display));

    XFlush(display);
    XClearWindow(display, win);
}

void visu_draw_universe() {
	int i, visx, visy, size;
	double px, py, mass;
	XClearWindow(display, win);
	for(i = 0; i < univ.cant; i++) {
		// Posiciones absolutas
		px =  univ.objects[i].pos.x;
		py = -univ.objects[i].pos.y;

        if(univ.objects[i].mass > 1.0E+29)
            size = 18;
        else
            size = 9;

		// Posiciones relativas
		visx = (int) floor((px + univ.ratio) / (univ.ratio * 2) * WINDOW_WIDTH);
		visy = (int) floor((py + univ.ratio) / (univ.ratio * 2) * WINDOW_HEIGHT);

		// Se dibujan las posiciones relativas
		grayColor.red = grayColor.green = grayColor.blue = 255;
        XAllocColor(display, screen_colormap, &grayColor);
        XSetForeground(display, gc, grayColor.pixel);

        XFillArc(display, win, gc, visx, visy, size, size, 0, 360*64);
        
        grayColor.red = grayColor.green= grayColor.blue = 0;
        XAllocColor(display, screen_colormap, &grayColor);
        XSetForeground(display, gc, grayColor.pixel);
	}
	XFlush(display);
}