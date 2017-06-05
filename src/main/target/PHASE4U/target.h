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

/* Phase4µ
 * [Main Card]
 *   Gyro/Acc		MPU6050		SPI2/PB12
 *   Barometer		xxx			I2C1
 *   Onboard flash	M25P16		SPI1/PB13
 *   LEDs			WS2812		TIM1_CH1 (PA8)
 *   USB
 *
 * [Top card]
 *   Magnetometer 	xxx			I2C1
 *   GPS			xxx			USART3
 *   OLED			xxx			I2C1
 *
 * Input
 *   PPM		PA0
 *   MPU6050 	PC13 EXTI?
 *
 * Outputs:
 *   Motor 1
 *   Motor 2
 *   Motor 3
 *   Motor 4
 *   Gimbal Tilt
 *   Gimbal Roll
 *   FrSKY Telemetry
 *   Buzzer?
 *   
**/

#define TARGET_BOARD_IDENTIFIER "PH4U"
#define USBD_PRODUCT_STRING     "Phase4u"

#define USE_VCP

// SPI2
#define USE_SPI
#define USE_SPI_DEVICE_2

#define GYRO
#define USE_GYRO_SPI_MPU6000
#define USE_FAKE_GYRO // DISCOVERY
#define MPU6000_CS_PIN			PB12
#define MPU6000_SPI_INSTANCE 	SPI2

#define GYRO_MPU6000_ALIGN      CW270_DEG

//#define USE_EXTI
//#define MPU_INT_EXTI            PC13
//#define USE_MPU_DATA_READY_SIGNAL
//#define ENSURE_MPU_DATA_READY_IS_LOW

//#define EXTI15_10_CALLBACK_HANDLER_COUNT 1
//#define EXTI_CALLBACK_HANDLER_COUNT 2 // MPU data ready and MAG data ready


#define ACC
#define USE_FAKE_ACC // DISCOVERY
#define USE_ACC_SPI_MPU6000
#define ACC_MPU6000_ALIGN       CW270_DEG


// SPI1
// NSS   PA4/PA15
// SCK   PB3
// MISO  PB4
// MOSI  PB5
#define USE_SPI_DEVICE_1
#define SPI1_NSS_PIN    PA4
#define SPI1_SCK_PIN    PB3
#define SPI1_MISO_PIN   PB4
#define SPI1_MOSI_PIN   PB5

#define M25P16_CS_PIN           PA13
#define M25P16_SPI_INSTANCE     SPI1

#define USE_FLASHFS
#define USE_FLASH_M25P16

#define ENABLE_BLACKBOX_LOGGING_ON_SPIFLASH_BY_DEFAULT


// I2C1
#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C_DEVICE              (I2CDEV_1)

#define BARO
#define USE_BARO_MS5611
//#define USE_BARO_BMP280
//#define USE_BARO_BMP085

#define MAG
//#define USE_MAG_AK8975
#define USE_MAG_HMC5883
#define MAG_HMC5883_ALIGN       CW270_DEG

//#define USE_MAG_DATA_READY_SIGNAL
//#define ENSURE_MAG_DATA_READY_IS_HIGH
//#define MAG_INT_EXTI            PC14

// TODO: OLED
#define DISPLAY
#define DISPLAY_ROTATE_180

#define USE_DASHBOARD
//#define OSD
//#define USE_OSD_OVER_MSP_DISPLAYPORT
//#define USE_SLOW_MSP_DISPLAYPORT_RATE_WHEN_UNARMED



#define SERIAL_PORT_COUNT       3 // Telemetry + GPS + USB

// USART1: Telemetry
#define USE_UART1
#define UART1_TX_PIN            PA9
#define UART1_RX_PIN            PA10

#define TELEMETRY_UART          SERIAL_PORT_USART1
// set tlm_inversion = ON


// USART2: Unused
//#define USE_UART2
//#define UART2_TX_PIN            PA14 // PA14 / SWCLK
//#define UART2_RX_PIN            PA15


// USART3: GPS
#define USE_UART3
#define UART3_TX_PIN            PB10
#define UART3_RX_PIN            PB11

#define GPS
#define USE_GPS
#define GPS_UART                SERIAL_PORT_USART3


// LED Strip
#define LED_STRIP


// PC15: Beeper
#define BEEPER                  PC15
#define BEEPER_INVERTED


// Voltage/current sensor
#define BOARD_HAS_VOLTAGE_DIVIDER
//#define BOARD_HAS_CURRENT_SENSOR

#define USE_ADC
#define ADC_INSTANCE            ADC2
#define VBAT_ADC_PIN            PA4
#define CURRENT_METER_ADC_PIN   PA5
//#define RSSI_ADC_PIN            PB2


#define CONFIG_FASTLOOP_PREFERRED_ACC ACC_NONE

#define LED0                    PA13
//#define LED1                    PA14




#define REMAP_TIM17_DMA

// UART1 TX uses DMA1_Channel4, which is also used by dshot on motor 4
#if defined(USE_UART1_TX_DMA) && defined(USE_DSHOT)
#undef USE_UART1_TX_DMA
#endif


#define DEFAULT_RX_FEATURE      FEATURE_RX_PPM
#define DEFAULT_FEATURES        (FEATURE_TRANSPONDER  | FEATURE_RSSI_ADC | FEATURE_TELEMETRY | FEATURE_LED_STRIP)

#define SPEKTRUM_BIND_PIN       UART3_RX_PIN

#define USE_SERIAL_4WAY_BLHELI_INTERFACE

// IO - stm32f303cc in 48pin package
#define TARGET_IO_PORTA         0xffff
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         (BIT(13)|BIT(14)|BIT(15))
#define TARGET_IO_PORTF         (BIT(0)|BIT(1)|BIT(3)|BIT(4))

#define USABLE_TIMER_CHANNEL_COUNT 17
#define USED_TIMERS             ( TIM_N(1) | TIM_N(2) | TIM_N(3) | TIM_N(4) | TIM_N(15) | TIM_N(16) | TIM_N(17) )
