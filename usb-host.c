#include "arduino-serial-lib.h"

int main()
{
    char buf[256];
    int RACE, RADIO;
    // "handshake" --> determine which ttyACM{0, 1} is RC/radio
    // init ttyACM0 and ttyACM1
    // send greeting to both devices
    // read a message from both devices, with timeout
    // whichever sent more than 0 bytes is the RC!

    for (;;) {
        // read until newline from RC
        // send most recent message to radio
    }
}