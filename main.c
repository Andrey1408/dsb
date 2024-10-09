#include "pipe_util.h"
#include "process_factory.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void parentProcedure() {
};

int main(int argc, char** argv)
{
    if (argc != 2 || argv[1] != "-p" || (int)argv[2] > 0)
    {
        return 1;
    }
    int N = 1 + (int)argv[2];
    int pipe_num = N * (N - 1);
    PipelinePtr pipeline = createPipeline(pipe_num);
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
        startDefaultProcedure();
    }
    /*процедура родительского процесса*/
    if (p > 0)
    {
        parentProcedure();
    }

    for (int i = 0; i < N - 1; i++)
    {
        wait(NULL);
    }

    destroyPipeline(pipeline);
    return 0;
}