#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include "scanner.h"

/* This will matter once I have proper argument parsing */
#define THREADS_DEFAULT 20
#define PORTS_DEFAULT 10000

/* Function prototypes. */
void usage(char *name);
void error(char *msg);
int connect_scan(char *target, int port, bool ID);
void argparse(struct host *h);


int main(int argc, char **argv) {
    if(argc == 1) usage(argv[0]);
    
    struct host target;
    argparse(&target);

    int port = 22;
    connect_scan(target.host, port, target.ID);
    

    printf("%s\n",target.host); 
    printf("PORT\tSERVICE\n");

    return 1;
}

void argparse(struct host *h) {
   h->host = "Testing structs"; 
}

void usage(char *name){
    printf ("Basic TCP Port Scanner with Threading\n");
    printf ("Usage: %s [options] target [-p portstart-portend]\n", name);
    printf("Options:\n");
    printf("  -t <threads to use> (defaults to 20)\n");
    printf("  -s scan using ports in /etc/services\n");\
    printf("If no port range is set, will default to 1-10000\n"); 
    exit(0);
}

void error(char *msg){
	perror(msg);
	exit(0);
}
