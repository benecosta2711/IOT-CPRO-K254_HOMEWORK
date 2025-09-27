#include <stdio.h>
#include "logger.h"


int connect_db(void) { return -1; }


int main(void) {
// Khởi tạo: min level = LOG_INFO, ghi file vào "app.log" (truncate)
if (logger_init(LOG_INFO, "app.log", /*append=*/false) != 0) {
fprintf(stderr, "Failed to initialize logger file. Continue with console only.\n");
}


LOG_INFO("System initialized (pid=%d)", 1234);
LOG_DEBUG("This debug should NOT appear since min_level is INFO");


// Thử thay đổi mức lọc ở runtime
logger_set_level(LOG_DEBUG);
LOG_DEBUG("Now debug logs are visible");


// Ví dụ nghiêm trọng -> đi stderr + file
if (connect_db() < 0) {
LOG_ERR("Failed to connect to database: code=%d", -1001);
}


// Ví dụ format theo đề bài
LOG_WARN("Battery low: %d%%", 12);


logger_shutdown();
return 0;
}