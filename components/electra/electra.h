#define USE_CALLBACKS

#include "esphome.h"

static const char *TAG = "electra.climate";
// static const char* ELECTRA_VERSION = "1.0.0";

using namespace esphome;


#ifndef ELECTRA_H
#define ELECTRA_H

 typedef enum IRElectraMode {
     IRElectraModeCool = 0b001,
     IRElectraModeHeat = 0b010,
     IRElectraModeAuto = 0b011,
     IRElectraModeDry  = 0b100,
     IRElectraModeFan  = 0b101,
     IRElectraModeOff  = 0b111
 } IRElectraMode;

 typedef enum IRElectraFan {
     IRElectraFanLow    = 0b00,
     IRElectraFanMedium = 0b01,
     IRElectraFanHigh   = 0b10,
     IRElectraFanAuto   = 0b11
 } IRElectraFan;

// That configuration has a total of 34 bits
//    33: Power bit, if this bit is ON, the A/C will toggle it's power.
// 32-30: Mode - Cool, heat etc.
// 29-28: Fan - Low, medium etc.
// 27-26: Zeros
//    25: Swing On/Off
//    24: iFeel On/Off
//    23: Zero
// 22-19: Temperature, where 15 is 0000, 30 is 1111
//    18: Sleep mode On/Off
// 17- 2: Zeros
//     1: One
//     0: Zero
typedef union ElectraCode {
    uint64_t num;
    struct {
        uint64_t zeros1 : 1;
        uint64_t ones1 : 1;
        uint64_t zeros2 : 16;
        uint64_t sleep : 1;
        uint64_t temperature : 4;
        uint64_t zeros3 : 1;
        uint64_t ifeel : 1;
        uint64_t swing : 1;
        uint64_t zeros4 : 2;
        uint64_t fan : 2;
        uint64_t mode : 3;
        uint64_t power : 1;
    };
} ElectraCode;

const uint8_t ELECTRA_TEMP_MIN = 16;  // Celsius
const uint8_t ELECTRA_TEMP_MAX = 30;  // Celsius

#define ELECTRA_TIME_UNIT 1000
#define ELECTRA_NUM_BITS 34

class ElectraClimate : public Component, public climate::Climate {
  public:
    void setup() override;

    void set_transmitter(remote_transmitter::RemoteTransmitterComponent *transmitter);

    void set_supports_cool(bool supports_cool);
    void set_supports_heat(bool supports_heat);
    void set_sensor(sensor::Sensor *sensor); 
    
    /// Override control to change settings of the climate device
    void control(const climate::ClimateCall &call) override;

    /// Return the traits of this controller
    climate::ClimateTraits traits() override;

    /// Transmit the state of this climate controller via IR
    void transmit_state_();

    ClimateMode active_mode_;

    bool supports_cool_{true};
    bool supports_heat_{true};

    remote_transmitter::RemoteTransmitterComponent *transmitter_;
    sensor::Sensor *sensor_{nullptr};
};