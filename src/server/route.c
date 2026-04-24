#include <stdio.h>
#include <stdlib.h>

#include <server/route.h>

route *route_construct(void) {
        route *rte = malloc(sizeof(route));
        printf("here\n");
        return rte;
}
