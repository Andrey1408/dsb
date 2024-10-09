int main(int argc, char *argv[]){
    if(argc != 2 || argv[0] != '-p' || (int)argv[1] > 0){
        return 1;
    }
    int N = (int) argv[1];
    int pipes = N * (N - 1);
    
    return 0;
}