//
//  przedmioty.c
//  BazaStudentow
//
//  Created by Maciej Dmowski on 19/11/2018.
//  Copyright © 2018 Maciej Dmowski. All rights reserved.
//
#include "przedmioty.h"

ElListyPrzedmioty* dodajElPrzedmioty( ElListyPrzedmioty* glowa, przedmiot el ){
    if(strcmp(el.nazwa, "BLAD")){
    ElListyPrzedmioty* nowyElListy = malloc( sizeof( ElListyPrzedmioty ) );
    if( NULL == nowyElListy )
        exit ( EXIT_FAILURE );
    nowyElListy->element = el;
    nowyElListy->nast = glowa;
    return nowyElListy ;
    }
    else
        return glowa;
}

void zwolnijPrzedmiot( ElListyPrzedmioty* elListy ){
    ElListyPrzedmioty* poprzedni = NULL;
    while( elListy ){
        poprzedni = elListy;
        elListy = elListy->nast;
        free ( poprzedni );
    }
}

int ilePrzedmiotow(ElListyPrzedmioty* elListy){
    ElListyPrzedmioty* wsk = elListy;
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

void wypiszPrzedmiot( ElListyPrzedmioty* elListy){
    ElListyPrzedmioty* wsk = elListy;
    if(wsk == NULL){
        printf("Lista jest pusta\n");
    }
    else{
        printf("Lp. Nazwa Prowadzący Studenci \n");
        int i=0;
        while(wsk != NULL){
            printf("%d %s  %s  %s\n", i, wsk->element.nazwa, wsk->element.prowadzacy, wsk->element.studenci);
            wsk=wsk->nast;
            ++i;
        }
    }
}

przedmiot dodajPrzedmiot( ElListyPrzedmioty* elPrzedmioty, ElListyWykladowcy* elWykladowcy){
    if(elWykladowcy != NULL){
        przedmiot nowy;
    imie:
        printf("Podaj nazwe przedmiotu\n");
        if(!scanf("%50s", nowy.nazwa)){
            czyscBufor();
            printf("Podaj poprawne dane\n");
            goto imie;
        }
        int ile = ileWykladowcow(elWykladowcy);
        ElListyWykladowcy* wsk = elWykladowcy;
        wykladowca tab[ile];
        ElListyWykladowcy* wskaznik[ile];
            for(int n=0; n<ile; n++){
                wskaznik[n] = wsk;
                strcpy(tab[n].imie, wsk->element.imie);
                strcpy(tab[n].nazwisko, wsk->element.nazwisko);
                strcpy(tab[n].przelozony, wsk->element.przelozony);
                strcpy(tab[n].przedmioty, wsk->element.przedmioty);
                wsk=wsk->nast;
            }
            for(int n=0; n < ile; ++n){
                printf("%d %s %s\n", n+1, tab[n].imie, tab[n].nazwisko);
            }
        wybierz:
            printf("Wybierz prowadzacego - podaj numer od 1 do %d\n", ile);
            int wybor = wczytajDodatniInt();
            if( wybor > ile){
                goto wybierz;
            }
            else{
                    char prowadzacy[60];
                    strcpy(prowadzacy, tab[wybor-1].imie);
                    strcat(strcat(prowadzacy," "), tab[wybor-1].nazwisko);
                    strcpy(nowy.prowadzacy, prowadzacy);
                if(!strcmp(wskaznik[wybor-1]->element.przedmioty,""))
                {
                    strcpy(wskaznik[wybor-1]->element.przedmioty, nowy.nazwa);
                }
                else{
                    char przedmioty[500];
                    strcpy(przedmioty, wskaznik[wybor-1]->element.przedmioty);
                    strcat(strcat(przedmioty, " "), nowy.nazwa);
                    strcpy(wskaznik[wybor-1]->element.przedmioty, przedmioty);
                }
            }
        strcpy(nowy.studenci, "BRAK");
        return nowy;
    }
    else{
        printf("Brak wykladowcow. Dodaj wykladowcow aby dodac przedmiot.\n");
        const przedmiot blad = {"BLAD","BLAD","BLAD"};
        return blad;
    }
}

void usunPrzedmiot(ElListyPrzedmioty* elPrzedmioty, ElListyPrzedmioty** adresWsk, ElListyWykladowcy* elWykladowcy){
    wypiszPrzedmiot(elPrzedmioty);
    int ile = ilePrzedmiotow(elPrzedmioty);
    if(ile){
        printf("Podaj jaki przedmiot chcesz usunąć od 0 do %d\n", ile-1);
        int wybor = wczytajDodatniInt();
    wybierz:
        if( wybor >= ile){
            printf("Podales niepoprawne dane, podaj poprawne:\n");
            goto wybierz;
        }
        ElListyPrzedmioty* wsk = elPrzedmioty;
        ElListyPrzedmioty* adres = NULL;
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
            
            
            char przedmioty[500];
            char nazwaPrzedmiotu[50];
            strcpy(nazwaPrzedmiotu, adres->element.nazwa);
            ElListyWykladowcy* wskWykladowca = elWykladowcy;
            while(wskWykladowca != NULL){
                strcpy(przedmioty, wskWykladowca->element.przedmioty);
                char nowePrzedmioty[500] = "";
                char prowadzacy[60];
                strcpy(prowadzacy, wskWykladowca->element.imie);
                strcat(strcat(prowadzacy," "), wskWykladowca->element.nazwisko);
                if(!strcmp(prowadzacy, elPrzedmioty->element.prowadzacy)){
                    char poczatek[500]="";
                    strcpy(przedmioty, wskWykladowca->element.przedmioty);
                    int j=0;
                    unsigned long dlugoscPrzedmioty = strlen(przedmioty);
                    while(j < dlugoscPrzedmioty){
                        char sprawdzenie[500] = "";
                        while(przedmioty[j] != 32){
                            strncat(sprawdzenie,&przedmioty[j],1);
                            ++j;
                        }
                        ++j;
                        if(!strcmp(sprawdzenie, nazwaPrzedmiotu)){
                            strcpy(nowePrzedmioty, poczatek);
                            strcat(nowePrzedmioty," ");
                            while( j < dlugoscPrzedmioty){
                                strncat(nowePrzedmioty,&przedmioty[j],1);
                                ++j;
                            }
                        }
                        else{
                            strcat(poczatek, sprawdzenie);
                        }
                    }
                    //printf("%s",nowePrzedmioty);
                    strcpy(wskWykladowca->element.przedmioty,nowePrzedmioty);
                }
                wskWykladowca=wskWykladowca->nast;
            }
            wsk = elPrzedmioty;
            if(elPrzedmioty != adres){
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

void sortPoNazwPrzed(ElListyPrzedmioty* elListy){
    int ile = ilePrzedmiotow(elListy);
    ElListyPrzedmioty* wsk = elListy;
    if(wsk == NULL){
        printf("Lista jest pusta\n");
    }
    else{
        int i=0;
        while(i<ile){
            ElListyPrzedmioty* wsk = elListy;
            while(wsk->nast != NULL){
                if(strcmp(wsk->element.nazwa, wsk->nast->element.nazwa)>0){
                    przedmiot pomoc1 = wsk->element;
                    wsk->element = wsk->nast->element;
                    wsk->nast->element = pomoc1;
                }
                wsk=wsk->nast;
            }
            ++i;
        }
        wypiszPrzedmiot(elListy);
    }
}

void sortPoProwPrzed(ElListyPrzedmioty* elListy){
    int ile = ilePrzedmiotow(elListy);
    ElListyPrzedmioty* wsk = elListy;
    if(wsk == NULL){
        printf("Lista jest pusta\n");
    }
    else{
        int i=0;
        while(i<ile){
            ElListyPrzedmioty* wsk = elListy;
            while(wsk->nast != NULL){
                if(strcmp(wsk->element.prowadzacy, wsk->nast->element.prowadzacy)>0){
                    przedmiot pomoc1 = wsk->element;
                    wsk->element = wsk->nast->element;
                    wsk->nast->element = pomoc1;
                }
                wsk=wsk->nast;
            }
            ++i;
        }
        wypiszPrzedmiot(elListy);
    }
}

void sortPrzedmioty( ElListyPrzedmioty* elListy){
    if(ilePrzedmiotow(elListy)){
        printf("Po czym chcesz sortować: 0 - nazwa, 1 - prowadzacy\n");
        int wybor;
        wybor = wczytajDodatniInt();
        switch (wybor) {
            case 0:
                sortPoNazwPrzed(elListy);
                break;
            case 1:
                sortPoProwPrzed(elListy);
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

ElListyPrzedmioty* operacjePrzedmioty(ElListyPrzedmioty* glowaPrzed, ElListyWykladowcy* glowaWykl){
    char wybor;
    do{
        puts("Wybierz operację: d - dodaj u - usuń w - wyświetl s - sortuj c - cofnij sie");
        scanf(" %c", &wybor);
        czyscBufor();
        przedmiot nowyPrzedmiot;
        switch(wybor){
            case 'd':
                nowyPrzedmiot = dodajPrzedmiot(glowaPrzed, glowaWykl);
                glowaPrzed = dodajElPrzedmioty(glowaPrzed, nowyPrzedmiot);
                break;
            case 'u':
                usunPrzedmiot(glowaPrzed, &glowaPrzed, glowaWykl);
                break;
            case 'w':
                wypiszPrzedmiot(glowaPrzed);
                break;
            case 's':
                sortPrzedmioty(glowaPrzed);
                break;
            case 'c':
                puts("Wracam do poprzedniego menu");
                break;
            default:
                puts("Nie ma takiej operacji.");
        }
    }while(wybor != 'c');
    return glowaPrzed;
}
