// Napisati program koji iz datoteke "temperature.txt" čita podatke o
// temperaturama Jadranskog mora koje su izmjerene na određenoj
// dubini određenog datuma. U datoteci je prvo zapisan datum, pa
// dubina mjerenja, pa temperatura. Podatke je potrebno spremiti u
// jednostruko vezanu listu sortiranu po datumu mjerenja te ispisati.

// OCJENA 2: Izračunati prosječnu temperaturu Jadranskog mora na
// dubini većoj od 50 metara u 2023. godini.SVA mjerenja čija je
// temperatura manja od prosječne potrebno je izbrisati iz vezane 
// liste te potom ispisati listu.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _date {
    int day;
    int month;
    int year;
} Date;

typedef struct _temperature* TemperatureP;
typedef struct _temperature {
    float temperature;
    int depth;
    Date dateOfMeasurments;
    TemperatureP next;
} Temperature;

TemperatureP createNewReadin(float temperature, int depth, Date date);
int loadFromFile(TemperatureP head, const char* fileName);
int insertSorted(TemperatureP head, TemperatureP newReading);
int printList(TemperatureP first);
int freeList(TemperatureP head);

float calcAvg(TemperatureP head);
int removeBlwAvg(TemperatureP head, float avg);

int main() {
    TemperatureP head = (TemperatureP)malloc(sizeof(Temperature));
    if (head == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return EXIT_FAILURE;
    }
    head->next = NULL;

    loadFromFile(head, "TEMPERATURE.txt");

    printf("Pocetna lista: \n");
    printList(head->next);

    float average = calcAvg(head->next);

    printf("\nProsjecna temperatura 2023. na dubini vecoj od 50m : %f\n", average);
    printf("Uklanjanje svih mjerenja manjih od prosjeka...\n");

    removeBlwAvg(head, average);

    printf("\nKonacna lista: \n");
    printList(head->next);

    freeList(head);

    return EXIT_SUCCESS;
}

TemperatureP createNewReadin(float temperature, int depth, Date date) {
    TemperatureP newReading = (TemperatureP)malloc(sizeof(Temperature));
    if (newReading == NULL) {
        printf("ERROR! Could not allocate memmory!\n");
        return NULL;
    }
    newReading->temperature = temperature;
    newReading->depth = depth;
    newReading->dateOfMeasurments = date;
    newReading->next = NULL;

    return newReading;
}

int loadFromFile(TemperatureP head, const char* fileName) {
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("ERROR! Could not open the file!\n");
        exit(EXIT_FAILURE);
    }
    int d, m, y, depth;
    float temp;

    while (fscanf(fp, "%d.%d.%d %d %f", &d, &m, &y, &depth, &temp) == 5) {
        Date date = { d,m,y };
        TemperatureP newReading = createNewReadin(temp, depth, date);
        if (newReading == NULL) {
            printf("ERROR! Could not allocate memmory!\n");
            return EXIT_FAILURE;
        }
        insertSorted(head, newReading);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

int insertSorted(TemperatureP head, TemperatureP newReading) {
    TemperatureP prev = head;
    TemperatureP curr = head->next;
    while (curr) {
        Date date1 = newReading->dateOfMeasurments;
        Date date2 = curr->dateOfMeasurments;

        if (date1.year < date2.year) {
            break;
        }
        else {
            if ((date1.year == date2.year) && (date1.month < date2.month)) {
                break;
            }
            else {
                if ((date1.year == date2.year) && (date1.month == date2.month) && (date1.day <= date2.day)) {
                    break;
                }
                else {
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
    }
    prev->next = newReading;
    newReading->next = curr;

    return EXIT_SUCCESS;
}

int printList(TemperatureP first) {
    TemperatureP temp = first;
    while (temp) {
        printf("Datum: %d.%d.%d, Temperatura: %.2f, Dubina: %d\n", temp->dateOfMeasurments.day,
            temp->dateOfMeasurments.month, temp->dateOfMeasurments.year, temp->temperature, temp->depth);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int freeList(TemperatureP head) {
    TemperatureP temp = head->next;
    while (temp) {
        TemperatureP toFree = temp;
        temp = temp->next;
        free(toFree);
    }
    head->next = NULL;

    return EXIT_SUCCESS;
}

float calcAvg(TemperatureP head) {
    TemperatureP temp = head;
    float totaltemp = 0.0;
    int total = 0;
    while (temp) {
        if ((temp->dateOfMeasurments.year == 2023) && (temp->depth > 50)) {
            total++;
            totaltemp += temp->temperature;
        }
        temp = temp->next;
    }
    return (float)totaltemp / total;
}

int removeBlwAvg(TemperatureP head, float avg) {
    TemperatureP prev = head;
    TemperatureP curr = head->next;
    while (curr) {
        if (curr->temperature < avg) {
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
