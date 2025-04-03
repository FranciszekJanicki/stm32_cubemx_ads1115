#include "ads1115.hpp"

namespace ADS1115 {

    ADS1115::ADS1115(I2CDevice&& i2c_device, Config const& config) noexcept :
        scale_{config_to_scale(config)}, i2c_device_{std::forward<I2CDevice>(i2c_device)}
    {
        this->initialize(config);
    }

    ADS1115::~ADS1115() noexcept
    {
        this->deinitialize();
    }

    std::optional<float> ADS1115::get_conversion_scaled() const noexcept
    {
        return this->get_conversion_raw().transform(
            [this](std::int16_t const raw) { return static_cast<float>(raw) * this->scale_; });
    }

    std::optional<float> ADS1115::get_conversion_scaled(MUX const mux) const noexcept
    {
        return this->get_conversion_raw(mux).transform(
            [this](std::int16_t const raw) { return static_cast<float>(raw) * this->scale_; });
    }

    std::uint8_t ADS1115::read_byte(std::uint8_t const reg_address) const noexcept
    {
        return this->i2c_device_.read_byte(reg_address);
    }

    void ADS1115::write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->i2c_device_.write_byte(reg_address, byte);
    }

    void ADS1115::initialize(Config const& config) noexcept
    {
        this->set_config_register(config.config);
        this->set_lo_thresh_register(config.lo_thresh);
        this->set_hi_thresh_register(config.hi_thresh);
        this->initialized_ = true;
    }

    void ADS1115::deinitialize() noexcept
    {
        this->initialized_ = false;
    }

    std::optional<std::int16_t> ADS1115::get_conversion_raw() const noexcept
    {
        return this->initialized_
                   ? std::optional<std::int16_t>{std::bit_cast<std::int16_t>(this->get_conversion_register())}
                   : std::optional<std::int16_t>{std::nullopt};
    }

    std::optional<std::int16_t> ADS1115::get_conversion_raw(MUX const mux) const noexcept
    {
        this->select_channel(mux);
        return this->get_conversion_raw();
    }

    void ADS1115::trigger_oneshot_conversion() const noexcept
    {
        auto config = this->get_config_register();
        config.os = true;
        this->set_config_register(config);
    }

    void ADS1115::select_channel(MUX const mux) const noexcept
    {
        auto config = this->get_config_register();
        config.mux = std::to_underlying(mux);
        this->set_config_register(config);
    }

    CONVERSION ADS1115::get_conversion_register() const noexcept
    {
        return std::bit_cast<CONVERSION>(this->read_bytes<sizeof(CONVERSION)>(std::to_underlying(RA::CONVERSION)));
    }

    void ADS1115::set_conversion_register(CONVERSION const conversion) const noexcept
    {
        this->write_bytes(std::to_underlying(RA::CONVERSION),
                          std::bit_cast<std::array<std::uint8_t, sizeof(CONVERSION)>>(conversion));
    }

    CONFIG ADS1115::get_config_register() const noexcept
    {
        return std::bit_cast<CONFIG>(this->read_bytes<sizeof(CONFIG)>(std::to_underlying(RA::CONFIG)));
    }

    void ADS1115::set_config_register(CONFIG const config) const noexcept
    {
        this->write_bytes(std::to_underlying(RA::CONFIG),
                          std::bit_cast<std::array<std::uint8_t, sizeof(CONFIG)>>(config));
    }

    LO_THRESH ADS1115::get_lo_thresh_register() const noexcept
    {
        return std::bit_cast<LO_THRESH>(this->read_bytes<sizeof(LO_THRESH)>(std::to_underlying(RA::LO_THRESH)));
    }

    void ADS1115::set_lo_thresh_register(LO_THRESH const lo_thresh) const noexcept
    {
        this->write_bytes(std::to_underlying(RA::LO_THRESH),
                          std::bit_cast<std::array<std::uint8_t, sizeof(LO_THRESH)>>(lo_thresh));
    }

    HI_THRESH ADS1115::get_hi_thresh_register() const noexcept
    {
        return std::bit_cast<HI_THRESH>(this->read_bytes<sizeof(HI_THRESH)>(std::to_underlying(RA::HI_THRESH)));
    }

    void ADS1115::set_hi_thresh_register(HI_THRESH const hi_thresh) const noexcept
    {
        this->write_bytes(std::to_underlying(RA::HI_THRESH),
                          std::bit_cast<std::array<std::uint8_t, sizeof(HI_THRESH)>>(hi_thresh));
    }

}; // namespace ADS1115