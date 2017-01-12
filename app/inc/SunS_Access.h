#ifndef APP_INC_SUNS_ACCESS_H_
#define APP_INC_SUNS_ACCESS_H_

#include "SoftI2C.h"
#include "array.h"
#include "Serial.h"
#include <string.h>

namespace SunS_Access_Types {
   #pragma pack(push, 1)
    union registerDesc {
        struct {
            uint8_t STATUS;
            uint8_t WHO_AM_I;
            uint16_t AZIMUTH_ANGLE;
            uint16_t ELEVATION_ANGLE;
            int16_t TEMPERATURE_A;
            int16_t TEMPERATURE_B;
            int16_t TEMPERATURE_C;
            int16_t TEMPERATURE_D;
            int16_t TEMPERATURE_STRUCT;
            uint16_t ALS_1A_VL_RAW;
            uint16_t ALS_1B_VL_RAW;
            uint16_t ALS_1C_VL_RAW;
            uint16_t ALS_1D_VL_RAW;
            uint16_t ALS_2A_VL_RAW;
            uint16_t ALS_2B_VL_RAW;
            uint16_t ALS_2C_VL_RAW;
            uint16_t ALS_2D_VL_RAW;
            uint16_t ALS_3A_VL_RAW;
            uint16_t ALS_3B_VL_RAW;
            uint16_t ALS_3C_VL_RAW;
            uint16_t ALS_3D_VL_RAW;
            uint16_t ALS_1A_IR_RAW;
            uint16_t ALS_1B_IR_RAW;
            uint16_t ALS_1C_IR_RAW;
            uint16_t ALS_1D_IR_RAW;
            uint16_t ALS_2A_IR_RAW;
            uint16_t ALS_2B_IR_RAW;
            uint16_t ALS_2C_IR_RAW;
            uint16_t ALS_2D_IR_RAW;
            uint16_t ALS_3A_IR_RAW;
            uint16_t ALS_3B_IR_RAW;
            uint16_t ALS_3C_IR_RAW;
            uint16_t ALS_3D_IR_RAW;
            uint16_t TEMPERATURE_A_RAW;
            uint16_t TEMPERATURE_B_RAW;
            uint16_t TEMPERATURE_C_RAW;
            uint16_t TEMPERATURE_D_RAW;
            uint16_t TEMPERATURE_STRUCT_RAW;
            uint16_t ALS_STATUS;
            uint8_t ALS_1A_ID;
            uint8_t ALS_1B_ID;
            uint8_t ALS_1C_ID;
            uint8_t ALS_1D_ID;
            uint8_t ALS_2A_ID;
            uint8_t ALS_2B_ID;
            uint8_t ALS_2C_ID;
            uint8_t ALS_2D_ID;
            uint8_t ALS_3A_ID;
            uint8_t ALS_3B_ID;
            uint8_t ALS_3C_ID;
            uint8_t ALS_3D_ID;
        } registerMap;
        uint8_t registerMapArray[88];
    };
    #pragma pack(pop)
} // namespace SunS_Access_Types

template<typename i2c_dev>
class SunS_Access {
 public:
    SunS_Access(i2c_dev i2c) : i2c{i2c} {
    }

    void triggerMeasurement(uint8_t time, uint8_t gain) {
        hal::libs::array<uint8_t, 2> trigger = {time, gain};
        this->i2c.write(trigger);
    }


    hal::libs::array<uint8_t, 88> plainDataRead() {
        hal::libs::array<uint8_t, 88> arr;
        this->i2c.read(arr);
        return arr;
    }

    SunS_Access_Types::registerDesc registersRead() {
        hal::libs::array<uint8_t, 88> arr = this->plainDataRead();
        SunS_Access_Types::registerDesc registermap;
        memcpy(registermap.registerMapArray, arr.elems, 88);
        return registermap;
    }

    void printRegistersTable() {
        SunS_Access_Types::registerDesc registermap = this->registersRead();
        // i know it's painful
        printf("Register Map of SunS\r\n");
        printf("====================\r\n");
        printf("STATUS = \t %u\r\n", registermap.registerMap.STATUS);
        printf("WHO_AM_I = \t %u\r\n", registermap.registerMap.WHO_AM_I);
        printf("AZIMUTH_ANGLE = \t %u\r\n", registermap.registerMap.AZIMUTH_ANGLE);
        printf("ELEVATION_ANGLE = \t %u\r\n", registermap.registerMap.ELEVATION_ANGLE);
        printf("TEMPERATURE_A = \t %d\r\n", registermap.registerMap.TEMPERATURE_A);
        printf("TEMPERATURE_B = \t %d\r\n", registermap.registerMap.TEMPERATURE_B);
        printf("TEMPERATURE_C = \t %d\r\n", registermap.registerMap.TEMPERATURE_C);
        printf("TEMPERATURE_D = \t %d\r\n", registermap.registerMap.TEMPERATURE_D);
        printf("TEMPERATURE_STRUCT = \t %d\r\n", registermap.registerMap.TEMPERATURE_STRUCT);
        printf("ALS_1A_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_1A_VL_RAW);
        printf("ALS_1B_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_1B_VL_RAW);
        printf("ALS_1C_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_1C_VL_RAW);
        printf("ALS_1D_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_1D_VL_RAW);
        printf("ALS_2A_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_2A_VL_RAW);
        printf("ALS_2B_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_2B_VL_RAW);
        printf("ALS_2C_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_2C_VL_RAW);
        printf("ALS_2D_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_2D_VL_RAW);
        printf("ALS_3A_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_3A_VL_RAW);
        printf("ALS_3B_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_3B_VL_RAW);
        printf("ALS_3C_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_3C_VL_RAW);
        printf("ALS_3D_VL_RAW = \t %u\r\n", registermap.registerMap.ALS_3D_VL_RAW);
        printf("ALS_1A_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_1A_IR_RAW);
        printf("ALS_1B_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_1B_IR_RAW);
        printf("ALS_1C_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_1C_IR_RAW);
        printf("ALS_1D_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_1D_IR_RAW);
        printf("ALS_2A_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_2A_IR_RAW);
        printf("ALS_2B_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_2B_IR_RAW);
        printf("ALS_2C_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_2C_IR_RAW);
        printf("ALS_2D_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_2D_IR_RAW);
        printf("ALS_3A_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_3A_IR_RAW);
        printf("ALS_3B_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_3B_IR_RAW);
        printf("ALS_3C_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_3C_IR_RAW);
        printf("ALS_3D_IR_RAW = \t %u\r\n", registermap.registerMap.ALS_3D_IR_RAW);
        printf("TEMPERATURE_A_RAW = \t %u\r\n", registermap.registerMap.TEMPERATURE_A_RAW);
        printf("TEMPERATURE_B_RAW = \t %u\r\n", registermap.registerMap.TEMPERATURE_B_RAW);
        printf("TEMPERATURE_C_RAW = \t %u\r\n", registermap.registerMap.TEMPERATURE_C_RAW);
        printf("TEMPERATURE_D_RAW = \t %u\r\n", registermap.registerMap.TEMPERATURE_D_RAW);
        printf("TEMPERATURE_STRUCT_RAW = \t %u\r\n", registermap.registerMap.TEMPERATURE_STRUCT_RAW);
        printf("ALS_STATUS = \t %u\r\n", registermap.registerMap.ALS_STATUS);
        printf("ALS_1A_ID = \t %u\r\n", registermap.registerMap.ALS_1A_ID);
        printf("ALS_1B_ID = \t %u\r\n", registermap.registerMap.ALS_1B_ID);
        printf("ALS_1C_ID = \t %u\r\n", registermap.registerMap.ALS_1C_ID);
        printf("ALS_1D_ID = \t %u\r\n", registermap.registerMap.ALS_1D_ID);
        printf("ALS_2A_ID = \t %u\r\n", registermap.registerMap.ALS_2A_ID);
        printf("ALS_2B_ID = \t %u\r\n", registermap.registerMap.ALS_2B_ID);
        printf("ALS_2C_ID = \t %u\r\n", registermap.registerMap.ALS_2C_ID);
        printf("ALS_2D_ID = \t %u\r\n", registermap.registerMap.ALS_2D_ID);
        printf("ALS_3A_ID = \t %u\r\n", registermap.registerMap.ALS_3A_ID);
        printf("ALS_3B_ID = \t %u\r\n", registermap.registerMap.ALS_3B_ID);
        printf("ALS_3C_ID = \t %u\r\n", registermap.registerMap.ALS_3C_ID);
        printf("ALS_3D_ID = \t %u\r\n", registermap.registerMap.ALS_3D_ID);
        printf("====================\r\n");
    }

    void printRegistersLine() {
        SunS_Access_Types::registerDesc registermap = this->registersRead();

        printf("%u;", registermap.registerMap.STATUS);
        printf("%u;", registermap.registerMap.WHO_AM_I);
        printf("%u;", registermap.registerMap.AZIMUTH_ANGLE);
        printf("%u;", registermap.registerMap.ELEVATION_ANGLE);
        printf("%d;", registermap.registerMap.TEMPERATURE_A);
        printf("%d;", registermap.registerMap.TEMPERATURE_B);
        printf("%d;", registermap.registerMap.TEMPERATURE_C);
        printf("%d;", registermap.registerMap.TEMPERATURE_D);
        printf("%d;", registermap.registerMap.TEMPERATURE_STRUCT);
        printf("%u;", registermap.registerMap.ALS_1A_VL_RAW);
        printf("%u;", registermap.registerMap.ALS_1B_VL_RAW);
        printf("%u;", registermap.registerMap.ALS_1C_VL_RAW);
        printf("%u;", registermap.registerMap.ALS_1D_VL_RAW);
        printf("%u;", registermap.registerMap.ALS_2A_VL_RAW);
        printf("%u;", registermap.registerMap.ALS_2B_VL_RAW);
        printf("%u;", registermap.registerMap.ALS_2C_VL_RAW);
        printf("%u;", registermap.registerMap.ALS_2D_VL_RAW);
        printf("%u;", registermap.registerMap.ALS_3A_VL_RAW);
        printf("%u;", registermap.registerMap.ALS_3B_VL_RAW);
        printf("%u;", registermap.registerMap.ALS_3C_VL_RAW);
        printf("%u;", registermap.registerMap.ALS_3D_VL_RAW);
        printf("%u;", registermap.registerMap.ALS_1A_IR_RAW);
        printf("%u;", registermap.registerMap.ALS_1B_IR_RAW);
        printf("%u;", registermap.registerMap.ALS_1C_IR_RAW);
        printf("%u;", registermap.registerMap.ALS_1D_IR_RAW);
        printf("%u;", registermap.registerMap.ALS_2A_IR_RAW);
        printf("%u;", registermap.registerMap.ALS_2B_IR_RAW);
        printf("%u;", registermap.registerMap.ALS_2C_IR_RAW);
        printf("%u;", registermap.registerMap.ALS_2D_IR_RAW);
        printf("%u;", registermap.registerMap.ALS_3A_IR_RAW);
        printf("%u;", registermap.registerMap.ALS_3B_IR_RAW);
        printf("%u;", registermap.registerMap.ALS_3C_IR_RAW);
        printf("%u;", registermap.registerMap.ALS_3D_IR_RAW);
        printf("%u;", registermap.registerMap.TEMPERATURE_A_RAW);
        printf("%u;", registermap.registerMap.TEMPERATURE_B_RAW);
        printf("%u;", registermap.registerMap.TEMPERATURE_C_RAW);
        printf("%u;", registermap.registerMap.TEMPERATURE_D_RAW);
        printf("%u;", registermap.registerMap.TEMPERATURE_STRUCT_RAW);
        printf("%u;", registermap.registerMap.ALS_STATUS);
        printf("%u;", registermap.registerMap.ALS_1A_ID);
        printf("%u;", registermap.registerMap.ALS_1B_ID);
        printf("%u;", registermap.registerMap.ALS_1C_ID);
        printf("%u;", registermap.registerMap.ALS_1D_ID);
        printf("%u;", registermap.registerMap.ALS_2A_ID);
        printf("%u;", registermap.registerMap.ALS_2B_ID);
        printf("%u;", registermap.registerMap.ALS_2C_ID);
        printf("%u;", registermap.registerMap.ALS_2D_ID);
        printf("%u;", registermap.registerMap.ALS_3A_ID);
        printf("%u;", registermap.registerMap.ALS_3B_ID);
        printf("%u;", registermap.registerMap.ALS_3C_ID);
        printf("%u", registermap.registerMap.ALS_3D_ID);
        printf("\r\n");
    }

 private:
    i2c_dev i2c;
};

#endif  // APP_INC_SUNS_ACCESS_H_
