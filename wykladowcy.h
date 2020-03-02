//
//  wykladowcy.h
//  BazaStudentow
//
//  Created by Maciej Dmowski on 18/11/2018.
//  Copyright © 2018 Maciej Dmowski. All rights reserved.
//

#ifndef wykladowcy_h
#define wykladowcy_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "czyscBufor.h"
#include "wczytajDodatniInt.h"

struct wykladowca{
    char imie[30];
    char nazwisko[30];
    char przelozony[61];
    char przedmioty[500];
};

typedef struct wykladowca wykladowca;

struct ElListyWykladowcy{
    struct wykladowca element;
    struct ElListyWykladowcy* nast;
};

typedef struct ElListyWykladowcy ElListyWykladowcy;

ElListyWykladowcy* dodajElWykladowcy( ElListyWykladowcy* glowa, wykladowca el );
void zwolnijWykladowcy( ElListyWykladowcy* glowa );
wykladowca dodajWykladowce( ElListyWykladowcy* glowa );
void wypiszWykladowce( ElListyWykladowcy* glowa );
int ileWykladowcow(ElListyWykladowcy* elListy);
void usunWykladowce(ElListyWykladowcy* elListy, ElListyWykladowcy** adresWsk);
void sortPoImieWykl(ElListyWykladowcy* elListy);
void sortPoNazwWykl(ElListyWykladowcy* elListy);
void sortPoPrzelWykl(ElListyWykladowcy* elListy);
void sortWykladowcow(ElListyWykladowcy* elListy);
ElListyWykladowcy* operacjeWykladowcy(ElListyWykladowcy* glowaWykl);

#endif /* wykladowcy_h */
