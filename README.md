
# IoT CPRO Assignment 2-3

Project mô phỏng một hệ thống IoT cơ bản: thu thập dữ liệu từ cảm biến, xử lý bằng Finite State Machine (FSM), điều khiển bơm và LED hiển thị.  
Chương trình được tổ chức theo kiến trúc module hóa, dễ dàng mở rộng và bảo trì.

---

## 📂 Cấu trúc thư mục
IOT_CPRO_Assignment_2-3/
│── include/ # Chứa thư viện hỗ trợ (module con)
│ ├── BUTTON/ # Xử lý button
│ ├── COMMON/ # Hàm dùng chung
│ ├── FSM_SYSTEM/ # Finite State Machine
│ ├── LED_DISPLAY/ # Điều khiển LED
│ ├── NOTIFICATION/ # Module cảnh báo
│ ├── PERIPHERAL/ # Quản lý ngoại vi
│ ├── PUMP/ # Điều khiển bơm
│ ├── SENSOR/ # Đọc dữ liệu cảm biến
│ └── TIMER/ # Quản lý timer
│
│── source/
│ └── main.c # Điểm vào chương trình
│
│── README.md # Tài liệu chính của project
│── .gitignore



---

## 🚀 Build & Run

### 1. Build bằng gcc
```bash
gcc $(find source include -name "*.c") $(find include -type d -printf "-I%p ") -o app
./app



