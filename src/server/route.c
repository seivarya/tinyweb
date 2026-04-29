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
                fprintf(stdout, "[%s]: error malloc failed for route route.c\n", __func__);
                return NULL;
        }
        fprintf(stdout, "[%s]: debug route constructed route.c\n", __func__);
        return rte;
}
