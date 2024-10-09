#include "ipc.h"
#include "pipe_util.h"
#include "process_factory.h"
#include <unistd.h>

// NEW
int send(void *self, local_id dst, const Message *msg)
{
    ProcessPtr process = (ProcessPtr)self;
    PipelinePtr pipeline = getPipeline(process);
    int *writer_pipe = getWriterById(getSelfId(process), pipeline);
    if (write(writer_pipe[1], msg, sizeof(Message)) < 0)
    {
        return 1;
    }
    if (msg->s_header.s_magic != MESSAGE_MAGIC)
    {
        return 1;
    }
    return 0;
}

int send_multicast(void *self, const Message *msg)
{
    Process *proc = self;
    for (local_id i = 0; i < proc->count_p; i++)
    {
        if (send(self, i, msg))
        {
            return 1;
        }
    }
    return 0;
}

int receive(void *self, local_id from, Message *msg)
{
    Process *proc = self;
    pipe_str pp = proc->pipe[from][proc->cur_id];
    if (read(pp.reader, msg, sizeof(Message)) < 0)
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
