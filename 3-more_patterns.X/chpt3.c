#include "xc.h"
#include <p24fxxxx.h>
#define SHORT_DELAY 100
#define LONG_DELAY 800

_CONFIG1(JTAGEN_OFF // disable JTAG interface
        & GCP_OFF // disable general code protection
        & GWRP_OFF // disable flash write protection
        & ICS_PGx2 // ICSP interface (2=default)
        & FWDTEN_OFF) // disable watchdog timer
_CONFIG2(IESO_OFF // two speed start up disabled
        & FCKSM_CSDCMD // disable clk-switching/monitor
        & FNOSC_PRIPLL // primary oscillator: enable PLL
        & POSCMOD_XT) // primary oscillator: XT mode

// 1. define timing constant

// 2. declare and initialize an array with the message bitmap
char bitmap[30] = {
    0b11111000, // A
    0b00100110,
    0b00100011,
    0b00100110,
    0b11111000,
    0b00000000, //empty
    0b00000000, //empty
    0b11111111, // D
    0b11000011,
    0b11000011,
    0b01111110,
    0b00000000,
    0b00000000, //empty
    0b00000000, //empty
    0b11111000, // A
    0b00100110,
    0b00100011,
    0b00100110,
    0b11111000,
    0b00000000, //empty
    0b00000000, //empty
    0b11111111, // M
    0b00000110,
    0b00001100,
    0b00011000,
    0b00001100,
    0b00000110,
    0b11111111,
    0b00000000, //empty
    0b00000000, //empty
};
// 3. the main program

int main() {
    // 3.1 variable declarations
    int i = 0; // i will serve as the index
    // 3.2 initialization
    TRISA = 0; // all PORTA as output
    T1CON = 0x8030; // TMR1 on, prescale 1:256 Tclk/2
    // 3.3 the main loop
    while (1) {
        // 3.3.1 display loop, hand moving to the right
        for (i = 0; i < 30; i++) { // 3.3.1.1 update the LEDs
            PORTA = bitmap[i];
            // 3.3.1.2 short pause
            TMR1 = 0;
            while (TMR1 < SHORT_DELAY) {
            }
        } // for i
        // 3.3.2 long pause, hand moving back to the left
        PORTA = 0; // turn LEDs off
        TMR1 = 0;
        while (TMR1 < (LONG_DELAY)) {
        }
    } // main loop
} // main
