#include"main.h"
void execute_n_pipe(char*input_string)
{
    int pipe_count=0;
    for(int i=0;input_string[i]!='\0';i++)
    {
        if(input_string[i]=='|')
        {
            pipe_count++;
        }
    }
    int cmnd_count=pipe_count+1;
    int fd[pipe_count][2];
    for(int i=0;i<pipe_count;i++)
    {
        if(pipe(fd[i])==-1)
        {
            perror("pipe");
            return;
        }
    }
    char*commands[cmnd_count+1];
    int i=0;
    commands[i]=strtok(input_string, "|");
    while(commands[i]!=NULL)
    {
        i++;
        commands[i]=strtok(NULL, "|");
    }
    for(i=0;i<cmnd_count;i++)
    {
        pid_t pid=fork();
        if(pid==0)
        {
            if(i==0)
            {
                dup2(fd[i][1],STDOUT_FILENO);
            }
            else if(i==cmnd_count-1)
            {
                dup2(fd[i-1][0],STDIN_FILENO);
            }
            else
            {
                dup2(fd[i-1][0],STDIN_FILENO);
                dup2(fd[i][1],STDOUT_FILENO);
            }
                for(int j=0;j<pipe_count;j++)
                {
                    close(fd[j][0]);
                    close(fd[j][1]);
                }
                char*argv[20];
                int k=0;
                argv[k]=strtok(commands[i]," \t");
                while(argv[k]!=NULL)
                {
                    k++;
                    argv[k]=strtok(NULL," \t");
                }
                signal(SIGINT,SIG_DFL);
                signal(SIGTSTP,SIG_DFL);
                execvp(argv[0],argv);
                perror("execvp");
                exit(1);
            }
            
            else if(pid<0)
            {
                perror("fork");
                return;
            }
        }
        for(int i=0;i<pipe_count;i++)
        {
            close(fd[i][0]);
            close(fd[i][1]);
        }
        for(i=0;i<cmnd_count;i++)
        {
            wait(NULL);
        }

    }
