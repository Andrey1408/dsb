#include "pipe_util.h"
#include "pa1log.h"

PipelinePtr createPipeline(int pipe_num)
{
    PipelinePtr pipeline = (PipelinePtr)malloc(sizeof(struct Pipeline));
    pipeline->size = (int *)malloc(sizeof(int));
    *pipeline->size = pipe_num;
    pipeline->recepients = (int ***)malloc(sizeof(int **) * pipe_num);
    for (int i = 0; i < pipe_num; i++)
    {
        pipeline->recepients[i] = (int **)malloc(sizeof(int *) * pipe_num);
    }
    for (int i = 0; i < pipe_num; i++)
    {
        for (int j = 0; j < pipe_num; j++)
        {
            pipeline->recepients[i][j] = (int *)calloc((size_t)2, sizeof(int));
        }
    }
    for (int i = 0; i < pipe_num; i++)
    {
        for (int j = 0; j < pipe_num; j++)
        {
            if(pipe(pipeline->recepients[i][j]) != 0){
                printf("PIPE FAILED");
            };
        }
    }
    return pipeline;
}

void destroyPipeline(PipelinePtr pipeline)
{
    printf("in destroyPipeline\n");
    for (int i = 0; i < *pipeline->size; i++)
    {
        for (int j = 0; j < *pipeline->size; j++)
        {
            free(pipeline->recepients[i][j]);
            free(pipeline->recepients[i] + j);
        }
        free(pipeline->recepients + i);
    }
    free(pipeline->size);
    free(pipeline);
}

int getWriterById(local_id self_id, local_id dest, PipelinePtr pipeline)
{

    return pipeline->recepients[self_id][dest][1];
}

int getReaderById(local_id self_id, local_id dest, PipelinePtr pipeline)
{

    return pipeline->recepients[self_id][dest][0];
}
