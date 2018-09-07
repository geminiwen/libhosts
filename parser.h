//
// Created by Gemini Wen on 2018/9/7.
//

#ifndef LIBHOSTS_PARSER_H
#define LIBHOSTS_PARSER_H

#include "hashmap.h"
#include "stdio.h"

/**
 * parse hosts file into a hashmap
 * @param hosts hosts string
 * @param len buffer length of hosts
 * @param map the container
 * @return
 */
int parse_hosts(const char *hosts, size_t len, map_t **map);

/**
 * release the pointers in records
 * @param map the records
 */
void destroy_records(map_t *map);

#endif //LIBHOSTS_PARSER_H
