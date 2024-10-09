#include "ipc.h"
#include "pipe_util.h"
#include <stdint.h>

typedef struct Process* ProcessPtr;

ProcessPtr createProcess(const int8_t* id, const PipelinePtr pipeline);


void startDefaultProcedure();

void destroyProcess(ProcessPtr process);