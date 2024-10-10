#include "pipe_util.h"
#include "process_factory.h"
#include "ipc.h"
#include "pa1log.h"
#include "common.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
    if (argc < 3 || argv[1][1] != 'p' || atoi(argv[2]) <= 0)
    {
        printf("illegal arguments \n");
        return 1;
    }
    int N = 1 + atoi(argv[2]);
    printf("N = %d\n", N);
    local_id id = 1;

    FILE *pipes_log_file = fopen(pipes_log, "w+t");
    FILE *events_log_file = fopen(events_log, "w+t");
    PipelinePtr pipeline = (PipelinePtr) mmap(NULL, sizeof(PipelinePtr), PROT_READ | PROT_WRITE, MAP_SHARED, -1, 0);
    pipeline = createPipeline(N);
    fclose(pipes_log_file);
    pid_t p = fork();
    printf("forked\n");
    if (p > 0)
    {
        for (int i = 0; i < N - 2; i++)
        {
            if (p > 0)
            {
                id++;
                p = fork();
            }
            else
            {
                break;
            }
        }
    }
    if (p > 0)
    {
        printf("in parent\n");
        local_id id_p = (local_id) 0;
        ProcessPtr parent_process = createProcess(&id_p, pipeline);
        parentProcedure(parent_process);
        destroyProcess(parent_process);
        for (int i = 0; i < N - 1; i++)
        {
            printf("waiting in parent %d \n", i);
            wait(NULL);
        }
        destroyPipeline(pipeline);
        return 0;
    }
    if (p == 0)
    {
        printf("in child %d\n", (int)p);
        ProcessPtr current_child_process = createProcess(&id, pipeline);
        startDefaultProcedure(current_child_process, events_log_file);
        destroyProcess(current_child_process);
        fclose(events_log_file);
        exit(EXIT_SUCCESS);
    }

    return 0;
}
