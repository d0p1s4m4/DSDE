#ifndef DSWM_H
# define DSWM_H 1

# include <X11/X.h>
# include <X11/Xlib.h>

typedef struct
{
	Display *display;
	int screen;
	Window root;
	Pixmap drawable;
	GC gc;

	int width;
	int height;

	int started;
} Wm;

typedef enum
{
	ERROR_ERROR,
	ERROR_FATAL,
} Error;

typedef void (*Callback)(Wm *wm, XEvent *evt);

typedef struct
{
	int code;
	Callback callback;
} EventHandler;

/* wm.c */
void wm_initalize(char const *disp);
void wm_run(void);
void wm_destroy(void);

/* error.c */
void error(Error err, char const *fmt, ...);

/* handler.c */
extern EventHandler handlers[];

/* main.c */
extern char const *prg_name;
extern int opt_colorize;

#endif /* DSWM_H */
