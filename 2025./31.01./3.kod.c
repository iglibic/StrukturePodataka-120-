// Napisati program koji iz datoteke „inventura.txt“ čita podatke o
// tehnološkoj opremi u učionici u formatu :

//    <naziv> <cijena>

// Pročitane podatke potrebno je učitati u vezanu listu sortiranu po
// nazivu opreme, na način da se ne smije ponavljati oprema istog naziva
// (npr.ako postoji više tipkovnica u datoteci, vezana lista treba
// sadržavati jedan čvor naziva tipkovnica s količinom koja predstavlja
// količinu svih tipkovnica).

// OCJENA 2: Ispisati učitanu vezanu listu u formatu :

//  Tipkovnica 3
//  Miš 2
//  Zvučnik 1

// OCJENA 3: Proširiti strukturu iz prethodnog dijela zadatka tako da
// se uzima u obzir i vrijednosna cijena opreme. Napomena - cijene
// opreme istog naziva ne moraju nužno biti jednake; u tom slučaju se
// dodaje novi čvor liste.

//  Tipkovnica 1 25
//  Tipkovnica 2 30
//  Miš 2 20
//  ...

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (64)  

typedef struct _item* ItemP;
typedef struct _item {
    char name[MAX_NAME];
    double sellPrice;
    int quantity;
    ItemP next;
} Item;

ItemP createNewItem(char* name, double price, int quantity);
int loadFromFile(ItemP head, const char* fileName);
int insertSorted(ItemP head, double price, char* name);
int printList(ItemP first);
int freeList(ItemP head);

int main() {
    ItemP head = (ItemP)malloc(sizeof(Item));
    if (head == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    loadFromFile(head, "OPREMA.txt");

    printList(head->next);

    freeList(head);

    return EXIT_SUCCESS;
}

ItemP createNewItem(char* name, double price, int quantity) {
    ItemP newItem = (ItemP)malloc(sizeof(Item));
    if (newItem == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    strcpy(newItem->name, name);
    newItem->sellPrice = price;
    newItem->quantity = quantity;
    newItem->next = NULL;

    return newItem;
}

int loadFromFile(ItemP head, const char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        exit(EXIT_FAILURE);
    }
    char name[MAX_NAME];
    double price;

    while (fscanf(fp, "%s %lf", name, &price) == 2) {
        insertSorted(head, price, name);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int insertSorted(ItemP head, double price, char* name) {
    ItemP prev = head;
    ItemP curr = head->next;
    while (curr) {
        if ((strcmp(curr->name, name) == 0) && (curr->sellPrice == price)) {
            curr->quantity++;
            return EXIT_SUCCESS;
        }
        else if ((strcmp(curr->name, name) > 0)) {
            break;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    ItemP newItem = createNewItem(name, price, 1);

    prev->next = newItem;
    newItem->next = curr;

    return EXIT_SUCCESS;
}

int printList(ItemP first) {
    ItemP temp = first;
    while (temp) {
        printf("%s %d %f\n", temp->name, temp->quantity, temp->sellPrice);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int freeList(ItemP head) {
    ItemP temp = head->next;
    while (temp) {
        ItemP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;

    return EXIT_SUCCESS;
}
