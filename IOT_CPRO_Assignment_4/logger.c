#include "logger.h"

#include <time.h>
#include <string.h>

// ===== Module state (internal) =====
static struct {
    log_level_t min_level;
    FILE *file_fp;          // NULL if disabled
    bool to_file;           // true if file_fp is valid
} g_logger = {
    .min_level = LOG_INFO,
    .file_fp   = NULL,
    .to_file   = false,
};

static const char *level_to_str(log_level_t lvl) {
    switch (lvl) {
        case LOG_EMERGENCY: return "EMERGENCY";
        case LOG_ALERT:     return "ALERT";
        case LOG_CRITICAL:  return "CRITICAL";
        case LOG_ERROR:     return "ERROR";
        case LOG_WARNING:   return "WARNING";
        case LOG_NOTICE:    return "NOTICE";
        case LOG_INFO:      return "INFO";
        case LOG_DEBUG:     return "DEBUG";
        default:            return "UNKNOWN";
    }
}

int logger_init(log_level_t min_level, const char *file_path, bool append) {
    g_logger.min_level = min_level;

    // Setup file output (optional)
    if (file_path && file_path[0] != '\0') {
        g_logger.file_fp = fopen(file_path, append ? "a" : "w");
        if (!g_logger.file_fp) {
            g_logger.to_file = false;
            return -1; // cannot open file
        }
        g_logger.to_file = true;
        // write a header line
        fprintf(g_logger.file_fp, "# Logger started. min_level=%d (%s)\n",
                (int)min_level, level_to_str(min_level));
        fflush(g_logger.file_fp);
    } else {
        g_logger.file_fp = NULL;
        g_logger.to_file = false;
    }

    return 0;
}

void logger_set_level(log_level_t min_level) {
    g_logger.min_level = min_level;
}

log_level_t logger_get_level(void) {
    return g_logger.min_level;
}

void logger_shutdown(void) {
    // flush console streams
    fflush(stdout);
    fflush(stderr);

    if (g_logger.to_file && g_logger.file_fp) {
        fflush(g_logger.file_fp);
        fclose(g_logger.file_fp);
        g_logger.file_fp = NULL;
        g_logger.to_file = false;
    }
}

// Internal: write a ready-formatted line to console streams
static void write_to_console(log_level_t level, const char *line) {
    // Serious issues (<= ERROR) -> stderr, otherwise stdout
    if (level <= LOG_ERROR) {
        fputs(line, stderr);
        fflush(stderr);
    } else {
        fputs(line, stdout);
        fflush(stdout);
    }
}

void logger_log_impl(log_level_t level, const char *file, int line,
                     const char *fmt, ...) {
    if (level > g_logger.min_level) {
        return; // filtered out
    }

    // 1) Format the user message safely with vsnprintf
    char msgbuf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msgbuf, sizeof(msgbuf), fmt, ap);
    va_end(ap);

    // 2) Build timestamp
    time_t now = time(NULL);
    struct tm tinfo;
    // Use localtime_r if available for reentrancy; fall back to localtime
    #if defined(_POSIX_THREAD_SAFE_FUNCTIONS)
        localtime_r(&now, &tinfo);
    #else
        struct tm *pt = localtime(&now);
        tinfo = *pt; // copy to stack
    #endif

    char timebuf[20]; // YYYY-MM-DD HH:MM:SS -> 19 + NUL
    strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", &tinfo);

    // Extract bare filename from path
    const char *fname = file;
    for (const char *p = file; *p; ++p) {
        if (*p == '/' || *p == '\\') fname = p + 1;
    }

    // 3) Assemble final line
    char linebuf[1280];
    int n = snprintf(linebuf, sizeof(linebuf),
                     "[%s] [%s] [%s:%d] - %s\n",
                     timebuf, level_to_str(level), fname, line, msgbuf);

    if (n < 0) {
        return; // formatting error
    }

    // 4) Console outputs
    write_to_console(level, linebuf);

    // 5) Optional file output
    if (g_logger.to_file && g_logger.file_fp) {
        fputs(linebuf, g_logger.file_fp);
        fflush(g_logger.file_fp);
    }
}