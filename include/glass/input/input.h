#ifndef GLASS_INPUT_INPUT_H
#define GLASS_INPUT_INPUT_H

#include <wayland-server.h>

void new_input_notify(struct wl_listener *listener, void *data);

#endif
