# pragma once
#include <stddef.h>

#define SCREEN_H 800
#define SCREEN_W 800
#define FRAMELIMITS 60

struct screen {
    size_t h;
    size_t w;
    int ratio = 1;
};
