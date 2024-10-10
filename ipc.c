#include "ipc.h"
#include "pipe_util.h"
#include "process_factory.h"
#include <unistd.h>

int send(void * self, local_id dst, const Message * msg) {
    ProcessPtr process = (ProcessPtr) self;
    PipelinePtr pipeline = getPipeline(process);
    if (write(getWriterById(dst, pipeline)[1], msg, sizeof(Message)) < 0) {
        return 1;
    }
    if (msg->s_header.s_magic != MESSAGE_MAGIC)
    {
        return 1;
    }
    return 0;
}

int send_multicast(void * self, const Message * msg) {
   PipelinePtr pipeline = getPipeline((ProcessPtr) self);
    for (int i = 0; i <  *pipeline->size; i++) {
        if (send(self, i, msg)) {
            return 1;
        }
    }
    return 0;
}

int receive(void * self, local_id from, Message * msg) {
    ProcessPtr process = (ProcessPtr) self;
    PipelinePtr pipeline = getPipeline(process);
    if (read(getReaderById(from, pipeline)[0], msg, sizeof(Message)) < 0)
    {
        return 1;
    }
    if (msg->s_header.s_magic != MESSAGE_MAGIC)
    {
        return 1;
    }
    free(msg);
    return 0;
}

int receive_any(void *self, Message *msg)
{
    return 0;
}
