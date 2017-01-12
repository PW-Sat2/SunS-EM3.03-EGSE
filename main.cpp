#include <util/delay.h>
#include "SoftI2C.h"
#include "boards.h"
#include "array.h"
#include "DigitalIO.h"
#include "Serial.h"
#include <string.h>
#include "SunS_Access.h"

using namespace hal;

int main() {
    hal::Serial0.init(9600, hal::STDIO::ENABLE);
    DigitalIO sda(32), scl(1);
    sda.init(DigitalIO::INPUT_PULLUP);
    scl.init(DigitalIO::INPUT_PULLUP);

    using SoftI2C = hal::SoftI2C<32, 1>;
    SoftI2C::init();
    constexpr hal::I2C_Device<SoftI2C> dev{0x1E};
    using SoftI2CDevice = hal::I2C_Device<SoftI2C>;

    SunS_Access<SoftI2CDevice> SunS(dev);

    uint8_t integration_time = 38;
    uint8_t gain = 0;

    printf("Start!\r\n");
    while (true) {
        SunS.triggerMeasurement(integration_time, gain);

        // wait for conversion end
        for (uint8_t i = 0; i < integration_time; i++) {
        _delay_ms(3);
        }
        _delay_ms(2);

        SunS_Access_Types::registerDesc test = SunS.registersRead();

        printf("ALS_1A_RAW = %u\r\n", test.registerMap.ALS_1A_VL_RAW);
        printf("LM60 = %u\r\n", test.registerMap.TEMPERATURE_STRUCT);
        printf("RTD_A = %u\r\n\r\n", test.registerMap.TEMPERATURE_A);

        SunS.printRegistersTable();
        printf("\r\n\r\n");
        SunS.printRegistersLine();

        _delay_ms(5000);
    }
}
