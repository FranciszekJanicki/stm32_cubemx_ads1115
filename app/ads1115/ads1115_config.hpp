#ifndef ADS1115_REGISTERS_HPP
#define ADS1115_CONFIG_HPP

#include "ads1115_registers.hpp"
#include <cstdint>

namespace ADS1115 {

    enum struct DevAddress : std::uint8_t {
        ADDR_GND = 0b1001000,
        ADDR_VDD = 0b1001001,
        ADDR_SDA = 0b1001010,
        ADDR_SCL = 0b1001011,
    };

    enum struct RA : std::uint8_t {
        CONVERSION = 0b00,
        CONFIG = 0b01,
        LO_THRESH = 0b10,
        HI_THRESH = 0b11,
    };

    enum struct MUX : std::uint8_t {
        P_AIN0_N_AIN1 = 0b000,
        P_AIN0_N_AIN3 = 0b001,
        P_AIN1_N_AIN3 = 0b010,
        P_AIN2_N_AIN3 = 0b011,
        P_AIN0_N_GND = 0b100,
        P_AIN1_N_GND = 0b101,
        P_AIN2_N_GND = 0b110,
        P_AIN3_N_GND = 0b111,
    };

    enum struct Mode : std::uint8_t {
        CONTINUOUS = 0b00,
        SINGLE_SHOT = 0b01,
    };

    enum struct Range : std::uint8_t {
        FSR_6V144 = 0b000,
        FSR_4V096 = 0b001,
        FSR_2V048 = 0b010,
        FSR_1V024 = 0b011,
        FSR_0V512 = 0b100,
        FSR_0V256 = 0b110,
    };

    enum struct DataRate : std::uint8_t {
        RATE_8HZ = 0b000,
        RATE_16HZ = 0b001,
        RATE_32HZ = 0b010,
        RATE_64HZ = 0b011,
        RATE_128HZ = 0b100,
        RATE_250HZ = 0b101,
        RATE_475HZ = 0b110,
        RATE_860HZ = 0b111,
    };

    enum struct CompMode : std::uint8_t {
        TRADITIONAL_COMPARATOR = 0b00,
        WINDOW_COMPARATOR = 0b01,
    };

    enum struct CompPolarity : std::uint8_t {
        ACTIVE_LOW = 0b00,
        ACTIVE_HIGH = 0b01,
    };

    enum struct CompLatch : std::uint8_t {
        LATCHING_COMPARATOR = 0b01,
        NONLATCHING_COMPARATOR = 0b00,
    };

    enum struct CompQueue : std::uint8_t {
        ASSERT_AFTER_1 = 0b00,
        ASSERT_AFTER_2 = 0b01,
        ASSERT_AFTER_4 = 0b10,
        DISABLE_COMPARATOR = 0b11,
    };

    inline float range_to_scale(Range const range) noexcept
    {
        switch (range) {
            case Range::FSR_6V144:
                return 187.5F;
            case Range::FSR_4V096:
                return 125.0F;
            case Range::FSR_2V048:
                return 62.5F;
            case Range::FSR_1V024:
                return 31.25F;
            case Range::FSR_0V512:
                return 15.625F;
            case Range::FSR_0V256:
                return 7.8125F;
            default:
                return 0.0F;
        }
    }

    inline float config_to_scale(Config const& config) noexcept
    {
        return range_to_scale(static_cast<Range>(config.config.pga));
    }

}; // namespace ADS1115

#undef PACKED

#endif // ADS1115_CONFIG_HPP