#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

using namespace std;

struct sockaddr_in {
    u_short sin_family;       // AF_INET
    u_short sin_port;         // numer portu
    struct in_addr sin_addr;  //adres węzła
    char sin_zero[8]
};

struct in_addr {
    u_long s_addr;           // 32 bitowy adres
};


int main(int argc, char *argv[]) {
    struct sockaddr_in sck_addr;

    int fd = socket(int domain, int type, int protocol)
    if(fd == -1){
        cout << strerror(errno) << endl;
    }
    else{
        if(connect(int sockfd, const struct sockaddr *srvaddr, 0) == -1){
            cout << strerror(errno) << endl;
        }
        char table[1024];
        while(read(fd, table, 1023) > 0) {
            cout << table;
        }
        cout<<endl;
    }

    return 0;
}