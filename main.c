//
//  main.c
//  BazaStudentow
//
//  Created by Maciej Dmowski on 18/11/2018.
//  Copyright © 2018 Maciej Dmowski. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wykladowcy.h"
#include "przedmioty.h"
#include "studenci.h"

int main( void ) {
    ElListyWykladowcy* glowaWykladowcy = NULL;
    ElListyPrzedmioty* glowaPrzedmioty = NULL;
    ElListyStudenci* glowaStudenci = NULL;
    char wybierz='w';
    do{
        puts("Wybierz tablice: w - wykladowcy, p - przedmioty, s - studenci, z - zakończ");
        scanf(" %c", &wybierz);
        czyscBufor();
        switch (wybierz) {
            case 'w':
                glowaWykladowcy = operacjeWykladowcy(glowaWykladowcy);
                break;
            case 'p':
                glowaPrzedmioty = operacjePrzedmioty(glowaPrzedmioty, glowaWykladowcy);
                break;
            case 's':
                glowaStudenci = operacjeStudenci(glowaStudenci, glowaPrzedmioty);
                break;
            case 'c':
                zwolnijWykladowcy(glowaWykladowcy);
                break;
            case 'z':
                puts("Żegnaj");
                break;
            default:
                puts("Nie ma takiej operacji.");
                break;
        }
    }while(wybierz != 'z');
    zwolnijPrzedmiot(glowaPrzedmioty);
    zwolnijWykladowcy(glowaWykladowcy);
    zwolnijStudent(glowaStudenci);
    return 0;
}
