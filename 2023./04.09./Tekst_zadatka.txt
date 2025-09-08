// Napisati program koji iz datoteke „riječi.txt“ čita riječi i slaže ih po redoslijedu pojavljivanja. Pri tome
// ukoliko riječ već postoji u vezanoj listi, ne treba je ponovo dodavati u listu, već se uvećava brojač.

// Uvjeti za bilo koju ocjenu :
// - Koristiti funkcije;
// - Provjeriti uspješnost dinamičkih alokacija memorije(i obaviti miran prekid programa u
//   slučaju neuspješne alokacije);
// - Provjeriti uspješnost otvaranja datoteka(i obaviti miran prekid programa u slučaju
// neuspješnog otvaranja);
// - Zatvoriti datoteku nakon rada s njom;
// - Na kraju programa osloboditi svu dinamički alociranu memoriju;
// - Zabranjeno koristiti globalne varijable i funkciju exit().

// U rješavanju zadatka se može koristiti struktura:

struct _student;
typedef struct _student student;
typedef struct Student* studentPosition;
struct _student {
    int matricni_broj;
    char ime[20], prezime[20];
    int ocjena;
    studentPosition next;
};

// OCJENA 2:
// Ispisati vezanu listu i pronaći pet riječi koje su se pojavile najviše puta, te ih pomaknuti na početak 
// liste.

// OCJENA 3 :
// Slučajno generirati neki broj u opsegu između minimalnog i maksimalnog broja riječi u listi i izbrisati
// sve riječi koje se ponavljaju toliko puta. Ispisati novu listu.
