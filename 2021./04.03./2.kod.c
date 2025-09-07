/*Napisi program koji iz datoteke (ime se unosi u programu) čita kategoriju, naziv i količinu artikala
u skladištu. Izgraditi vezanu listu, način ovisi o ocjeni, a nakon toga iz druge datoteke (ime se unosi
u programu), koja predstavlja račun, čitaju podaci i umanjuje stanja na skladištu. Ispisati
kategoriju, a zatim i nazive artikala čija je količina pala ispod 5.

Za ocjenu 2 - napraviti vezanu listu u kojoj su elementi složeni po kategorijama.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NOT_OPENED (-1)
#define MAX 32

typedef struct _artikal* ArtikalP;
typedef struct _artikal {
    char category[MAX];
    char name[MAX];
    int amount;
    ArtikalP next;
} Artikal;

ArtikalP createNewArtikl(char* category, char* name, int amount);
int loadFromFile(ArtikalP head, const char* fileName);
int insertSorted(ArtikalP head, ArtikalP newArtikl);
int printList(ArtikalP first);
int freeList(ArtikalP head);

int removeProducts(ArtikalP head, const char* fileName);
int printBelowFive(ArtikalP first);

int main() {
    ArtikalP head = (ArtikalP)malloc(sizeof(Artikal));
    if (head == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    printf("Unesite ime datoteke u kojoj je sadrzaj skladista: ");
    char filename[MAX];
    scanf("%s", filename);
    printf("\n");

    loadFromFile(head, filename);

    printList(head->next);

    printf("\nUnesite ime datoteke koja sadrzi podatke racuna: ");
    char fileName[MAX];
    scanf("%s", fileName);
    printf("\n");

    removeProducts(head, fileName);

    printBelowFive(head->next);

    freeList(head);

    return EXIT_SUCCESS;
}

ArtikalP createNewArtikl(char* category, char* name, int amount) {
    ArtikalP newArtikl = (ArtikalP)malloc(sizeof(Artikal));
    if (newArtikl == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }

    strcpy(newArtikl->category, category);
    strcpy(newArtikl->name, name);
    newArtikl->amount = amount;
    newArtikl->next = NULL;

    return newArtikl;
}

int loadFromFile(ArtikalP head, const char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        exit(FILE_NOT_OPENED);
    }
    char category[MAX], name[MAX];
    int amount = 0;

    while (fscanf(fp, "%s %s %d", category, name, &amount) == 3) {
        ArtikalP newArtikl = createNewArtikl(category, name, amount);
        if (newArtikl == NULL) {
            printf("ERROR! Could not allocate memmory!\n");
            return EXIT_FAILURE;
        }
        insertSorted(head, newArtikl);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int insertSorted(ArtikalP head, ArtikalP newArtikl) {
    ArtikalP prev = head;
    ArtikalP curr = head->next;

    while (curr) {
        if (strcmp(curr->category, newArtikl->category) > 0) {
            break;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    prev->next = newArtikl;
    newArtikl->next = curr;

    return EXIT_SUCCESS;
}

int printList(ArtikalP first) {
    ArtikalP temp = first;
    while (temp) {
        printf("Kategorija: %s, Naziv: %s, Kolicina: %d\n", temp->category, temp->name, temp->amount);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int freeList(ArtikalP head) {
    ArtikalP temp = head->next;
    while (temp) {
        ArtikalP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;

    return EXIT_SUCCESS;
}

int removeProducts(ArtikalP head, const char* fileName) {
    FILE* fpp = fopen(fileName, "r");
    if (fpp == NULL) {
        printf("ERROR! Could not open the file!\n");
        return EXIT_FAILURE;
    }
    char name[MAX];
    int amount;


    while (fscanf(fpp, "%s %d", name, &amount) == 2) {
        ArtikalP temp = head->next;

        while (temp) {
            if (strcmp(temp->name, name) == 0) {
                temp->amount -= amount;
            }
            temp = temp->next;
        }
    }

    fclose(fpp);

    return EXIT_SUCCESS;
}

int printBelowFive(ArtikalP first) {
    ArtikalP temp = first;
    while (temp) {
        if (temp->amount < 5) {
            printf("Kategorija: %s, Naziv: %s, Kolicina: %d\n", temp->category, temp->name, temp->amount);
        }
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}
