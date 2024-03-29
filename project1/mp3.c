/*

Mp3 Linked List Program written by Ankith Ede

*/

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
}mp3_t;

int main()
{
    mainMenu();

return 0;
}

/**
 * Allocates memory for an mp3 struct and character arrays for the artistName and songTitle
**/
struct mp3 *createMp3()
{ 
    char buffer[BUFFERSIZE];
    int len;
    struct mp3 *mp3 = NULL;
    printf("Enter a name: ");
    getchar();

    if (fgets(buffer, BUFFERSIZE, stdin) != NULL)
    {
        len = (int)strlen(buffer);
        buffer[len - 1] = '\0';
        mp3 = (mp3_t *)malloc(sizeof(mp3_t));
        mp3->next = NULL;
        mp3->prev = NULL;
        mp3->artistName = (char *)malloc(len);
        strcpy(mp3->artistName, buffer);
    }

    printf("Enter a song: ");

    if (fgets(buffer, BUFFERSIZE, stdin) != NULL)
    {
        len = (int)strlen(buffer);
        buffer[len - 1] = '\0';
        mp3->songTitle = (char *)malloc(len);
        strcpy(mp3->songTitle, buffer);
    }
    printf("Enter the Year of the Song: ");
    scanf("%d", &mp3->year);
    printf("Enter the Duration of the Song: ");
    scanf("%d", &mp3->runTime);
    getchar();

    printf("Name is [ %s]...\n", mp3->artistName);
    printf("Name is [%s]...\n", mp3->songTitle);
    printf("Year: %d\n", mp3->year);
    printf("Duration: %d\n", mp3->runTime);

    return mp3;
}

/**
 * called in main to run the mp3 program 
**/
void mainMenu(){
    struct mp3* headMp3 = NULL;
    struct mp3* tailMp3 = NULL;

    char menu_option;

    printf("        MP3 Linked List\n");
    printf("------------------------------------------\n\n");

    do
    {
        printf("Main Menu\n");
        printf("a. Add to the list\n");
        printf("b. Delete from the list \n");
        printf("c. Print list forware\n");
        printf("d. Print list reverse\n");
        printf("e. Save and quit.\n");
        printf(" Please enter an option from the main menu: ");
        scanf(" %c", &menu_option);

        switch (menu_option)
        {

        case 'a':
            addMp3(&headMp3, &tailMp3);

            break;
        case 'b':
            delete(&headMp3, &tailMp3);

            break;
        case 'c':
            printListForward(headMp3);

            break;
        case 'd':
            printListReverse(tailMp3);

            break;
        case 'e':
            break;
        default:
            printf("invalid input");
            break;
        }

    } while (menu_option != 'e');

    freeList(headMp3);
}

/**
 * pass in the address to a pointer for the head and tail references of the linked list.
 * allocates memory for and mp3 object and charachter array for artistTitle and songTitle
**/
void addMp3(mp3_t **head_ref, mp3_t **tail_ref)
{
    mp3_t *mp3 = NULL;
    mp3 = createMp3();

    if (*head_ref == NULL)
    {
        (*head_ref) = mp3;
        (*tail_ref) = mp3;
        (*head_ref)->prev = NULL;
    }
    else
    {
        mp3->prev = *tail_ref;
        (*tail_ref)->next = mp3;
        *tail_ref = mp3;
    }
}

/**
 * pass in a pointer for the head of the linked list.
**/
void printListForward(struct mp3 *head)
{
    if (head == NULL)
    {
        printf("This list is empty \n");
    }
    else
    {
        printf("Forward List: \n");
        while (head != NULL)
        {
            printf("Name: [%s], ", head->artistName);
            printf("Song title: [%s], ", head->songTitle);
            printf("Year: [%d], ", head->year);
            printf("Runtime: [%d}. \n", head->runTime);
            head = head->next;
        }
    }
}

/**
 * pass in a pointer for the tail of the linked list.
**/
void printListReverse(struct mp3 *tail_ref)
{
    if (tail_ref == NULL)
    {
        printf("theres nothing in this list \n");
    }
    else
    {
        printf("Reversed List: \n");

        while (tail_ref != NULL)
        {
            printf("Name: [%s], ", tail_ref->artistName);
            printf("Song title: [%s], ", tail_ref->songTitle);
            printf("Year: [%d], ", tail_ref->year);
            printf("Runtime: [%d}. \n", tail_ref->runTime);
            tail_ref = tail_ref->prev;
        }
    }
}

/**
 * pass in a pointer for the head of the linked list.
 * free's all allocated memory for the mp3's in a linked list.
**/
void freeList(struct mp3 *head)
{
    struct mp3 *tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp->artistName);
        free(tmp->songTitle);
        free(tmp);
    }
}

/**
 * pass in the address of a pointer for the head and tail of the linked list.
 * free's all allocated memory for the mp3 based on the user's input for artist name.
**/
void delete (mp3_t **first, mp3_t **tail)
{
    
    char buffer[BUFFERSIZE];
    int len;
    char *artistDel;
    mp3_t *tmp = NULL;
    tmp = *first;
    mp3_t* delete = NULL;
    getchar();
    printf("Enter the Name of the Artist you would like to delete: ");
    if (fgets(buffer, BUFFERSIZE, stdin) != NULL)
    {
        len = (int)strlen(buffer);
        buffer[len - 1] = '\0';
        artistDel = (char *)malloc(len);
        strcpy(artistDel, buffer);
    }

    while (tmp != NULL)
    {
        if (strcmp(tmp->artistName, artistDel) == 0)
        {
            delete = tmp;
            tmp = tmp->next;
            deleteMP3(delete, first, tail);
        }else{
            tmp = tmp->next;
        }
    }

    free(artistDel);
}

/**
 * pass in the address of a pointer for the head and tail of the linked list. 
 * Also pass in a pointer for the mp3 struct that has to be deleted.
 * free's all allocated memory for the mp3 that is passed in as the first parameter.
**/

void deleteMP3(mp3_t *deleteArtist, mp3_t **tmpFirst, mp3_t** tail)
{
    if (*tmpFirst == NULL)
    {
        return;
    }
    if (deleteArtist->prev == NULL)
    {
        *tmpFirst = deleteArtist->next;
    }

    if(deleteArtist->next == NULL){
        *tail = deleteArtist->prev;
    }


    if (deleteArtist->next != NULL)
    {
        deleteArtist->next->prev = deleteArtist->prev;
    }
    if (deleteArtist->prev != NULL)
    {
        deleteArtist->prev->next = deleteArtist->next;
    }

    free(deleteArtist->artistName);
    free(deleteArtist->songTitle);
    free(deleteArtist);
}
