/*Napisati program koji generira 30 slučajnih brojeva u opsegu od 0 do 100 i od generiranih
brojeva gradi vezanu listu. Ispisati listu.

Izbaciti iz liste sve one brojeve koji su djeljivi s 3 ili imaju znamenku 3 i rezultatnu listu
upisati u datoteku u sortiranom redoslijedu od najmanjeg do najvećeg broja (sama lista se
ne smije sortirati prije upisa u datoteku). – za ocjenu dovoljan*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _node* NodeP;
typedef struct _node {
    int value;
    NodeP next;
} Node;

int generateRandValue();
NodeP createNewNode(int value);
int addNewNode(NodeP head, int el);
int printList(NodeP first);
int freeList(NodeP head);

int removeThree(NodeP head);
int insertSorted(NodeP head, const char* fileName);

int main() {
    srand((unsigned int)time(NULL));

    NodeP head = (NodeP)malloc(sizeof(Node));
    if (head == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    for (int i = 0; i < 30; i++) {
        addNewNode(head, generateRandValue());
    }

    printList(head->next);

    printf("\nMicanje vrijednosti djeljivih sa tri i vrijednosti koje sadrze broj tri...\n");

    removeThree(head);

    printList(head->next);

    printf("\nUpis preostallih vrijednosti u datoteku...");
    insertSorted(head, "UPIS.txt");

    freeList(head);

    return EXIT_SUCCESS;
}

int generateRandValue() {
    return rand() % 101;
}

NodeP createNewNode(int value) {
    NodeP newNode = (NodeP)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

int addNewNode(NodeP head, int el) {
    NodeP temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    NodeP newNode = createNewNode(el);
    temp->next = newNode;

    return EXIT_SUCCESS;
}

int printList(NodeP first) {
    NodeP temp = first;
    while (temp) {
        printf("Vrijednost elementa: %d\n", temp->value);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int freeList(NodeP head) {
    NodeP temp = head->next;
    while (temp) {
        NodeP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;

    return EXIT_SUCCESS;
}

int removeThree(NodeP head) {
    NodeP prev = head;
    NodeP curr = head->next;

    while (curr) {
        if ((curr->value % 3) == 0) {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
        }
        else {
            if ((((curr->value / 10) % 10) == 3) || (((curr->value % 10) == 3))) {
                prev->next = curr->next;
                free(curr);
                curr = prev->next;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
    }
    return EXIT_SUCCESS;
}

int insertSorted(NodeP head, const char* fileName) {
    FILE* fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        exit(EXIT_FAILURE);
    }

    NodeP sortHead = (NodeP)malloc(sizeof(Node));
    if (sortHead == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        fclose(fp);
        return EXIT_FAILURE;
    }
    sortHead->next = NULL;

    NodeP curr = head->next;
    while (curr) {
        NodeP newNode = createNewNode(curr->value);
        NodeP temp = sortHead;
        while (temp->next && temp->next->value < newNode->value) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;

        curr = curr->next;
    }

    NodeP t = sortHead->next;
    while (t) {
        fprintf(fp, "%d\n", t->value);
        t = t->next;
    }

    freeList(sortHead);
    free(sortHead);

    fclose(fp);

    return EXIT_SUCCESS;
}
