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
#define THREADS_MAX 200
#define PORTS_DEFAULT 10000

/* Function prototypes. */
void usage(char *name);
void error(char *msg);
int connect_scan(char *target, int port, bool ID);
void argparse(struct host *h, int argc, char *args[]);
int getopt(int argc, char * const argv[], const char *optstring);
extern char *optarg;
extern int optind, opterr, optopt;


int main(int argc, char *argv[]) {
    if(argc == 1) usage(argv[0]);

    struct host target;
    argparse(&target, argc, argv);

    printf("PORT\tSERVICE\n");
    for(int port = target.portstart; port <= target.portend; port++)
        connect_scan(target.host, port, target.ID);
    return 1;
}

/* Argument parsing */
void argparse(struct host *target, int argc, char *argv[]) {
   target->host = argv[1];

   /* Set defaults for struct */
   target->portstart = 0;
   target->portstart = PORTS_DEFAULT;
   target->ID = false;
   for(int i = 0;i<argc;i++) {
       if(strcmp(argv[i],"-p")==0) {
           target->portstart = atoi(argv[i+1]);
           target->portend = atoi(argv[i+2]);
          }
       if(strcmp(argv[i],"-t")==0) {
           if(atoi(argv[i+1])>THREADS_MAX) {
               printf("To many threads!\n");
               exit(0);
           }
           target->threads = atoi(argv[i+1]);
        }
        if(strcmp(argv[i],"-id")==0)
            target->ID = true;
        else
            target->ID = false;
   }
}

void usage(char *name){
    printf ("Basic TCP Port Scanner with Threading\n");
    printf ("Usage: %s target [options] [-p portstart-portend]\n", name);
    printf("Options:\n");
    printf("  -t <threads to use> (defaults to 20)\n");
    printf("  -id enables send() and recv() on the connection\n");

    //Maybe at some point I will actually do this, but not for now.
    //printf("  -s scan using ports in /etc/services\n");

    printf("If no port range is set, will default to 1-10000\n"); 
    exit(0);
}

void error(char *msg){
	perror(msg);
	exit(0);
}
