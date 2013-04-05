#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

struct host{
    char *host;
    int portstart;
    int portend;
    bool ID;
    int threads;
};
