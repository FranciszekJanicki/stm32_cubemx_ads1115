#ifndef ADS1115_HPP
#define ADS1115_HPP

#include "../utility/i2c_device.hpp"
#include "ads1115_config.hpp"
#include "ads1115_registers.hpp"
#include <optional>

namespace ADS1115 {

    struct ADS1115 {
    public:
        using I2CDevice = Utility::I2CDevice;

        ADS1115() noexcept = default;

        ADS1115(I2CDevice&& i2c_device, Config const& config) noexcept;

        ADS1115(ADS1115 const& other) = delete;
        ADS1115(ADS1115&& other) noexcept = default;

        ADS1115& operator=(ADS1115 const& other) = delete;
        ADS1115& operator=(ADS1115&& other) noexcept = default;

        ~ADS1115() noexcept;

        std::optional<float> get_conversion_scaled() const noexcept;
        std::optional<float> get_conversion_scaled(MUX const mux) const noexcept;

    private:
        std::uint8_t read_byte(std::uint8_t const reg_address) const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> read_bytes(std::uint8_t const reg_address) const noexcept;

        void write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept;

        template <std::size_t SIZE>
        void write_bytes(std::uint8_t const reg_address, std::array<std::uint8_t, SIZE> const& bytes) const noexcept;

        void initialize(Config const& config) noexcept;
        void deinitialize() noexcept;

        std::optional<std::int16_t> get_conversion_raw() const noexcept;
        std::optional<std::int16_t> get_conversion_raw(MUX const mux) const noexcept;

        void trigger_oneshot_conversion() const noexcept;

        void select_channel(MUX const mux) const noexcept;

        CONVERSION get_conversion_register() const noexcept;
        void set_conversion_register(CONVERSION const conversion) const noexcept;

        CONFIG get_config_register() const noexcept;
        void set_config_register(CONFIG const config) const noexcept;

        LO_THRESH get_lo_thresh_register() const noexcept;
        void set_lo_thresh_register(LO_THRESH const lo_thresh) const noexcept;

        HI_THRESH get_hi_thresh_register() const noexcept;
        void set_hi_thresh_register(HI_THRESH const hi_thresh) const noexcept;

        bool initialized_{};

        float scale_{};

        I2CDevice i2c_device_{};
    };

    template <std::size_t SIZE>
    inline std::array<std::uint8_t, SIZE> ADS1115::read_bytes(std::uint8_t const reg_address) const noexcept
    {
        return this->i2c_device_.read_bytes<SIZE>(reg_address);
    }

    template <std::size_t SIZE>
    inline void ADS1115::write_bytes(std::uint8_t const reg_address,
                                     std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        this->i2c_device_.write_bytes(reg_address, bytes);
    }

}; // namespace ADS1115

#undef PACKED

#endif // ADS1115_HPP