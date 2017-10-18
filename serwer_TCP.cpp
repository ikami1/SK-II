#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

#define SERVER_PORT 41111
#define QUEUE_SIZE 5
#define BUFSIZE 1024

int main(int argc, char* argv[])
{
    int nSocket, nClientSocket;
    int nBind, nListen;
    int nFoo = 1;
    socklen_t nTmp;
    struct sockaddr_in stAddr, stClientAddr;


    /* address structure */
    memset(&stAddr, 0, sizeof(struct sockaddr));
    stAddr.sin_family = AF_INET;
    stAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    stAddr.sin_port = htons(SERVER_PORT);

    /* create a socket */
    nSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (nSocket < 0){
        perror ("Can't create a socket.");
        exit (EXIT_FAILURE);
    }
    setsockopt(nSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&nFoo, sizeof(nFoo));

    /* bind a name to a socket */
    nBind = bind(nSocket, (struct sockaddr*)&stAddr, sizeof(struct sockaddr));
    if (nBind < 0){
        perror ("Can't bind a name to a socket");
        exit (EXIT_FAILURE);
    }
    /* specify queue size */
    nListen = listen(nSocket, QUEUE_SIZE);
    if (nListen < 0) {
        fprintf(stderr, "%s: Can't set queue size.\n", argv[0]);
    }

    while(1){
        nTmp = sizeof(struct sockaddr);
        nClientSocket = accept(nSocket, (struct sockaddr*)&stClientAddr, &nTmp);
        if (nClientSocket < 0)
        {
            fprintf(stderr, "%s: Can't create a connection's socket.\n", argv[0]);
            exit(1);
        }

        printf("%s: [connection from %s]\n",
               argv[0], inet_ntoa((struct in_addr)stClientAddr.sin_addr));


        int question[BUFSIZE];
        read(nClientSocket, question, 2*sizeof(int));
        std::cout<<"Dostalem liczby: "<<question[0]<<" i "<<question[1]<<std::endl;
        question[0] += question[1];
        std::cout<<"Zwracam "<<question[0]<<std::endl;

        write(nClientSocket, question, sizeof(int));

        close(nClientSocket);
    }

    close(nSocket);
    return(0);
}

