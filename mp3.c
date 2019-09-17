#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3.h"

#define BUFFERSIZE 128

typedef struct mp3 
{ 
   char *artistName; 
   char *songTitle; 
   int year; 
   int runTime; 
   struct mp3 *next;
   struct mp3 *prev;
} mp3_t;

struct mp3* createMp3(){
    char  buffer[BUFFERSIZE];
    int   len;
    mp3_t *mp3 = NULL;
    printf("Enter a name: ");
  if (fgets(buffer, BUFFERSIZE , stdin) != NULL)
  {
    len = (int) strlen(buffer);
    buffer[len - 1] = '\0';
    mp3 = (mp3_t *) malloc(sizeof(mp3_t));
    mp3->artistName = (char *) malloc(len);
    strcpy(mp3->artistName, buffer);
  }



  printf("Enter a song: ");
  if (fgets(buffer, BUFFERSIZE , stdin) != NULL)
  {
    len = (int) strlen(buffer);
    buffer[len - 1] = '\0';
    mp3->songTitle = (char *) malloc(len);
    strcpy(mp3->songTitle, buffer);
  }
    printf("Enter the Year of the Song: ");
    scanf("%d",&mp3->year);
    printf("Enter the Duration of the Song: ");
    scanf("%d",&mp3->runTime);
    getchar();

    mp3->next = NULL;
    mp3->prev = NULL;

    printf("Name is [ %s]...\n", mp3->artistName);
    printf("Name is [%s]...\n", mp3->songTitle);
    printf("Year: %d\n",mp3->year);
    printf("Duration: %d\n",mp3->runTime);

    return mp3;

}

int main (){
// struct mp3* headMp3 = NULL;

// addMp3Append(&headMp3);
// addMp3Append(&headMp3);
// printListForward(headMp3);
// delete1(&headMp3);
// printListReverse(headMp3);
// freeList(headMp3);


struct mp3* headMp3 = NULL;
struct mp3* tailMp3 = NULL;

addMp3(&headMp3, &tailMp3);
addMp3(&headMp3, &tailMp3);
addMp3(&headMp3, &tailMp3);
printListForward(headMp3);
printListReverse(tailMp3);
freeList(headMp3);

return 0;
}

void addMp3(mp3_t** head_ref, mp3_t** tail_ref){
    mp3_t *mp3 = NULL;
    mp3 = createMp3();

    if(*head_ref == NULL){
        (*head_ref) = mp3; 
        (*tail_ref) = mp3; 
        (*head_ref)->prev = NULL; 
    }
    else{
        mp3->prev = *tail_ref;
        (*tail_ref)->next = mp3;
        *tail_ref = mp3;
    }

    printf("inserted");
}





void printListForward(struct mp3* head){
    if (head == NULL) { 
        printf("This list is empty");
    }else{
        printf("Forward List: \n");
        while (head != NULL){
            printf("Name: [%s], ", head->artistName);
            printf("Song title: [%s], ", head->songTitle);
            printf("Year: [%d], ", head->year);
            printf("Runtime: [%d}. \n", head->runTime);
            head=head->next;
        }
    }
}

void printListReverse(struct mp3* tail_ref){
        if (tail_ref == NULL){ 
            printf("theres nothing in this list");
        }else{
            printf("Reversed List: \n");
            
            while (tail_ref != NULL){
                printf("Name: [%s], ", tail_ref->artistName);
                printf("Song title: [%s], ", tail_ref->songTitle);
                printf("Year: [%d], ", tail_ref->year);
                printf("Runtime: [%d}. \n", tail_ref->runTime);
                tail_ref=tail_ref->prev;
            }
        }
    }



void freeList(struct mp3* head)
{
   struct mp3* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp->artistName);
       free(tmp->songTitle);
       free(tmp->next);
       free(tmp->prev);
       free(tmp);
       printf("deleted this node");
    }

}

