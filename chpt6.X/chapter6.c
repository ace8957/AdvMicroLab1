#include "xc.h"
#include <p24fxxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

_CONFIG1(JTAGEN_OFF // disable JTAG interface
        & GCP_OFF // disable general code protection
        & GWRP_OFF // disable flash write protection
        & ICS_PGx2 // ICSP interface (2=default)
        & FWDTEN_OFF) // disable watchdog timer
_CONFIG2(IESO_OFF // two speed start up disabled
        & FCKSM_CSDCMD // disable clk-switching/monitor
        & FNOSC_PRIPLL // primary oscillator: enable PLL
        & POSCMOD_XT); // primary oscillator: XT mode

char full_name [] = "Adam Franklin Wilford";

int main(void) {
    char *tmp;
    char sp2[8];
    short len = strlen(full_name);
    short tmplen = 0;
    if (full_name != NULL) {
        //place the first letter of the first name in the second-to-last position
        sp2[6] = tolower(full_name[0]);

        //iterate until we find the space between firs and middle names
        tmp = full_name;
        while (*tmp != ' ') {
            tmp++;
            tmplen++; //keep track to make sure we aren't overflowing
        }
        //we have found the space between names
        tmp++; //move tmp pointer to first character of middle name
        tmplen++;
        //place the first letter of the middle name in the last place in sp2
        sp2[7] = tolower(*tmp);

        //iterate again until we find the beginning of the last name
        while (*tmp != ' ') {
            tmp++;
            tmplen++;
        }
        //move to point to the first letter of the last name
        tmp++;
        tmplen++;

        //copy the next six characters (or until end of array) into the
        //appropriate positions in the sp2 array
        int count;
        for (count = 0; (count < 6) && (tmplen < len); ++count) {
            if (count == 0) {
                sp2[count] = tolower(*tmp);
            } else {
                sp2[count] = *tmp;
            }
            tmp++;
            tmplen++;
        }
    }
    return 0;
}