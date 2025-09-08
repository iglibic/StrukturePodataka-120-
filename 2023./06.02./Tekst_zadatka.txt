// Napisati program koji za tri različita predmeta iz datoteka čita
// podatke o studentima koji su položili predmet i gradi tri vezane
// liste. Svaki predmet ima svoju datoteku (Subject1.txt,
// Subject2.txt, Subject3.txt).

// Pročitani podaci se pohranjuju u strukturu :

struct student;
typedef struct _student* StudentP;
typedef struct _student {
    char firstName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    int Subject[MAX_NAME_LEN];
    StudentP Next;
} Student;

// OCJENA 2:
// Iz tri gornje vezane liste napraviti novu na način da za svakog
// studenta postoji samo jedan element u listi, tj. ukoliko je
// student položio više predmeta treba grupirati njegove ocjene u 
// jedan element liste. Ukoliko student nije položio neki predmet,
// tada je njegova ocjena iz tog predmeta 1. Ispisati listu u
// formatu:
//      - lastName firstName (Subject1, Subject2, Subject3)

// OCJENA 3 :
// Izmijeniti kreiranje nove liste na način da se kreira sortirana
// lista i to po prosjeku svih predmeta, pa po prezimenima.
// Ispisati listu u formatu :
//      - lastName firstName (Subject1, Subject2, Subject3) -Prosjek

// OCJENA 4 :
// Izbrisati iz liste sve osobe čije ime unesete s tastature.
// Ispisati listu.

// OCJENA 5 :
// Izgenerirati slučajnu ocjenu (od 1 do 5) i sve osobe koje imaju
// bar jednu tu ocjenu pomaknuti na početak liste.

// NAPOMENA : Za bilo koju ocjenu potrebno je pri završetku programa
// osloboditi svu dinamički alociranu memoriju i zatvoriti sve datoteke.
