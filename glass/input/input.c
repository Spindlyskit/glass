#include "glass/input/input.h"

#include <wayland-server.h>
#include <wlr/types/wlr_input_device.h>
#include <wlr/util/log.h>

#include "glass/server.h"

static void
new_pointer(struct glass_server *server, struct wlr_input_device *dev)
{
	wlr_cursor_attach_input_device(server->cursor->cursor, dev);
}

void
new_input_notify(struct wl_listener *listener, void *data)
{
	struct glass_server *server =
		wl_container_of(listener, server, new_input);
	struct wlr_input_device *dev = data;

	wlr_log(WLR_DEBUG, "Found new input device: %s", dev->name);

	switch (dev->type) {
		case WLR_INPUT_DEVICE_POINTER:
			new_pointer(server, dev);
			break;
		default:
			// Pass
			break;
	}
}
