
// muuttujia
#define VX_VARIABLE_HEATING_STATUS 0x07 //
#define VX_VARIABLE_IO_08 0x08
#define VX_VARIABLE_FAN_SPEED 0x29
#define VX_VARIABLE_CO2_HI 0x2B
#define VX_VARIABLE_CO2_LO 0x2C
#define VX_VARIABLE_RH1 0x2F
#define VX_VARIABLE_RH2 0x30
#define VX_VARIABLE_T_OUTSIDE 0x32
#define VX_VARIABLE_T_OUTGOING 0x33
#define VX_VARIABLE_T_INSIDE 0x34
#define VX_VARIABLE_T_INCOMING 0x35
#define VX_VARIABLE_FAULT_CODE 0x36
#define VX_VARIABLE_FLAGS_06 0x71
#define VX_VARIABLE_SWITCH_REMAINING 0x79
#define VX_VARIABLE_STATUS 0xA3
#define VX_VARIABLE_HEATING_TARGET 0xA4
#define VX_VARIABLE_FAN_SPEED_MAX 0xA5
#define VX_VARIABLE_FAN_SPEED_MIN 0xA9
#define VX_VARIABLE_SERVICE_PERIOD 0xA6
#define VX_VARIABLE_PROGRAM 0xAA
#define VX_VARIABLE_SERVICE_REMAINING 0xAB
#define VX_VARIABLE_T_HEAT_BYPASS 0xAF

// lippumuuttuja variable A3
#define VX_STATUS_FLAG_POWER 0x01           // biti 0 lukee/kirjoittaa
#define VX_STATUS_FLAG_CO2 0x02             // biti 1 lukee/kirjoittaa
#define VX_STATUS_FLAG_RH 0x04              // biti 2 lukee/kirjoittaa
#define VX_STATUS_FLAG_HEATING_MODE 0x08    // biti 3 lukee/kirjoittaa
#define VX_STATUS_FLAG_FILTER 0x10          // biti 4 lukee
#define VX_STATUS_FLAG_HEATING 0x20         // biti 5 lukee
#define VX_STATUS_FLAG_FAULT 0x40           // biti 6 lukee
#define VX_STATUS_FLAG_SERVICE 0x80         // biti 7 lukee       

// lippumuuttuja variable 08
#define VX_08_FLAG_SUMMER_MODE 0x02
#define VX_08_FLAG_ERROR_RELAY 0x04
#define VX_08_FLAG_MOTOR_IN 0x08
#define VX_08_FLAG_FRONT_HEATING 0x10
#define VX_08_FLAG_MOTOR_OUT 0x20
#define VX_08_FLAG_EXTRA_FUNC 0x40 // takkakytkin/turbo

// trubo/takkakytkin
#define VX_EXTRA_FUNC_COUNTER 0x79 // aikaa jäljellä minutteina

// lippumuuttuja variable 06
#define VX_06_FIREPLACE_FLAG_ACTIVATE 0x20 // lue ja lähetä
#define VX_06_FIREPLACE_FLAG_IS_ACTIVE 0x40 // 0 = ei päällä, 1 = päällä

// lippumuuttuja ohjelman muuttujia
#define VX_PROGRAM_SWITCH_TYPE 0x20

// ohjelman muuttujia
#define PROGRAM_VARIABLE_BOOST 0x20 // turbo = 0, takkakytkin = 1

// tuulettimen nopeudet
#define VX_FAN_SPEED_1 0x01
#define VX_FAN_SPEED_2 0x03
#define VX_FAN_SPEED_3 0x07
#define VX_FAN_SPEED_4 0x0F
#define VX_FAN_SPEED_5 0x1F
#define VX_FAN_SPEED_6 0x3F
#define VX_FAN_SPEED_7 0x7F
#define VX_FAN_SPEED_8 0xFF
#define VX_MIN_FAN_SPEED 1
#define VX_MAX_FAN_SPEED 8
