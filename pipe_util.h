#include <stdio.h>

#include "ipc.h"

typedef struct {
    int read;
    int write;
} pipe_str;

typedef struct {
    local_id cur_id;
    size_t N;
    
} Process;
