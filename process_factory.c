#include "process_factory.h"

Message* create_message(MessageType type)
{
    Message* msg = (Message*) malloc(sizeof(Message)); 

    msg->s_header.s_magic = MESSAGE_MAGIC;
    msg->s_header.s_payload_len = (uint16_t)0;
    msg->s_header.s_type = type;
    msg->s_header.s_local_time = (timestamp_t)0;
    void *contents = calloc(MAX_PAYLOAD_LEN, sizeof(char));
    memcpy(&(msg->s_payload), contents, sizeof(char) * MAX_PAYLOAD_LEN);
    free(contents);
    return msg;
}

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

void startDefaultProcedure(ProcessPtr process)
{
    send_multicast(process, create_message(STARTED));
    Message *message_bin = NULL;
    for (int i = 0; i < *process->pipeline->size; i++)
    {
        receive(process, (local_id)i, message_bin);
    }
    Message msg = create_message(DONE);
    send_multicast(process, &msg);
    for (int i = 0; i < *process->pipeline->size; i++)
    {
        receive(process, (local_id)i, message_bin);
    }
}

void parentProcedure(ProcessPtr process)
{
    Message *message_bin = NULL;
    for (int i = 1; i < *process->pipeline->size; i++)
    {
        receive(process, (local_id)i, message_bin);
    }
    for (int i = 1; i < *process->pipeline->size; i++)
    {
        receive(process, (local_id)i, message_bin);
    }
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
