#include "pipe_util.h"

struct Pipeline{
    int* size;
    int* reader;
    int* writer;
};


PipelinePtr createPipeline(int pipe_num){
    PipelinePtr pipeline = (PipelinePtr) malloc(sizeof(struct Pipeline));
    pipeline->size = (int*) malloc(sizeof(int));
    *pipeline->size = pipe_num/2;
    pipeline->reader = (int*) calloc(pipe_num/2, sizeof(int[2]));
    pipeline->writer = (int*) calloc(pipe_num/2, sizeof(int[2]));
    for(int i = 0; i < *pipeline->size; i++){
        pipe(pipeline->reader[i]);
        pipe(pipeline->writer[i]);
    }
    return pipeline;
};

void destroyPipeline(PipelinePtr pipeline){
    for(int i = 0; i < *pipeline->size; i++){
        free(pipeline->reader[i]);
        free(pipeline->writer[i]);
    }
    free(pipeline->size);
    free(pipeline);
};


int* getWriterById(int id, PipelinePtr pipeline){
    if(id > *pipeline->size || id < 0){
        return -1;
    }
    return pipeline->writer[id];
};

int* getReaderById(int id, PipelinePtr pipeline){
    if(id > *pipeline->size || id < 0){
        return -1;
    }
    return pipeline->reader[id];
};