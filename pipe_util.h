#ifndef _PIPE_UTILITIES_C
#define _PIPE_UTILITIES_C

#include "ipc.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Pipeline *PipelinePtr;
struct Pipeline
{
    // кол-во пайпов[2]
    int *size;
    int ***recepients;
};
PipelinePtr createPipeline(int pipe_num);

int getWriterById(local_id self_id, local_id dest, PipelinePtr pipeline);
int getReaderById(local_id self_id, local_id dest, PipelinePtr pipeline);

void destroyPipeline(PipelinePtr pipeline);

#endif
