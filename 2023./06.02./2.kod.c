// Napisati program koji za tri različita predmeta iz datoteka čita
// podatke o studentima koji su položili predmet i gradi tri vezane
// liste. Svaki predmet ima svoju datoteku (Subject1.txt,
// Subject2.txt, Subject3.txt).

// OCJENA 2:
// Iz tri gornje vezane liste napraviti novu na način da za svakog
// studenta postoji samo jedan element u listi, tj. ukoliko je
// student položio više predmeta treba grupirati njegove ocjene u 
// jedan element liste. Ukoliko student nije položio neki predmet,
// tada je njegova ocjena iz tog predmeta 1. Ispisati listu u
// formatu:
//      - lastName firstName (Subject1, Subject2, Subject3)

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN (32)
#define MAX_SUBJECTS (3)

struct student;
typedef struct _student* StudentP;
typedef struct _student {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int grades[MAX_SUBJECTS];
    StudentP next;
} Student;

StudentP createNewStudent(char* fName, char* lName);
int loadFromFile(StudentP head, const char* fileName, int index);
int addNewStudent(StudentP head, StudentP newStudent);
int printList(StudentP first);
int freeList(StudentP head);

int mergeLists(StudentP head1, StudentP head2, StudentP head3, StudentP headResult);


int main() {
    StudentP head1 = (StudentP)malloc(sizeof(Student));
    StudentP head2 = (StudentP)malloc(sizeof(Student));
    StudentP head3 = (StudentP)malloc(sizeof(Student));
    StudentP head4 = (StudentP)malloc(sizeof(Student));


    if (head1 == NULL || head2 == NULL || head3 == NULL || head4 == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head1->next = NULL;
    head2->next = NULL;
    head3->next = NULL;
    head4->next = NULL;

    loadFromFile(head1, "Subject1.txt", 0);
    loadFromFile(head2, "Subject2.txt", 1);
    loadFromFile(head3, "Subject3.txt", 2);

    printf("Lista 1: \n");
    printList(head1->next);

    printf("\nLista 2: \n");
    printList(head2->next);

    printf("\nLista 3: \n");
    printList(head3->next);

    mergeLists(head1, head2, head3, head4);

    printf("\nRezultantna lista: \n");
    printList(head4->next);

    freeList(head1);
    freeList(head2);
    freeList(head3);
    freeList(head4);


    return EXIT_SUCCESS;
}

StudentP createNewStudent(char* fName, char* lName) {
    StudentP newStudnet = (StudentP)malloc(sizeof(Student));
    if (newStudnet == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    strcpy(newStudnet->firstName, fName);
    strcpy(newStudnet->lastName, lName);
    for (int i = 0; i < 3; i++) {
        newStudnet->grades[i] = 1;
    }
    newStudnet->next = NULL;

    return newStudnet;
}

int loadFromFile(StudentP head, const char* fileName, int index) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        exit(EXIT_FAILURE);
    }
    char fname[MAX_NAME_LEN], lname[MAX_NAME_LEN];
    int grade;
    while (fscanf(fp, "%s %s %d", lname, fname, &grade) == 3) {
        StudentP newStudent = createNewStudent(fname, lname);
        if (newStudent == NULL) {
            printf("ERROR! Could not allocate memmory!\n");
            return EXIT_FAILURE;
        }
        newStudent->grades[index] = grade;
        addNewStudent(head, newStudent);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int addNewStudent(StudentP head, StudentP newStudent) {
    StudentP temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newStudent;

    return EXIT_SUCCESS;
}

int mergeLists(StudentP head1, StudentP head2, StudentP head3, StudentP headResult) {
    StudentP temp1 = head1->next;
    while (temp1) {
        StudentP temp = headResult;
        int found = 0;
        while (temp) {
            if (strcmp(temp->lastName, temp1->lastName) == 0 && strcmp(temp->firstName, temp1->firstName) == 0) {
                found = 1;
                temp->grades[0] = temp1->grades[0];

                break;
            }
            temp = temp->next;
        }
        if (!found) {
            StudentP noviCvor = createNewStudent(temp1->firstName, temp1->lastName);
            for (int i = 0; i < 3; i++)
                if (temp1->grades[i] > 1) {
                    noviCvor->grades[i] = temp1->grades[i];
                }
            addNewStudent(headResult, noviCvor);
        }

        temp1 = temp1->next;
    }

    StudentP temp2 = head2->next;
    while (temp2) {
        StudentP temp = headResult;
        int found = 0;
        while (temp) {
            if (strcmp(temp->lastName, temp2->lastName) == 0 && strcmp(temp->firstName, temp2->firstName) == 0) {
                found = 1;
                temp->grades[1] = temp2->grades[1];

                break;
            }
            temp = temp->next;
        }
        if (!found) {
            StudentP noviCvor = createNewStudent(temp2->firstName, temp2->lastName);
            for (int i = 0; i < 3; i++)
                if (temp2->grades[i] > 1) {
                    noviCvor->grades[i] = temp2->grades[i];
                }
            addNewStudent(headResult, noviCvor);
        }

        temp2 = temp2->next;
    }

    StudentP temp3 = head3->next;
    while (temp3) {
        StudentP temp = headResult;
        int found = 0;
        while (temp) {
            if (strcmp(temp->lastName, temp3->lastName) == 0 && strcmp(temp->firstName, temp3->firstName) == 0) {
                found = 1;
                temp->grades[2] = temp3->grades[2];

                break;
            }
            temp = temp->next;
        }
        if (!found) {
            StudentP noviCvor = createNewStudent(temp3->firstName, temp3->lastName);
            for (int i = 0; i < 3; i++)
                if (temp3->grades[i] > 1) {
                    noviCvor->grades[i] = temp3->grades[i];
                }
            addNewStudent(headResult, noviCvor);
        }

        temp3 = temp3->next;
    }

    return EXIT_SUCCESS;
}

int printList(StudentP first) {
    StudentP temp = first;
    while (temp) {
        printf(" -  %s %s (%d, %d, %d)\n", temp->lastName, temp->firstName, temp->grades[0], temp->grades[1], temp->grades[2]);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int freeList(StudentP head) {
    StudentP temp = head->next;
    while (temp) {
        StudentP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;
    return EXIT_SUCCESS;
}
