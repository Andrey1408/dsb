#ifndef _PROCESS_FACTORY_C
#define _PROCESS_FACTORY_C

#include "ipc.h"
#include "pipe_util.h"
#include "pa1log.h"
#include <stdint.h>
#include <string.h>

typedef struct Process *ProcessPtr;

struct Process
{
    local_id id;
    PipelinePtr pipeline;
};

ProcessPtr createProcess(const local_id *id, const PipelinePtr pipeline);

void parentProcessInit(ProcessPtr process, int proc_count);

/* TODO: тут сделать процедуру для дочерних процессов */
void startDefaultProcedure(ProcessPtr process, FILE* events_log_file);

void parentProcedure(ProcessPtr process);

PipelinePtr getPipeline(ProcessPtr process);

local_id getSelfId(ProcessPtr process);

void destroyProcess(ProcessPtr process);

#endif
