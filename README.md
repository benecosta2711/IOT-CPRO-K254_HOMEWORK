```markdown
# Logger Utility for C Applications

## Giới thiệu
`logger` là một **thư viện ghi log đơn giản và linh hoạt** cho ứng dụng C/C++.  
Nó hỗ trợ:
- Ghi log ra **console (stdout / stderr)**.  
- Ghi log ra **file** (với tùy chọn ghi nối tiếp hoặc ghi mới).  
- Quản lý **mức độ log (log level)** để kiểm soát chi tiết thông tin hiển thị.  
- Ghi kèm **timestamp**, **tên file**, **số dòng**, và **mức độ log**.  

> Mục tiêu: dễ tích hợp, gọn nhẹ, hoạt động được trên cả **Linux** và **Embedded Linux**.

---

## Cấu trúc thư mục

```

project/
│
├── logger.h           # Header khai báo hàm và macro tiện ích
├── logger.c           # Triển khai logic ghi log
├── main.c             # Chương trình mẫu minh họa cách sử dụng
└── README.md          # Tài liệu hướng dẫn

````

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

## Mức độ log (log levels)

| Mức | Macro | Ý nghĩa |
|------|--------|----------|
| 0 | `LOG_EMERG` | Hệ thống không thể sử dụng |
| 1 | `LOG_ALERT` | Cần hành động khẩn cấp |
| 2 | `LOG_CRIT` | Lỗi nghiêm trọng |
| 3 | `LOG_ERR` | Lỗi thông thường |
| 4 | `LOG_WARN` | Cảnh báo |
| 5 | `LOG_NOTICE` | Thông báo quan trọng |
| 6 | `LOG_INFO` | Thông tin chung |
| 7 | `LOG_DEBUG` | Thông tin gỡ lỗi chi tiết |

> Mức log càng cao → log càng chi tiết.

---

**Kết quả console:**

```
[2025-10-04 21:45:12] [INFO] [main.c:8] - System initialized (pid=1234)
[2025-10-04 21:45:12] [DEBUG] [main.c:11] - Now debug logs are visible
[2025-10-04 21:45:12] [ERROR] [main.c:14] - Failed to connect to database: code=-1001
[2025-10-04 21:45:12] [WARNING] [main.c:17] - Battery low: 12%
```

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

