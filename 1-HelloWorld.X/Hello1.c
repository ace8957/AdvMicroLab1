/*
 * File:   Hello1.c
 * Author: Adam
 *
 * Created on January 11, 2014, 12:26 PM
 */


#include "xc.h"
#include <p24fxxxx.h>

_CONFIG1(JTAGEN_OFF // disable JTAG interface
        & GCP_OFF // disable general code protection
        & GWRP_OFF // disable flash write protection
        & ICS_PGx2 // ICSP interface (2=default)
        & FWDTEN_OFF) // disable watchdog timer
_CONFIG2(IESO_OFF // two speed start up disabled
        & FCKSM_CSDCMD // disable clk-switching/monitor
        & FNOSC_PRIPLL // primary oscillator: enable PLL
        & POSCMOD_XT) // primary oscillator: XT mode

int main(void) {
    PORTA = 0x76;
    //AD1PCFG = 0xffff; // all PORTA as digital
    TRISA = 0; // all PORTA as output
    return 0;
}
