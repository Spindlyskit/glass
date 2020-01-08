#ifndef GLASS_DESKTOP_OUTPUT_H
#define GLASS_DESKTOP_OUTPUT_H

#include <wayland-server.h>
#include <wlr/types/wlr_output.h>

#include "glass/server.h"

struct glass_output {
	struct wlr_output *wlr_output;
	struct glass_server *server;

	struct wl_listener frame;
	struct wl_listener destroy;

	struct wl_list link;
};

void new_output_notify(struct wl_listener *listener, void *data);
void output_destroy_notify(struct wl_listener *listener, void *data);
void output_frame_notify(struct wl_listener *listener, void *data);

#endif
