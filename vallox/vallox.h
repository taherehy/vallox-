#pragma once

#include <queue>
#include <vector>
#include <unordered_map>
#include "vallox_protocol.h"
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/climate/climate.h"
#include "esphome/components/number/number.h"
#include "esphome/components/button/button.h"
#include "esphome/components/select/select.h"

using std::queue;
using std::vector;
using std::unordered_map;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

#define VX_MSG_LENGTH 6
#define VX_MSG_DOMAIN 0x01
#define VX_MSG_POLL_BYTE 0x00
#define NOT_SET -999
#define SLOW_QUERY_INTERVAL 300000 // millisekunteina (5 min)
#define FAST_QUERY_INTERVAL 5000 // millisekunteina (5 s)
#define RETRY_INTERVAL 4200 // millisekunteina (4,2 s)
#define SEND_INTERVAL 300 // millisekunteina, viestien lähettämisen välinen aika
#define VX_MAX_RETRIES 10
#define VX_REPLY_WAIT_TIME 10
#define SEND_QUEUE_MAX_DEPTH 50  // Väylälle kirjoittamista odottavien jonotettujen viestien enimmäismäärä

// lähettäjät ja vastaanottajat
#define VX_MSG_MAINBOARD_1 0x11
#define VX_MSG_MAINBOARDS 0x10
#define VX_MSG_PANEL_1 0x21 // Tämän paneelin osoite, ei saa olla sama kuin muilla paneeleilla
#define VX_MSG_THIS_PANEL 0x22 // Tämän paneelin osoite, ei saa olla sama kuin muilla paneeleilla
#define VX_MSG_PANELS 0x20

#define CO2_LIFE_TIME_MS 2000 // Enimmäisaika, jona LO- ja HI-tavuja pidetään samana arvona

// Vallox-puhaltimen nopeuksien (1-8) muunnostaulukko
const uint8_t vxFanSpeeds[] = {
  VX_FAN_SPEED_1,
  VX_FAN_SPEED_2,
  VX_FAN_SPEED_3,
  VX_FAN_SPEED_4,
  VX_FAN_SPEED_5,
  VX_FAN_SPEED_6,
  VX_FAN_SPEED_7,
  VX_FAN_SPEED_8
};

// Vallox NTC -lämpötilan muunnostaulukko
const int8_t vxTemps[] = {
  -74, -70, -66, -62, -59, -56, -54, -52, -50, -48, // 0x00 - 0x09
  -47, -46, -44, -43, -42, -41, -40, -39, -38, -37, // 0x0a - 0x13
  -36, -35, -34, -33, -33, -32, -31, -30, -30, -29, // 0x14 - 0x1d
  -28, -28, -27, -27, -26, -25, -25, -24, -24, -23, // 0x1e - 0x27
  -23, -22, -22, -21, -21, -20, -20, -19, -19, -19, // 0x28 - 0x31
  -18, -18, -17, -17, -16, -16, -16, -15, -15, -14, // 0x32 - 0x3b
  -14, -14, -13, -13, -12, -12, -12, -11, -11, -11, // 0x3c - 0x45
  -10, -10, -9, -9, -9, -8, -8, -8, -7, -7,         // 0x46 - 0x4f
  -7, -6, -6, -6, -5, -5, -5, -4, -4, -4,           // 0x50 - 0x59
  -3, -3, -3, -2, -2, -2, -1, -1, -1, -1,           // 0x5a - 0x63
  0,  0,  0,  1,  1,  1,  2,  2,  2,  3,            // 0x64 - 0x6d
  3,  3,  4,  4,  4,  5,  5,  5,  5,  6,            // 0x6e - 0x77
  6,  6,  7,  7,  7,  8,  8,  8,  9,  9,            // 0x78 - 0x81
  9, 10, 10, 10, 11, 11, 11, 12, 12, 12,            // 0x82 - 0x8b
  13, 13, 13, 14, 14, 14, 15, 15, 15, 16,           // 0x8c - 0x95
  16, 16, 17, 17, 18, 18, 18, 19, 19, 19,           // 0x96 - 0x9f
  20, 20, 21, 21, 21, 22, 22, 22, 23, 23,           // 0xa0 - 0xa9
  24, 24, 24, 25, 25, 26, 26, 27, 27, 27,           // 0xaa - 0xb3
  28, 28, 29, 29, 30, 30, 31, 31, 32, 32,           // 0xb4 - 0xbd
  33, 33, 34, 34, 35, 35, 36, 36, 37, 37,           // 0xbe - 0xc7
  38, 38, 39, 40, 40, 41, 41, 42, 43, 43,           // 0xc8 - 0xd1
  44, 45, 45, 46, 47, 48, 48, 49, 50, 51,           // 0xd2 - 0xdb
  52, 53, 53, 54, 55, 56, 57, 59, 60, 61,           // 0xdc - 0xe5
  62, 63, 65, 66, 68, 69, 71, 73, 75, 77,           // 0xe6 - 0xef
  79, 81, 82, 86, 90, 93, 97, 100, 100, 100,        // 0xf0 - 0xf9
  100, 100, 100, 100, 100, 100                      // 0xfa - 0xff
};


// HA climate -käyttöliittymän oletusarvot:

#define CLIMATE_MIN_TEMPERATURE 10
#define CLIMATE_MAX_TEMPERATURE 30
#define CLIMATE_TEMPERATURE_STEP 1

#define SWITCH_TYPE_ACTION_FIREPLACE "fireplace"
#define SWITCH_TYPE_ACTION_BOOST     "boost"


// puhaltimen tilojen oletusnimet (1-8)
static constexpr const char *const FAN_MODES[] = {"1", "2", "3", "4", "5", "6", "7", "8"};


#define RECEIVED_IDLE                        0x00
#define RECEIVED_SYSTEM_AWAITING_SENDER      0x01
#define RECEIVED_SENDER_AWAITING_RECIPIENT   0x02
#define RECEIVED_RECIPIENT_AWAITING_VARIABLE 0x03
#define RECEIVED_VARIABLE_AWAITING_DATA      0x04
#define RECEIVED_DATA_AWAITING_CHECKSUM      0x05
#define SENT_PACKET_AWAITING_CHECKSUM        0x11



/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


namespace esphome {
	namespace vallox {

		class ValloxVentilation;
		class ValloxVentilationHeatBypassNum;
		class ValloxVentilationServiceResetBtn;
		class ValloxVentilationSwitchTypeSelectSel;
		class ValloxVentilationFanSpeedMaxNum;
		class ValloxVentilationFanSpeedMinNum;
		class ValloxVentilationSwitchBtn;

/////////////////////////////////////////////////////////////////////////////////////////

		class ValloxVentilationHeatBypassNum : public number::Number, public Component {
			public:
				void set_vallox_parent(ValloxVentilation *parent) { this->parent_ = parent; }

			protected:
				void control(float value) override;

				ValloxVentilation *parent_;
		};

/////////////////////////////////////////////////////////////////////////////////////////

		class ValloxVentilationServiceResetBtn : public button::Button, public Component {
			public:
				void set_vallox_parent(ValloxVentilation *parent) { this->parent_ = parent; }

			protected:
				void press_action() override;

				ValloxVentilation *parent_;
		};

/////////////////////////////////////////////////////////////////////////////////////////

		class ValloxVentilationSwitchTypeSelectSel : public select::Select, public Component {
			public:
				void set_vallox_parent(ValloxVentilation *parent) { this->parent_ = parent; }

			protected:
				void control(const std::string &value) override;

			ValloxVentilation *parent_;
		};

/////////////////////////////////////////////////////////////////////////////////////////

		class ValloxVentilationFanSpeedMaxNum : public number::Number, public Component {
			public:
				void set_vallox_parent(ValloxVentilation *parent) { this->parent_ = parent; }

			protected:
				void control(float value) override;

				ValloxVentilation *parent_;
		};

/////////////////////////////////////////////////////////////////////////////////////////

		class ValloxVentilationFanSpeedMinNum : public number::Number, public Component {
			public:
				void set_vallox_parent(ValloxVentilation *parent) { this->parent_ = parent; }

			protected:
				void control(float value) override;

				ValloxVentilation *parent_;
		};

/////////////////////////////////////////////////////////////////////////////////////////

		class ValloxVentilationSwitchBtn : public button::Button, public Component {
			public:
			void set_vallox_parent(ValloxVentilation *parent) { this->parent_ = parent; }

			protected:
			void press_action() override;

			ValloxVentilation *parent_;
		};

/////////////////////////////////////////////////////////////////////////////////////////


		class ValloxVentilation : public Component, public climate::Climate, public uart::UARTDevice {
			public:
				void setup() override;
				void dump_config() override;
				void loop() override;

				float get_setup_priority() const override { return esphome::setup_priority::LATE; }


				// numeroanturit
				void set_fan_speed_sensor(sensor::Sensor *sensor)            { this->fan_speed_sensor_            = sensor; }
				void set_fan_speed_default_sensor(sensor::Sensor *sensor)    { this->fan_speed_default_sensor_    = sensor; }
				void set_temperature_target_sensor(sensor::Sensor *sensor)   { this->temperature_target_sensor_   = sensor; }
				void set_temperature_outside_sensor(sensor::Sensor *sensor)  { this->temperature_outside_sensor_  = sensor; }
				void set_temperature_inside_sensor(sensor::Sensor *sensor)   { this->temperature_inside_sensor_   = sensor; }
				void set_temperature_outgoing_sensor(sensor::Sensor *sensor) { this->temperature_outgoing_sensor_ = sensor; }
				void set_temperature_incoming_sensor(sensor::Sensor *sensor) { this->temperature_incoming_sensor_ = sensor; }
				void set_humidity_1_sensor(sensor::Sensor *sensor)           { this->humidity_1_sensor_           = sensor; }
				void set_humidity_2_sensor(sensor::Sensor *sensor)           { this->humidity_2_sensor_           = sensor; }
				void set_co2_sensor(sensor::Sensor *sensor)                  { this->co2_sensor_                  = sensor; }
				void set_service_period_sensor(sensor::Sensor *sensor)       { this->service_period_sensor_       = sensor; }
				void set_service_remaining_sensor(sensor::Sensor *sensor)    { this->service_remaining_sensor_    = sensor; }
				void set_switch_remaining_sensor(sensor::Sensor *sensor)     { this->switch_remaining_sensor_     = sensor; }
				// tekstianturit
				void set_switch_type_text_sensor(text_sensor::TextSensor *sensor) { this->switch_type_text_sensor_ = sensor; }
				void set_fault_condition_text_sensor(text_sensor::TextSensor *sensor) { this->fault_condition_text_sensor_ = sensor; }
				// binäärianturit
				void set_status_on_binary_sensor(binary_sensor::BinarySensor *sensor)        { this->status_on_binary_sensor_        = sensor; }
				void set_status_motor_in_binary_sensor(binary_sensor::BinarySensor *sensor)  { this->status_motor_in_binary_sensor_  = sensor; }
				void set_status_motor_out_binary_sensor(binary_sensor::BinarySensor *sensor) { this->status_motor_out_binary_sensor_ = sensor; }
				void set_service_needed_binary_sensor(binary_sensor::BinarySensor *sensor)   { this->service_needed_binary_sensor_   = sensor; }
				void set_switch_active_binary_sensor(binary_sensor::BinarySensor *sensor)    { this->switch_active_binary_sensor_    = sensor; }
				void set_heating_binary_sensor(binary_sensor::BinarySensor *sensor)          { this->heating_binary_sensor_          = sensor; }
				void set_heating_mode_binary_sensor(binary_sensor::BinarySensor *sensor)     { this->heating_mode_binary_sensor_     = sensor; }
				void set_front_heating_binary_sensor(binary_sensor::BinarySensor *sensor)    { this->front_heating_binary_sensor_    = sensor; }
				void set_summer_mode_binary_sensor(binary_sensor::BinarySensor *sensor)      { this->summer_mode_binary_sensor_      = sensor; }
				void set_problem_binary_sensor(binary_sensor::BinarySensor *sensor)          { this->problem_binary_sensor_          = sensor; }
				void set_error_relay_binary_sensor(binary_sensor::BinarySensor *sensor)      { this->error_relay_binary_sensor_      = sensor; }
				// numero-ohjaimet
				void set_heat_bypass_number(number::Number *number)   { this->heat_bypass_number_ = number; }
				void set_fan_speed_max_number(number::Number *number) { this->fan_speed_max_number_ = number; }
				void set_fan_speed_min_number(number::Number *number) { this->fan_speed_min_number_ = number; }
				// painikeohjaimet
				void set_service_reset_button(button::Button *button) { this->service_reset_button_ = button; }
				void set_switch_button(button::Button *button)        { this->switch_button_        = button; }
				// valinta-asetusohjaimet
				void set_switch_type_select_select(select::Select *select) { this->switch_type_select_select_ = select; }


				// muiden luokkien kutsumat valloxesp-funktiot
				unsigned char convCel2Ntc(int cel);
				void setVariable(unsigned char variable, unsigned char value);
				void setFlags(unsigned char element, unsigned char bitpos, bool value);
				void requestVariable(unsigned char variable);
				uint service_period = 1; // asetettu 1 kuukauteen, jotta mahdolliset ongelmat huomattaisiin helpommin

			private:

				unsigned long		iots;  // viimeisimmän I/O-toiminnan aikaleima
				unsigned long		ionow; // nykyinen aikaleima
				unsigned long		ioretryts; // viimeisin retryVariables-kutsu
				unsigned long		ioslowqueryts; // viimeisin kysely muuttujille, jotka voivat muuttua ilman ilmoitusta
				unsigned long		iofastqueryts; // viimeisin kysely muuttujille, jotka voivat muuttua ilman ilmoitusta
				unsigned long		iosendts;  // viimeisimmän lähetetyn viestin aikaleima
				uint				iostate = RECEIVED_IDLE;
				unsigned char				iomessage_recv_byte;
				unsigned char				iomessage_recv[VX_MSG_LENGTH-1]; // Tarkistussummatavua ei sisällytetä, se validoidaan vastaanoton aikana
				vector<unsigned char>		iomessage_send;
				queue<vector<unsigned char>>	iomessage_send_queue;
				queue<vector<unsigned char>>	iomessage_send_command_queue;
				unsigned char		iochecksum = 0;
				uint				iomessage_send_retries = 0;

				unordered_map<unsigned char,unsigned char> buffer;

				unsigned long buffer_co2_hi_ts = 0;
				unsigned long buffer_co2_lo_ts = 0;

				void retryVariables();
				void clearChecksum();
				void addChecksum(unsigned char newbyte);
				unsigned char getChecksum();
				unsigned char getChecksum(vector<unsigned char> newmessage);	
				void sendMessage(vector<unsigned char> newmessage);
				uint getState();
				void setState(uint newstate);
				void updateState(bool ionewdata);
				void setVariable(unsigned char variable, unsigned char value, unsigned char target);
				void decodeMessage(const unsigned char message[]);
				void decodeFlags(unsigned char element, unsigned char program);
				int convNtc2Cel(unsigned char ntc);
				int convHex2Rh(unsigned char hex);
				unsigned char convFanSpeed2Hex(int fan);
				int convHex2FanSpeed(unsigned char hex);


			protected:
				void control(const climate::ClimateCall &call) override;
				climate::ClimateTraits traits() override;
				sensor::Sensor *fan_speed_sensor_{nullptr};
				sensor::Sensor *fan_speed_default_sensor_{nullptr};
				sensor::Sensor *temperature_target_sensor_{nullptr};
				sensor::Sensor *temperature_outside_sensor_{nullptr};
				sensor::Sensor *temperature_inside_sensor_{nullptr};
				sensor::Sensor *temperature_outgoing_sensor_{nullptr};
				sensor::Sensor *temperature_incoming_sensor_{nullptr};
				sensor::Sensor *humidity_1_sensor_{nullptr};
				sensor::Sensor *humidity_2_sensor_{nullptr};
				sensor::Sensor *co2_sensor_{nullptr};
				sensor::Sensor *service_period_sensor_{nullptr};
				sensor::Sensor *service_remaining_sensor_{nullptr};
				sensor::Sensor *switch_remaining_sensor_{nullptr};
				text_sensor::TextSensor *switch_type_text_sensor_{nullptr};
				text_sensor::TextSensor *fault_condition_text_sensor_{nullptr};
				binary_sensor::BinarySensor *status_on_binary_sensor_{nullptr};
				binary_sensor::BinarySensor *status_motor_in_binary_sensor_{nullptr};
				binary_sensor::BinarySensor *status_motor_out_binary_sensor_{nullptr};
				binary_sensor::BinarySensor *service_needed_binary_sensor_{nullptr};
				binary_sensor::BinarySensor *switch_active_binary_sensor_{nullptr};
				binary_sensor::BinarySensor *heating_binary_sensor_{nullptr};
				binary_sensor::BinarySensor *heating_mode_binary_sensor_{nullptr};
				binary_sensor::BinarySensor *front_heating_binary_sensor_{nullptr};
				binary_sensor::BinarySensor *summer_mode_binary_sensor_{nullptr};
				binary_sensor::BinarySensor *problem_binary_sensor_{nullptr};
				binary_sensor::BinarySensor *error_relay_binary_sensor_{nullptr};
				number::Number *heat_bypass_number_{nullptr};
				number::Number *fan_speed_max_number_{nullptr};
				number::Number *fan_speed_min_number_{nullptr};
				button::Button *service_reset_button_{nullptr};
				button::Button *switch_button_{nullptr};
				select::Select *switch_type_select_select_{nullptr};
		};

	};  // namespace vallox
};  // namespace esphome