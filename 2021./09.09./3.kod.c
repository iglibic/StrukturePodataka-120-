/*Napisati program koji iz datoteke čita imena studenata. Nakon što se pročita ime jednog studenta dodijeli
mu se ocjena iz predmeta (slučajna vrijednost od 1 do 5) i sprema se u vezanu listu sortirano prema 
ocjenama od najveće prema najnižoj. Ispisati listu.

Slučajno generirati jednu ocjenu i izbrisati sve studente koji imaju tu ocjenu. Ispisati listu. – ocjena 
dovoljan

Izmijeniti gornji zadatak na način da se student ne sortira samo po ocjenama, nego i po prezimenu i
imenu. – ocjena dobar.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LEN 32

typedef struct _student* StudentP;
typedef struct _student {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int grade;
    StudentP next;
} Student;

int generateRandValue();
StudentP createNewStudent(char* fName, char* lName, int grade);
int loadFromFile(StudentP head, const char* fileName);
int insertSorted(StudentP head, StudentP newStudent);
int printList(StudentP first);
int freeList(StudentP head);

int deleteByGrade(StudentP head, int grade);

int main() {
    srand((unsigned int)time(NULL));

    StudentP head = (StudentP)malloc(sizeof(Student));
    if (head == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    loadFromFile(head, "STUDENTI2.txt");

    printf("Pocetna lista: \n");
    printList(head->next);

    int grade = generateRandValue();

    printf("\nBrisanje svih studenata sa ocjenom %d: \n", grade);
    deleteByGrade(head, grade);

    printf("Konacna lista: \n");
    printList(head->next);

    freeList(head);

    return EXIT_SUCCESS;
}

int generateRandValue() {
    return rand() % 5 + 1;
}

StudentP createNewStudent(char* fName, char* lName, int grade) {
    StudentP newStudent = (StudentP)malloc(sizeof(Student));
    if (newStudent == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    strcpy(newStudent->firstName, fName);
    strcpy(newStudent->lastName, lName);
    newStudent->grade = grade;
    newStudent->next = NULL;

    return newStudent;
}

int loadFromFile(StudentP head, const char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        exit(EXIT_FAILURE);
    }
    char fname[MAX_NAME_LEN], lname[MAX_NAME_LEN];

    while (fscanf(fp, "%s %s", fname, lname) == 2) {
        int grade = generateRandValue();
        StudentP newStudent = createNewStudent(fname, lname, grade);
        if (newStudent == NULL) {
            printf("ERROR! Could not allocate memmory!\n");
            return EXIT_FAILURE;
        }
        insertSorted(head, newStudent);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int insertSorted(StudentP head, StudentP newStudent) {
    StudentP prev = head;
    StudentP curr = head->next;
    while (curr) {
        if (newStudent->grade > curr->grade) {
            break;
        }
        else {
            if ((newStudent->grade == curr->grade) && (strcmp(newStudent->lastName, curr->lastName) < 0)) {
                break;
            }
            else {
                if ((newStudent->grade == curr->grade) && (strcmp(newStudent->lastName, curr->lastName) == 0) 
                    && (strcmp(newStudent->firstName, curr->firstName) <= 0)) {
                    break;
                }
                else{
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }
    prev->next = newStudent;
    newStudent->next = curr;

    return EXIT_SUCCESS;
}

int printList(StudentP first) {
    StudentP temp = first;
    while (temp) {
        printf("Osoba: %s %s, Ocjena: %d\n", temp->firstName, temp->lastName, temp->grade);
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

int deleteByGrade(StudentP head, int grade) {
    StudentP prev = head;
    StudentP curr = head->next;
    while (curr) {
        if (curr->grade == grade) {
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
