#ifndef GLASS_SERVER_H
#define GLASS_SERVER_H

#include <wayland-server.h>
#include <wlr/backend.h>
#include <wlr/types/wlr_compositor.h>
#include <wlr/types/wlr_data_device.h>
#include <wlr/types/wlr_output_layout.h>

struct glass_server {
	struct wl_display *wl_display;
	struct wl_event_loop *wl_event_loop;

	struct wlr_backend *backend;
	struct wlr_compositor *compositor;
	struct wlr_data_device_manager *data_device_manager;
	struct wlr_output_layout *output_layout;

	struct wl_listener new_output;
	struct wl_list outputs;

	const char *socket;
};

bool server_init(struct glass_server *server);
void server_run(struct glass_server *server);
void server_finish(struct glass_server *server);

#endif
