// Napisati program koji čita datoteku koja sadrži podatke o
// osobama ("people.txt") te kreirati vezanu listu osoba sortiranju
// po prezimenu i imenu.
// Nakon toga iz datoteke "vehicle.txt", treba pročitati podatke o
// automibilima koje posjeduje pojedina osoba i za svaku osobu
// kreirati dodatnu vezanu listu koja sadrži podatke o njenim
// vozilima.

// OCJENA 2: Ispisati podatke o svim osobama i njihovim vozilima, 
// uz uvjet da se za osobe koje nemaju vozila ispiše "NEMA VOZILA".

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ID_LEN (8)
#define MAX_NAME_LEN (64)

typedef struct _vehicle* VehicleP;
typedef struct _person* PersonP;

typedef struct _date {
	int year;
	int month;
	int day;
} Date;

typedef struct _person {
	char id[MAX_NAME_LEN];
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
	PersonP next;
	VehicleP vehicles;
} People;

typedef struct _vehicle {
	char brandName[MAX_NAME_LEN];
	char modelName[MAX_NAME_LEN];
	Date date;
	VehicleP next;
} Vehicle;

PersonP createNewPerson(char* iD, char* fName, char* lName);
VehicleP createNewVehicle(char* brandname, char* modelname, Date date);
PersonP findPerson(PersonP head, char* id);
int insertSorted(PersonP head, PersonP newPerson);
int connectVehiclesToPeople(PersonP person, VehicleP vehicle);
int loadFromFilePeople(PersonP head, const char* fileName);
int loadFromFileVehicles(PersonP head, const char* fileName);

int printList(PersonP first);
int freeVehicles(VehicleP head);
int freePeople(PersonP head);

int main() {
	PersonP head = (PersonP)malloc(sizeof(People));
	if (head == NULL) {
		printf("ERROR! Could not allocate memmory!\n");
		return EXIT_FAILURE;
	}
	head->next = NULL;

	loadFromFilePeople(head, "People.txt");
	loadFromFileVehicles(head, "Vehicle.txt");

	printf("Pocetna lista: \n");
	printList(head->next);

	freePeople(head);

	return EXIT_SUCCESS;
}

PersonP createNewPerson(char* iD, char* fName, char* lName) {
	PersonP newPerson = (PersonP)malloc(sizeof(People));
	if (newPerson == NULL) {
		printf("ERROR! Could not allocate memmory!\n");
		return NULL;
	}
	strcpy(newPerson->id, iD);
	strcpy(newPerson->firstName, fName);
	strcpy(newPerson->lastName, lName);
	newPerson->vehicles = NULL;
	newPerson->next = NULL;

	return newPerson;
}

VehicleP createNewVehicle(char* brandname, char* modelname, Date date) {
	VehicleP newVehicle = (VehicleP)malloc(sizeof(Vehicle));
	if (newVehicle == NULL) {
		printf("ERROR! Could not allocate memmory!\n");
		return NULL;
	}
	strcpy(newVehicle->brandName, brandname);
	strcpy(newVehicle->modelName, modelname);
	newVehicle->date = date;
	newVehicle->next = NULL;

	return newVehicle;
}

PersonP findPerson(PersonP head, char* id) {
	PersonP temp = head->next;
	while (temp) {
		if (strcmp(temp->id, id) == 0) {
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

int insertSorted(PersonP head, PersonP newPerson) {
	PersonP prev = head;
	PersonP curr = head->next;
	while (curr) {
		if (strcmp(newPerson->lastName, curr->lastName) < 0) {
			break;
		}
		else {
			if ((strcmp(newPerson->lastName, curr->lastName) == 0) && (strcmp(newPerson->firstName, curr->firstName) <= 0)) {
				break;
			}
			else {
				prev = curr;
				curr = curr->next;
			}
		}
	}
	prev->next = newPerson;
	newPerson->next = curr;

	return EXIT_SUCCESS;
}

int connectVehiclesToPeople(PersonP person, VehicleP vehicle) {
	if (person == NULL || vehicle == NULL) {
		printf("ERROR! Irregular values!\n");
		return EXIT_FAILURE;
	}

	vehicle->next = person->vehicles;
	person->vehicles = vehicle;

	return EXIT_SUCCESS;
}

int loadFromFilePeople(PersonP head, const char* fileName) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("ERROR! Could not open the file!\n");
		exit(EXIT_FAILURE);
	}
	char id[MAX_ID_LEN], fname[MAX_NAME_LEN], lname[MAX_NAME_LEN];
	while (fscanf(fp, "%s %s %s", id, fname, lname) == 3) {
		PersonP newPerson = createNewPerson(id, fname, lname);
		if (newPerson == NULL) {
			printf("ERROR! Could not allocate memmory!\n");
			return EXIT_FAILURE;
		}
		insertSorted(head, newPerson);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int loadFromFileVehicles(PersonP head, const char* fileName) {
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("ERROR! Could not open the file!\n");
		return EXIT_FAILURE;
	}
	char brName[MAX_NAME_LEN], modName[MAX_NAME_LEN], id[MAX_ID_LEN];
	int d, m, y;
	while (fscanf(fp, "%s %s %s %d-%d-%d", id, brName, modName, &y, &m, &d) == 6) {
		Date date = { y, m, d };
		VehicleP newVehicle = createNewVehicle(brName, modName, date);
		if (newVehicle == NULL) {
			printf("ERROR! Could not allocate memmory!\n");
			return EXIT_FAILURE;
		}
		PersonP person = findPerson(head, id);
		if (person == NULL) {
			free(newVehicle);
		}
		else {
			connectVehiclesToPeople(person, newVehicle);
		}
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int printList(PersonP first) {
	PersonP temp = first;
	while (temp) {
		int found = 1;
		printf("\nOsoba: %s %s, ID: %s\n", temp->firstName, temp->lastName, temp->id);
		VehicleP vehicle = temp->vehicles;
		while (vehicle) {
			printf("Vozilo: %s %s, Datum: %d-%d-%d\n", vehicle->brandName,
				vehicle->modelName, vehicle->date.year, vehicle->date.month, vehicle->date.day);
			found = 0;
			vehicle = vehicle->next;
		}
		if (found) {
			printf("NEMA VOZILA!\n");
		}
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

int freeVehicles(VehicleP head) {
	VehicleP temp = head;
	while (temp) {
		VehicleP toFree = temp;
		temp = temp->next;
		free(toFree);
	}
	return EXIT_SUCCESS;
}

int freePeople(PersonP head) {
	PersonP temp = head->next;
	while (temp) {
		freeVehicles(temp->vehicles);
		PersonP toFree = temp;
		temp = temp->next;
		free(toFree);
	}
	head->next = NULL;

	return EXIT_SUCCESS;
}
