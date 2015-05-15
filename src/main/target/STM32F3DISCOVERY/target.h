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

#pragma once

#define TARGET_BOARD_IDENTIFIER "SDF3" // STM Discovery F3 aka. Phase4u

#define USABLE_TIMER_CHANNEL_COUNT  12

#define LED0_GPIO   GPIOE
#define LED0_PIN    Pin_8|Pin_12 // Blue LEDs - PE8/PE12
#define LED0_PERIPHERAL RCC_AHBPeriph_GPIOE
#define LED0_INVERTED
#define LED1_GPIO   GPIOE
#define LED1_PIN    Pin_10|Pin_14  // Orange LEDs - PE10/PE14
#define LED1_PERIPHERAL RCC_AHBPeriph_GPIOE
#define LED1_INVERTED

#define BEEP_GPIO   GPIOE
#define BEEP_PIN    Pin_9|Pin_13 // Red LEDs - PE9/PE13
#define BEEP_PERIPHERAL RCC_AHBPeriph_GPIOE
#define BEEPER_INVERTED


#define BEEPER_INVERTED

#define USE_SPI
#define USE_SPI_DEVICE_1
#define USE_SPI_DEVICE_2


#define GYRO
#define USE_GYRO_SPI_MPU6000
//#define USE_FAKE_GYRO

#define MPU6000_CS_GPIO       GPIOB
#define MPU6000_CS_PIN        GPIO_Pin_12
#define MPU6000_SPI_INSTANCE  SPI2

#define GYRO_SPI_MPU6000_ALIGN CW270_DEG


#define ACC
#define USE_ACC_SPI_MPU6000

#define ACC_SPI_MPU6000_ALIGN CW270_DEG

/*#define ACC
#define USE_ACC_LSM303DLHC*/

#define MAG
#define USE_MAG_HMC5883
#define MAG_HMC5883_ALIGN CW0_DEG_FLIP

#define BARO
#define USE_BARO_MS5611

#define BEEPER
#define LED0
#define LED1

#define USE_FLASHFS
#define USE_FLASH_M25P16

#define M25P16_CS_GPIO          GPIOA
#define M25P16_CS_PIN           GPIO_Pin_13
#define M25P16_SPI_INSTANCE     SPI1

#define SPI1_GPIO               GPIOB
#define SPI1_GPIO_PERIPHERAL    RCC_AHBPeriph_GPIOB

#define SPI1_SCK_PIN            GPIO_Pin_3
#define SPI1_SCK_PIN_SOURCE     GPIO_PinSource3
#define SPI1_SCK_CLK            RCC_AHBPeriph_GPIOB

#define SPI1_MISO_PIN           GPIO_Pin_4
#define SPI1_MISO_PIN_SOURCE    GPIO_PinSource4
#define SPI1_MISO_CLK           RCC_AHBPeriph_GPIOB

#define SPI1_MOSI_PIN           GPIO_Pin_5
#define SPI1_MOSI_PIN_SOURCE    GPIO_PinSource5
#define SPI1_MOSI_CLK           RCC_AHBPeriph_GPIOB

#define USE_VCP
#define USE_USART1
#define USE_USART2
#define USE_USART3
#define SERIAL_PORT_COUNT 4

#define USE_I2C
#define I2C_DEVICE (I2CDEV_1)

#define USE_ADC

#define ADC_INSTANCE                ADC2
#define ADC_AHB_PERIPHERAL          RCC_AHBPeriph_DMA1
#define ADC_DMA_CHANNEL             DMA1_Channel1

#define VBAT_ADC_GPIO               GPIOA
#define VBAT_ADC_GPIO_PIN           GPIO_Pin_5
#define VBAT_ADC_CHANNEL            ADC_Channel_2

#define CURRENT_METER_ADC_GPIO      GPIOB
#define CURRENT_METER_ADC_GPIO_PIN  GPIO_Pin_2
#define CURRENT_METER_ADC_CHANNEL   ADC_Channel_12

/*#define RSSI_ADC_GPIO               GPIOC
#define RSSI_ADC_GPIO_PIN           GPIO_Pin_2
#define RSSI_ADC_CHANNEL            ADC_Channel_8

#define EXTERNAL1_ADC_GPIO          GPIOC
#define EXTERNAL1_ADC_GPIO_PIN      GPIO_Pin_3
#define EXTERNAL1_ADC_CHANNEL       ADC_Channel_9*/

#define BLACKBOX
#define GPS
//#define LED_STRIP
//#define LED_STRIP_TIMER TIM16
#define TELEMETRY
#define SERIAL_RX
#define AUTOTUNE
#define DISPLAY
#define DISPLAY_ROTATE_180
#define USE_SERVOS
