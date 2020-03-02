//
//  czyscBufor.c
//  gra_w_zycie
//
//  Created by Maciej Dmowski on 18/10/2018.
//  Copyright © 2018 Maciej Dmowski. All rights reserved.
//

#include "czyscBufor.h"

void czyscBufor ( void ) {
    char c;
    do
        c = getchar();
    while ( c != '\n' && c != EOF );
}
