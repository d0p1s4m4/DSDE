#include "dswm.h"
#include <X11/Xlib.h>

void
on_key_press(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_button_press(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_motion_notify(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_enter_notify(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_create_notify(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_expose(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_configure_request(Wm *wm, XEvent *evt)
{
	XConfigureRequestEvent crevt;
	XWindowChanges chg;

	crevt = evt->xconfigurerequest;
	chg.x = crevt.x;
	chg.y = crevt.y;
    chg.width = crevt.width;
	chg.height = crevt.height;
    chg.border_width = crevt.border_width;
    chg.sibling = crevt.above;
    chg.stack_mode = crevt.detail;

	XConfigureWindow(wm->display, crevt.window, crevt.value_mask, &chg);
}

void
on_configure_notify(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_map_request(Wm *wm, XEvent *evt)
{
	XMapWindow(wm->display, evt->xmaprequest.window);
}

void
on_reparent_notify(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_map_notify(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_unmap_notify(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_destroy_notify(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_property_notify(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_client_message(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

void
on_mapping_notify(Wm *wm, XEvent *evt)
{
	(void)wm;
	(void)evt;
}

EventHandler handlers[] = {
	{KeyPress, on_key_press},
	{ButtonPress, on_button_press},
	{MotionNotify, on_motion_notify},
	{EnterNotify, on_enter_notify},
	{Expose, on_expose},
	{CreateNotify, on_create_notify},
	{DestroyNotify, on_destroy_notify},
	{UnmapNotify, on_unmap_notify},
	{MapNotify, on_map_notify},
	{MapRequest, on_map_request},
	{ReparentNotify, on_reparent_notify},
	{ConfigureRequest, on_configure_request},
	{ConfigureNotify, on_configure_notify},
	{PropertyNotify, on_property_notify},
	{ClientMessage, on_client_message},
	{MappingNotify, on_mapping_notify},
	{0, NULL}
};
