#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct host{
    char *host;
    int portstart;
    int portend;
    bool ID;
    bool services;
    int threads;
};
