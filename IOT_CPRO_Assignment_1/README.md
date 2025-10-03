# Bài thực hành: Phân tích Lỗi Bộ nhớ với GDB

---

Tài liệu này hướng dẫn cách biên dịch, chạy, và sử dụng GDB để phân tích lỗi rò rỉ bộ nhớ (Memory Leak) trong chương trình C memory_lab.c.
## Phần 1: Hướng dẫn Build và Chạy chương trình
Biên dịch chương trình
Để GDB có thể liên kết mã máy với mã nguồn C của bạn, bạn cần biên dịch với cờ -g để bao gồm các thông tin gỡ lỗi (debugging symbols).

```Bash
gcc -g -o memory_lab memory_lab.c
```

---

## Phần 2: Chạy chương trình
Chương trình có thể được chạy với các đối số khác nhau để mô phỏng các lỗi:
- Stack Overflow:
```Bash
./memory_lab stack_overflow
```
- Memory Leak (dẫn đến Out of Memory):
```Bash
./memory_lab memory_leak
```

**Lưu ý quan trọng khi gỡ lỗi Out of Memory**
Khi một chương trình tiêu thụ quá nhiều bộ nhớ, hệ điều hành Linux có thể kích hoạt OOM Killer (Out of Memory Killer) để "giết" tiến trình đó nhằm bảo vệ hệ thống. Điều này khiến chương trình của bạn kết thúc đột ngột trước khi GDB có thể bắt lỗi.
Giải pháp: Sử dụng lệnh ulimit để giới hạn bộ nhớ ảo mà chương trình được phép dùng. Điều này đảm bảo chương trình sẽ tự hết bộ nhớ của "nó" trước khi gây nguy hiểm cho hệ thống.
Giới hạn bộ nhớ ảo xuống khoảng 200MB trước khi chạy GDB
```Bash
ulimit -v 200000
gdb ./memory_lab
```

---

## Phần 3: Phân tích bằng GDB - Trả lời câu hỏi
Dưới đây là câu trả lời chi tiết cho các yêu cầu phân tích bằng GDB.
- Câu hỏi 1: Làm thế nào để đặt một điểm dừng (breakpoint) trong GDB mà nó chỉ kích hoạt khi malloc trả về NULL?
    - Trả lời:
        Để làm điều này, chúng ta sử dụng một điểm dừng có điều kiện (conditional breakpoint). Điểm dừng này chỉ tạm ngưng chương trình khi một điều kiện cụ thể được thỏa mãn.
        Trong mã nguồn, việc malloc trả về NULL được phát hiện tại dòng if (p == NULL). Ta sẽ đặt breakpoint tại dòng đó với điều kiện p == NULL.
        Lệnh GDB cụ thể: (Giả sử dòng kiểm tra nằm ở dòng 27)
        ``` Bash
        (gdb) break memory_lab.c:27 if p == NULL
        ```
        Lệnh này có nghĩa là: "Dừng tại dòng 27 của file memory_lab.c, nhưng chỉ khi giá trị của biến p bằng NULL."

- Câu hỏi 2: Khi chương trình dừng tại điểm đó, lệnh GDB nào giúp bạn xác định được hàm và dòng mã đã gây ra yêu cầu cấp phát bộ nhớ thất bại?
    - Trả lời:
    `Lệnh GDB giúp xác định vị trí hiện tại trong chuỗi lời gọi hàm là backtrace (hoặc viết tắt là bt). Lệnh này hiển thị ngăn xếp lời gọi (call stack).
    ```Bash
    (gdb) bt
    ```
    Kết quả ví dụ và cách đọc:
    ```Bash
    #0  cause_memory_leak_and_oom () at memory_lab.c:27
    #1  0x00005555555551fa in main (argc=2, argv=0x7fffffffe4a8) at memory_lab.c:50
    ```
    Dòng #0 là khung stack trên cùng, cho biết chính xác vị trí chương trình đang dừng lại.
    Từ đây, ta xác định được:
    Hàm: cause_memory_leak_and_oom()
    Tệp và dòng mã: memory_lab.c:27
    Đây chính là nơi yêu cầu cấp phát bộ nhớ (malloc) đã thất bại.

- Câu hỏi 3: Dựa trên việc phân tích mã nguồn, hãy chỉ ra chính xác dòng code hoặc logic nào đã gây ra tình trạng Memory Leak.
    - Trả lời:
        Logic gây ra Memory Leak nằm hoàn toàn trong hàm cause_memory_leak_and_oom. Nguyên nhân gốc rễ là sự kết hợp của hai yếu tố:
        Cấp phát bộ nhớ trong vòng lặp vô tận: Lệnh void *p = malloc(1024); được thực thi liên tục bên trong vòng lặp while (1).
        Không giải phóng bộ nhớ: Sau mỗi lần cấp phát, không có lệnh free(p) nào được gọi.
    - Cơ chế gây rò rỉ:
        Ở mỗi vòng lặp, một khối bộ nhớ 1KB mới được cấp phát và địa chỉ của nó được lưu vào con trỏ p. Sang vòng lặp tiếp theo, p lại được gán một địa chỉ mới từ malloc. Điều này làm cho địa chỉ của khối bộ nhớ cũ bị mất dấu vĩnh viễn (orphaned memory), và chương trình không còn cách nào để truy cập hay giải phóng nó.
        Quá trình này lặp đi lặp lại, khiến bộ nhớ bị chiếm dụng ngày càng nhiều cho đến khi cạn kiệt, dẫn đến lỗi Out of Memory.
