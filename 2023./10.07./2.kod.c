// Napisati program koji čita datoteku koja sadrži podatke o
// zaposlenicima("zaposlenici.txt") te kreirati vezanu listu
// sortiranu po datumu njihovog zaposlenja (potom po imenu). 
// Uz datum zaposlenja, u datoteci se nalaze i ime i
// prezime zaposlenika. Svaki zaposlenik ima svoju plaću koju je
// potrebno generirati na random način, uz ograničenje da nijedan
// zaposlenik ne smije imati istu plaću, s tim da je plaća u
// opsegu od 1000 do 1050€.
//
// OCJENA 2: Ispisati vezanu listu zaposlenika sortiranu po datumu
// njihovog zaposlenja, te ispisati njiovu plaću. Sve zaposlenike
// s imenom "Ivan" izbrisati iz vezane liste te ju potom ispisati.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NAME_LEN (32)  

typedef struct _date {
    int day;
    int month;
    int year;
} Date;

typedef struct _employee* EmployeeP;
typedef struct _employee {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    Date date;
    int salary;
    EmployeeP next;
} Employee;

EmployeeP createNewEmployee(char* fName, char* lName, int salary, Date date);
int loadFromFile(EmployeeP head, const char* fileName, int usedValues[]);
int insertSorted(EmployeeP head, EmployeeP newEmplyoee);
int generateUniqueSalary(int usedValues[]);
int printList(EmployeeP first);
int freeList(EmployeeP head);

int deleteIvan(EmployeeP head);

int main() {
    srand((unsigned int)time(NULL));

    EmployeeP head = (EmployeeP)malloc(sizeof(Employee));
    if (head == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    int usedValues[51] = { 0 };

    loadFromFile(head, "Zaposlenici.txt", usedValues);

    printf("Pocetna lista: \n");
    printList(head->next);

    printf("\nBrisanje svih osoba s imenom Ivan iz liste...\n");

    deleteIvan(head);

    printf("\nKonacna lista: \n");
    printList(head->next);

    freeList(head);

    return EXIT_SUCCESS;
}

EmployeeP createNewEmployee(char* fName, char* lName, int salary, Date date) {
    EmployeeP newEmplyoee = (EmployeeP)malloc(sizeof(Employee));
    if (newEmplyoee == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    strcpy(newEmplyoee->firstName, fName);
    strcpy(newEmplyoee->lastName, lName);
    newEmplyoee->salary = salary;
    newEmplyoee->date = date;
    newEmplyoee->next = NULL;

    return newEmplyoee;
}

int loadFromFile(EmployeeP head, const char* fileName, int usedValues[]) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        exit(EXIT_FAILURE);
    }
    char fname[MAX_NAME_LEN], lname[MAX_NAME_LEN];
    int d, m, y;

    while (fscanf(fp, "%d.%d.%d %s %s", &d, &m, &y, fname, lname) == 5) {
        Date date = { d, m, y };
        int salary = generateUniqueSalary(usedValues);
        EmployeeP newEmplyoee = createNewEmployee(fname, lname, salary, date);
        if (newEmplyoee == NULL) {
            printf("ERROR! Could not allocate memmory!\n");
            return EXIT_FAILURE;
        }
        insertSorted(head, newEmplyoee);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int insertSorted(EmployeeP head, EmployeeP newEmplyoee) {
    EmployeeP prev = head;
    EmployeeP curr = head->next;
    while (curr) {
        Date date1 = newEmplyoee->date;
        Date date2 = curr->date;
        if (date1.year < date2.year) {
            break;
        }
        else {
            if ((date1.year == date2.year) && (date1.month < date2.month)) {
                break;
            }
            else {
                if ((date1.year == date2.year) && (date1.month == date2.month) && (date1.day < date2.day)) {
                    break;
                }
                else {
                    if ((date1.year == date2.year) && (date1.month == date2.month) && (date1.day < date2.day)
                        && (strcmp(newEmplyoee->firstName, curr->firstName) <= 0)) {
                        break;
                    }
                    else {
                        prev = curr;
                        curr = curr->next;
                    }
                }
            }
        }
    }
    prev->next = newEmplyoee;
    newEmplyoee->next = curr;

    return EXIT_SUCCESS;
}

int generateUniqueSalary(int usedValues[]) {
    int value;
    do {
        value = rand() % 51 + 1000;
    } while (usedValues[value - 1000]);
    usedValues[value - 1000] = 1;
    return value;
}

int printList(EmployeeP first) {
    EmployeeP temp = first;
    while (temp) {
        printf("Osoba: %s %s, Placa: %d, Datum: %d.%d.%d\n", temp->firstName,
            temp->lastName, temp->salary, temp->date.day, temp->date.month, temp->date.year);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int freeList(EmployeeP head) {
    EmployeeP temp = head->next;
    while (temp) {
        EmployeeP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;

    return EXIT_SUCCESS;
}

int deleteIvan(EmployeeP head) {
    EmployeeP prev = head;
    EmployeeP curr = head->next;
    while (curr) {
        if (strcmp(curr->firstName, "Ivan") == 0) {
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
