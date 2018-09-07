#include <stdio.h>

#include "parser.h"
#include "string.h"


int iterator(any_t item, char *key, any_t value) {
   printf("key: %s, value: %s\n", key, (char *)value);
   return MAP_OK;
}

int main() {

    map_t *map;

    char * hosts = "#1231312312\r\n127.0.0.1       localhost abc.com\r\n255.255.255.255 broadcasthost\r\n127.0.0.1 phpmyadmin.localhost";

    parse_hosts(hosts, strlen(hosts), &map);

    hashmap_iterate(map, iterator, NULL);

    return 0;
}