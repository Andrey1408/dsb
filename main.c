#include "pipe_util.h"
#include "process_factory.h"
#include "ipc.h"
#include "pa1log.h"
#include "common.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char** argv)
{
    if (argc != 2 || argv[1][1] != 'p' || (int)argv[2] > 0)
    {
        return 1;
    }
    int N = 1 + (int)argv[2];
    int pipe_num = N * (N - 1);
    local_id id = 0;

    FILE *pipes_log_file = fopen(pipes_log, "w+t");
    FILE *events_log_file = fopen(events_log, "w+t");

    PipelinePtr pipeline = createPipeline(pipe_num);
    fclose(pipes_log_file);
    pid_t p = fork();
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
        ProcessPtr parent_process = createProcess(&id, pipeline);
        parentProcedure(parent_process);
        destroyProcess(parent_process);
    }

    for (int i = 0; i < N - 1; i++)
    {
        wait(NULL);
    }

    destroyPipeline(pipeline);
    return 0;
}
