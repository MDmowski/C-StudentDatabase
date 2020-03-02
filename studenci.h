//
//  przedmioty.h
//  BazaStudentow
//
//  Created by Maciej Dmowski on 19/11/2018.
//  Copyright © 2018 Maciej Dmowski. All rights reserved.
//

#ifndef studenci_h
#define studenci_h

#include <stdlib.h>
#include <string.h>
#include "czyscBufor.h"
#include "wczytajDodatniInt.h"
#include "wykladowcy.h"
#include "przedmioty.h"
#include <stdbool.h>

struct student{
    char imie[30];
    char nazwisko[30];
    int indeks;
    char przedmioty[500];
};

typedef struct student student;

struct ElListyStudenci{
    struct student element;
    struct ElListyStudenci* nast;
};

typedef struct ElListyStudenci ElListyStudenci;

ElListyStudenci* dodajElStudenci( ElListyStudenci* glowa, student el );
void zwolnijStudent( ElListyStudenci* glowa );
student dodajStudent( ElListyStudenci* elStudenci, ElListyPrzedmioty* elPrzedmioty );
void wypiszStudent( ElListyStudenci* glowa );
int ileStudent(ElListyStudenci* elListy);
void usunStudent(ElListyStudenci* elListy, ElListyStudenci** adresWsk, ElListyPrzedmioty* elPrzedmioty);
void sortPoNazwStudent(ElListyStudenci* elListy);
void sortPoIndeksStudent(ElListyStudenci* elListy);
void sortPoImieStudent(ElListyStudenci* elListy);
void sortStudenci(ElListyStudenci* elListy);
ElListyStudenci* operacjeStudenci(ElListyStudenci* glowaStudenci, ElListyPrzedmioty* glowaPrzedmioty);
#endif /* przedmioty_h */
