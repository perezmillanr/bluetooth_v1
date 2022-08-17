#include "mbed.h"

// Create a DigitalOutput object to toggle an LED whenever data is received.
static  DigitalOut led1(LED1);
static  DigitalOut led2(LED2);
static  DigitalOut led3(LED3);

// Create a UnbufferedSerial object with a default baud rate.
static UnbufferedSerial serial_port(USBTX, USBRX);

void on_rx_interrupt()
{
    char c;
    // Read the data to clear the receive interrupt.
    if (serial_port.read(&c, 1)) {
        // Echo the input back to the terminal.
        serial_port.write(&c, 1);

        switch(c){
            case '1':
                led1 = !led1;
                break;
            case '2':
                led2 = !led2;
                break;
            case '3':
                led3 = !led3;
                break;
            default:
                break;
        }

    }
}

int main(void)
{
    // Set desired properties (9600-8-N-1).
    serial_port.baud(9600);
    serial_port.format(
        /* bits */ 8,
        /* parity */ SerialBase::None,
        /* stop bit */ 1
    );

    // Register a callback to process a Rx (receive) interrupt.
    serial_port.attach(&on_rx_interrupt, SerialBase::RxIrq);
}
