#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include<errno.h>
 

#define BUILTIN		1
#define EXTERNAL	2
#define NO_COMMAND  3

#define RUNNING 1
#define STOPPED 2
typedef struct job
{
    pid_t pid;
    char command[100];
    int status;
    struct job*next;

}Job;
extern Job* head;


char**external_commands;
extern int status;
extern pid_t child_pid;
extern int background_process;
extern volatile sig_atomic_t sig_rec;

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


void scan_input(char *prompt, char *input_string);
char *get_command(char *input_string);

void copy_change(char *prompt, char *input_string);

int check_command_type(char *command);
void echo(char *input_string, int status);
void execute_internal_commands(char *input_string);
void signal_handler(int sig_num);
void extract_external_commands(char **external_commands);
void execute_external_commands(char *input_string);
void execute_n_pipe(char*input_string);
void insert_first(pid_t pid,char*command,int status);
void delete_first(void);
void print_jobs(void);
void delete_job(pid_t pid);
void execute_bg(void);
void execute_fg(void);
void check_background_jobs(void);

#endif