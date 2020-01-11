#ifndef GLASS_INPUT_CURSOR_H
#define GLASS_INPUT_CURSOR_H

#include <wayland-server-core.h>
#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_xcursor_manager.h>

/**
 * glass_cursor is a wrapper around wlr_cursor that handles input devices
 * and the xcursor theme.
 * It also subscribes to relevant events to handle the motion of the cursor
 */
struct glass_cursor {
	struct wlr_cursor *cursor;
	struct wlr_xcursor_manager *xcursor_manager;
	struct wl_listener cursor_motion;
	struct wl_listener cursor_motion_absolute;
};

/**
 * Create a new glass_cursor and attach it to the given output_layout.
 * This creates a wlr_cursor and an xcursor_manager as well as subscribing
 * to the cursor_motion and cursor_motion_absolute events.
 */
struct glass_cursor *cursor_create(struct wlr_output_layout *layout);

#endif
