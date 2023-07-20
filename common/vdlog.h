/*
   Copyright (C) 2009 Red Hat, Inc.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _H_VDLOG
#define _H_VDLOG

#include <stdio.h>
#include <tchar.h>
#include <crtdbg.h>
#include <windows.h>
#include <time.h>
#include <sys/timeb.h>

#include "vdcommon.h"

class VDLog {
public:
    ~VDLog();
    static VDLog* get(TCHAR* path = NULL);
#ifdef __GNUC__
    __attribute__((__format__ (gnu_printf, 1, 2)))
#endif
    static void printf(const char* format, ...);
#ifdef __GNUC__
    __attribute__((__format__ (gnu_printf, 3, 4)))
#endif
    static void logf(const char *type, const char *function, const char* format, ...);

private:
    VDLog(FILE* handle);

private:
    static VDLog* _log;
    FILE* _handle;
};

typedef enum {
  LOG_DEBUG,
  LOG_TRACE,
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
  LOG_FATAL
} VDLogLevel;

extern VDLogLevel log_level;

#define LOG(type, format, ...) do {                                     \
    if (LOG_ ## type >= log_level && LOG_ ## type <= LOG_FATAL) {       \
        VDLog::logf(#type, __FUNCTION__, format "\n", ## __VA_ARGS__);  \
    }                                                                   \
} while(0)


#define vd_printf(format, ...) LOG(INFO, format, ## __VA_ARGS__)
#define LOG_TRACE(format, ...) LOG(TRACE, format, ## __VA_ARGS__)
#define LOG_INFO(format, ...) LOG(INFO, format, ## __VA_ARGS__)
#define LOG_WARN(format, ...) LOG(WARN, format, ## __VA_ARGS__)
#define LOG_ERROR(format, ...) LOG(ERROR, format, ## __VA_ARGS__)

#define DBGLEVEL 1000

#define DBG(level, format, ...) do {            \
    if (level <= DBGLEVEL) {                    \
        LOG(DEBUG, format, ## __VA_ARGS__);     \
    }                                           \
} while(0)

#define ASSERT(x) _ASSERTE(x)

void log_version();

#endif
