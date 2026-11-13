#include"main.h"
void signal_handler(int sig_num)
{
    
    if(sig_num==SIGINT)
    {
        if(child_pid>0)
        {
            kill(child_pid,SIGINT);
           
        }
        write(STDOUT_FILENO,"\n",1);
    
    }
    else if(sig_num==SIGTSTP)
    {
        if(child_pid>0)
        {
            kill(child_pid,SIGTSTP);
        }
        else
        {
            write(STDOUT_FILENO,"\n",1);
        }
    }
    else if(sig_num==SIGCHLD)
    {
        int child_status;
        pid_t pid;
        while((pid=waitpid(-1,&child_status,WNOHANG))>0)
        {
            if(pid==child_pid)
            {
                continue;
            }
            if(WIFEXITED(child_status))
            {
                delete_job(pid);
            }
        }
    }
}