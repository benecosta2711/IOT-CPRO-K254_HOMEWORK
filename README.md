# README.md
## Smart Plant Watering System (SPWS)
```markdown
Hệ thống tưới cây tự động thông minh chạy mô phỏng trên PC (gcc).  
Kiến trúc module rõ ràng, dễ dàng thay thế lớp HAL để triển khai trên phần cứng thật.
```
---

## Phần 1: Cấu trúc thư mục
```

IOT_CPRO_Assignment_2-3/
├─ include/

│  ├─ CONFIG               # Enums/Structs + default config + logging macro

|  |  ├─ config.h

│  ├─ HAL_ACTUATORS        # API điều khiển hệ thống

|  |  ├─ hal_actuators.c

|  |  ├─ hal_actuators.h

│  ├─ HAL_BUTTONS          # HAL cảm biến (mô phỏng)

|  |  ├─ hal_buttons. c

|  |  ├─ hal_buttons. h

│  ├─ HAL_SENSORS          # HAL bơm + LED (mô phỏng)

|  |  ├─ hal_sensors.c

|  |  ├─ hal_sensors.h

│  ├─ SPWS_CONTROLLER      # HAL nút nhấn (mô phỏng: đọc stdin)

|  |  ├─ spws_controller.c

|  |  ├─ spws_controller.h

└─ source/

├─ main.c

```
---

## Phần 2: Build & Run

### 1. Biên dịch bằng `gcc`
```bash
gcc $(find source include -name "*.c") $(find include -type d -printf "-I%p ") -o spws
./spws
````

### 2. Truyền tham số khi chạy
```bash
./spws <minMoist> <maxMoist> <manualDur_s> <sensorInterval_s> <maxWaterDur_s>

# Ví dụ:
./spws 30 60 8 2 45
```

---

## Phần 3: Giá trị mặc định

Nếu không truyền tham số, hệ thống sử dụng giá trị trong `include/config.h`:

* `CFG_MIN_MOISTURE_DEFAULT` = **35%**
* `CFG_MAX_MOISTURE_DEFAULT` = **55%**
* `CFG_MANUAL_WATER_DUR_S_DEFAULT` = **10s**
* `CFG_SENSOR_INTERVAL_S_DEFAULT` = **2s**
* `CFG_MAX_WATER_DUR_S_DEFAULT` = **60s**

---

## Phần 4: Điều khiển khi chạy

* Gõ **`a`** + Enter → chuyển chế độ **AUTO ↔ MANUAL** (nút 1).
* Gõ **`m`** + Enter → tưới **MANUAL** với thời lượng cấu hình (nút 2).
* Nhấn **Ctrl + C** để thoát.

---

## Phần 5: Kiến trúc & Luồng chính

Hàm `SPWS_Tick1s()` chạy mỗi giây, thực hiện:

1. Mô phỏng cảm biến thay đổi theo trạng thái bơm.
2. Cập nhật bộ đếm (`wateringElapsed`, `manualWateringCounter`).
3. Đọc nút (stdin).
4. Đọc cảm biến theo chu kỳ `sensorReadInterval_s` và log giá trị.
5. Thực thi logic:

   * **AUTO**:

     * Nếu ẩm `< min` → bật bơm.
     * Nếu đang bơm và ẩm `> max` hoặc vượt `maxWateringDuration_s` → tắt bơm.
   * **MANUAL**:

     * Nếu hết `manualWateringDuration_s` → tắt bơm.

### LED hiển thị:

* `LED_WATERING` → khi bơm ON.
* `LED_LOW_MOISTURE_ALERT` → khi AUTO & không tưới & ẩm < min.
* `LED_NORMAL` → khi bơm OFF và không cảnh báo.

---

