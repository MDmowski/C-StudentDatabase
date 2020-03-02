//
//  wykladowcy.c
//  BazaStudentow
//
//  Created by Maciej Dmowski on 18/11/2018.
//  Copyright © 2018 Maciej Dmowski. All rights reserved.
//

#include "wykladowcy.h"
#include "wczytajDodatniInt.h"

ElListyWykladowcy* dodajElWykladowcy( ElListyWykladowcy* glowa, wykladowca el ){
    ElListyWykladowcy* nowyElListy = malloc( sizeof( ElListyWykladowcy ) );
    if( NULL == nowyElListy )
        exit ( EXIT_FAILURE );
    nowyElListy->element = el;
    nowyElListy->nast = glowa;
    return nowyElListy ;
}

void zwolnijWykladowcy ( ElListyWykladowcy* elListy ){
    ElListyWykladowcy* poprzedni = NULL;
    while( elListy ){
        poprzedni = elListy;
        elListy = elListy->nast;
        free ( poprzedni );
    }
}

int ileWykladowcow(ElListyWykladowcy* elListy){
    ElListyWykladowcy* wsk = elListy;
    int i=0;
    if(elListy == NULL){
        return 0;
    }
    else{
        while(wsk != NULL){
            ++i;
            wsk=wsk->nast;
        }
    }
    return i;
}

void wypiszWykladowce( ElListyWykladowcy* elListy){
    ElListyWykladowcy* wsk = elListy;
    if(wsk == NULL){
        printf("Lista jest pusta\n");
    }
    else{
        printf("Lp. Imie Nazwisko Przelozony Przedmioty \n");
        int i=0;
        while(wsk != NULL){
            printf("%d %s  %s  %s  %s\n", i, wsk->element.imie, wsk->element.nazwisko, wsk->element.przelozony, wsk->element.przedmioty);
            wsk=wsk->nast;
            ++i;
        }
    }
}

wykladowca dodajWykladowce(ElListyWykladowcy* elListy){
    wykladowca nowy;
imie:
    printf("Podaj imię wykładowcy\n");
    if(!scanf("%30s", nowy.imie)){
        czyscBufor();
        printf("Podaj poprawne dane\n");
        goto imie;
    }
nazwisko:
    printf("Podaj nazwisko wykładowcy\n");
    if(!scanf("%30s", nowy.nazwisko)){
        czyscBufor();
        printf("Podaj poprawne dane\n");
        goto nazwisko;
    }
    printf("Wybierz przelozonego\n");
    int ile = ileWykladowcow(elListy);
    if(ile == 0){
        printf("Brak przelozonego\n");
        strcpy(nowy.przelozony,"BRAK");
    }
    else{
        ElListyWykladowcy* wsk = elListy;
        wykladowca tab[ile];
        for(int n=0; n<ile; n++){
            strcpy(tab[n].imie, wsk->element.imie);
            strcpy(tab[n].nazwisko, wsk->element.nazwisko);
            strcpy(tab[n].przelozony, wsk->element.przelozony);
            strcpy(tab[n].przedmioty, wsk->element.przedmioty);
            wsk=wsk->nast;
        }
        printf("0 - brak przelozonego\n");
        for(int n=0; n < ile; ++n){
            printf("%d %s %s\n", n+1, tab[n].imie, tab[n].nazwisko);
        }
wybierz:
        printf("Wybierz przełożonego - podaj numer od 0 do %d\n", ile);
        int wybor = wczytajDodatniInt();
        if( wybor > ile){
            goto wybierz;
        }
        else{
            if(wybor != 0){
            char przelozony[60];
            strcpy(przelozony, tab[wybor-1].imie);
            strcat(strcat(przelozony," "), tab[wybor-1].nazwisko);
            strcpy(nowy.przelozony, przelozony);
            }
            else{
                strcpy(nowy.przelozony, "BRAK");
            }
        }
    }
    strcpy(nowy.przedmioty, "");
    return nowy;
}

void usunWykladowce(ElListyWykladowcy* elListy, ElListyWykladowcy** adresWsk){
    wypiszWykladowce(elListy);
    int ile = ileWykladowcow(elListy);
    if(ile){
    printf("Podaj kogo chcesz usunąć od 0 do %d", ile-1);
    int wybor = wczytajDodatniInt();
wybierz:
        if( wybor >= ile){
            printf("Podales niepoprawne dane, podaj poprawne:\n");
            goto wybierz;
        }
        ElListyWykladowcy* wsk = elListy;
        ElListyWykladowcy* adres = NULL;
        if(wsk == NULL){
            printf("Lista jest pusta\n");
            return;
        }
        else{
            int i=0;
            while(wsk != NULL){
                if(i == wybor){
                    adres=wsk;
                    break;
                }
                wsk=wsk->nast;
                ++i;
            }
            char przelozony[60];
            strcpy(przelozony,adres->element.imie);
            strcat(strcat(przelozony," "), adres->element.nazwisko);
            wsk = elListy;
            while(wsk != NULL){
                if(!strcmp(wsk->element.przelozony,przelozony)){
                    strcpy(wsk->element.przelozony,"BRAK");
                }
                wsk=wsk->nast;
            }
            wsk = elListy;
            if(elListy != adres){
                while(wsk->nast != adres ){
                    wsk=wsk->nast;
                }
                wsk->nast = adres->nast;
                free(adres);
            }
            else{
                if(ile == 1){
                *adresWsk = NULL;
                free(wsk);
                }
                else{
                    *adresWsk = adres->nast;
                }
            }
        }
    }
}

void sortPoImieWykl(ElListyWykladowcy* elListy){
    int ile = ileWykladowcow(elListy);
    ElListyWykladowcy* wsk = elListy;
    if(wsk == NULL){
        printf("Lista jest pusta\n");
    }
    else{
        int i=0;
        while(i<ile){
            ElListyWykladowcy* wsk = elListy;
            while(wsk->nast != NULL){
                if(strcmp(wsk->element.imie, wsk->nast->element.imie)>0){
                    wykladowca pomoc1 = wsk->element;
                    wsk->element = wsk->nast->element;
                    wsk->nast->element = pomoc1;
                }
                wsk=wsk->nast;
            }
            ++i;
        }
        wypiszWykladowce(elListy);
    }
}

void sortPoNazwWykl(ElListyWykladowcy* elListy){
    int ile = ileWykladowcow(elListy);
    ElListyWykladowcy* wsk = elListy;
    if(wsk == NULL){
        printf("Lista jest pusta\n");
    }
    else{
        int i=0;
        while(i<ile){
            ElListyWykladowcy* wsk = elListy;
            while(wsk->nast != NULL){
                if(strcmp(wsk->element.nazwisko, wsk->nast->element.nazwisko)>0){
                    wykladowca pomoc1 = wsk->element;
                    wsk->element = wsk->nast->element;
                    wsk->nast->element = pomoc1;
                }
                wsk=wsk->nast;
            }
            ++i;
        }
        wypiszWykladowce(elListy);
    }
}

void sortPoPrzelWykl(ElListyWykladowcy* elListy){
    int ile = ileWykladowcow(elListy);
    ElListyWykladowcy* wsk = elListy;
    if(wsk == NULL){
        printf("Lista jest pusta\n");
    }
    else{
        int i=0;
        while(i<ile){
            ElListyWykladowcy* wsk = elListy;
            while(wsk->nast != NULL){
                if(strcmp(wsk->element.przelozony, wsk->nast->element.przelozony)>0){
                    wykladowca pomoc1 = wsk->element;
                    wsk->element = wsk->nast->element;
                    wsk->nast->element = pomoc1;
                }
                wsk=wsk->nast;
            }
            ++i;
        }
        wypiszWykladowce(elListy);
    }
}

void sortWykladowcow( ElListyWykladowcy* elListy){
    if(ileWykladowcow(elListy)){
        printf("Po czym chcesz sortować: 0 - imie, 1 - nazwisko, 2 - przelozony\n");
        int wybor;
        wybor = wczytajDodatniInt();
        switch (wybor) {
            case 0:
                sortPoImieWykl(elListy);
                break;
            case 1:
                sortPoNazwWykl(elListy);
                break;
            case 2:
                sortPoPrzelWykl(elListy);
                break;
            default:
                printf("Podales niepoprawne dane\n");
                break;
        }
    }
    else{
        printf("Lista jest pusta\n");
    }
}

ElListyWykladowcy* operacjeWykladowcy(ElListyWykladowcy* glowaWykl){
    char wybor;
    do{
        puts("Wybierz operację: d - dodaj u - usuń w - wyświetl s - sortuj c - cofnij do poprzedniego menu");
        scanf(" %c", &wybor);
        czyscBufor();
        wykladowca nowyWykladowca;
        switch( wybor ){
            case 'd':
                nowyWykladowca = dodajWykladowce(glowaWykl);
                glowaWykl = dodajElWykladowcy(glowaWykl, nowyWykladowca);
                break;
            case 'u':
                usunWykladowce(glowaWykl, &glowaWykl);
                break;
            case 'w':
                wypiszWykladowce(glowaWykl);
                break;
            case 's':
                sortWykladowcow(glowaWykl);
                break;
            case 'c':
                puts("Wracam do poprzedniego menu.");
                break;
            default:
                puts("Nie ma takiej operacji.");
        }
    }while(wybor != 'c');
    return glowaWykl;
}
