#include "arduino-serial-lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <poll.h>

int main()
{
    struct pollfd pfds[2];
    char *port_0= "/dev/ttyACM0";
    char *port_1= "/dev/ttyACM1";
    char buf[256]; 
    int RACE, RADIO;
    int ret, res;

    int serial_0 = open(port_0, O_RDWR | O_NOCTTY | O_NONBLOCK);
    int serial_1 = open(port_1, O_RDWR | O_NOCTTY | O_NONBLOCK);

    if (serial_0 < 0 || serial_1 < 0 ) {
        // perror
        perror("error opening one of ttyACM0 and ttyACM1\n"); // should probably distinguish bw cases
        exit(-1);
    }
    
    pfds[0].fd= serial_0;
    pfds[1].fd= serial_1;

    ret= poll(pfds, 1, 3000);
    if (ret > 0) {
        if (pfds[0].revents != 0) {
            RACE= 0;
            RADIO= 1;
        }
        else {
            RADIO= 1;
            RACE= 0;
        }

        for (;;) {
            res= read(pfds[RACE].fd, buf, sizeof(buf)); // make this into read until new line
            write(pfds[RADIO].fd, buf, sizeof(buf));
        }
    }

    else {
        // perror
        perror("unable to read from tty; aborting\n");
        exit(-2);
    }
    
    // "handshake" --> determine which ttyACM{0, 1} is RC/radio
    // init ttyACM0 and ttyACM1
    // send greeting to both devices
    // read a message from both devices, with timeout
    // whichever sent more than 0 bytes is the RC!
    // read until newline from RC
    // send most recent message to radio
}