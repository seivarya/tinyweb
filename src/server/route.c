/* route.c */

#include <stdlib.h>
#include <stdio.h>

#include <server/route.h>

route *route_construct(void) {
        route *rte = malloc(sizeof(route));
        if (!rte) {
                fprintf(stderr, "error: [%s]: malloc failed for route\n", __func__);
                return NULL;
        }
        fprintf(stderr, "debug: [%s]: route constructed\n", __func__);
        return rte;
}
