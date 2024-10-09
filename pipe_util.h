#ifndef _PIPE_UTILITIES_C
#define _PIPE_UTILITIES_C

#include "ipc.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Pipeline *PipelinePtr;

PipelinePtr createPipeline(int pipe_num);

int *getWriterById(int id, PipelinePtr pipeline);
int *getReaderById(int id, PipelinePtr pipeline);

void destroyPipeline(PipelinePtr pipeline);

#endif
