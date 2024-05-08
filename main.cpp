#include <iostream>
#include <mp-units/systems/si.h>
#include <mp-units/ostream.h>

using namespace mp_units;
using namespace mp_units::si::unit_symbols;

namespace {
    constexpr quantity BATTERY_CAPACITY{ 6000, mA * h };
    constexpr quantity BATTERY_DISCHARGE{ 80, percent }; //todo
    constexpr quantity MOTOR_CURRENT{ 32.9, A };

    //todo motor
    constexpr const std::array EQUIP_CURR_ARR = {
            quantity{300, mA},      // FC
            quantity{40, mA},       // GNSS_COMPASS
            quantity{166, mA},      // CAMERA
            quantity{55, mA},       // VTX  800mW / 14.5 V
            quantity{222, mA},      // RECEIVER 1000 mW / 4.5V
            quantity{120 * 5, mA}   // 5 servos, approximate average value, haven't checked yet
    };

    constexpr auto sumOnboardCurr() {
        quantity  ONBOARD_EQUIP_CURR{ 0, mA };
        for (auto i : EQUIP_CURR_ARR) {
            ONBOARD_EQUIP_CURR += i;
        }
        return ONBOARD_EQUIP_CURR;
    }
}


int main() {
    constexpr quantity<A>   ONBOARD_EQUIP_CURR = sumOnboardCurr();
    constexpr quantity<A>   AVG_CURR_DRAW = MOTOR_CURRENT + ONBOARD_EQUIP_CURR;
    constexpr quantity<min> TIME = BATTERY_CAPACITY * BATTERY_DISCHARGE / AVG_CURR_DRAW;
    std::cout << TIME;
}