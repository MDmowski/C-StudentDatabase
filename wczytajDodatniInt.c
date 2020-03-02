//
//  wczytajDodatniInt.c
//  gra_w_zycie
//
//  Created by Maciej Dmowski on 19/10/2018.
//  Copyright © 2018 Maciej Dmowski. All rights reserved.
//
//wczytywanie dodatniej wartości liczbowej - zabezpieczenie przed literami oraz wartościami ujemnymi
#include "wczytajDodatniInt.h"
#include "czyscBufor.h"

int wczytajDodatniInt( void ){
    int liczba;
    liczba = 0;
    while( 1 != scanf( "%d", &liczba ) || liczba < 0 ){
        puts( "Podałeś niepoprawne dane. Wpisz poprawne" );
        czyscBufor();
        liczba = 0;
    }
    czyscBufor();
    return liczba ;
}
