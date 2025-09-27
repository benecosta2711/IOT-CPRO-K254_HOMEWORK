/**
 * @file    peripheral.h
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Peripheral abstraction layer (GPIO, LED, Button, Pump, Sensor)
 *
 * @details 
 *  - Định nghĩa các cổng (PORT) và GPIO giả lập để test trên phần mềm.
 *  - Cấu trúc dữ liệu `PORT_Type` mô phỏng thanh ghi điều khiển PORT.
 *  - Cấu trúc dữ liệu `GPIO_Type` mô phỏng thanh ghi điều khiển GPIO.
 *  - Cung cấp macro để gán LED, Button, Pump và Sensor vào chân GPIO.
 *  - Khai báo API khởi tạo GPIO.
 *
 * @note 
 *  - Đây chỉ là code giả lập, không ánh xạ trực tiếp tới thanh ghi thật của MCU.
 *  - Cần được mở rộng nếu bạn muốn mô phỏng thêm peripheral khác (UART, ADC...).
 */

#ifndef PERIPHERAL_H_
#define PERIPHERAL_H_

#include <common.h>

#define NUM_PIN 7   /**< Số pin giả lập trong mỗi PORT */

/* ================== LED Configuration ================== */
#define LED_RED_PORT        GPIOC
#define LED_YELLOW_PORT     GPIOC
#define LED_GREEN_PORT      GPIOC
#define LED_RED_PIN         1
#define LED_YELLOW_PIN      2
#define LED_GREEN_PIN       3

/* ================== Button Configuration ================== */
#define BUTTON1_PORT         GPIOA 
#define BUTTON1_PIN          1
#define BUTTON2_PORT         GPIOB 
#define BUTTON2_PIN          1

/* ================== Pump Configuration ================== */
#define PUMP_PORT           GPIOB
#define PUMP_PIN            3

/* ================== Sensor Configuration ================== */
#define SOILMOISTURE_PORT   GPIOA
#define SOILMOITURE_PIN     2
#define TEMPERATURE_PORT    GPIOA
#define TEMPERATURE_PIN     3

/**
 * @struct PORT_Type
 * @brief  Cấu trúc mô phỏng thanh ghi PORT
 *
 * @details 
 *  - Mỗi PORT có 7 pin (theo định nghĩa NUM_PIN).
 *  - Mỗi pin có một thanh ghi cấu hình chức năng:
 *      - 0: default
 *      - 1: GPIO
 *      - 2: Alternate function
 */
typedef struct {
    int PIN_REG[NUM_PIN]; 
} PORT_Type;

/* Base address giả lập cho PORT */
extern PORT_Type PORTA_BASE;
extern PORT_Type PORTB_BASE;
extern PORT_Type PORTC_BASE;

#define PORTA (&PORTA_BASE)
#define PORTB (&PORTB_BASE)
#define PORTC (&PORTC_BASE)


/**
 * @struct GPIO_Type
 * @brief  Cấu trúc mô phỏng thanh ghi GPIO
 *
 * @details
 *  - PIN_SET[]: bật/tắt pin (0 = disable, 1 = enable).
 *  - MODE: chế độ hoạt động (input/output/alternate...).
 *  - DATA[]: dữ liệu gắn cho từng pin (0 = low, 1 = high hoặc giá trị sensor).
 */
typedef struct {
    uint32_t PIN_SET[NUM_PIN];
    uint32_t MODE;
    uint8_t  DATA[NUM_PIN];
} GPIO_Type;

/* Base address giả lập cho GPIO */

extern GPIO_Type GPIOA_BASE;
extern GPIO_Type GPIOB_BASE;
extern GPIO_Type GPIOC_BASE;

#define GPIOA (&GPIOA_BASE)
#define GPIOB (&GPIOB_BASE)
#define GPIOC (&GPIOC_BASE)


/* ================== API Prototypes ================== */

/**
 * @brief  Bật clock/enable cho GPIO (giả lập).
 * @note   Trong code giả lập có thể để trống, 
 *         nhưng giữ nguyên API cho giống MCU thật.
 */
void GPIO_Enable(void);

/**
 * @brief  Khởi tạo một pin GPIO
 * @param  port         Con trỏ đến PORT_Type (PORTA, PORTB, PORTC).
 * @param  gpio_port    Con trỏ đến GPIO_Type (GPIOA, GPIOB, GPIOC).
 * @param  port_index   Vị trí pin trong port (0..NUM_PIN-1).
 * @param  gpio_set_mode Chế độ hoạt động của pin (ví dụ input/output).
 */
void GPIO_Init(PORT_Type *port, GPIO_Type *gpio_port, uint8_t port_index, uint8_t gpio_set_mode);

#endif /* PERIPHERAL_H_ */
