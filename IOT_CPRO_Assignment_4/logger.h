#ifndef LOGGER_H
#define LOGGER_H


#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>


// Syslog-compatible levels (0..7)
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


// Initialize the logger.
// - min_level: messages with level > min_level are ignored
// - file_path: optional path to log file; pass NULL to disable file output
// - append: if true, append to file; otherwise truncate
// Returns 0 on success, negative on error (e.g., cannot open file)
int logger_init(log_level_t min_level, const char *file_path, bool append);


// Change minimum level at runtime
void logger_set_level(log_level_t min_level);


// Get current minimum level
log_level_t logger_get_level(void);


// Close and clean up (flushes streams and closes file if any)
void logger_shutdown(void);


// Low-level logging entry point (prefer using macro below)
void logger_log_impl(log_level_t level, const char *file, int line,
const char *fmt, ...) __attribute__((format(printf,4,5)));


// Convenience macro that auto-fills file & line
#define LOG_MESSAGE(level, fmt, ...) \
logger_log_impl((level), __FILE__, __LINE__, (fmt), ##__VA_ARGS__)


// Optional: per-level convenience macros
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