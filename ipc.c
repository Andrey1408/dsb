#include <unistd.h>
#include "ipc.h"
#include "pipe_util.h"

int send(void * self, local_id dst, const Message * msg) {
    Process *proc = (Process *)self;
    pipe_str pp = proc->pipe[proc->cur_id][dst];
    if (write(pp.writer, msg, sizeof(Message)) < 0) {
        return 1;
    }
    if (msg->s_header.s_magic != MESSAGE_MAGIC) {
        return 1;
    }
    return 0;
}

int send_multicast(void * self, const Message * msg) {
    Process *proc = (Process *)self;
    for (local_id i = 0; i < proc->count_p; i++) {
        if (send(self, i, msg)) {
            return 1;
        }
    }
    return 0;
}

int receive(void * self, local_id from, Message * msg) {
    Process *proc = (Process *)self;
    pipe_str pp = proc->pipe[from][proc->cur_id];
    if (read(pp.reader, msg, sizeof(Message)) < 0) {
        return 1;
    }
    if (msg->s_header.s_magic != MESSAGE_MAGIC) {
        return 1;
    }
    return 0;  
}

int receive_any(void * self, Message * msg) {
    return 0;
}
