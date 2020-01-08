#include <stdlib.h>
#include <stdio.h>
#include <wayland-server.h>
#include <wlr/util/log.h>

#include "glass/server.h"

int
main(void)
{
	wlr_log_init(WLR_DEBUG, NULL);

	struct glass_server server;

	if (!server_init(&server)) {
		wlr_log(WLR_ERROR, "Failed to initalise server");
		exit(EXIT_FAILURE);
	}

	wlr_log(WLR_INFO, "Starting glass");

	server_run(&server);
	server_finish(&server);

	return EXIT_SUCCESS;
}
