#include "ipc.h"
#include "pipe_util.h"
#include "process_factory.h"
#include <unistd.h>
#include <errno.h>

int send(void *self, local_id dst, const Message *msg)
{
    ProcessPtr process = (ProcessPtr)self;
    PipelinePtr pipeline = getPipeline(process);
    if (write(getWriterById(getSelfId(process), dst, pipeline), msg, sizeof(Message)) < 0)
    {
        return 1;
    }
    if (msg->s_header.s_magic != MESSAGE_MAGIC)
    {
        return 1;
    }
    printf("sent! to %d \n", (int)dst);
    return 0;
}

int send_multicast(void *self, const Message *msg)
{
    PipelinePtr pipeline = getPipeline((ProcessPtr)self);
    for (int i = 0; i < *pipeline->size; i++)
    {
        send(self, i, msg);
    }
    return 0;
}

int receive(void *self, local_id from, Message *msg)
{
    ProcessPtr process = (ProcessPtr)self;
    PipelinePtr pipeline = getPipeline(process);
    int read_size = (int)read(getReaderById(getSelfId(process), from, pipeline), msg, sizeof(*msg));
    printf("%d received from! %d  OF SIZE %d, PROJECTED %d\n", getSelfId(process), (int)from, read_size, (int)sizeof(*msg));
    printf("%d  %s\n", errno, strerror(errno));
    return 0;
}

int receive_any(void *self, Message *msg)
{
    return 0;
}
