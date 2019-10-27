#ifndef __SERIALOUT_CPP__
#define __SERIALOUT_CPP__

#include "serialout.h"

void serialout(int x){
    char c[5];
    int i = 3;
    if(x < 0) {
        c[0] = '-';
        x *= -1;
    }
    else c[0] = '+';
    while(i > 0){
        switch (x % 10){
            case 0: c[i] = '0'; break;
            case 1: c[i] = '1'; break;
            case 2: c[i] = '2'; break;
            case 3: c[i] = '3'; break;
            case 4: c[i] = '4'; break;
            case 5: c[i] = '5'; break;
            case 6: c[i] = '6'; break;
            case 7: c[i] = '7'; break;
            case 8: c[i] = '8'; break;
            case 9: c[i] = '9'; break;
        }
        i--;
        x /= 10;
    }
    Serial1.write(c, 5);
}

#endif