#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh.h"

#define BUFFERSIZE 2048

int sh( int argc, char **argv, char **envp )
{
  char *prompt = calloc(PROMPTMAX, sizeof(char));
  char *commandline = calloc(MAX_CANON, sizeof(char));
  char *command, *arg, *commandpath, *p, *pwd, *owd;
  char **args = calloc(MAXARGS, sizeof(char*));
  int uid, i, status, argsct, go = 1;
  struct passwd *password_entry;
  char *homedir;
  struct pathelement *pathlist;

  uid = getuid();
  password_entry = getpwuid(uid);               /* get passwd info */
  homedir = password_entry->pw_dir;		/* Home directory to start
						  out with*/
     
  if ( (pwd = getcwd(NULL, PATH_MAX+1)) == NULL )
  {
    perror("getcwd");
    exit(2);
  }
  owd = calloc(strlen(pwd) + 1, sizeof(char));
  memcpy(owd, pwd, strlen(pwd));
  prompt[0] = ' '; prompt[1] = '\0';

  /* Put PATH into a linked list */
  pathlist = get_path();

  while ( go )
  {
      /* print your prompt */
    printf("[%s]%s",pwd,prompt);
    /* get command line and process */
    arg = fgets(commandline,BUFSIZ,stdin);
    int argLen = strlen(arg);
    arg[argLen-1]=0;
    args = stringToArray(arg);
    i=0;
    argsct=0;
    while(args[i]!=NULL){
      argsct++;
      i++;
    }
    if((strcmp(args[0],"exit")==0) && argsct==1){
      go = 0;
    }
    else if(strcmp(&arg[0],"which") ==0){
      which(command,pathlist );
    }else if(strcmp(&arg[0],"where") ==0){
      where(command,pathlist );
    }
    // else{
    //   char *ab = checkpath(cmd[0]);
    //   if(ab == NULL){
    //     printf("Command not found: %s\n",cmd[0]);
    //   }
    //   else{
    //     int pid = fork();
    //     if(pid == 0){
    //       exec(ab,cmd);
    //       printf("exited");
    //       exit(2);
    //     }
    //     else{
    //       waitpid(pid,NULL,NULL);
    //     }
    //   }
    ///}
    freeArgs(args);
  }

  free(args);
  free(prompt);
  free(commandline);
  free(pwd);
  free(owd);
  free(pathlist->element);
  freeList(pathlist);
  return 0;
} /* sh() */

void freeList(struct pathelement* head)
{
   struct pathelement* tmp = NULL;
   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

char *which(char *command, struct pathelement *pathlist )
{
   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */
   printf("you called which");
   return NULL;

} /* which() */

char *where(char *command, struct pathelement *pathlist )
{
  /* similarly loop through finding all locations of command */
    printf("you called where");
     return NULL;

} /* where() */

void list ( char *dir )
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
}

void freeArgs(char **array){
  int i = 0;
  while(array[i] != NULL){
    free(array[i]);
    i++;
  }
}

char **stringToArray(char *input){
  char buf[BUFSIZ];
  strcpy(buf,input);
  char *t = strtok(buf," ");
  int count=1;
  while(strtok(NULL," ")){
    count++;
  }
  char **array = malloc((count+1)*sizeof(char*));
  array[count]= 0;

  count = 0;
  strcpy(buf,input);
  t=strtok(buf," ");
  while(t){
    int len = strlen(t);
    array[count] = (char *) malloc((len+1)*sizeof(char));
    strcpy(array[count],t);
    count++;
    t=strtok(NULL," ");
  }
  return array;
}
