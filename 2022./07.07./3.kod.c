/*Za ocjenu 2:
Napisati program koji iz datoteke čita prezime i ime studenta i svakom studentu se dodjeljuje
jedninstven broj (ID) u opsegu od 100 do 199 (voditi računa da broj bude jedinstven, tj. da se ne
ponavlja). Od dobivenih podataka (ID-a, prezimena i imena) se gradi lista koja je sortirana po ID-u.
Pri tome koristi sortirani unos, a ne sortiranje liste. Ispisati listu.

Iz liste ukloniti sve one osobe čije se ime ponavlja u listi, tako da ostane samo jedna osoba tog imena.
Npr. ukoliko u listi postoji 3 Ivana, nakon brisanja ostaje samo jedan. Ispisati novu listu.

Za ocjenu 3:
Unijeti neki broj i sve one članove liste čiji je ID djeljiv s tim brojem postaviti na kraj liste.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_NOT_OPENED (-1)
#define MAX_NAME_LEN (32)

typedef struct _osoba* OsobaP;
typedef struct _osoba {
    char firstname[MAX_NAME_LEN];
    char lastname[MAX_NAME_LEN];
    int id;
    OsobaP next;
} Osoba;

int generateUniqueValue(int usedValues[]);
OsobaP createNewPerson(char* fName, char* lName, int id);
int loadFromFile(OsobaP head, const char* fileNamem, int usedValues[]);
int insertSorted(OsobaP head, OsobaP newPerson);
int printList(OsobaP first);
int freeList(OsobaP head);

int removeRepeatName(OsobaP head);

OsobaP findLast(OsobaP head);
int moveDividableByNum(OsobaP head, int id);

int main() {
    srand((unsigned int)time(NULL));

    OsobaP head = (OsobaP)malloc(sizeof(Osoba));
    if (head == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    int usedValues[100] = { 0 };

    loadFromFile(head, "STUDENTI1.txt", usedValues);

    printf("Pocetna lista:\n");
    printList(head->next);

    printf("\nUklanjanje istih imena...");
    removeRepeatName(head);

    printf("\nKonacna lista:\n");
    printList(head->next);

    int id;

    printf("\nUnesite vrijednost s kojom dijelimo: ");
    scanf("%d", &id);

    moveDividableByNum(head, id);

    printf("\nLista poslije promjena:\n");
    printList(head->next);

    freeList(head);

    return EXIT_SUCCESS;
}

int generateUniqueValue(int usedValues[]) {
    int value;
    do {
        value = rand() % 100 + 100;
    } while (usedValues[value - 100]);
    usedValues[value - 100] = 1;
    return value;
}

OsobaP createNewPerson(char* fName, char* lName, int id) {
    OsobaP newPerson = (OsobaP)malloc(sizeof(Osoba));
    if (newPerson == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    strcpy(newPerson->firstname, fName);
    strcpy(newPerson->lastname, lName);
    newPerson->id = id;
    newPerson->next = NULL;

    return newPerson;
}

int loadFromFile(OsobaP head, const char* fileName, int usedValues[]) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        exit(EXIT_FAILURE);
    }
    char fname[MAX_NAME_LEN], lname[MAX_NAME_LEN];
    while (fscanf(fp, "%s %s", lname, fname) == 2) {
        int id = generateUniqueValue(usedValues);
        OsobaP newPerson = createNewPerson(fname, lname, id);
        if (newPerson == NULL) {
            printf("ERROR! Could not allocate memmory!\n");
            return EXIT_FAILURE;
        }
        insertSorted(head, newPerson);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int insertSorted(OsobaP head, OsobaP newPerson) {
    OsobaP prev = head;
    OsobaP curr = head->next;
    while (curr) {
        if (newPerson->id <= curr->id) {
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

int printList(OsobaP first) {
    OsobaP temp = first;
    while (temp) {
        printf("Osoba: %s %s, ID: %d\n", temp->firstname, temp->lastname, temp->id);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int freeList(OsobaP head) {
    OsobaP temp = head->next;
    while (temp) {
        OsobaP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;

    return EXIT_SUCCESS;
}

int removeRepeatName(OsobaP head) {
    OsobaP outer = head->next;
    while (outer) {
        OsobaP prev = outer;                                        //odradis ime, ostavis ga i ides na iduce drugacije
        OsobaP curr = outer->next;
        while (curr) {
            if (strcmp(outer->firstname, curr->firstname) == 0) {
                prev->next = curr->next;
                free(curr);
                curr = prev->next;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
        outer = outer->next;
    }
    return EXIT_SUCCESS;
}

OsobaP findLast(OsobaP head) {
    OsobaP temp = head->next;
    while (temp->next) {
        temp = temp->next;
    }
    return temp;
}

int moveDividableByNum(OsobaP head, int id) {
    OsobaP prev = head;
    OsobaP curr = head->next;
    OsobaP last = findLast(head);

    OsobaP originalLast = last;

    while (curr && curr != originalLast) {
        if ((curr->id % id) == 0) {
            prev->next = curr->next;
            last->next = curr;
            curr->next = NULL;
            last = curr;
            curr = prev->next;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    return EXIT_SUCCESS;
}
