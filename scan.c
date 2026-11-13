#include"main.h"
void scan_input(char *prompt, char *input_string)
{
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; 
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
    sa.sa_flags=SA_RESTART;
    while(1)
    {
        check_background_jobs();
        if(sig_rec)
        {
            sig_rec=0;
        }
        printf("%s",prompt);
        fflush(stdout);
        if(fgets(input_string,100,stdin)==NULL)
        {
            clearerr(stdin);
            input_string[0]='\0';
            continue;
        }
        input_string[strcspn(input_string,"\n")]='\0';
        if(strlen(input_string)==0)
        {
            continue;
        }
        //scanf(" %[^\n]",input_string);
        if(strncmp(input_string,"PS1=",4)==0)
        {
            if(strrchr(input_string,' ')!=NULL)
            {
                printf("Invalid PS1 command\n");
                continue;
            }
            strcpy(prompt,&input_string[4]);
            continue;
        }
        char temp[100];
        strcpy(temp,input_string);
        char*command=get_command(temp);
        if(strchr(input_string,'|')!=NULL)
        {
            execute_n_pipe(input_string);
        }
        else
        {
            int ret=check_command_type(command);
            if(ret==BUILTIN)
            {
                execute_internal_commands(input_string);
            }
            else if(ret==EXTERNAL)
            {
                if(strchr(input_string,'|')!=NULL)
                {
                    execute_n_pipe(input_string);
                }
                else
                {
                    execute_external_commands(input_string);
                }
            }
            else
            {
              printf("%s: command not found\n",command);
              status=1;
            }
        }
    }

}
        

char*get_command(char*input_string)
{
    for(int i=0;input_string[i]!='\0';i++)
    {
        if(input_string[i]==' ')
        {
            
            input_string[i]='\0';
            break;
        }
    }
    return input_string;

}