#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>




/**
 * Execute process and write data to it.s
 * @param proc
 * @param args
 * @return 
 */
int execute_proc(const char * proc,  char * const args[])
{
    int fd[2];
    pid_t pid = 0;
    int status;
    if( (status = pipe(fd)) < 0){
        perror("Pipe error");
    }
    if(!status && (pid = fork()) < 0){
        perror("fork");
    } else if(pid > 0){
        //parent
        close(fd[0]);//close read end, because child will use this
        write(fd[1], "foo\n", 4);
        close(fd[1]);
    } else {
        //child
        close(fd[1]);//close fd1, because parent will write to this
        if(dup2(fd[0], STDIN_FILENO) < 0) //duplicate STDIN to fd0 //read end
        {
            printf("bad read fd\n");
            exit(1);
        }
        close(fd[0]); //don't need fd0, after dup2
        execvp(proc, args);
    }
    return pid;
}


int main(int argc, char *argv[]) {
    
    char const * const args[] = {"/bin/cat", NULL};
    
    pid_t pid = execute_proc("/bin/cat", (char **)args);

    printf("pid of proc = %d\n", pid);
    printf("waiting for child\n");
    waitpid(pid, NULL, 0);

}
