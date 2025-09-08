// Napisati program koji iz datoteke „Osobe.txt“ čita podatke o
// osobama i njihovim datumima rođenja i te podatke sprema u vezanu
// listu sortiranu po datumu. Ispisati listu.

// OCJENA 2:
// Svim osobama na listi generirati jedinstveni ID u opsegu od 100
// do 180, a zatim unijeti jedan ID i izbrisati tu osobu. Ispisati novu listu.

// OCJENA 3 :
// Pronaći u kojem mjesecu je rođeno najviše osoba, te sve osobe
// koje su rođene u tom mjesecu prebaciti u novu vezanu listu bez
// dodatne alokacije memorije.

// U izradi zadatka se može koristiti struktura :

typedef struct _date {
    int day;
    int month;
    int year;
} Date;

#define MAX_NAME_LEN (32)
struct _person;
typedef struct _person* PersonP;
typedef struct _person {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int idNumber;
    Date birthDate;
    PersonP Next;
} Person;

// NAPOMENA: Za bilo koju ocjenu potrebno je pri završetku programa
// osloboditi svu dinamički alociranu memoriju i zatvoriti sve datoteke.
