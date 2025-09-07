// Napisati program koji čita datoteku koja sadrži podatke o
// kategorijama proizvoda ("kategorije.txt") te kreirati vezanu
// listu kategorija sortiranu po abecedi. Uz kategoriju proizvoda
// u datoteci se nalaze i podaci o minimalnoj i maksimalnoj cijeni
// proizvoda u toj kategoriji.
// Nakon toga iz datoteke "proizvodi.txt" treba pročitati podatke
// o proizvodima iz kategorijama kojima pripadaju. Svaki proizvod
// treba smjestiti u dodatnu vezanu listu za pojedinu kategoriju, 
// tj. svaka kategorija sadržava dodatnu vezanu listu proizvoda koji 
// spadaju u tu kategoriju. Za svaki proizvod iz kategorije treba
// izgenerirati cijenu (slučajan broj iz min.i maks.opsega
// kategorije) i ne smije biti ponavljanja brojeva unutar iste
// kategorije.

// Kategorija je definirana strukturom :

#define MAX_NAME_LEN (32)  
struct _kategorija;
typedef struct _kategorija* KategorijaP;
typedef struct _kategorija {
    char imeKategorije[MAX_NAME_LEN];
    int minCijena;
    int maxCijena;
    float avgCijena;
    KategorijaP next;
    ProizvodP child;
} Kategorija;

// Proizvodi su definirani strukturom :

struct _proizvod;
typedef struct _proizvod* ProizvodP;
typedef struct _proizvod {
    char proizvodIme[MAX_NAME_LEN];
    int cijena;
    ProizvodP next;
} Proizvod;

// OCJENA 2: Ispisati konačnu listu da prvo ide naziv kategorije,
// pa nazivi i cijene proizvoda u toj kategoriji.

// OCJENA 3: Izračunati prosječnu cijenu proizvoda u svakoj
// kategoriji i izbrisati proizvode koji su skuplji. Ispisati listu.

// OCJENA 4: Pronaći kategoriju s najmanjom prosječnom cijenom
// proizvoda i pomaknuti je na početak. Ispisati listu.

// OCJENA 5 : Ponavljanjem koraka za ocjenu 4 sortirati listu po
// prosječnim cijenama.Ispisati novu listu.
