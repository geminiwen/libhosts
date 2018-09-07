//
// Created by Gemini Wen on 2018/9/7.
//

#ifndef LIBHOSTS_PARSER_H
#define LIBHOSTS_PARSER_H

#include "hashmap.h"
#include "stdio.h"

int parse_hosts(const char *hosts, size_t len, map_t **map);

#endif //LIBHOSTS_PARSER_H
