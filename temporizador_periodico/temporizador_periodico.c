#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_RED 11
#define LED_YELLOW 12
#define LED_BLUE 13

// Função que vai para a função, que utiliza o hardware, add_repeating_timer_ms()
bool repeating_timer_callback(struct repeating_timer *t);

int main() {
  stdio_init_all(); // Para poder usar printf()

  // Iniciando os leds rgb
  gpio_init(LED_RED);
  gpio_set_dir(LED_RED, GPIO_OUT);
  gpio_put(LED_RED, 1);

  gpio_init(LED_YELLOW);
  gpio_set_dir(LED_YELLOW, GPIO_OUT);
  gpio_put(LED_YELLOW, 0);
  
  gpio_init(LED_BLUE);
  gpio_set_dir(LED_BLUE, GPIO_OUT);
  gpio_put(LED_BLUE, 0);

  struct repeating_timer timer;

  // Função de timer que utiliza o hardware, para amenizar o uso da CPU 
  add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

  while (true) {
    // Capturar o tempo desde que o programa iniciou
    uint32_t actual_time = to_ms_since_boot(get_absolute_time());

    printf("Tempo ativo do sistema: %ds\n", actual_time / 1000);
    sleep_ms(1000);
  }
}

bool repeating_timer_callback(struct repeating_timer *t) {
  // Verificação de qual LED está acesso e ligar o próximo LED da fila
  if (gpio_get(LED_RED)) {
    gpio_put(LED_RED, 0);
    gpio_put(LED_YELLOW, 1);

  } else if (gpio_get(LED_YELLOW)) {
    gpio_put(LED_YELLOW, 0);
    gpio_put(LED_BLUE, 1);

  } else {
    gpio_put(LED_BLUE, 0);
    gpio_put(LED_RED, 1);
  }
}