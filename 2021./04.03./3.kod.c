/*Napisi program koji iz datoteke (ime se unosi u programu) čita kategoriju, naziv i količinu artikala
u skladištu. Izgraditi vezanu listu, način ovisi o ocjeni, a nakon toga iz druge datoteke (ime se unosi
u programu), koja predstavlja račun, čitaju podaci i umanjuje stanja na skladištu. Ispisati
kategoriju, a zatim i nazive artikala čija je količina pala ispod 5.

Za ocjenu 2 - napraviti vezanu listu u kojoj su elementi složeni po kategorijama.

Za ocjenu 3 - napraviti vezanu listu kategorija, a svaka kategorija ima dodatnu listu artikala koji joj pripadaju.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NOT_OPENED (-1)
#define MAX 32

typedef struct _artikal* ArtikalP;
typedef struct _artikal {
    char name[MAX];
    int amount;
    ArtikalP next;
} Artikal;

typedef struct _kategorija* KategorijaP;
typedef struct _kategorija {
    char name[MAX];
    ArtikalP artikli;
    KategorijaP next;
} Kategorija;

ArtikalP createNewArtikl(char* name, int amount);
KategorijaP createNewCategory(char* name);
KategorijaP findCategory(KategorijaP head, char* categoryName);
int insertSorted(KategorijaP head, KategorijaP category);
int connectArtikltoCategory(KategorijaP category, ArtikalP artikl);
int loadFromFile(KategorijaP head, const char* fileName);
int printList(KategorijaP first);
int freeList(KategorijaP head);
int freeArtikl(ArtikalP head);

int removeProducts(KategorijaP head, const char* fileName);
int printBelowFive(KategorijaP first);

int main() {
    KategorijaP head = (KategorijaP)malloc(sizeof(Kategorija));
    if (head == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    char fileName1[MAX], fileName2[MAX];

    printf("Unesite ime datoteke: ");
    scanf("%s", fileName1);

    loadFromFile(head, fileName1);

    printf("\nPocetna lista: \n");
    printList(head->next);

    printf("\nUnesite ime datoteke s kojom se usporedjuje: ");
    scanf("%s", fileName2);

    removeProducts(head, fileName2);

    printf("\nKonacna lista: \n");
    printBelowFive(head->next);

    freeList(head);

    return EXIT_SUCCESS;
}

KategorijaP createNewCategory(char* name) {
    KategorijaP newCategory = (KategorijaP)malloc(sizeof(Kategorija));
    if (newCategory == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    strcpy(newCategory->name, name);
    newCategory->artikli = NULL;
    newCategory->next = NULL;

    return newCategory;
}

ArtikalP createNewArtikl(char* name, int amount) {
    ArtikalP newArtikl = (ArtikalP)malloc(sizeof(Artikal));
    if (newArtikl == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }

    strcpy(newArtikl->name, name);
    newArtikl->amount = amount;
    newArtikl->next = NULL;

    return newArtikl;
}

KategorijaP findCategory(KategorijaP head, char* categoryName) {
    KategorijaP temp = head;
    while (temp) {
        if (strcmp(temp->name, categoryName) == 0) {
            return temp;
        }
        else {
            temp = temp->next;
        }
    }
    return NULL;
}

int insertSorted(KategorijaP head, KategorijaP category) {
    KategorijaP prev = head;
    KategorijaP curr = head->next;
    while (curr) {
        if (strcmp(category->name, curr->name) <= 0) {
            break;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    prev->next = category;
    category->next = curr;

    return EXIT_SUCCESS;
}

int connectArtikltoCategory(KategorijaP category, ArtikalP artikl) {
    if (category == NULL || artikl == NULL) {
        printf("ERROR! Irregular values!\n");
        return EXIT_FAILURE;
    }
    artikl->next = category->artikli;
    category->artikli = artikl;
    return EXIT_SUCCESS;
}

int loadFromFile(KategorijaP head, const char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        exit(EXIT_FAILURE);
    }
    char categoryName[MAX], name[MAX];
    int amount = 0;

    while (fscanf(fp, "%s %s %d", categoryName, name, &amount) == 3) {
        KategorijaP category = findCategory(head, categoryName);
        if (category == NULL) {
            category = createNewCategory(categoryName);
            insertSorted(head, category);
        }
        ArtikalP artikl = createNewArtikl(name, amount);
        connectArtikltoCategory(category, artikl);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int printList(KategorijaP first) {
    KategorijaP temp = first;
    while (temp) {
        printf("\nKategorija: %s\n", temp->name);
        ArtikalP artikl = temp->artikli;
        while (artikl) {
            printf("Artikl: %s, Kolicina: %d\n", artikl->name, artikl->amount);
            artikl = artikl->next;
        }
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int freeList(KategorijaP head) {
    KategorijaP temp = head->next;
    while (temp) {
        freeArtikl(temp->artikli);
        KategorijaP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;
    return EXIT_SUCCESS;
}

int freeArtikl(ArtikalP head) {
    ArtikalP temp = head;
    while (temp) {
        ArtikalP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    return EXIT_SUCCESS;
}

int removeProducts(KategorijaP head, const char* fileName) {
    FILE* fpp = fopen(fileName, "r");
    if (fpp == NULL) {
        printf("ERROR! Could not open the file!\n");
        return EXIT_FAILURE;
    }
    char name[MAX];
    int amount;


    while (fscanf(fpp, "%s %d", name, &amount) == 2) {
        KategorijaP temp = head->next;

        while (temp) {
            ArtikalP artikl = temp->artikli;
            while (artikl) {
                if (strcmp(artikl->name, name) == 0) {
                    artikl->amount = artikl->amount - amount;
                }
                artikl = artikl->next;
            }
            temp = temp->next;
        }
    }

    fclose(fpp);

    return EXIT_SUCCESS;
}

int printBelowFive(KategorijaP first) {
    KategorijaP temp = first;
    while (temp) {
        printf("\nKategorija: %s\n", temp->name);
        int found = 0;
        ArtikalP artikl = temp->artikli;
        while (artikl) {
            if (artikl->amount < 5) {
                printf("Artikl: %s, Kolicina: %d\n", artikl->name, artikl->amount);
                found = 1;
            }
            artikl = artikl->next;
        }
        if (!found) {
            printf("Nema nijedan artikl!\n");
        }
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}
