#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>


/* This will matter once I have proper argument parsing */
#define THREADS_DEFAULT 20
#define PORTS_DEFAULT 10000


/* Function prototypes. */
void usage();
void error(char *msg);
int connect_scan(char *target, int port, int i);

int main(int argc, char **argv) {
    if(argc < 3) usage();

    /*
       Sets up the port range and the target to pass to the
       scan functions. Will be replaced at some point by
       proper argument parsing
   */
    char *target = argv[1];
    int port_start = atoi(argv[2]);
    int port_end = atoi(argv[3]);

    //Prints column labels
    printf("PORT\tSERVICE\n");

    // for loop for running on the port range. Once again, will eventually
    // be replaced in some capacity by a proper argument parser
    for(int port = port_start; port <= port_end; port++)
        // passes ID scan flag of one automatically, eventually will be parsed
	connect_scan(target, port, 1);
    return 1;
}

void usage(){
    printf("Usage: ./portscan ip initial_port final_port\n");
    exit(0);
}

void error(char *msg){
	perror(msg);
	exit(0);
}
