#include "process_factory.h"

struct Process
{
    local_id id;
    PipelinePtr pipeline;
};

ProcessPtr createProcess(const local_id *id, const PipelinePtr pipeline)
{
    ProcessPtr process = malloc(sizeof(struct Process));
    if (process)
    {
        process->id = *id;
        process->pipeline = pipeline;
    }
    return process;
}

PipelinePtr getPipeline(ProcessPtr process)
{
    return process->pipeline;
}

local_id getSelfId(ProcessPtr process)
{
    return process->id;
}

void destroyProcess(ProcessPtr process)
{
    free(process);
}
