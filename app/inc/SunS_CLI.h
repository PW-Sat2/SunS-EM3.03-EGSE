#ifndef APP_INC_SUNS_CLI_H_
#define APP_INC_SUNS_CLI_H_

#include "SoftI2C.h"
#include "array.h"
#include "Serial.h"
#include <string.h>
#include "CLI.h"
#include "SunS_Access.h"


template <typename T>
class Measure: hal::libs::CLI::Command {
 public:
    Measure(SunS_Access<T> SunS) : hal::libs::CLI::Command("measure"), SunS{SunS} {
    }
    void callback(const hal::libs::array_view<char *> & parameters)
            override {

        SunS.triggerMeasurement(atoi(parameters[0]), atoi(parameters[1]));
        // wait for conversion end
        for (uint8_t i = 0; i < atoi(parameters[0]); i++) {
        _delay_ms(3);
        }
        _delay_ms(2);

        SunS.printRegistersLine();

    }
 private:
    SunS_Access<T> SunS;
};

#endif  // APP_INC_SUNS_CLI_H_
