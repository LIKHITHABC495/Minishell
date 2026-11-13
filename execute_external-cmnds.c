void execute_external_commands(char*input_string)
{
    char command_copy[100];
    strcpy(command_copy,input_string);
    char*argv[20];
    int i=0;
    int back=0;
    int len=strlen(input_string);
    if(len>0 && input_string[len-1]=='&')
    {
        back=1;
        input_string[len-1]='\0';
        command_copy[len-1]='\0';

    }
    argv[i]=strtok(input_string," ");
    while(argv[i]!=NULL)
    {
        i++;
        argv[i]=strtok(NULL," ");
    }
    pid_t pid=fork();
    if(pid==0)
    {
        
        execvp(argv[0],argv);
        perror("execvp");
        exit(1);
    }
    else if(pid>0)
    {
        if(back==0)
        {
            //sig_rec=0;
            child_pid=pid;
            int wait_status;
            pid_t ret;
            do
            {
                ret=waitpid(pid,&wait_status,WUNTRACED);
                
            } 
            while(ret==-1 && errno==EINTR);
            child_pid=-1;
            if(ret==pid)
            {
                if(WIFEXITED(wait_status))
                {
                    status=WEXITSTATUS(wait_status);
                }
                else if(WIFSIGNALED(wait_status))
                {
                    status=128+WTERMSIG(wait_status);
                }
                else if(WIFSTOPPED(wait_status))
                {
                    status=128+WSTOPSIG(wait_status);
                    insert_first(pid,command_copy,STOPPED);
                    printf("\nStopped PID: %d\n",pid);
                }
            }

        }
        else
        {
            int len=strlen(command_copy);
            while(len>0 && command_copy[len-1]==' ')
            {
                command_copy[len-1]='\0';
                len--;
            }
            insert_first(pid,command_copy,RUNNING);
            printf("Background PID: %d\n",pid);
        }

    }
    else
    {
        perror("fork");
        status=1;

    }
}
      