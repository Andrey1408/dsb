#include <stdio.h>

#include "ipc.h"

typedef struct Pipeline* PipelinePtr;

PipelinePtr createPipeline(int pipe_num);

void destroyPipeline(PipelinePtr ptr);




