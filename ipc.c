#include "ipc.h"
#include "pipe_util.h"
#include "process_factory.h"

int send(void * self, local_id dst, const Message * msg) {
    ProcessPtr process = (ProcessPtr)self;
    PipelinePtr pipeline = getPipeline(process);
    if (write(getWriterById(getSelfId(process), dst, pipeline), msg, sizeof(Message)) < 0) {
        return 1;
    }
    if (msg->s_header.s_magic != MESSAGE_MAGIC)
    {
        return 1;
    }
    return 0;
}

int send_multicast(void * self, const Message * msg) {
   ProcessPtr process = (ProcessPtr)self;
   PipelinePtr pipeline = getPipeline(process);
    for (local_id i = 0; i < pipeline->size; i++) {
        if (send(self, i, msg)) {
            return 1;
        }
    }
    return 0;
}

int receive(void * self, local_id from, Message * msg) {
    ProcessPtr process = (ProcessPtr)self;
    PipelinePtr pipeline = getPipeline(process);
    if (read(getReaderById(from, getSelfId(process), pipeline), msg, sizeof(Message)) < 0)
    {
        return 1;
    }
    if (msg->s_header.s_magic != MESSAGE_MAGIC)
    {
        return 1;
    }
    return 0;
}

int receive_any(void *self, Message *msg)
{
    return 0;
}
