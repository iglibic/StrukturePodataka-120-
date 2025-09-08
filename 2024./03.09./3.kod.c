/*Napisati program koji stvara dvije vezane liste, svaku od 20 elemenata, na način da se za svaki element
liste generiraju dvije vrijednosti. Prva je vrijednost u opsegu od 100–130 (i u listi se ne smiju ponavljati
vrijednosti), a druga je prioritet u opsegu od 1–5 (bit će ponavljanja). Elementi u listi moraju biti
sortirani prvo po prioritetu, pa po vrijednosti.

Ocjena 2:
Ispisati vezanu listu i pronaći vrijednosti koje se ponavljaju u obje liste (uspoređuje se po value
elementu), te ispisati te vrijednosti uz njihov prioritet i nakon toga ih izbrisati iz liste.
Ispisati nove liste.

Ocjena 3:
Napraviti novu vezanu listu u koju će se prebaciti sve te vrijednosti koje se ponavljaju (bez nove
alokacije) i to sortirane po vrijednosti i potom po prioritetu.
Ispisati sve tri liste.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_NOT_OPENED (-1)

struct _data;
typedef struct _data* DataP;
typedef struct _data {
    int value;
    int priority;
    DataP next;
} Data;

int generatePriority();
int generateUniqueValue(int usedValues[]);
DataP createNewElement(int value, int prioritiy);
int insertSorted(DataP head, int value, int priority);
int printList(DataP first);
int freeList(DataP head);

int findSameValue(DataP head1, DataP head2, DataP head3);
int deleteElement(DataP head, int value);

int findValue(DataP head, DataP head3, int value);
int insertSorted3(DataP head, DataP newElement);

int main() {
    srand((unsigned int)time(NULL));

    DataP head1 = (DataP)malloc(sizeof(Data));
    DataP head2 = (DataP)malloc(sizeof(Data));
    DataP head3 = (DataP)malloc(sizeof(Data));

    if (head1 == NULL || head2 == NULL || head3 == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head1->next = NULL;
    head2->next = NULL;
    head3->next = NULL;

    int usedValues1[31] = { 0 };
    int usedValues2[31] = { 0 };

    for (int i = 0; i < 20; i++) {
        insertSorted(head1, generateUniqueValue(usedValues1), generatePriority());
    }

    for (int i = 0; i < 20; i++) {
        insertSorted(head2, generateUniqueValue(usedValues2), generatePriority());
    }
    printf("Lista 1: \n");
    printList(head1->next);

    printf("\nLista 2: \n");
    printList(head2->next);

    printf("\nTrazimo vrijednosti koje se nalaze u obje liste...\n");
    findSameValue(head1, head2, head3);

    printf("\nBrisanje istih vrijednostii...\n");

    printf("\nKonacna lista 1: \n");
    printList(head1->next);

    printf("\nKonacna lista 2: \n");
    printList(head2->next);

    printf("\nLista 3: \n");
    printList(head3->next);

    freeList(head1);
    freeList(head2);

    return EXIT_SUCCESS;
}

int generatePriority() {
    return rand() % 5 + 1;
}

int generateUniqueValue(int usedValues[]) {
    int value;
    do {
        value = rand() % (130 - 100 + 1) + 100;
    } while (usedValues[value - 100]);
    usedValues[value - 100] = 1;
    return value;
}

DataP createNewElement(int value, int prioritiy) {
    DataP newElement = (DataP)malloc(sizeof(Data));
    if (newElement == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    newElement->value = value;
    newElement->priority = prioritiy;
    newElement->next = NULL;

    return newElement;
}

int insertSorted(DataP head, int value, int priority) {
    DataP newElement = createNewElement(value, priority);
    if (newElement == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }

    DataP prev = head;
    DataP curr = head->next;
    while (curr) {
        if (newElement->priority < curr->priority) {
            break;
        }
        else {
            if ((newElement->priority == curr->priority) && (newElement->value <= curr->value)) {
                break;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
    prev->next = newElement;
    newElement->next = curr;

    return EXIT_SUCCESS;
}
int printList(DataP first) {
    DataP temp = first;
    while (temp) {
        printf("Vrijednost: %d, Prioritet: %d\n", temp->value, temp->priority);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int freeList(DataP head) {
    DataP temp = head->next;
    while (temp) {
        DataP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;

    return EXIT_SUCCESS;
}

int findSameValue(DataP head1, DataP head2, DataP head3) {
    DataP prev1 = head1;
    DataP temp1 = head1->next;
    while (temp1) {
        DataP prev2 = head2;
        DataP temp2 = head2->next;

        while (temp2) {
            if (temp1->value == temp2->value) {
                printf("Vrijednost: %d, Prioritet u listi 1: %d, Prioritet u listi 2: %d\n", temp1->value, temp1->priority, temp2->priority);
                //deleteElement(head1, temp1->value);
                //deleteElement(head2, temp2->value);
                //found = 1;
                prev1->next = temp1->next;
                temp1->next = NULL;
                insertSorted3(head3, temp1);

                prev2->next = temp2->next;
                temp2->next = NULL;
                insertSorted3(head3, temp2);

                temp1 = head1->next;

                break;
            }
            prev2 = temp2;
            temp2 = temp2->next;
        }
        /*if (found) {
             temp1 = head1->next;
         }
         else {
             temp1 = temp1->next;
         }*/
        prev1 = temp1;
        temp1 = temp1->next;
    }
    return EXIT_SUCCESS;
}

int deleteElement(DataP head, int value) {
    DataP prev = head;
    DataP curr = head->next;
    while (curr) {
        if (curr->value == value) {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    return EXIT_SUCCESS;
}

int findValue(DataP head, DataP head3, int value) {
    DataP prev = head;
    DataP curr = head->next;
    while (curr) {
        if (curr->value == value) {
            prev->next = curr->next;
            insertSorted3(head3, curr);
            break;                                                               
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    return EXIT_SUCCESS;
}

int insertSorted3(DataP head, DataP newElement) {
    DataP prev = head;
    DataP curr = head->next;
    while (curr) {
        if (newElement->value < curr->value) {
            break;
        }
        else {
            if ((newElement->value == curr->value) && (newElement->priority <= curr->priority)) {
                break;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
    prev->next = newElement;
    newElement->next = curr;

    return EXIT_SUCCESS;
}
