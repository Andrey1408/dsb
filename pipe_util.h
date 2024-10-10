#ifndef _PIPE_UTILITIES_C
#define _PIPE_UTILITIES_C

#include "ipc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Pipeline *PipelinePtr;
struct Pipeline
{
    // кол-во пайпов[2]
    int *size;
    int **reader;
    int **writer;
};
PipelinePtr createPipeline(int pipe_num);

int *getWriterById(local_id id, local_id to, PipelinePtr pipeline);
int *getReaderById(local_id id, local_id to, PipelinePtr pipeline);

void destroyPipeline(PipelinePtr pipeline);

#endif
