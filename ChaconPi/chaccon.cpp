#include <wiringPi.h>
#include "MyDom433.h"
#include <iostream>

using namespace std;

bool controller_id[] = {0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0}; //Saisissez le code de la télécommande
bool device_code[] = {0, 0, 0, 0}; //Saisissez le code de l'appareil à utiliser

// émetteur (pin 4) et led (pin 13)
MyDom433 easy(7, 0, controller_id);

int main(void)
{
    if(wiringPiSetup() == -1)
    {
        return -1;
    }

    for(;;)
    {
        easy.deviceOn(device_code);    // turn on device
        delay(100);
        easy.deviceOn(device_code);    // turn on device
        cout << "On" << endl;
        delay(3000);        // wait 3 sec

        easy.deviceOff(device_code);   // turn it off again
        delay(100);
        easy.deviceOff(device_code);   // turn it off again
        cout << "Off" << endl;
        delay(3000);        // wait 3 sec
    }
}

