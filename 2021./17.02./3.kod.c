/*Napisati program koji iz datoteke (ime se unosi u programu) čita podatke o ljudima i kaficima
u kojima su ti ljudi bili. Izraditi vezanu listu, način ovisi o ocjeni, ispisati je, te za traženi kafic
ispisati koliko ga je ljudi posjetilo i koji su to ljudi.

Za ocjenu 2 - napraviti vezanu listu u kojoj su elementi složeni po nazivu kaficima.

Za ocjenu 3 – napraviti vezanu listu kafica, a svaki kafic ima dodatnu listu ljudi koji su ga posjetili.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NOT_OPENED (-1)
#define MAX 32

typedef struct person* PersonP;
typedef struct cafe* CafeP;

typedef struct person {
    char firstName[MAX];
    char lastName[MAX];
    PersonP next;
} Person;

typedef struct cafe {
    char name[MAX];
    PersonP visitors;
    CafeP next;
} Cafe;

CafeP createNewCafe(char* cafeName);
PersonP createNewPerson(char* fName, char* lName);
CafeP findCafe(CafeP head, char* cafeName);
int insertSortedCafe(CafeP head, CafeP newCafe);
int connectPersonToCafe(CafeP cafe, PersonP person);
int loadFromFile(CafeP head, const char* fileName);
int printList(CafeP head);
int printVisits(CafeP head, char* cafeName);
int freePerson(PersonP head);
int freeCafe(CafeP head);

int main() {
    CafeP head = (CafeP)malloc(sizeof(Cafe));
    if (head == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    loadFromFile(head, "KAFICI.txt");

    printf("Ispis pocetne liste: \n");
    printList(head->next);

    char cafeName[MAX];
    printf("\nUnesite ima kafica koji zelite pretraziti: ");
    scanf("%s", cafeName);
    printf("\n");

    printVisits(head, cafeName);

    freeCafe(head);

    return EXIT_SUCCESS;
}

CafeP createNewCafe(char* cafeName) {
    CafeP newCafe = (CafeP)malloc(sizeof(Cafe));
    if (newCafe == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    strcpy(newCafe->name, cafeName);
    newCafe->visitors = NULL;
    newCafe->next = NULL;

    return newCafe;
}

PersonP createNewPerson(char* fName, char* lName) {
    PersonP newPerson = (PersonP)malloc(sizeof(Person));
    if (newPerson == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    strcpy(newPerson->firstName, fName);
    strcpy(newPerson->lastName, lName);
    newPerson->next = NULL;

    return newPerson;
}

CafeP findCafe(CafeP head, char* cafeName) {
    CafeP temp = head;
    while (temp) {
        if (strcmp(temp->name, cafeName) == 0) {
            return temp;
        }
        else {
            temp = temp->next;
        }
    }
    return NULL;
}

int insertSortedCafe(CafeP head, CafeP newCafe) {
    CafeP prev = head;
    CafeP curr = head->next;
    while (curr) {
        if (strcmp(newCafe->name, curr->name) <= 0) {
            break;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    prev->next = newCafe;
    newCafe->next = curr;

    return EXIT_SUCCESS;
}

int connectPersonToCafe(CafeP cafe, PersonP person) {
    if (cafe == NULL || person == NULL) {
        printf("ERROR! Irregular values!\n");
        return EXIT_FAILURE;
    }
    PersonP prev = NULL;
    PersonP curr = cafe->visitors;
    while (curr) {
        if (strcmp(person->lastName, curr->lastName) < 0) {
            break;
        }
        else {
            if ((strcmp(person->lastName, curr->lastName) == 0) && (strcmp(person->firstName, curr->firstName) <= 0)) {
                break;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
    if (prev == NULL) {
        person->next = cafe->visitors;
        cafe->visitors = person;
    }
    else {
        prev->next = person;
        person->next = curr;
    }
    return EXIT_SUCCESS;
}

int loadFromFile(CafeP head, const char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    char cafename[MAX], fname[MAX], lname[MAX];
    while (fscanf(fp, "%s %s %s", fname, lname, cafename) == 3) {
        CafeP cafe = findCafe(head, cafename);
        if (cafe == NULL) {
            cafe = createNewCafe(cafename);
            insertSortedCafe(head, cafe);
        }
        PersonP person = createNewPerson(fname, lname);
        connectPersonToCafe(cafe, person);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int printList(CafeP head) {
    CafeP temp = head;
    while (temp) {
        printf("\nKafic: %s\n", temp->name);
        PersonP person = temp->visitors;
        while (person) {
            printf("Osoba: %s %s\n", person->firstName, person->lastName);
            person = person->next;
        }
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int printVisits(CafeP head, char* cafeName) {
    CafeP cafe = findCafe(head, cafeName);
    if (cafe == NULL) {
        printf("ERROR! Cafe does not exist!\n");
        return EXIT_FAILURE;
    }
    PersonP person = cafe->visitors;
    int quantity = 0;
    while (person) {
        printf("Osoba: %s %s\n", person->firstName, person->lastName);
        quantity++;
        person = person->next;
    }
    if (quantity == 0) {
        printf("\nKafic nije posjetila nijedna osoba!\n");
    }
    else {
        printf("\nKafic je posjetilo %d osoba!\n", quantity);
    }
    return EXIT_SUCCESS;
}

int freePerson(PersonP head) {
    PersonP temp = head;
    while (temp) {
        PersonP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;
    return EXIT_SUCCESS;
}

int freeCafe(CafeP head) {
    CafeP temp = head->next;
    while (temp) {
        freePerson(temp->visitors);
        CafeP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;
    return EXIT_SUCCESS;
}
