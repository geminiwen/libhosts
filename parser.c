//
// Created by Gemini Wen on 2018/9/7.
//

#include <memory.h>
#include "parser.h"
#include "stdlib.h"

enum {
    STATE_INIT,
    STATE_IP,
    STATE_HOST,
    STATE_SPACE,
    STATE_COMMENT,
    STATE_INVALID
};

int parse_hosts(const char *hosts, size_t len, map_t **map) {
    char *host = NULL, *ip = NULL;
    char host_len = 0, ip_len = 0;

    int state = STATE_INIT;
    int result = 0;
    *map = hashmap_new();
    int i;
    for (i = 0; i < len; i++) {
        char ch = hosts[i];
        switch (state) {
            case STATE_INIT: {
                if (ch == '#') {
                    state = STATE_COMMENT;
                } else {
                    state = STATE_IP;
                    ip = malloc(64);
                    bzero(ip, 64);
                    ip_len = 0;
                    ip[ip_len++] = ch;
                }
                break;
            }
            case STATE_IP: {
                if (ch == ' ') {
                    state = STATE_SPACE;
                } else if (ch == '\r' || ch == '\n') {
                    state = STATE_INVALID;
                    result = -1;
                    goto end;
                } else {
                    ip[ip_len++] = ch;
                }
                break;
            }
            case STATE_SPACE: {
                if (ch == '\r' || ch == '\n') {
                    state = STATE_INVALID;
                    result = -1;
                    goto end;
                } else if (ch != ' ') {
                    state = STATE_HOST;
                    host = malloc (256);
                    bzero(host, 64);
                    host_len = 0;
                    host[host_len++] = ch;
                }
                break;
            }
            case STATE_HOST: {
                if (ch == '\n' || (ch == '\r' && (hosts[i + 1]) == '\n')) {
                    if (ch == '\r') i++;
                    state = STATE_INIT;
                    hashmap_put(*map, host, ip);
                    host = ip = NULL;
                } else if (ch == ' ') {
                    state = STATE_SPACE;
                    hashmap_put(*map, host, ip);
                    host = NULL;
                } else {
                    host[host_len++] = ch;
                }
                break;
            }
            case STATE_COMMENT: {
                if (ch == '\n' || (ch == '\r' && (hosts[i + 1]) == '\n')) {
                    if (ch == '\r') i++;
                    state = STATE_INIT;
                }
                break;
            }
            default: break;
        }
    }

    if (host != NULL && ip != NULL) {
        hashmap_put(*map, host, ip);
    }
    
end:
    return result;
}
