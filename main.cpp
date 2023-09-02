#include "mbed.h"
#include "arm_book_lib.h"

//=====[Biblioteca necesaria para usar la estructura gpio_t]========
#include "hal/gpio_api.h"

int main()
{
    gpio_t gpioGasDetector;
    gpio_t gpioOverTempDetector;
    gpio_t gpioAlarmOffButton;
    gpio_t gpioAlarmLed;
    gpio_init_in_ex(&gpioGasDetector, D2, PullDown);
    gpio_init_in_ex(&gpioOverTempDetector, D2, PullDown);
    gpio_init_in(&gpioAlarmOffButton, BUTTON1);
    gpio_init_out(&gpioAlarmLed, LED1);
    
    gpio_write(&gpioAlarmLed, OFF);

    bool alarmState = OFF;

    while (true) {

        if ( gpio_read(&gpioGasDetector) || gpio_read(&gpioOverTempDetector) ) {
            alarmState = ON;
            printf("%s%s\n", "El sensor de gas está ", gpio_read(&gpioGasDetector) ? "ACTIVADO" : "DESACTIVADO");
            printf("%s%s\n", "El sensor de sobretemperatura está ", gpio_read(&gpioOverTempDetector) ? "ACTIVADO" : "DESACTIVADO");
            printf("%s\n" , "El estado de la alarma es ACTIVADO.");
        }

        gpio_write(&gpioAlarmLed, alarmState);

        if ( gpio_read(&gpioAlarmOffButton) ) {
            alarmState = OFF;
            printf("%s\n" , "El estado de la alarma es DESACTIVADO.");
        }
    }
}