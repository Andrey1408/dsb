#include <stdio.h>

#include "ipc.h"

typedef struct Pipeline* PipelinePtr;

PipelinePtr createPipeline(int pipe_num);

int* getWriterById(int id, PipelinePtr pipeline);
int* getReaderById(int id, PipelinePtr pipeline);

void destroyPipeline(PipelinePtr pipeline);




