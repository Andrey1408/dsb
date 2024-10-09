#include "pipe_util.h"

int main(int argc, char *argv[]){
    if(argc != 2 || argv[0] != '-p' || (int)argv[1] > 0){
        return 1;
    }
    int N = (int) argv[1];
    int pipe_num = N * (N - 1);
    PipelinePtr pipeline = createPipeline(pipe_num);
    
    return 0;
}