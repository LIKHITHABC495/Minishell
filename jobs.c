#include"main.h"
void insert_first(pid_t pid,char*command,int status)
{
    Job*new=malloc(sizeof(Job));
    if(new==NULL)
    {
        perror("malloc");
        return;
    }
    new->pid=pid;
    strcpy(new->command,command);
    new->status=status;
    new->next=head;
    head=new;
}
void delete_first()
{
    if(head==NULL)
    {
        return;
    }
    Job*temp=head;
    head=head->next;
    free(temp);
}
void print_jobs()
{
    Job*temp=head;
    while(temp!=NULL)
    {
        if(temp->status==RUNNING)
        {
            printf("%d         Running     %s\n",temp->pid,temp->command);
        }
        else if(temp->status==STOPPED)
        {
            printf("%d         Stopped     %s\n",temp->pid,temp->command);

        }
        temp=temp->next;
    }
}
void delete_job(pid_t pid)
{
    Job*temp=head;
    Job*prev=NULL;
    if(head==NULL)
    {
        return ;
    }
    if(head->pid==pid)
    {
        delete_first();
        return;
    }
    while(temp!=NULL)
    {
        if(temp->pid==pid)
        {
            prev->next=temp->next;
            free(temp);
            return;
        }
        prev=temp;
        temp=temp->next;
    }
}
void execute_bg(void)
{
    Job*temp=head;
    while(temp!=NULL)
    {
        if(temp->status==STOPPED)
        {
            kill(temp->pid,SIGCONT);
            temp->status=RUNNING;
            return;
        }
        temp=temp->next;
    }
    printf("bg: no stopped processes\n");
}
void execute_fg(void)
{
    if(head==NULL)
    {
        printf("fg: no backgrond process\n");
        return;
    }
    Job*temp=head;
    if(temp->status==STOPPED)
    {
        kill(temp->pid,SIGCONT);
        temp->status=RUNNING;
    }
    child_pid=temp->pid;
    int fg_status;
    pid_t ret;
    do
    {
        ret=waitpid(temp->pid,&fg_status,0);
        
    } while (ret==-1 && errno==EINTR);
    if(ret==temp->pid)
    {
        if(WIFEXITED(fg_status))
        {
            status=WEXITSTATUS(fg_status);
            delete_job(temp->pid);
            
        }
        else if(WIFSIGNALED(fg_status))
        {
            status=128+WTERMSIG(fg_status);
            delete_job(temp->pid);
            
        }
    }
    child_pid=-1;
    
}
void check_background_jobs(void)
{
    int bg_status;
    pid_t pid;
    while((pid=waitpid(-1,&bg_status,WNOHANG))>0)
    {
        
            delete_job(pid);
        
    }
}