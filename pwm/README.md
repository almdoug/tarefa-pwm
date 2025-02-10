# Controle de Servomotor com PWM no Raspberry Pi Pico W

Este projeto demonstra o controle de um servomotor utilizando PWM (Pulse Width Modulation) no Raspberry Pi Pico W. Nele, foi implementado o seguinte:

1. **Configuração da GPIO 22 para PWM a 50Hz:**  
   Foi definida a frequência do PWM para aproximadamente 50Hz, o que equivale a um período de 20ms.

2. **Posição de 180° (Flange em 2400µs):**  
   O ciclo ativo do PWM é configurado para 2400µs.  
   - Cálculo do Duty Cycle: (2400/20000) * 100 = 12%  
   - Ação: Ajusta o servomotor para aproximadamente 180° e aguarda 5 segundos.

3. **Posição de 90° (Flange em 1470µs):**  
   O ciclo ativo do PWM é configurado para 1470µs.  
   - Cálculo do Duty Cycle: (1470/20000) * 100 = 7,35%  
   - Ação: Ajusta o servomotor para aproximadamente 90° e aguarda 5 segundos.

4. **Posição de 0° (Flange em 500µs):**  
   O ciclo ativo do PWM é configurado para 500µs.  
   - Cálculo do Duty Cycle: (500/20000) * 100 = 2,5%  
   - Ação: Ajusta o servomotor para aproximadamente 0° e aguarda 5 segundos.

5. **Movimentação Suave entre 0° e 180°:**  
   Após as posições fixas, o programa realiza uma movimentação suave do servomotor:
   - Movimento de 0° a 180° com incremento de 5µs por passo, equivalente a um incremento de 0,025% no duty cycle em cada iteração.
   - Cada passo tem um atraso de 10ms, garantindo uma transição suave.
   - O processo se repete também no sentido inverso (de 180° a 0°).

## Arquivos do Projeto

- **pwm.c**  
  Contém o código fonte onde é implementado:
  - A função `pwm_set_duty_cycle_percent` para ajustar o duty cycle do PWM.
  - A configuração da GPIO 22 para operação PWM.
  - A inicialização do PWM para trabalhar a 50Hz.
  - A sequência de movimentação do servomotor com posições de 180°, 90° e 0°, além da varredura suave entre esses extremos.

## Compilação e Execução

Para compilar e executar este projeto, certifique-se de ter o Pico SDK devidamente configurado e o ambiente de desenvolvimento para o Raspberry Pi Pico. Em geral, o processo inclui:

1. Configurar o ambiente e instalar as ferramentas necessárias (CMake, etc.).
2. Criar um diretório de build:
   ```bash
   mkdir build && cd build
   ```
3. Gerar os arquivos de compilação:
   ```bash
   cmake ..
   ```
4. Compilar o projeto:
   ```bash
   make
   ```
5. Gravar o firmware compilado (`.uf2`) na placa Raspberry Pi Pico (através do modo BOOTSEL).

## Funcionamento do Código

- **PWM e Duty Cycle:**  
  O PWM é configurado utilizando uma resolução máxima representada por um wrap de 65535, e o duty cycle é calculado em porcentagem.  
  A função `pwm_set_duty_cycle_percent` converte o valor percentual para o nível correspondente na resolução do PWM.

- **Movimentação do Servomotor:**  
  São definidos duty cycles específicos para posicionar o servo em 0°, 90° e 180°. Após essas posições, o servo realiza uma varredura suave entre os ângulos, permitindo uma transição gradual.

## Considerações

Este exemplo é útil para entender como manipular sinais PWM para controle de servomotores, além de demonstrar como implementar ajustes finos de movimentos utilizando incrementos pequenos e atrasos controlados.

--- 