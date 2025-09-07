 // Napisati program koji čita datoteku koja sadrži podatke o
 // zaposlenicima("zaposlenici.txt") te kreirati vezanu listu
 // sortiranu po datumu njihovog zaposlenja (potom po imenu). 
 // Uz datum zaposlenja, u datoteci se nalaze i ime i
 // prezime zaposlenika. Svaki zaposlenik ima svoju plaću koju je
 // potrebno generirati na random način, uz ograničenje da nijedan
 // zaposlenik ne smije imati istu plaću, s tim da je plaća u
 // opsegu od 1000 do 1050€.

// Zaposlenik je definiran strukturom :

#define MAX_NAME_LEN (32)  
struct _employee;
typedef struct _employee* EmployeeP;
typedef struct _employee {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    DateP date;
    int salary;
    HotelP next;
} Employee;

// Datum je definiran strukturom :

struct _date;
typedef struct _date* DateP;
typedef struct _date {
    int year;
    int month;
    int date;
} Date;

// OCJENA 2: Ispisati vezanu listu zaposlenika sortiranu po datumu
// njihovog zaposlenja, te ispisati njiovu plaću. Sve zaposlenike
// s imenom "Ivan" izbrisati iz vezane liste te ju potom ispisati.

// OCJENA 3: Pronaći troje zaposlenika koji imaju najvišu plaću te
// ih premjestiti na početak vezane liste zaposlenika. Ispisati 
// modificiranu vezanu listu zaposlenika.

// Uvjeti za bilo koju ocjenu :
//
// - Koristiti funkcije;
// - Provjeriti uspješnost dinamičkih alokacija memorije (i
//   obaviti miran prekid programa u slučaju neuspješne alokacije);
// - Provjeriti uspješnost otvaranja datoteka (i obaviti miran
//   prekid programa u slučaju neuspješnog otvaranja);
// - Zatvoriti datoteke nakon rada s njima;
// 
// Na kraju programa osloboditi svu dinamički alociranu memoriju.
