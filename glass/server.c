#include "glass/server.h"

#include <stdlib.h>
#include <wayland-server.h>
#include <wlr/backend.h>
#include <wlr/render/wlr_renderer.h>
#include <wlr/types/wlr_compositor.h>
#include <wlr/types/wlr_data_device.h>
#include <wlr/types/wlr_gamma_control_v1.h>
#include <wlr/types/wlr_gtk_primary_selection.h>
#include <wlr/types/wlr_idle.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_xdg_shell.h>
#include <wlr/util/log.h>

#include "desktop/output.h"

bool
server_init(struct glass_server *server)
{
	wlr_log(WLR_DEBUG, "Initialising Wayland server");

	server->wl_display = wl_display_create();
	server->backend = wlr_backend_autocreate(server->wl_display, NULL);
	if (!server->backend) {
		wlr_log(WLR_ERROR, "Failed to create backend");
		wl_display_destroy(server->wl_display);
		return false;
	}

	wl_list_init(&server->outputs);
	server->new_output.notify = new_output_notify;
	wl_signal_add(&server->backend->events.new_output, &server->new_output);

	struct wlr_renderer *renderer = wlr_backend_get_renderer(server->backend);
	wlr_renderer_init_wl_display(renderer, server->wl_display);

	server->compositor = wlr_compositor_create(server->wl_display, renderer);
	server->data_device_manager = wlr_data_device_manager_create(server->wl_display);

	wl_display_init_shm(server->wl_display);
	wlr_gamma_control_manager_v1_create(server->wl_display);
	wlr_gtk_primary_selection_device_manager_create(server->wl_display);
	wlr_idle_create(server->wl_display);

	wlr_xdg_shell_create(server->wl_display);

	server->output_layout = wlr_output_layout_create();
	server->socket = wl_display_add_socket_auto(server->wl_display);
	if (!server->socket) {
		wlr_log(WLR_ERROR, "Failed to open Wayland socket");
		wlr_backend_destroy(server->backend);
		wl_display_destroy(server->wl_display);
		return false;
	}

	if (!wlr_backend_start(server->backend)) {
		wlr_log(WLR_ERROR, "Failed to start backend");
		wlr_backend_destroy(server->backend);
		wl_display_destroy(server->wl_display);
		return false;
	}

	setenv("WAYLAND_DISPLAY", server->socket, true);

	return true;
}

void
server_run(struct glass_server *server)
{
	wlr_log(WLR_DEBUG, "Running Wayland server on display '%s'", server->socket);

	wl_display_run(server->wl_display);
}

void
server_finish(struct glass_server *server)
{
	wlr_log(WLR_DEBUG, "Shutting down Wayland server");

	wlr_backend_destroy(server->backend);
	wl_display_destroy_clients(server->wl_display);
	wl_display_destroy(server->wl_display);
}
