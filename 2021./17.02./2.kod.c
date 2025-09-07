/*Napisati program koji iz datoteke (ime se unosi u programu) čita podatke o ljudima i kaficima
u kojima su ti ljudi bili. Izraditi vezanu listu, način ovisi o ocjeni, ispisati je, te za traženi kafic
ispisati koliko ga je ljudi posjetilo i koji su to ljudi.

Za ocjenu 2 - napraviti vezanu listu u kojoj su elementi složeni po nazivu kaficima.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NOT_OPENED (-1)
#define MAX 32

typedef struct _person* PersonP;
typedef struct _person {
    char firstName[MAX];
    char lastName[MAX];
    char barName[MAX];
    PersonP next;
} Person;

PersonP createNewPerson(char* fName, char* lName, char* barName);
int loadFromFile(PersonP head, const char* fileName);
int insertSorted(PersonP head, PersonP newPerson);
int printList(PersonP first);
int freeList(PersonP head);

int numOfVisits(PersonP head, char* barName);

int main() {
    PersonP head = (PersonP)malloc(sizeof(Person));
    if (head == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    char fileName[MAX], barName[MAX];

    printf("Unesite naziv datoteke: ");
    scanf("%s", fileName);
    printf("\n");

    loadFromFile(head, fileName);

    printList(head->next);

    printf("\nUnesite ime kafica: ");
    scanf("%s", barName);
    printf("\n");

    numOfVisits(head, barName);

    freeList(head);

    return EXIT_SUCCESS;
}

PersonP createNewPerson(char* fName, char* lName, char* barName) {
    PersonP newPerson = (PersonP)malloc(sizeof(Person));
    if (newPerson == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    strcpy(newPerson->firstName, fName);
    strcpy(newPerson->lastName, lName);
    strcpy(newPerson->barName, barName);
    newPerson->next = NULL;

    return newPerson;
}

int loadFromFile(PersonP head, const char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        return FILE_NOT_OPENED;
    }

    char fname[MAX], lname[MAX], bname[MAX];

    while (fscanf(fp, "%s %s %s", fname, lname, bname) == 3) {
        PersonP newPerson = createNewPerson(fname, lname, bname);
        if (newPerson == NULL) {
            printf("ERROR! Could not allocate memmory!\n");
            return EXIT_FAILURE;
        }
        insertSorted(head, newPerson);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int insertSorted(PersonP head, PersonP newPerson) {
    PersonP prev = head;
    PersonP curr = head->next;

    while (curr) {
        if (strcmp(newPerson->barName, curr->barName) < 0) {
            break;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    prev->next = newPerson;
    newPerson->next = curr;

    return EXIT_SUCCESS;
}

int printList(PersonP first) {
    PersonP temp = first;
    while (temp) {
        printf("Naziv kafica: %s, Osoba: %s %s\n", temp->barName, temp->firstName, temp->lastName);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int freeList(PersonP head) {
    PersonP temp = head->next;
    while (temp) {
        PersonP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;

    return EXIT_SUCCESS;
}

int numOfVisits(PersonP head, char* barName) {
    PersonP temp = head->next;
    int quantity = 0;


    while (temp) {
        if (strcmp(temp->barName, barName) == 0) {
            printf("Osoba: %s %s\n", temp->firstName, temp->lastName);
            quantity++;
        }
        temp = temp->next;
    }

    if (quantity == 0) {
        printf("Kafic nije posjetila nijedna osoba!\n");
        return EXIT_SUCCESS;
    }

    printf("\nBroj osoba koji su posjetili kafic %s je: %d\n", barName, quantity);

    return EXIT_SUCCESS;
}
