#include <stdio.h>

#include "ipc.h"

typedef struct {
    int reader;
    int writer;
} pipe_str;

typedef struct {
    local_id cur_id;
    local_id count_p;
    pipe_str **pipe;
} Process;
