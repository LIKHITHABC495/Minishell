#include"main.h"
void execute_internal_commands(char*input_string)
{
    if(strcmp(input_string,"exit")==0)
    {
        exit(0);
    }
    else if(strcmp(input_string,"pwd")==0)
    {
        char str[100];
        if(getcwd(str,sizeof(str))!=NULL)
        {
            printf("%s\n",str);
            status=0;

        }
        
    }
    else if(strncmp(input_string,"cd ",3)==0)
    {
        if(chdir(&input_string[3])==-1)
        {
            perror("cd");
            status=1;
        }
        else
        {
            status=0;
        }
    }
    else if(strncmp(input_string,"echo ",5)==0)
    {
        if(strcmp(&input_string[5],"$$")==0)
        {
            printf("%d\n",getpid());
        }
        else if(strcmp(&input_string[5],"$SHELL")==0)
        {
            printf("%s\n",getenv("SHELL"));
        }
        else if(strcmp(&input_string[5],"$?")==0)
        {
            printf("%d\n",status);
        }
        else
        {
            printf("%s\n",&input_string[5]);

        }
    }
    else if(strcmp(input_string,"jobs")==0)
    {
        check_background_jobs();
        print_jobs();
    }
    else if(strcmp(input_string,"bg")==0)
    {
        execute_bg();
    }
    else if(strcmp(input_string,"fg")==0)
    {
        execute_fg();
    }

}