/* 
 * File:   loop.c
 * Author: Adam
 *
 * Created on January 14, 2014, 8:50 PM
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

#define DELAY 16000
int main() {
    // init control registers
    TRISA = 0xff00; // all PORTA as output
    T1CON = 0x8030; // TMR1 on, prescale 1:256 Tclk/2
    int porta_tmp = 0x76;

    // main application loop
    while (1) {
        PORTA = porta_tmp;
        //1. turn pin 0-7 on and wait for 1/4 of a second
        TMR1 = 0;
        while (TMR1 < DELAY) {
        }
        // 2. turn all pin off and wait for a 1/4 of a second
        PORTA = 0;
        TMR1 = 0;
        if(porta_tmp & 0x80) {
            porta_tmp = porta_tmp << 1;
            porta_tmp |= 1;
        }
        else {
            porta_tmp = porta_tmp << 1;
        }
        while (TMR1 < DELAY) {
        }
    } // main loop
} // main

