# README.md
## Cấu trúc thư mục

project/

│

├── logger.h # Header khai báo hàm và macro tiện ích

├── logger.c # Triển khai logic ghi log

├── main.c # Chương trình mẫu minh họa cách sử dụng

└── README.md # Tài liệu hướng dẫn

---
## Cách hoạt động
1. **Khởi tạo logger** với `logger_init()`:
   - Chỉ định mức log tối thiểu (`LOG_INFO`, `LOG_DEBUG`, …).  
   - Tùy chọn đường dẫn file log (`file_path`).  
   - Tùy chọn `append` để ghi nối tiếp hay ghi đè.

2. **Ghi log** ở bất kỳ nơi nào bằng các macro tiện dụng:
   - `LOG_INFO("Message")`
   - `LOG_ERR("Error: %s", reason)`
   - `LOG_DEBUG("Debug var=%d", var)`

3. **Kết thúc** bằng `logger_shutdown()` để đóng file log và giải phóng tài nguyên.

---

## Build & Run

### 1 Biên dịch:

```bash
gcc main.c logger.c -o app
```

### 2 Chạy thử:

```bash
./app
```

### 3 Xem file log:

```bash
cat app.log
```
---

### 4 Kết quả console:

```
[2025-10-04 21:45:12] [INFO] [main.c:8] - System initialized (pid=1234)
[2025-10-04 21:45:12] [DEBUG] [main.c:11] - Now debug logs are visible
[2025-10-04 21:45:12] [ERROR] [main.c:14] - Failed to connect to database: code=-1001
[2025-10-04 21:45:12] [WARNING] [main.c:17] - Battery low: 12%
```

---
