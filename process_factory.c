#include "process_factory.h"

struct Process {
    int8_t id;
    PipelinePtr pipeline;
};

ProcessPtr createProcess(const int8_t* id, const PipelinePtr pipeline){
    ProcessPtr process = malloc(sizeof(struct Process));
    if(process){
        process->id = *id;
        process->pipeline = pipeline;
    }
    return process;   
};

void destroyProcess(ProcessPtr process){
    free(process);
};