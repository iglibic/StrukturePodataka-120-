// Napisati program koji iz datoteke membership.txt i visits.txt (imena datoteka unosi korisnik) čita podatke
// u mjesečnim članarinama korisnika i o posjetima u teretani.

// Posjeta u teretani je deinirana strukturom: 

#define MAX_ID_LENGTH (64)
#define MAX_NAME_LENGTH (64)
struct _visit;
typedef struct _visit *VisitP;
typedef struct _visit{
	char userId[MAX_ID_LENGTH];
	int day;
	int month;
	int year;
	VisitP next;
} Visit;

// Dok je članarina definirana strukturom:

struct _membership;
typedef struct _membership* MembershipP;
typedef struct _membership {
	char userId[MAX_ID_LENGTH];
	char firstName[MAX_NAME_LENGTH];
	char lastName[MAX_NAME_LENGTH];
	int month;
	int year;
	int price;
	VisitP visits;
	MembershipP next;
} Membership;

// OCJENA 2: Pročitati datoteke i uvezati na način da se posjete povežu s članovima (lista u listi). Posjeta se
// veže s članarinom ako je userId isti i ako se posjeta dogodila u tom mjesecu.
// Lista članarine mora biti sortirana po godini i mjesecu. Posjete moraju biti sortirane po danu u mjesecu.
// Ispisati sve članarine i posjete u tom mjesecu.

// OCJENA 3: Prepraviti program da mjesečne članarine budu sortirane po godini, mjesecu, zatim brojem posjeta
// u tom mjesecu. Korisnika zamoli za unos mjeseca i godine, te ispisati sve članarine koje imaju najmanje
// jednu posjetu u tom mjesecu i ukupnu zaradu takvih članarina.

//Uvjet za bilo koju ocjenu:
// - Koristiti funkcije
// - Provjeriti uspješnost dinamičkih alokacija memorije (i obaviti miran prekid programa u slučaju neuspješne
//   alokacije)
// - Provjeriti uspješnost otvaranja datoteka (i obaviti moran prekid programa u slučaju neuspješnog otvaranja)
// - Zatvoriti datoteke nakon rada s njima
// - Na kraju programa osloboditi svu dinamički alociranu memoriju-
