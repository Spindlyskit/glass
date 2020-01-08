#include "desktop/output.h"

#include <stdlib.h>
#include <wayland-server.h>
#include <wlr/types/wlr_output.h>
#include <wlr/render/wlr_renderer.h>
#include <wlr/util/log.h>

#include "glass/server.h"

void
new_output_notify(struct wl_listener *listener, void *data)
{
	struct glass_server *server = wl_container_of(listener, server, new_output);
	struct wlr_output *wlr_output = data;

	wlr_log(WLR_DEBUG, "New output: %p ('%s')", wlr_output, wlr_output->name);

	if (!wl_list_empty(&wlr_output->modes)) {
		struct wlr_output_mode *mode =
			wl_container_of(wlr_output->modes.prev, mode, link);
		wlr_output_set_mode(wlr_output, mode);
	}

	struct glass_output *output = calloc(1, sizeof(struct glass_output));
	output->server = server;
	output->wlr_output = wlr_output;
	wl_list_insert(&server->outputs, &output->link);

	output->destroy.notify = output_destroy_notify;
	wl_signal_add(&wlr_output->events.destroy, &output->destroy);
	output->frame.notify = output_frame_notify;
	wl_signal_add(&wlr_output->events.frame, &output->frame);

	wlr_output_layout_add_auto(server->output_layout, wlr_output);
	wlr_output_create_global(wlr_output);
}

void
output_destroy_notify(struct wl_listener *listener, void *data)
{
	struct glass_output *output = wl_container_of(listener, output, destroy);
	wl_list_remove(&output->link);
	wl_list_remove(&output->destroy.link);
	wl_list_remove(&output->frame.link);
	free(output);
}

void
output_frame_notify(struct wl_listener *listener, void *data)
{
	struct glass_output *output = wl_container_of(listener, output, frame);
	struct wlr_output *wlr_output = data;
	struct wlr_renderer *renderer = wlr_backend_get_renderer(wlr_output->backend);

	wlr_output_attach_render(wlr_output, NULL);

	{
		float color[4] = { 1.0, 0, 0, 1.0 };
		wlr_renderer_clear(renderer, color);
	}

	wlr_output_commit(wlr_output);
	wlr_renderer_end(renderer);
}
