#include "glass/input/cursor.h"

#include <stdlib.h>

#include <wayland-server.h>
#include <wlr/types/wlr_cursor.h>
#include <wlr/types/wlr_output_layout.h>
#include <wlr/types/wlr_xcursor_manager.h>
#include <wlr/util/log.h>

static void
cursor_motion_notify(struct wl_listener *listener, void *data) {
	struct glass_cursor *cursor =
		wl_container_of(listener, cursor, cursor_motion);
	struct wlr_event_pointer_motion *e = data;

	wlr_cursor_move(cursor->cursor, e->device, e->delta_x, e->delta_y);
}

static void
cursor_motion_absolute_notify(struct wl_listener *listener, void *data) {
	struct glass_cursor *cursor =
		wl_container_of(listener, cursor, cursor_motion_absolute);
	struct wlr_event_pointer_motion_absolute *e = data;

	wlr_cursor_move(cursor->cursor, e->device, e->x, e->y);
}

struct glass_cursor *
cursor_create(struct wlr_output_layout *layout)
{
	wlr_log(WLR_DEBUG, "Creating cursor");

	struct glass_cursor *cursor = malloc(sizeof(*cursor));
	if (!cursor) {
		wlr_log(WLR_ERROR, "Failed to allocate glass_cursor");
		return NULL;
	}

	cursor->cursor = wlr_cursor_create();
	if (!cursor->cursor) {
		wlr_log(WLR_ERROR, "Failed to create cursor");
		free(cursor);
		return NULL;
	}

	wlr_cursor_attach_output_layout(cursor->cursor, layout);

	cursor->xcursor_manager = wlr_xcursor_manager_create(NULL, 24);
	wlr_xcursor_manager_load(cursor->xcursor_manager, 24);

	cursor->cursor_motion.notify = cursor_motion_notify;
	wl_signal_add(
			&cursor->cursor->events.motion,
			&cursor->cursor_motion);

	cursor->cursor_motion_absolute.notify = cursor_motion_absolute_notify;
	wl_signal_add(
			&cursor->cursor->events.motion_absolute,
			&cursor->cursor_motion_absolute);

	return cursor;
}
