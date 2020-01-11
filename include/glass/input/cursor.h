#ifndef GLASS_INPUT_CURSOR_H
#define GLASS_INPUT_CURSOR_H

#include <wayland-server-core.h>
#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_xcursor_manager.h>

struct glass_cursor {
	struct wlr_cursor *cursor;
	struct wlr_xcursor_manager *xcursor_manager;
	struct wl_listener cursor_motion;
	struct wl_listener cursor_motion_absolute;
};

struct glass_cursor *cursor_create(struct wlr_output_layout *layout);

#endif
