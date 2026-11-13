/*
Name:LIKHITHA B C
Description:Developed a MiniShell in C that supports internal and external commands, foreground and background process execution, job control using `jobs`, `fg`, and `bg`, 
signal handling for `Ctrl+C` and `Ctrl+Z`, exit status tracking, and multiple command pipelines using pipes.
Implemented process management using `fork()`, `execvp()`, `waitpid()`, signals, and a linked list for job storage.
Date:28/08/2026
Batch:26001B*/
#include"main.h"
int status=0;
pid_t child_pid=-1;
int background_process=0;
char prompt[50]="minishell$";
volatile sig_atomic_t sig_rec=0;
Job*head=NULL;
int job_count=0;
int main()
{
    system("clear");
    char input_string[100];
    
    external_commands=malloc(200*sizeof(char*));
    if(external_commands==NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
    extract_external_commands(external_commands);
    scan_input(prompt,input_string);
    return 0;


}
