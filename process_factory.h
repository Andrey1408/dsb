#include "ipc.h"
#include "pipe_util.h"
#include <stdint.h>

typedef struct Process *ProcessPtr;

ProcessPtr createProcess(const local_id *id, const PipelinePtr pipeline);

/* TODO: тут сделать процедуру для дочерних процессов */
void startDefaultProcedure(ProcessPtr process);

PipelinePtr getPipeline(ProcessPtr process);

local_id getSelfId(ProcessPtr process);

void destroyProcess(ProcessPtr process);
