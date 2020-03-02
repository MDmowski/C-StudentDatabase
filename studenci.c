//
//  przedmioty.c
//  BazaStudentow
//
//  Created by Maciej Dmowski on 19/11/2018.
//  Copyright © 2018 Maciej Dmowski. All rights reserved.
//

#include "studenci.h"
#include "wczytajDodatniInt.h"

ElListyStudenci* dodajElStudenci( ElListyStudenci* glowa, student el ){
    if(strcmp(el.imie, "BLAD")){
        ElListyStudenci* nowyElListy = malloc( sizeof( ElListyStudenci ) );
        if( NULL == nowyElListy )
            exit ( EXIT_FAILURE );
        nowyElListy->element = el;
        nowyElListy->nast = glowa;
        return nowyElListy ;
    }
    else
        return glowa;
}

void zwolnijStudent( ElListyStudenci* elListy ){
    ElListyStudenci* poprzedni = NULL;
    while( elListy ){
        poprzedni = elListy;
        elListy = elListy->nast;
        free ( poprzedni );
    }
}

int ileStudent(ElListyStudenci* elListy){
    ElListyStudenci* wsk = elListy;
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

void wypiszStudent( ElListyStudenci* elListy){
    ElListyStudenci* wsk = elListy;
    if(wsk == NULL){
        printf("Lista jest pusta\n");
    }
    else{
        printf("Lp. Imie Nazwisko Nr Ideksu Przedmioty \n");
        int i=0;
        while(wsk != NULL){
            printf("%d %s  %s  %d %s\n", i, wsk->element.imie, wsk->element.nazwisko, wsk->element.indeks, wsk->element.przedmioty);
            wsk=wsk->nast;
            ++i;
        }
    }
}

student dodajStudent( ElListyStudenci* elStudenci, ElListyPrzedmioty* elPrzedmioty){
    if(elPrzedmioty != NULL){
        student nowy;
    imie:
        printf("Podaj imie studenta\n");
        if(!scanf("%30s", nowy.imie)){
            czyscBufor();
            printf("Podaj poprawne dane\n");
            goto imie;
        }
    nazwisko:
        printf("Podaj nazwisko studenta\n");
        if(!scanf("%30s", nowy.nazwisko)){
            czyscBufor();
            printf("Podaj poprawne dane\n");
            goto nazwisko;
        }
        nowy.indeks = rand()%900000+100000;
        int ile = ilePrzedmiotow(elPrzedmioty);
        ElListyPrzedmioty* wsk = elPrzedmioty;
        przedmiot tab[ile];
        ElListyPrzedmioty* wskaznik[ile];
        bool czyWybrany[ile];
        for(int n=0; n<ile; n++){
            wskaznik[n] = wsk;
            strcpy(tab[n].nazwa, wsk->element.nazwa);
            strcpy(tab[n].prowadzacy, wsk->element.prowadzacy);
            wsk=wsk->nast;
            czyWybrany[n]=0;
        }
        bool stop = 1;
        char przedmioty[500] = "";
        int licznik = 0;
        while(stop){
        for(int n=0; n < ile; ++n){
            printf("%d %s %s\n", n+1, tab[n].nazwa, tab[n].prowadzacy);
        }
            if(licznik == ile){
                puts("Wszystkie przedmioty zostały wybrane");
                break;
            }
        wybierz:
            printf("Wybierz przedmiot - podaj numer od 1 do %d\n", ile);
            int wybor = wczytajDodatniInt();
            if( wybor > ile || czyWybrany[wybor-1] || wybor <= 0){
                puts("Przedmiot już wybrany!");
                goto wybierz;
            }
            else{
                licznik++;
                czyWybrany[wybor-1] = 1;
                if(!strcmp(przedmioty,""))
                    strcat(strcat(przedmioty, tab[wybor-1].nazwa),",");
                else
                    strcat(strcat(strcat(przedmioty," "), tab[wybor-1].nazwa),",");
                char studenci[500];
                if(!strcmp(wskaznik[wybor-1]->element.studenci, "BRAK")){
                    strcpy(studenci, nowy.imie);
                    strcat(strcat(strcat(studenci, " "), nowy.nazwisko),",");
                    strcpy(wskaznik[wybor-1]->element.studenci, studenci);
                }
                else{
                    strcpy(studenci, wskaznik[wybor-1]->element.studenci);
                    strcat(strcat(studenci, " "), nowy.imie);
                    strcat(strcat(strcat(studenci, " "), nowy.nazwisko),",");
                    printf("%s", studenci);
                    strcpy(wskaznik[wybor-1]->element.studenci, studenci);
                }
                printf("Czy chcesz wybrać następny przedmiot? t-tak, n-nie");
                char odp = getchar();
                if(odp == 'n')
                    stop=0;
            }
        }
            strcpy(nowy.przedmioty, przedmioty);
        return nowy;
    }
    else{
        printf("Brak przedmiotow. Dodaj przedmioty aby dodac studentow.\n");
        const student blad = {"BLAD","BLAD",0, "BLAD"};
        return blad;
    }
}


void usunStudent(ElListyStudenci* elStudenci, ElListyStudenci** adresWsk, ElListyPrzedmioty* elPrzedmioty){
    wypiszStudent(elStudenci);
    int ile = ileStudent(elStudenci);
    if(ile){
        printf("Podaj studenta, którego chcesz usunąć od 0 do %d\n", ile-1);
        int wybor = wczytajDodatniInt();
    wybierz:
        if( wybor >= ile){
            printf("Podales niepoprawne dane, podaj poprawne:\n");
            goto wybierz;
        }
        ElListyStudenci* wsk = elStudenci;
        ElListyStudenci* adres = NULL;
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
            
            char studenci[500];
            char przedmioty[500];
            strcpy(przedmioty, adres->element.przedmioty);
            ElListyPrzedmioty* wskPrzedmioty = elPrzedmioty;
            while(wskPrzedmioty != NULL){
                char nowiStudenci[500] = "";
                char student[61];
                strcpy(student, adres->element.imie);
                strcat(strcat(student," "), adres->element.nazwisko);
                //printf("%s\n",student);
                    char poczatek[500]="";
                    strcpy(studenci, wskPrzedmioty->element.studenci);
                    int j=0;
                    unsigned long dlugoscStudenci = strlen(studenci);
                    //printf("%s\n",studenci);
                    while(j < dlugoscStudenci){
                        //printf("%d ", j);
                        char sprawdzenie[500] = "";
                        while(studenci[j] != 44){
                            strncat(sprawdzenie,&studenci[j],1);
                            ++j;
                        }
                        ++j;
                        if(!strcmp(sprawdzenie, student)){
                            strcpy(nowiStudenci, poczatek);
                            strcat(nowiStudenci,", ");
                            while( j < dlugoscStudenci){
                                strncat(nowiStudenci,&studenci[j],1);
                                ++j;
                            }
                        }
                        else{
                            strcat(poczatek, sprawdzenie);
                        }
                    }
                
                if(strlen(nowiStudenci)>1){
                    if(strcmp(nowiStudenci,", "))
                        strcpy(wskPrzedmioty->element.studenci,nowiStudenci);
                    else{
                        strcpy(wskPrzedmioty->element.studenci,"BRAK");
                    }
                }
                else{
                    strcpy(wskPrzedmioty->element.studenci, studenci);
                }
                wskPrzedmioty=wskPrzedmioty->nast;
            }
        
        
            wsk = elStudenci;
            if(elStudenci != adres){
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

void sortPoImieStudent(ElListyStudenci* elListy){
    int ile = ileStudent(elListy);
    ElListyStudenci* wsk = elListy;
    if(wsk == NULL){
        printf("Lista jest pusta\n");
    }
    else{
        int i=0;
        while(i<ile){
            ElListyStudenci* wsk = elListy;
            while(wsk->nast != NULL){
                if(strcmp(wsk->element.imie, wsk->nast->element.imie)>0){
                    student pomoc1 = wsk->element;
                    wsk->element = wsk->nast->element;
                    wsk->nast->element = pomoc1;
                }
                wsk=wsk->nast;
            }
            ++i;
        }
        wypiszStudent(elListy);
    }
}

void sortPoNazwStudent(ElListyStudenci* elListy){
    int ile = ileStudent(elListy);
    ElListyStudenci* wsk = elListy;
    if(wsk == NULL){
        printf("Lista jest pusta\n");
    }
    else{
        int i=0;
        while(i<ile){
            ElListyStudenci* wsk = elListy;
            while(wsk->nast != NULL){
                if(strcmp(wsk->element.nazwisko, wsk->nast->element.nazwisko)>0){
                    student pomoc1 = wsk->element;
                    wsk->element = wsk->nast->element;
                    wsk->nast->element = pomoc1;
                }
                wsk=wsk->nast;
            }
            ++i;
        }
        wypiszStudent(elListy);
    }
}

void sortPoIndeksStudent(ElListyStudenci* elListy){
    int ile = ileStudent(elListy);
    ElListyStudenci* wsk = elListy;
    if(wsk == NULL){
        printf("Lista jest pusta\n");
    }
    else{
        int i=0;
        while(i<ile){
            ElListyStudenci* wsk = elListy;
            while(wsk->nast != NULL){
                if(wsk->element.indeks > wsk->nast->element.indeks){
                    student pomoc1 = wsk->element;
                    wsk->element = wsk->nast->element;
                    wsk->nast->element = pomoc1;
                }
                wsk=wsk->nast;
            }
            ++i;
        }
        wypiszStudent(elListy);
    }
}

void sortStudenci(ElListyStudenci* elListy){
    if(ileStudent(elListy)){
        printf("Po czym chcesz sortować: 0 - imie, 1 - nazwisko, 2 - indeks\n");
        int wybor;
        wybor = wczytajDodatniInt();
        switch (wybor) {
            case 0:
                sortPoImieStudent(elListy);
                break;
            case 1:
                sortPoNazwStudent(elListy);
                break;
            case 2:
                sortPoIndeksStudent(elListy);
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

ElListyStudenci* operacjeStudenci(ElListyStudenci* glowaStudenci, ElListyPrzedmioty* glowaPrzedmioty){
    char wybor;
    do{
        puts("Wybierz operację: d - dodaj u - usuń w - wyświetl s - sortuj c - cofnij sie");
        scanf(" %c", &wybor);
        czyscBufor();
        student nowyStudent;
        switch( wybor ){
            case 'd':
                nowyStudent = dodajStudent(glowaStudenci, glowaPrzedmioty);
                glowaStudenci = dodajElStudenci(glowaStudenci, nowyStudent);
                break;
            case 'u':
                usunStudent(glowaStudenci, &glowaStudenci, glowaPrzedmioty);
                break;
            case 'w':
                wypiszStudent(glowaStudenci);
                break;
            case 's':
                sortStudenci(glowaStudenci);
                break;
            case 'c':
                puts("Wracam do poprzedniego menu");
                break;
            default:
                puts("Nie ma takiej operacji.");
        }
    }while(wybor != 'c');
    return glowaStudenci;
}
