#include "xc.h"
#include <p24fxxxx.h>
#include <rtcc.h>
#include <stdio.h>

_CONFIG1(JTAGEN_OFF // disable JTAG interface
        & GCP_OFF // disable general code protection
        & GWRP_OFF // disable flash write protection
        & ICS_PGx2 // ICSP interface (2=default)
        & FWDTEN_OFF) // disable watchdog timer
_CONFIG2(IESO_OFF // two speed start up disabled
        & FCKSM_CSDCMD // disable clk-switching/monitor
        & FNOSC_PRIPLL // primary oscillator: enable PLL
        & POSCMOD_XT); // primary oscillator: XT mode

// 1. RTCC interrupt service routine

void _ISR _RTCCInterrupt(void) {
    // 1.1 clear the interrupt flag
    _RTCIF = 0;
    PORTA = 0xff;
    // 1.2 your code here, will be executed only once a year
    // or once every 365 x 24 x 60 x 60 x 16,000,000 MCU cycles
    // that is once every 504,576,000,000,000 MCU cycles
} // RTCCInterrupt

int main() {
    TRISA = 0xff00; // all PORTB as output
    RtccInitClock();
    mRtccOn();
    RtccWrOn();
    rtccTimeDate TD = {0x06, 0x20, // year
        0x01, 0x11, // day, month
        0x12, 0x03, // hour, weekday
        0x30, 0x01}; // sec, min
    RtccWriteTimeDate(&TD, FALSE);
    RtccSetAlarmRpt(RTCC_RPT_SEC, FALSE);
    mRtccSetInt(TRUE);
    while (1) {
        if (mRtccIsOn())
            PORTA = 0xff;
    }
    return 0;
} // main
