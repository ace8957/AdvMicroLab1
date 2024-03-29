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

int i1, i2, i3;
long x1, x2, x3;
long long y1, y2, y3;
float f1, f2, f3;
long double d1, d2, d3;

int main() {
    T1CON = 0x8000; // enable Timer1 1:1 with main clock
    i1 = 0x1234; // testing integers (16-bit)
    i2 = 0x5678;
    TMR1 = 0; // clear the timer
    i3 = i1 / i2;
    x1 = 0x01234567L; // testing long integers (32-bit)
    x2 = 0x89ABCDEFL;
    TMR1 = 0; // clear the timer
    x3 = x1 / x2;
    y1 = 0x0123456789ABCDEFLL; // testing 64-bit integers
    y2 = 0xFEDCBA9876543210LL;
    TMR1 = 0; // clear the timer
    y3 = y1 / y2;
    f1 = 12.34; // testing single precision floating point
    f2 = 56.78;
    TMR1 = 0; // clear the timer
    f3 = f1 / f2;
    d1 = 12.34L; // testing double precision floating point
    d2 = 56.78L;
    TMR1 = 0;
    d3 = d1 / d2;
    return 0;
} // main