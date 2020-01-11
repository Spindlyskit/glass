#ifndef GLASS_INPUT_INPUT_H
#define GLASS_INPUT_INPUT_H

#include <wayland-server.h>

/**
 * Handles a new input device.
 * This should be the notify function for server->new_input.notify.
 */
void new_input_notify(struct wl_listener *listener, void *data);

#endif
