#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/StringDefs.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dswm.h"

static Wm wm;

static int
wm_error_handler(Display *display, XErrorEvent *err)
{
	char err_str[128];

	if (wm.started == 0)
	{
		error(ERROR_FATAL,
				"another window manager on display %s",
				XDisplayString(display));
	}

	memset(err_str, 0, 128 * sizeof(char));
	XGetErrorText(display, err->error_code, err_str, 128 * sizeof(char));
	error(ERROR_ERROR, "%s", err->error_code, err_str);
	return (0);
}

void
wm_initalize(const char *disp)
{
	wm.started = 0;
	wm.display = XOpenDisplay(disp);
	if (wm.display == NULL)
	{
		if (disp == NULL)
		{
			disp = getenv("DISPLAY");
		}
		error(ERROR_FATAL, " can't open display: %s", disp);
	}
	XSetErrorHandler(wm_error_handler);

	wm.screen = DefaultScreen(wm.display);
	wm.width = DisplayWidth(wm.display, wm.root);
	wm.height = DisplayHeight(wm.display, wm.root);
	wm.root = XDefaultRootWindow(wm.display);
	wm.drawable = XCreatePixmap(wm.display, wm.root, wm.width, wm.height,
								DefaultDepth(wm.display, wm.screen));
	wm.gc = XCreateGC(wm.display, wm.root, 0, NULL);
	XSelectInput(wm.display, wm.root,
				ButtonPressMask | EnterWindowMask | LeaveWindowMask
				| SubstructureRedirectMask | SubstructureNotifyMask
				| PropertyChangeMask | StructureNotifyMask);
	XSync(wm.display, 0);

	wm.started = 1;
}

void
wm_run(void)
{
	XEvent event;
	int idx;

	while (1)
	{
		XNextEvent(wm.display, &event);

		for (idx = 0; handlers[idx].callback != NULL; idx++)
		{
			if (handlers[idx].code == event.type)
			{
				handlers[idx].callback(&wm, &event);
				break;
			}
		}
#ifndef NDEBUG
		printf("evt: %d\n", event.type);
#endif /* !NDEBUG */
	}
}

void
wm_destroy(void)
{
	XFreePixmap(wm.display, wm.drawable);
	XFreeGC(wm.display, wm.gc);
	XCloseDisplay(wm.display);
}
