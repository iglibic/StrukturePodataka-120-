// Napisati program koji čita datoteku koja sadrži podatke o
// kategorijama proizvoda ("kategorije.txt") te kreirati vezanu
// listu kategorija sortiranu po abecedi. Uz kategoriju proizvoda
// u datoteci se nalaze i podaci o minimalnoj i maksimalnoj cijeni
// proizvoda u toj kategoriji.
// Nakon toga iz datoteke "proizvodi.txt" treba pročitati podatke
// o proizvodima iz kategorija kojima pripadaju. Svaki proizvod
// treba smjestiti u dodatnu vezanu listu za pojedinu kategoriju, 
// tj. svaka kategorija sadržava dodatnu vezanu listu proizvoda koji 
// spadaju u tu kategoriju. Za svaki proizvod iz kategorije treba
// izgenerirati cijenu (slučajan broj iz min.i maks.opsega
// kategorije) i ne smije biti ponavljanja brojeva unutar iste
// kategorije.
//
// OCJENA 2: Ispisati konačnu listu da prvo ide naziv kategorije,
// pa nazivi i cijene proizvoda u toj kategoriji.
//
// OCJENA 3: Izračunati prosječnu cijenu proizvoda u svakoj
// kategoriji i izbrisati proizvode koji su skuplji. Ispisati listu.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LEN (32)

struct _proizvod;
typedef struct _proizvod* ProizvodP;
typedef struct _proizvod {
    char proizvodIme[MAX_NAME_LEN];
    int cijena;
    ProizvodP next;
} Proizvod;

struct _kategorija;
typedef struct _kategorija* KategorijaP;
typedef struct _kategorija {
    char imeKategorije[MAX_NAME_LEN];
    int minCijena;
    int maxCijena;
    float avgCijena;
    KategorijaP next;
    ProizvodP products;
} Kategorija;

KategorijaP createNewCategory(char* name, int min, int max, float avg);
ProizvodP createNewProduct(char* name, int price);
KategorijaP findCategory(KategorijaP head, char* name);
int insertSortedCategory(KategorijaP head, KategorijaP newCategory);
int connectProductToCategory(KategorijaP category, ProizvodP product);
int loadFromFileCategory(KategorijaP head, const char* fileName);
int loadFromFileProduct(KategorijaP head, const char* fileName);
int generateUniquePrice(KategorijaP category, int min, int max);
int freeProduct(ProizvodP head);
int freeCategory(KategorijaP head);

int printList(KategorijaP first);

int calcAvg(KategorijaP head);
int removeProductsBlwAvg(KategorijaP head);

int main() {
    srand((unsigned int)time(NULL));

    KategorijaP head = (KategorijaP)malloc(sizeof(Kategorija));
    if (head == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    loadFromFileCategory(head, "KATEGORIJE.txt");
    loadFromFileProduct(head, "PROIZVODI.txt");

    calcAvg(head);

    printf("Pocetna lista: \n");
    printList(head->next);

    printf("\n\nBrisanje proizvoda cija je cijena veca od prosjeka...\n\n");

    removeProductsBlwAvg(head);

    printf("\nKonacna lista: \n");
    printList(head->next);

    freeCategory(head);

    return EXIT_SUCCESS;
}

KategorijaP createNewCategory(char* name, int min, int max, float avg) {
    KategorijaP newCategory = (KategorijaP)malloc(sizeof(Kategorija));
    if (newCategory == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    strcpy(newCategory->imeKategorije, name);
    newCategory->minCijena = min;
    newCategory->maxCijena = max;
    newCategory->avgCijena = 0.0;
    newCategory->products = NULL;
    newCategory->next = NULL;

    return newCategory;
}

ProizvodP createNewProduct(char* name, int price) {
    ProizvodP newProduct = (ProizvodP)malloc(sizeof(Proizvod));
    if (newProduct == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    strcpy(newProduct->proizvodIme, name);
    newProduct->cijena = price;
    newProduct->next = NULL;

    return newProduct;
}

KategorijaP findCategory(KategorijaP head, char* name) {
    KategorijaP temp = head->next;
    while (temp) {
        if (strcmp(temp->imeKategorije, name) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int insertSortedCategory(KategorijaP head, KategorijaP newCategory) {
    KategorijaP prev = head;
    KategorijaP curr = head->next;
    while (curr) {
        if (strcmp(newCategory->imeKategorije, curr->imeKategorije) <= 0) {
            break;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
    prev->next = newCategory;
    newCategory->next = curr;

    return EXIT_SUCCESS;
}

int connectProductToCategory(KategorijaP category, ProizvodP product) {
    if (category == NULL || product == NULL) {
        printf("ERROR! Irregular values!\n");
        return EXIT_FAILURE;
    }

    product->next = category->products;
    category->products = product;

    return EXIT_SUCCESS;
}

int loadFromFileCategory(KategorijaP head, const char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        exit(EXIT_FAILURE);
    }
    char name[MAX_NAME_LEN];
    int min, max;
    while (fscanf(fp, "%s %d %d", name, &min, &max) == 3) {
        KategorijaP newCategory = createNewCategory(name, min, max, 0);
        if (newCategory == NULL) {
            printf("ERROR! Could not allocate memmory!\n");
            return EXIT_FAILURE;
        }
        insertSortedCategory(head, newCategory);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int loadFromFileProduct(KategorijaP head, const char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        return EXIT_FAILURE;
    }
    char name[MAX_NAME_LEN], cat[MAX_NAME_LEN];
    while (fscanf(fp, "%s %s", cat, name) == 2) {
        KategorijaP category = findCategory(head, cat);
        if (category != NULL) {
            int price = generateUniquePrice(category, category->minCijena, category->maxCijena);
            ProizvodP newProduct = createNewProduct(name, price);
            if (newProduct == NULL) {
                printf("ERROR! Could not allocate memmory!\n");
                return EXIT_FAILURE;
            }
            connectProductToCategory(category, newProduct);
        }
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

int generateUniquePrice(KategorijaP category, int min, int max) {
    int price = min + rand() % (max - min + 1);

    ProizvodP proizvod = category->products;
    while (proizvod) {
        if (proizvod->cijena == price) {
            return generateUniquePrice(category, min, max);
        }
        proizvod = proizvod->next;
    }
    return price;
}

int freeProduct(ProizvodP head) {
    ProizvodP temp = head;
    while (temp) {
        ProizvodP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    return EXIT_SUCCESS;
}

int freeCategory(KategorijaP head) {
    KategorijaP temp = head->next;
    while (temp) {
        freeProduct(temp->products);
        KategorijaP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;
    return EXIT_SUCCESS;
}

int printList(KategorijaP first) {
    KategorijaP temp = first;
    while (temp) {
        printf("\nKategorija: %s, Prosjecna cijena proizvoda: %f\n", temp->imeKategorije, temp->avgCijena);
        ProizvodP proizvod = temp->products;
        while (proizvod) {
            printf("\tNaziv proizvoda: %s, Cijena: %d\n", proizvod->proizvodIme, proizvod->cijena);
            proizvod = proizvod->next;
        }
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int calcAvg(KategorijaP head) {
    KategorijaP temp = head->next;
    while (temp) {
        int totalPrice = 0;
        int total = 0;
        ProizvodP product = temp->products;
        while (product) {
            totalPrice += product->cijena;
            total++;
            product = product->next;
        }
        temp->avgCijena = (float)totalPrice / total;
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int removeProductsBlwAvg(KategorijaP head) {
    KategorijaP temp = head->next;
    while (temp) {
        ProizvodP prev = NULL;
        ProizvodP curr = temp->products;
        while (curr) {
            if ((float)curr->cijena > temp->avgCijena) {
                ProizvodP toFree = curr;

                if (prev == NULL) {
                    temp->products = curr->next;
                    curr = temp->products;
                }
                else {
                    prev->next = curr->next;
                    curr = prev->next;
                }
                free(toFree);
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}
