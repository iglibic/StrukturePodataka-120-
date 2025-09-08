// Napisati program koji iz datoteke „inventura.txt“ čita podatke o
// tehnološkoj opremi u učionici u formatu :

//    <naziv> <cijena>

// Pročitane podatke potrebno je učitati u vezanu listu sortiranu po
// nazivu opreme, na način da se ne smije ponavljati oprema istog naziva
// (npr.ako postoji više tipkovnica u datoteci, vezana lista treba
// sadržavati jedan čvor naziva tipkovnica s količinom koja predstavlja
// količinu svih tipkovnica).

// Čvor vezane liste definiran je strukturom :

#define MAX_NAME (64)
struct _item;
typedef struct _item* ItemP;
typedef struct _item {
    char name[MAX_NAME];
    int quantity;
    ItemP next;
} Item;

// OCJENA 2: Ispisati učitanu vezanu listu u formatu :

//  Tipkovnica 3
//  Miš 2
//  Zvučnik 1

// OCJENA 3: Proširiti strukturu iz prethodnog dijela zadatka tako da
// se uzima u obzir i vrijednosna cijena opreme. Napomena - cijene
// opreme istog naziva ne moraju nužno biti jednake; u tom slučaju se
// dodaje novi čvor liste.

//  Tipkovnica 1 25
//  Tipkovnica 2 30
//  Miš 2 20
//  ...

// Čvor proširene vezane liste definiran je strukturom :

#define MAX_NAME (64)  
struct _item;
typedef struct _item* ItemP;
typedef struct _item {
    char name[MAX_NAME];
    double sellPrice;
    int quantity;
    ItemP next;
} Item;

// Ispisati listu, iz nje izbrisati sve one članove čija je ukupna
// vrijednost preko 50. Ispisati novu listu.
