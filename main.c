#include "pipe_util.h"
#include "process_factory.h"
#include "ipc.h"
#include "pa1log.h"
#include "common.h"
#include <unistd.h>
#include <sys/types.h>
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
    int pipe_num = N * (N - 1);
    local_id id = 0;

    FILE *pipes_log_file = fopen(pipes_log, "w+t");
    FILE *events_log_file = fopen(events_log, "w+t");

    PipelinePtr pipeline = createPipeline(pipe_num);
    fclose(pipes_log_file);
    pid_t p = fork();
    printf("forked\n");
    if (p > 0)
    {
        for (int i = 0; i < N - 1; i++)
        {
            if (p > 0)
            {
                p = fork();
            }
            else
            {
                break;
            }
        }
    }
    /*child тут стартануть процедуру для дочерок*/
    if (p == 0)
    {
        printf("in child %d\n", (int)p);
        id++;
        ProcessPtr current_child_process = createProcess(&id, pipeline);
        startDefaultProcedure(current_child_process, events_log_file);
        destroyProcess(current_child_process);
        fclose(events_log_file);
        exit(EXIT_SUCCESS);
    }
    /*процедура родительского процесса*/
    if (p > 0)
    {
        printf("in parent");
        ProcessPtr parent_process = createProcess(&id, pipeline);
        parentProcedure(parent_process);
        destroyProcess(parent_process);
        for (int i = 0; i < N - 1; i++)
        {
            printf("waiting in parent %d", i);
            wait(NULL);
        }
        destroyPipeline(pipeline);
        return 0;
    }

    return 0;
}
