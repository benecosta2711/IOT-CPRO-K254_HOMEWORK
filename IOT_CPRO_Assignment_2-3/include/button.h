/**
 * @file    button.h
 * @author  [Tên bạn/nhóm]
 * @date    [yyyy-mm-dd]
 * @brief   Button driver header
 *
 * @details 
 *  - Cung cấp API để kiểm tra trạng thái nút nhấn (pressed/released).
 *  - Hỗ trợ callback khi phát hiện sự kiện nhấn nút.
 *  - Bao gồm cả chức năng giả lập (emulation) để test logic mà không cần phần cứng.
 *
 * @note 
 *  - Các hàm callback (EXCEPTION1_Callback, EXCEPTION2_Callback) chỉ nên dùng để set cờ (flag), 
 *    không nên xử lý logic nặng trực tiếp bên trong.
 *  - Trong chế độ giả lập, các hàm EMULATOR_* cho phép mô phỏng hành vi nhấn nút 
 *    thông qua phần mềm nhằm thuận tiện cho việc test.
 *  - Module này không xử lý debounce phần cứng; nếu cần chống dội phím, 
 *    hãy bổ sung trong tầng ứng dụng hoặc scheduler.
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "stdbool.h"
#include "common.h"
#include "peripheral.h"

/**
 * @brief Callback xử lý khi nút nhấn số 1 được phát hiện.
 *
 * @details 
 *  - Hàm này chỉ nên set một biến cờ (flag) để báo hiệu cho logic chính.
 *  - Không nên thực hiện tác vụ mất thời gian dài (VD: printf, giao tiếp ngoại vi).
 */
void EXCEPTION1_Callback(void);

/**
 * @brief Callback xử lý khi nút nhấn số 2 được phát hiện.
 *
 * @details 
 *  - Tương tự như EXCEPTION1_Callback, chỉ nên set flag.
 *  - Dùng cho các tác vụ cần phản ứng nhanh khi nút 2 được nhấn.
 */
void EXCEPTION2_Callback(void);

/**
 * @brief Kiểm tra trạng thái nút số 1.
 *
 * @retval true   Nếu nút đang được nhấn.
 * @retval false  Nếu nút đang thả (released).
 */
bool BUTTON1_IsPressed(void);

/**
 * @brief Kiểm tra trạng thái nút số 2.
 *
 * @retval true   Nếu nút đang được nhấn.
 * @retval false  Nếu nút đang thả (released).
 */
bool BUTTON2_IsPressed(void);

/**
 * @brief Giả lập việc nhấn nút tại một GPIO pin cụ thể.
 *
 * @param gpio     Con trỏ đến GPIO_Type (ví dụ: GPIOB).
 * @param gpio_pin Vị trí pin cần giả lập.
 *
 * @note 
 *  - Dùng trong test software khi không có phần cứng thật.
 *  - Có thể set nhiều lần để mô phỏng nhiều nút khác nhau.
 */
void EMULATOR_ButtonSetOn(GPIO_Type *gpio, int gpio_pin);

/**
 * @brief Gọi hàm giả lập nút nhấn.
 *
 * @param arg  Tham số tuỳ chọn (có thể là NULL hoặc struct mô phỏng).
 *
 * @note 
 *  - Được thiết kế để chạy như một task trong scheduler.
 *  - Khi gọi sẽ tự động cập nhật trạng thái nút theo giả lập.
 */
void EMULATOR_Button(void *arg);

#endif /* BUTTON_H_ */
