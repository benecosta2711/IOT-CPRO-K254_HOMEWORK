#ifndef LOGGER_H
#define LOGGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

typedef enum {
LOG_EMERGENCY = 0, // system is unusable
LOG_ALERT = 1, // action must be taken immediately
LOG_CRITICAL = 2, // critical conditions
LOG_ERROR = 3, // error conditions
LOG_WARNING = 4, // warning conditions
LOG_NOTICE = 5, // normal but significant condition
LOG_INFO = 6, // informational
LOG_DEBUG = 7 // debug-level messages
} log_level_t;

int logger_init(log_level_t min_level, const char *file_path, bool append);

void logger_set_level(log_level_t min_level);

log_level_t logger_get_level(void);

void logger_shutdown(void);

void logger_log_impl(log_level_t level, const char *file, int line,
const char *fmt, ...) __attribute__((format(printf,4,5)));

#define LOG_MESSAGE(level, fmt, ...) \
logger_log_impl((level), __FILE__, __LINE__, (fmt), ##__VA_ARGS__)

#define LOG_EMERG(fmt, ...) LOG_MESSAGE(LOG_EMERGENCY, (fmt), ##__VA_ARGS__)
#define LOG_ALERT(fmt, ...) LOG_MESSAGE(LOG_ALERT, (fmt), ##__VA_ARGS__)
#define LOG_CRIT(fmt, ...) LOG_MESSAGE(LOG_CRITICAL, (fmt), ##__VA_ARGS__)
#define LOG_ERR(fmt, ...) LOG_MESSAGE(LOG_ERROR, (fmt), ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) LOG_MESSAGE(LOG_WARNING, (fmt), ##__VA_ARGS__)
#define LOG_NOTICE(fmt, ...) LOG_MESSAGE(LOG_NOTICE, (fmt), ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) LOG_MESSAGE(LOG_INFO, (fmt), ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...) LOG_MESSAGE(LOG_DEBUG, (fmt), ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // LOGGER_H