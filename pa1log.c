#include "pa1log.h"
#include "common.h"
#include "pa1.h"
#include "ipc.h"

#include <stdio.h>
#include <unistd.h>


static const char * const log_pipe_open_fmt = "Pipe from process %d to %d was opened\n";


void log_started(FILE *events_log_file, local_id process_id) {
    printf(log_started_fmt, id, getpid(), getppid());
    fprintf(events_log_file, log_started_fmt, process_id, getpid(), getppid());
}

void log_received_all_started(FILE *events_log_file, local_id process_id) {
    printf(log_received_all_started_fmt, id);
    fprintf(events_log_file, log_received_all_started_fmt, process_id);
}

void log_done(FILE *events_log_file, local_id process_id) {
	printf(log_done_fmt, id);
    fprintf(events_log_file, log_done_fmt, process_id);
}

void log_received_all_done(FILE *events_log_file, local_id process_id) {
	printf(log_received_all_done_fmt, id);
    fprintf(events_log_file, log_received_all_done_fmt, process_id);
}

void log_pipe(FILE *pipes_log_file, local_id from, local_id to, int read, int write) {
	fprintf(pipes_log_file, log_pipe_created_fmt, from, to, read, write);
}



