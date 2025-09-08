// Napisati program koji generira slučajne brojeve u opsegu od 130 - 160. 
// Ukoliko broj ne postoji u vezanoj listi dodaje se sortirano po vrijednosti,
// a ukoliko broj već postoji u vezanoj listi, samo se uveća broj ponavljanja tog broja.
// Ispisati listu (vrijednost i broj ponavljanja).
//
// Ocjena 2: Pronaći broj/brojeve koji su se ponovili najmanje puta i ispisati ih.
// 
// Ocjena 3: Tražiti od korisnika da upiše jedan broj i sve brojeve koji su se
// ponovili toliko puta treba pomaknuti na početak liste. Ispisati novu listu.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct number_;
typedef struct number_* NumberP;
typedef struct number_ {
	int value;
	int no_repeats;
	NumberP next;
} Number;

int generateRandNum();
NumberP createNewNumber(int value, int noRepeats);
int addSorted(NumberP head, int value);
int printList(NumberP first);
int freeList(NumberP head);

int findLowestCount(NumberP head);
int printLowestCount(NumberP head, int count);

int moveToTheFront(NumberP head, int count);

int main() {
	srand((unsigned int)time(NULL));

	NumberP head = (NumberP)malloc(sizeof(Number));
	if (head == NULL) {
		printf("ERROR! Could not allocate memmory!\n");
		return EXIT_FAILURE;
	}
	head->next = NULL;

	for (int i = 0; i < 30; i++) {
		addSorted(head, generateRandNum());
	}

	printf("Lista: \n");
	printList(head->next);

	int count = findLowestCount(head);
	
	printf("\nNajmanji broj ponavljanja je: %d\n", count);
	
	printf("\nBrojevi s najmanjim brojem ponavljanja: \n");
	
	printLowestCount(head, count);

	int cnt;

	printf("\nUnesite broj ponavljanja koji zelite pomaknuti: ");
	scanf("%d", &cnt);

	moveToTheFront(head, cnt);

	printList(head->next);


	freeList(head);

	return EXIT_SUCCESS;
}

int generateRandNum() {
	return rand() % 31 + 130;
}

NumberP createNewNumber(int value, int noRepeats) {
	NumberP newNumber = (NumberP)malloc(sizeof(Number));
	if (newNumber == NULL) {
		printf("ERROR! Could not allocate memmory!\n");
		return NULL;
	}
	newNumber->value = value;
	newNumber->no_repeats = noRepeats;
	newNumber->next = NULL;

	return newNumber;
}

int addSorted(NumberP head, int value) {
	NumberP prev = head;
	NumberP curr = head->next;

	while (curr) {
		if (curr->value == value) {
			curr->no_repeats++;
			return EXIT_SUCCESS;
		}
		else if(curr->value > value){
			break;
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
	
	NumberP newNumber = createNewNumber(value, 1);

	prev->next = newNumber;
	newNumber->next = curr;

	return EXIT_SUCCESS;
}

int printList(NumberP first) {
	NumberP temp = first;
	while (temp) {
		printf("Vrijednost: %d, Broj ponavljanja: %d\n", temp->value, temp->no_repeats);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

int freeList(NumberP head) {
	NumberP temp = head->next;
	while (temp) {
		NumberP toFree = temp;
		temp = temp->next;
		free(toFree);
	}
	head->next = NULL;

	return EXIT_SUCCESS;
}

int findLowestCount(NumberP head) {
	NumberP temp = head->next;
	int count = 9999;
	while (temp) {
		if (temp->no_repeats < count && temp->no_repeats >= 1) {
			count = temp->no_repeats;
		}
		temp = temp->next;
	}
	return count;
}

int printLowestCount(NumberP head, int count) {
	NumberP temp = head->next;
	while (temp) {
		if (temp->no_repeats == count) {
			printf("Vrijednost: %d\n", temp->value);
		}
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

int moveToTheFront(NumberP head, int count) {
	NumberP prev = head;
	NumberP curr = head->next;

	while (curr) {
		if (curr->no_repeats == count) {
			prev->next = curr->next;
			curr->next = head->next;
			head->next = curr;
			curr = prev->next;
		}
		else {
			prev = curr;
			curr = curr->next;
		}
	}
	return EXIT_SUCCESS;
}
