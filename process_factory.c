#include "process_factory.h"



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

void parentProcessInit(ProcessPtr process, int proc_count) {
    process->id = PARENT_ID;
    process->pipeline->size = proc_count;
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
