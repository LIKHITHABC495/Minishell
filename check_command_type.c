#include"main.h"
int check_command_type(char *command)
{
   // List of builtin commands
	char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval","set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source","exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", "jobs","bg","fg",NULL};
   int i=0;
   while(builtins[i]!=NULL)
   {
      if(strcmp(command,builtins[i])==0)
      {
         return BUILTIN;
      }
      i++;

   }
   i=0;
   while(external_commands[i]!=NULL)
   {
      if(strcmp(command,external_commands[i])==0)
      {
         return EXTERNAL;
      }
      i++;
   }
    return NO_COMMAND;             
}
void extract_external_commands(char **external_commands)
{
   int fd=open("external_commd.txt",O_RDONLY);
   if(fd==-1)
   {
      printf("File not opened\n");
      return;
   }
   char buffer[100];
   char ch;
   int i=0;
   int index=0;
   while(read(fd,&ch,1)>0)
   {
      if(ch=='\n')
      {
         buffer[i]='\0';
         external_commands[index]=malloc(strlen(buffer)+1);
         if(external_commands[index]==NULL)
         {
            perror("malloc");
            close(fd);
            return;
         }
         strcpy(external_commands[index],buffer);
         index++;
         i=0;
      }
      else
      {
         buffer[i]=ch;
         i++;

      }

   }
   external_commands[index]=NULL;
   close(fd);
    

}