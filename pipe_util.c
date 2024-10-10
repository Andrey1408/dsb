#include "pipe_util.h"
#include "pa1log.h"

PipelinePtr createPipeline(int pipe_num)
{
    PipelinePtr pipeline = (PipelinePtr)malloc(sizeof(struct Pipeline));
    pipeline->size = (int *)malloc(sizeof(int));
    *pipeline->size = pipe_num / 2;
    pipeline->recepients = (int ***)malloc(sizeof(int **) * 2);
    pipeline->recepients[0] = (int **)malloc(sizeof(int *) * pipe_num / 2);
    pipeline->recepients[1] = (int **)malloc(sizeof(int *) * pipe_num / 2);
    for (int i = 0; i < pipe_num / 2; i++)
    {
        pipeline->recepients[0][i] = (int *)calloc(2, sizeof(int));
        pipeline->recepients[1][i] = (int *)calloc(2, sizeof(int));
    }
    for (int i = 0; i < pipe_num / 2; i++)
    {
        pipe(pipeline->recepients[0][i]);
        pipe(pipeline->recepients[1][i]);
    }
    return pipeline;
}

void destroyPipeline(PipelinePtr pipeline)
{;
    printf("in destroyPipeline\n");
    for (int i = 0; i < *pipeline->size; i++)
    {
   /*     for (int j = 0; j < 2; j++)
        {
            free(pipeline->recepients[0][i] + j);
            free(pipeline->recepients[1][i] + j);
        }
        */
        free(pipeline->recepients[0] + i);
        free(pipeline->recepients[1] + i);
    }
    free(pipeline->recepients + 1);
    free(pipeline->recepients);
    free(pipeline->size);
    free(pipeline);
}

int *getWriterById(local_id id, PipelinePtr pipeline)
{
    if (id > *pipeline->size || id < 0)
    {
        // err
    }
    return pipeline->recepients[1][id];
}

int *getReaderById(local_id id, PipelinePtr pipeline)
{
    if (id > *pipeline->size || id < 0)
    {
        // err
    }
    return pipeline->recepients[0][id];
}
