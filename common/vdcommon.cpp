/*
   Copyright (C) 2013 Red Hat, Inc.

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

#include "vdcommon.h"

#include <stdarg.h>
#include <versionhelpers.h>

SystemVersion supported_system_version()
{
    if (IsWindowsVistaOrGreater()) {
        return SYS_VER_WIN_7_CLASS;
    }
    if (IsWindowsXPOrGreater()) {
        return SYS_VER_WIN_XP_CLASS;
    }
    return SYS_VER_UNSUPPORTED;
}

#ifndef HAVE_SWPRINTF_S
int vdagent_swprintf_s(wchar_t *buf, size_t len, const wchar_t *format, ...)
{
    va_list ap;
    va_start(ap, format);
    int res = _vsnwprintf(buf, len, format, ap);
    va_end(ap);
    if ((res < 0 || (unsigned) res >= len) && len > 0) {
        buf[0] = 0;
    }
    return res;
}
#endif
