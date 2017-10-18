#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <cerrno>
#include <stdio.h>

using namespace std;

#define BUFSIZE 1024

string server = "150.254.32.150";	/* adres IP petli zwrotnej */
short service_port = 1234;	/* port uslugi */


int main(int argc, char *argv[]) {
    struct sockaddr_in sck_addr;
    int answere[BUFSIZE];
    int question[BUFSIZE];
    
    int sck = socket(AF_INET , SOCK_STREAM, 0);
    memset (&sck_addr, 0, sizeof sck_addr);
    sck_addr.sin_family = AF_INET;
    inet_aton (&server[0], &sck_addr.sin_addr);
    sck_addr.sin_port = htons (service_port);

    if(sck == -1){
        perror ("Nie można utworzyć socketa");
        exit (EXIT_FAILURE);
    }
    if(connect(sck, (struct sockaddr*) &sck_addr, sizeof sck_addr) == -1){
        perror ("Brak połączenia");
        exit (EXIT_FAILURE);
    }

    cout<<"Podaj 2 liczby:"<<endl;
    cin>>question[0]>>question[1];
    write(sck, question, 2*sizeof(int));

    while (read(sck, answere, sizeof(int)) > 0) {
        cout << answere[0]<<endl;
    }
    close(sck);

    return 0;
}
