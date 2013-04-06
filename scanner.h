#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
struct host{
    char *host;
    int portstart;
    int portend;
    bool ID;
    int threads;
    int curr_port;
    int active_threads;
};
