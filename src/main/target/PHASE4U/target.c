/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>

#include <platform.h>
#include "drivers/io.h"

#include "drivers/dma.h"
#include "drivers/timer.h"
#include "drivers/timer_def.h"

/*
SPRACINGF3:
    // Production boards swapped RC_CH3/4 swapped to make it easierTIM_USE_MOTOR,  to using supplied cables - compared to first prototype.
const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    DEF_TIM(TIM2,  CH1, PA0,  TIM_USE_PWM | TIM_USE_PPM, 0), // RC_CH1 - PA0  - *TIM2_CH1
    DEF_TIM(TIM2,  CH2, PA1,  TIM_USE_PWM,               0), // RC_CH2 - PA1  - *TIM2_CH2, TIM15_CH1N
    DEF_TIM(TIM2,  CH4, PB11, TIM_USE_PWM,               0), // RC_CH3 - PB11 - *TIM2_CH4, UART3_RX (AF7)
    DEF_TIM(TIM2,  CH3, PB10, TIM_USE_PWM,               0), // RC_CH4 - PB10 - *TIM2_CH3, UART3_TX (AF7)
    DEF_TIM(TIM3,  CH1, PB4,  TIM_USE_PWM,               0), // RC_CH5 - PB4  - *TIM3_CH1
    DEF_TIM(TIM3,  CH2, PB5,  TIM_USE_PWM,               0), // RC_CH6 - PB5  - *TIM3_CH2
    DEF_TIM(TIM3,  CH3, PB0,  TIM_USE_PWM,               0), // RC_CH7 - PB0  - *TIM3_CH3, TIM1_CH2N, TIM8_CH2N
    DEF_TIM(TIM3,  CH4, PB1,  TIM_USE_PWM,               0), // RC_CH8 - PB1  - *TIM3_CH4, TIM1_CH3N, TIM8_CH3N
    DEF_TIM(TIM16, CH1, PA6,  TIM_USE_MOTOR,             1), // PWM1 - PA6  - TIM3_CH1, TIM8_BKIN, TIM1_BKIN, *TIM16_CH1
    DEF_TIM(TIM17, CH1, PA7,  TIM_USE_MOTOR,             1), // PWM2 - PA7  - TIM3_CH2, *TIM17_CH1, TIM1_CH1N, TIM8_CH1
    DEF_TIM(TIM4,  CH1, PA11, TIM_USE_MOTOR,             1), // PWM3 - PA11
    DEF_TIM(TIM4,  CH2, PA12, TIM_USE_MOTOR,             1), // PWM4 - PA12
    DEF_TIM(TIM4,  CH3, PB8,  TIM_USE_MOTOR,             1), // PWM5 - PB8
    DEF_TIM(TIM4,  CH4, PB9,  TIM_USE_MOTOR,             1), // PWM6 - PB9
    DEF_TIM(TIM15, CH1, PA2,  TIM_USE_MOTOR,             1), // PWM7 - PA2
    DEF_TIM(TIM15, CH2, PA3,  TIM_USE_MOTOR,             1), // PWM8 - PA3
    DEF_TIM(TIM1,  CH1, PA8,  TIM_USE_LED,               1), // GPIO_TIMER / LED_STRIP
};*/


const timerHardware_t timerHardware[USABLE_TIMER_CHANNEL_COUNT] = {
    // [Input]
    // PWM / PPM
    DEF_TIM(TIM2,  CH1, PA0,  TIM_USE_PWM | TIM_USE_PPM, 0), // RC_CH1 - PA0  - *TIM2_CH1
    // PWM
    DEF_TIM(TIM2,  CH2, PA1,  TIM_USE_PWM,               0), // RC_CH2 - PA1  - *TIM2_CH2, TIM15_CH1N
    DEF_TIM(TIM3,  CH3, PB0,  TIM_USE_PWM,               0), // RC_CH7 - PB0  - *TIM3_CH3, TIM1_CH2N, TIM8_CH2N
    DEF_TIM(TIM3,  CH4, PB1,  TIM_USE_PWM,               0), // RC_CH8 - PB1  - *TIM3_CH4, TIM1_CH3N, TIM8_CH3N
    
    // [Output]
    // Motors:
    DEF_TIM(TIM16, CH1, PA6,  TIM_USE_MOTOR,             1), // PWM1 - PA6  - TIM3_CH1, TIM8_BKIN, TIM1_BKIN, *TIM16_CH1
    DEF_TIM(TIM17, CH1, PA7,  TIM_USE_MOTOR,             1), // PWM2 - PA7  - TIM3_CH2, *TIM17_CH1, TIM1_CH1N, TIM8_CH1
    DEF_TIM(TIM4,  CH3, PB8,  TIM_USE_MOTOR,             1), // PWM3 - PB8
    DEF_TIM(TIM4,  CH4, PB9,  TIM_USE_MOTOR,             1), // PWM4 - PB9
    
    // Gimbal control    
    DEF_TIM(TIM15, CH1, PA2,  TIM_USE_SERVO,             1), // PWM5 - PA2
    DEF_TIM(TIM15, CH2, PA3,  TIM_USE_SERVO,             1), // PWM6 - PA3
    
    // LED Strip
    DEF_TIM(TIM1,  CH1, PA8,  TIM_USE_LED,               1), // GPIO_TIMER / LED_STRIP
};


// Phase32:

/*


    { TIM15, GPIOA, Pin_2,  TIM_Channel_1, TIM1_BRK_TIM15_IRQn,     1, Mode_AF_PP, GPIO_PinSource2,  GPIO_AF_9},  // PWM5 - PA2
    { TIM2,  GPIOA, Pin_1,  TIM_Channel_2, TIM2_IRQn,               0, Mode_AF_PP, GPIO_PinSource1,  GPIO_AF_1}, // RC2 - PA1
    { TIM3,  GPIOB, Pin_0,  TIM_Channel_3, TIM3_IRQn,               0, Mode_AF_PP, GPIO_PinSource0,  GPIO_AF_2}, // RC3 - PB0
    { TIM3,  GPIOB, Pin_1,  TIM_Channel_4, TIM3_IRQn,               0, Mode_AF_PP_PD, GPIO_PinSource1, GPIO_AF_2},// PC4 - PB1
    { TIM3,  GPIOA, Pin_4,  TIM_Channel_2, TIM3_IRQn,               0, Mode_AF_PP, GPIO_PinSource4, GPIO_AF_2},    // RC5 - PA4
    { TIM1,  GPIOA, Pin_8,  TIM_Channel_1, TIM1_CC_IRQn,            1, Mode_AF_PP_PD, GPIO_PinSource8, GPIO_AF_6},// RC6/LED - PA8
    
    { TIM16, GPIOA, Pin_6,  TIM_Channel_1, TIM1_UP_TIM16_IRQn,      1, Mode_AF_PP, GPIO_PinSource6,  GPIO_AF_1},  // PWM1 - PA6
    { TIM17, GPIOA, Pin_7,  TIM_Channel_1, TIM1_TRG_COM_TIM17_IRQn, 1, Mode_AF_PP, GPIO_PinSource7,  GPIO_AF_1},  // PWM2 - PA7
    { TIM4,  GPIOB, Pin_8,  TIM_Channel_3, TIM4_IRQn,               1, Mode_AF_PP, GPIO_PinSource8,  GPIO_AF_2},  // PWM3 - PB8
    { TIM4,  GPIOB, Pin_9,  TIM_Channel_4, TIM4_IRQn,               1, Mode_AF_PP, GPIO_PinSource9,  GPIO_AF_2},  // PWM4 - PB9
    { TIM2,  GPIOA, Pin_0,  TIM_Channel_1, TIM2_IRQn,               0, Mode_AF_PP, GPIO_PinSource0,  GPIO_AF_1}, // RC1/PPM - PA0
    { TIM15, GPIOA, Pin_3,  TIM_Channel_2, TIM1_BRK_TIM15_IRQn, 1, Mode_AF_PP, GPIO_PinSource3, GPIO_AF_9} // PWM6 - PA3


    
static const uint16_t multiPPM[] = {
    PWM12  | (MAP_TO_PPM_INPUT    << 8), // PPM input
    
    PWM8  | (MAP_TO_MOTOR_OUTPUT << 8),
    PWM10  | (MAP_TO_MOTOR_OUTPUT << 8),
    PWM7  | (MAP_TO_MOTOR_OUTPUT << 8),
    PWM9 | (MAP_TO_MOTOR_OUTPUT << 8),
    PWM11 | (MAP_TO_MOTOR_OUTPUT << 8),
    //PWM12 | (MAP_TO_MOTOR_OUTPUT << 8),
    0xFFFF
};

*/