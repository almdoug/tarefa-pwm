#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Definição para o servo
#define SERVO_PIN 22

// Função para configurar o PWM com duty cycle em porcentagem
void pwm_set_duty_cycle_percent(uint slice_num, uint channel, float duty_cycle_percent) {
    uint16_t level = (uint16_t)((duty_cycle_percent / 100.0f) * 65535.0f);
    pwm_set_chan_level(slice_num, channel, level);
}

int main() {
    stdio_init_all();

    // Configurar GPIO para PWM
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);
    uint channel = pwm_gpio_to_channel(SERVO_PIN);

    // Configurar frequência para 50Hz (período de 20ms)
    uint32_t clock = clock_get_hz(clk_sys);
    uint32_t wrap = 65535;
    float divider = (float)clock / ((wrap + 1) * 50.0f);
    
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, divider);
    pwm_config_set_wrap(&config, wrap);
    pwm_init(slice_num, &config, true);

    // 180° -> 2400µs = (2400/20000)*100 = 12%
    // 90°  -> 1470µs = (1470/20000)*100 = 7.35%
    // 0°   -> 500µs  = (500/20000)*100 = 2.5%
    while (true) {
        // Posição de 180 graus (2400µs -> 12%)
        pwm_set_duty_cycle_percent(slice_num, channel, 12);
        sleep_ms(5000);

        // Posição de 90 graus (1470µs -> 7.35%)
        pwm_set_duty_cycle_percent(slice_num, channel, 7.35);
        sleep_ms(5000);

        // Posição de 0 graus (500µs -> 2.5%)
        pwm_set_duty_cycle_percent(slice_num, channel, 2.5);
        sleep_ms(5000);

        // Movimento suave de 0 a 180 graus:
        // Incremento de 5µs equivale a (5/20000)*100 = 0.025% de variação
        for (float dc = 2.5; dc <= 12; dc += 0.025) {
            pwm_set_duty_cycle_percent(slice_num, channel, dc);
            sleep_ms(10);
        }

        // Movimento suave de 180 a 0 graus:
        for (float dc = 12; dc >= 2.5; dc -= 0.025) {
            pwm_set_duty_cycle_percent(slice_num, channel, dc);
            sleep_ms(10);
        }
    }

    return 0;
}
