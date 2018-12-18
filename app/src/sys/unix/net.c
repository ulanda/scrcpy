#include "net.h"

# include <unistd.h>
# include <ifaddrs.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

SDL_bool net_init(void) {
    // do nothing
    return SDL_TRUE;
}

void net_cleanup(void) {
    // do nothing
}

SDL_bool net_close(socket_t socket) {
    return !close(socket);
}


const char* net_addr_string(int idx) {
    struct ifaddrs *addrs;
    getifaddrs(&addrs);
    struct ifaddrs *tmp = addrs;
    int lCur = 0;
    const char* lRet = 0;
    while (tmp) {
        if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET) {
            if(lCur==idx) { 
                struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
                lRet = inet_ntoa(pAddr->sin_addr);
                break;
            }
            ++lCur;
        }
        tmp = tmp->ifa_next;
    }
    freeifaddrs(addrs);
    return lRet;
}
