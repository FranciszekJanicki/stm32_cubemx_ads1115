#include "main.h"
#include "ads1115.hpp"
#include "gpio.h"
#include "i2c.h"
#include "usart.h"
#include <cstdio>
#include <utility>

namespace {

    volatile auto interrupt = false;

};

void HAL_TIM_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    interrupt = true;
}

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();

    using namespace ADS1115;

    auto i2c_device = I2CDevice{&hi2c1, std::to_underlying(DevAddress::ADDR_GND)};

    auto config = CONFIG{.os = false,
                         .mux = std::to_underlying(MUX::P_AIN0_N_GND),
                         .pga = std::to_underlying(Range::FSR_6V144),
                         .mode = std::to_underlying(Mode::CONTINUOUS),
                         .dr = std::to_underlying(DataRate::RATE_860HZ),
                         .comp_mode = std::to_underlying(CompMode::TRADITIONAL_COMPARATOR),
                         .comp_pol = std::to_underlying(CompPolarity::ACTIVE_HIGH),
                         .comp_lat = std::to_underlying(CompLatch::LATCHING_COMPARATOR),
                         .comp_que = std::to_underlying(CompQueue::ASSERT_AFTER_1)};

    auto lo_thresh = LO_THRESH{.lo_thresh = 0U};

    auto hi_thresh = HI_THRESH{.hi_thresh = 6U};

    auto ads1115 = ADS1115::ADS1115{std::move(i2c_device),
                                    Config{.config = config, .lo_thresh = lo_thresh, .hi_thresh = hi_thresh}};

    while (true) {
        if (interrupt) {
            auto const voltage = ads1115.get_conversion_scaled().value();
            std::printf("voltage: %f\n\r", voltage);
            HAL_Delay(100);
            interrupt = false;
        }
    }

    return 0;
}
