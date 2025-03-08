#ifndef ADS1115_REGISTERS_HPP
#define ADS1115_REGISTERS_HPP

#include <cstdint>

#define PACKED __attribute__((__packed__))

namespace ADS1115 {

    struct ADDRESS_POINTER {
        std::uint8_t : 6;
        std::uint8_t p : 2;
    } PACKED;

    struct CONVERSION {
        std::uint16_t conversion : 16;
    } PACKED;

    struct CONFIG {
        std::uint8_t os : 1;
        std::uint8_t mux : 3;
        std::uint8_t pga : 3;
        std::uint8_t mode : 1;
        std::uint8_t dr : 3;
        std::uint8_t comp_mode : 1;
        std::uint8_t comp_pol : 1;
        std::uint8_t comp_lat : 1;
        std::uint8_t comp_que : 2;
    } PACKED;

    struct LO_THRESH {
        std::uint16_t lo_thresh : 16;
    } PACKED;

    struct HI_THRESH {
        std::uint16_t hi_thresh : 16;
    } PACKED;

    struct Config {
        CONFIG config{};
        LO_THRESH lo_thresh{};
        HI_THRESH hi_thresh{};
    };

}; // namespace ADS1115

#undef PACKED

#endif // ADS1115_REGISTERS_HPP