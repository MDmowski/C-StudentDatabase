//
//  przedmioty.h
//  BazaStudentow
//
//  Created by Maciej Dmowski on 19/11/2018.
//  Copyright © 2018 Maciej Dmowski. All rights reserved.
//

#ifndef przedmioty_h
#define przedmioty_h

#include <stdlib.h>
#include <string.h>
#include "czyscBufor.h"
#include "wczytajDodatniInt.h"
#include "wykladowcy.h"

struct przedmiot{
    char nazwa[50];
    char prowadzacy[60];
    char studenci[500];
};

typedef struct przedmiot przedmiot;

struct ElListyPrzedmioty{
    struct przedmiot element;
    struct ElListyPrzedmioty* nast;
};

typedef struct ElListyPrzedmioty ElListyPrzedmioty;

ElListyPrzedmioty* dodajElPrzedmioty( ElListyPrzedmioty* glowa, przedmiot el );
void zwolnijPrzedmiot( ElListyPrzedmioty* glowa );
przedmiot dodajPrzedmiot( ElListyPrzedmioty* elPrzedmioty, ElListyWykladowcy* elWykladowcy );
void wypiszPrzedmiot( ElListyPrzedmioty* glowa );
int ilePrzedmiotow(ElListyPrzedmioty* elListy);
void usunPrzedmiot(ElListyPrzedmioty* elListy, ElListyPrzedmioty** adresWsk, ElListyWykladowcy* elWykladowcy);
void sortPoNazwPrzed(ElListyPrzedmioty* elListy);
void sortPoProwPrzed(ElListyPrzedmioty* elListy);
void sortPrzedmioty(ElListyPrzedmioty* elListy);
ElListyPrzedmioty* operacjePrzedmioty(ElListyPrzedmioty* glowaPrzed, ElListyWykladowcy* glowaWykl);
#endif /* przedmioty_h */
