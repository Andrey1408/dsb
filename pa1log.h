#ifndef __IFMO_DISTRIBUTED_CLASS_PA1LOG__H
#define __IFMO_DISTRIBUTED_CLASS_PA1LOG__H
#include "common.h"
#include "pa1.h"
#include "ipc.h"
#include <stdio.h>
#include <unistd.h>

void log_started(FILE *events_log_file, local_id process_id);

void log_received_all_started(FILE *events_log_file, local_id process_id);

void log_done(FILE *events_log_file, local_id process_id);

void log_received_all_done(FILE *events_log_file, local_id process_id);

void log_pipe(FILE *pipes_log_file, local_id from, local_id to, int read, int write);

#endif
