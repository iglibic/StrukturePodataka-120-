// Napisati program koji iz datoteke „riječi.txt“ čita riječi i slaže ih po redoslijedu pojavljivanja. Pri tome
// ukoliko riječ već postoji u vezanoj listi, ne treba je ponovo dodavati u listu, već se uvećava brojač.

// OCJENA 2:
// Ispisati vezanu listu i pronaći pet riječi koje su se pojavile najviše puta, te ih pomaknuti na početak 
// liste.

// OCJENA 3 :
// Slučajno generirati neki broj u opsegu između minimalnog i maksimalnog broja riječi u listi i izbrisati
// sve riječi koje se ponavljaju toliko puta. Ispisati novu listu.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NOT_OPENED (-1)
#define MAX_NAME 32

typedef struct _rijeci* RijeciP;
typedef struct _rijeci {
    char word[MAX_NAME];
    int nORepeats;
    RijeciP next;
} Rijeci;

RijeciP createNewWord(char* word, int numOfRepeats);
int loadFromFile(RijeciP head, const char* fileName);
int addNew(RijeciP head, char* word);
int printList(RijeciP first);
int freeList(RijeciP head);

int moveTopFiveToFront(RijeciP head);

int findMinRps(RijeciP head);
int findMaxRps(RijeciP head);
int generateRand(RijeciP head, int min, int max);
int removeSame(RijeciP head, int num);

int main() {
    RijeciP head = (RijeciP)malloc(sizeof(Rijeci));
    if (head == NULL) {
        printf("ERROR! Could not allocate memory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    loadFromFile(head, "RIJECI.txt");

    printf("Pocetna lista:\n");
    printList(head->next);

    moveTopFiveToFront(head);

    printf("\nLista nakon premjestanja 5 najcescih rijeci na pocetak:\n");
    printList(head->next);

    int min = findMinRps(head);
    int max = findMaxRps(head);
    int num = generateRand(head, min, max);

    printf("\nUklanjanje svi rijeci s brojem ponavljanja: %d\n", num);

    removeSame(head, num);

    printf("\nKonacna lista: \n");
    printList(head->next);


    freeList(head);

    return EXIT_SUCCESS;
}

RijeciP createNewWord(char* word, int numOfRepeats) {
    RijeciP newWord = (RijeciP)malloc(sizeof(Rijeci));
    if (newWord == NULL) {
        printf("ERROR! Could not allocate memory!\n");
        return NULL;
    }
    strcpy(newWord->word, word);
    newWord->nORepeats = numOfRepeats;
    newWord->next = NULL;

    return newWord;
}

int loadFromFile(RijeciP head, const char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        exit(EXIT_FAILURE);
    }
    char word[MAX_NAME];
    while (fscanf(fp, "%s", word) == 1) {
        addNew(head, word);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int addNew(RijeciP head, char* word) {
    RijeciP prev = head;
    RijeciP temp = head->next;

    while (temp) {
        if (strcmp(temp->word, word) == 0) {
            temp->nORepeats++;
            return EXIT_SUCCESS;
        }
        prev = temp;
        temp = temp->next;
    }

    RijeciP newWord = createNewWord(word, 1);
    prev->next = newWord;

    return EXIT_SUCCESS;
}

int printList(RijeciP first) {
    RijeciP temp = first;
    while (temp) {
        printf("Rijec: %s,  Ponavljanja: %d\n", temp->word, temp->nORepeats);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int freeList(RijeciP head) {
    RijeciP temp = head->next;
    while (temp) {
        RijeciP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;

    return EXIT_SUCCESS;
}

int moveTopFiveToFront(RijeciP head) {
    RijeciP top[5] = { NULL };
    int i;

    for (i = 0; i < 5; i++) {
        RijeciP prev = head, curr = head->next, maxPrev = head, max = NULL;
        int maxCount = -1;
        while (curr) {
            int alreadyChosen = 0;
            for (int j = 0; j < i; j++) {
                if (curr == top[j]) {
                    alreadyChosen = 1;
                    break;
                }
            }
            if (!alreadyChosen && curr->nORepeats > maxCount) {
                maxCount = curr->nORepeats;
                maxPrev = prev;
                max = curr;
            }
            prev = curr;
            curr = curr->next;
        }
        if (max) {
            maxPrev->next = max->next;
            top[i] = max;
        }
    }

    for (i = 4; i >= 0; i--) {
        if (top[i]) {
            top[i]->next = head->next;
            head->next = top[i];
        }
    }

    return EXIT_SUCCESS;
}

int findMinRps(RijeciP head) {
    RijeciP temp = head->next;
    int min = 99;
    while (temp) {
        if (temp->nORepeats < min) {
            min = temp->nORepeats;
        }
        temp = temp->next;
    }
    return min;
}

int findMaxRps(RijeciP head) {
    RijeciP temp = head->next;
    int max = 0;
    while (temp) {
        if (temp->nORepeats > max) {
            max = temp->nORepeats;
        }
        temp = temp->next;
    }
    return max;
}

int generateRand(RijeciP head, int min, int max) {
    return rand() % (max - min + 1) + min;
}

int removeSame(RijeciP head, int num) {
    RijeciP prev = head;
    RijeciP curr = head->next;
    while (curr) {
        if (curr->nORepeats == num) {
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
