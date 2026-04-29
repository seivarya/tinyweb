/* route.c */

#include <stdlib.h>
#include <stdio.h>

#include <server/route.h>


route *route_construct(void) {
        route *rte = malloc(sizeof(route));

	for (size_t i = 0; i < METHOD_COUNT; i++) {
		rte->methods[i] = 0;
	}

	rte->uri = NULL;
	rte->route_func = NULL;

        if (!rte) {
                fprintf(stderr, "error: [%s]: malloc failed for route\n", __func__);
                return NULL;
        }
        fprintf(stderr, "debug: [%s]: route constructed\n", __func__);
        return rte;
}
