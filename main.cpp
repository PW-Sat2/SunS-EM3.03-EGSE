#include <util/delay.h>
#include "SoftI2C.h"
#include "boards.h"
#include "array.h"
#include "DigitalIO.h"
#include "Serial.h"
#include <string.h>
#include "SunS_Access.h"
#include "CLI.h"
#include "SunS_CLI.h"

using namespace hal;

using softi2c = hal::SoftI2C<32, 1>;
using softi2cdevice = hal::I2C_Device<softi2c>;
constexpr softi2cdevice dev{0x1E};
Measure<softi2cdevice> measure(dev);

int main() {
    hal::Serial0.init(9600, hal::STDIO::ENABLE);
    DigitalIO sda(32), scl(1);
    sda.init(DigitalIO::INPUT_PULLUP);
    scl.init(DigitalIO::INPUT_PULLUP);

    softi2c::init();
    
    static char buf[100];
    static uint8_t cnt = 0;

    printf("Start!\r\n");
    while (true) {
        while (true) {
            uint8_t now = Serial0.read_byte();
            buf[cnt++] = now;
            if (now == '\r') {
                buf[cnt-1] = 0;
                cnt = 0;
                break;
            }
        }
        hal::libs::CLI::parse_line(buf);
    }
}
