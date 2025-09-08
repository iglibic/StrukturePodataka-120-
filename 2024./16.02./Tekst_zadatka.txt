// Napisati program koji iz datoteke "temperature.txt" čita podatke o
// temperaturama Jadranskog mora koje su izmjerene na određenoj
// dubini određenog datuma. U datoteci je prvo zapisan datum, pa
// dubina mjerenja, pa temperatura. Podatke je potrebno spremiti u
// jednostruko vezanu listu sortiranou po datumu mjerenja te ispisati.

// OCJENA 2: Izračunati prosječnu temperaturu Jadranskog mora na
// dubini većoj od 50 metara u 2023. godini.SVA mjerenja čija je
// temperatura manja od prosječne potrebno je izbrisati iz vezane 
// liste te potom ispisati listu.

// OCJENA 3 : Za svako mjerenje generirati jedinstveni ID u opsegu od
// 500 do 610, a zatim unijeti jedan ID i prebaciti mjerenje koje ima
// taj ID na početak vezane liste. Potom ispisati novu listu.

// Za izradu zadatka mogu se koristiti strukture :

struct _date;
typedef struct _date* DateP;
typedef struct _date {
    int day;
    int month;
    int year;
} Date;

struct _temperature;
typedef struct _temperature* TemperatureP;
typedef struct _temperature {
    int depth;
    DateP dateOfMeasurments;
    TemperatureP next;
};

// NAPOMENA: Za bilo koju ocjenu potrebno je pri završetku programa
// osloboditi svu dinamički alociranu memoriju i zatvoriti sve datoteke.
