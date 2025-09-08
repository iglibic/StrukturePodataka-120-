// Napisati program koji iz datoteke „Osobe.txt“ čita podatke o
// osobama i njihovim datumima rođenja i te podatke sprema u vezanu
// listu sortiranu po datumu. Ispisati listu.
//
// OCJENA 2:
// Svim osobama na listi generirati jedinstveni ID u opsegu od 100
// do 180, a zatim unijeti jedan ID i izbrisati tu osobu. Ispisati novu listu.
//
// OCJENA 3 :
// Pronaći u kojem mjesecu je rođeno najviše osoba, te sve osobe
// koje su rođene u tom mjesecu prebaciti u novu vezanu listu bez
// dodatne alokacije memorije.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_NOT_OPENED (-1)
#define MAX_NAME_LEN (32)

typedef struct _date {
    int day;
    int month;
    int year;
} Date;

struct _person;
typedef struct _person* PersonP;
typedef struct _person {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int idNumber;
    Date birthDate;
    PersonP next;
} Person;

int generateUniqueID(int usedValues[]);
PersonP createNewPerson(char* fName, char* lName, int id, Date date);
int loadFromFile(PersonP head, const char* fileName, int usedValues[]);
int insertSorted(PersonP head, PersonP newPerson);
int printList(PersonP first);
int freeList(PersonP head);

int deleteByID(PersonP head, int id);

int findPeopleByMonth(PersonP head);
PersonP extractByMonth(PersonP head, int month);

int main() {
    srand((unsigned int)time(NULL));

    PersonP head = (PersonP)malloc(sizeof(Person));
    if (head == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    int usedValues[81] = { 0 };

    loadFromFile(head, "OSOBE.txt", usedValues);

    printf("Pocetna lista: \n");
    printList(head->next);

    int id;

    printf("\nUnesite ID osobe koju zelite izbrisati iz liste: ");
    scanf("%d", &id);

    deleteByID(head, id);

    printf("\nLista nakon brisanja: \n");
    printList(head->next);

    int maxMonth = findPeopleByMonth(head);

    printf("\nNajvise ljudi je rodjeno u mjesecu: %d\n", maxMonth);
    PersonP newList = extractByMonth(head, maxMonth);

    printList(newList);

    printf("\nKonacna lista: \n");
    printList(head->next);

    freeList(head);

    return EXIT_SUCCESS;
}

int generateUniqueID(int usedValues[]) {
    int value;
    do {
        value = rand() % (180 - 100 + 1) + 100;
    } while (usedValues[value - 100]);
    usedValues[value - 100] = 1;
    return value;
}

PersonP createNewPerson(char* fName, char* lName, int id, Date date) {
    PersonP newPerson = (PersonP)malloc(sizeof(Person));
    if (newPerson == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    strcpy(newPerson->firstName, fName);
    strcpy(newPerson->lastName, lName);
    newPerson->idNumber = id;
    newPerson->birthDate = date;
    newPerson->next = NULL;

    return newPerson;
}

int loadFromFile(PersonP head, const char* fileName, int usedValues[]) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        exit(EXIT_FAILURE);
    }
    char fname[MAX_NAME_LEN], lname[MAX_NAME_LEN];
    int d, m, y;
    while (fscanf(fp, "%s %s %d.%d.%d", fname, lname, &d, &m, &y) == 5) {
        int id = generateUniqueID(usedValues);
        Date date = { d, m, y };
        PersonP newPerson = createNewPerson(fname, lname, id, date);
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
        Date date1 = newPerson->birthDate;
        Date date2 = curr->birthDate;
        if (date1.year < date2.year) {
            break;
        }
        else {
            if ((date1.year == date2.year) && (date1.month < date2.month)) {
                break;
            }
            else {
                if ((date1.year == date2.year) && (date1.month == date2.month) && (date1.day <= date2.day)) {
                    break;
                }
                else {
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }
    prev->next = newPerson;
    newPerson->next = curr;

    return EXIT_SUCCESS;
}

int printList(PersonP first) {
    PersonP temp = first;
    while (temp) {
        printf("Osoba: %s %s, ID: %d, Datum: %d.%d.%d\n", temp->firstName, temp->lastName,
            temp->idNumber, temp->birthDate.day, temp->birthDate.month, temp->birthDate.year);
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

int deleteByID(PersonP head, int id) {
    PersonP prev = head;
    PersonP curr = head->next;
    while (curr) {
        if (curr->idNumber == id) {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
            return EXIT_SUCCESS;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    printf("\nNije pronadjena osoba s tim ID-om!\n");

    exit(EXIT_FAILURE);
}

int findPeopleByMonth(PersonP head) {
    int mjeseci[13] = { 0 };

    PersonP temp = head->next;
    while (temp) {
        mjeseci[temp->birthDate.month]++;
        temp = temp->next;
    }

    int maxMonth = 1, maxCount = mjeseci[1];
    for (int i = 2; i <= 12; i++) {
        if (mjeseci[i] > maxCount) {
            maxCount = mjeseci[i];
            maxMonth = i;
        }
    }

    return maxMonth;
}

PersonP extractByMonth(PersonP head, int month) {
    PersonP newList = NULL;
    PersonP prev = head;
    PersonP curr = head->next;

    while (curr) {
        if (curr->birthDate.month == month) {

            prev->next = curr->next;

            curr->next = newList;
            newList = curr;

            curr = prev->next;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }

    return newList;
}
