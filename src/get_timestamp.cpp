#include "get_timestamp.h"
#include <sys/time.h>
#include <cstdlib>

timestamp_t get_timestamp ()
{
    struct timeval now;
    gettimeofday (&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

