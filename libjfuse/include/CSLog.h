/*-
 * jFUSE - FUSE bindings for Java
 * Copyright (C) 2008-2009  Erik Larsson <erik82@kth.se>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _CSLOG_H
#define	_CSLOG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>

#ifdef DEBUG
#define DEFAULT_LOG_ENABLE_TRACE    1
#define DEFAULT_LOG_ENABLE_MEMORY   1
#define DEFAULT_LOG_ENABLE_DEBUG    1
#define DEFAULT_LOG_ENABLE_WARNING  1
#define DEFAULT_LOG_ENABLE_ERROR    1
#define DEFAULT_LOG_ENABLE_PRINT    1
#else
#define DEFAULT_LOG_ENABLE_TRACE    0
#define DEFAULT_LOG_ENABLE_MEMORY   1
#define DEFAULT_LOG_ENABLE_DEBUG    0
#define DEFAULT_LOG_ENABLE_WARNING  1
#define DEFAULT_LOG_ENABLE_ERROR    1
#define DEFAULT_LOG_ENABLE_PRINT    1
#endif

#ifndef LOG_ENABLE_TRACE
#define LOG_ENABLE_TRACE    DEFAULT_LOG_ENABLE_TRACE
#endif

#ifndef LOG_ENABLE_MEMORY
#define LOG_ENABLE_MEMORY   DEFAULT_LOG_ENABLE_MEMORY
#endif

#ifndef LOG_ENABLE_DEBUG
#define LOG_ENABLE_DEBUG    DEFAULT_LOG_ENABLE_DEBUG
#endif

#ifndef LOG_ENABLE_WARNING
#define LOG_ENABLE_WARNING  DEFAULT_LOG_ENABLE_WARNING
#endif

#ifndef LOG_ENABLE_ERROR
#define LOG_ENABLE_ERROR    DEFAULT_LOG_ENABLE_ERROR
#endif

#ifndef LOG_ENABLE_PRINT
#define LOG_ENABLE_PRINT    DEFAULT_LOG_ENABLE_PRINT
#endif

static inline void CSPanic() {
    char *ptr = 0;
    *ptr = 0;
}

#if LOG_ENABLE_TRACE
#define CSLogTrace(...) do { FILE *logFile = stderr; fprintf(logFile, "TRACE: "); fprintf(logFile, __VA_ARGS__); fprintf(logFile, "\n"); fflush(logFile); } while(0)
#define CSLogTraceEnter(...) do { FILE *logFile = stderr; fprintf(logFile, "ENTER: "); fprintf(logFile, __VA_ARGS__); fprintf(logFile, "\n"); fflush(logFile); } while(0)
#define CSLogTraceLeave(...) do { FILE *logFile = stderr; fprintf(logFile, "LEAVE: "); fprintf(logFile, __VA_ARGS__); fprintf(logFile, "\n"); fflush(logFile); } while(0)
#else
#define CSLogTrace(...)
#define CSLogTraceEnter(...)
#define CSLogTraceLeave(...)
#endif

#if LOG_ENABLE_MEMORY
#define CSLogMemory(...) do { FILE *logFile = stderr; fprintf(logFile, "MEMORY: "); fprintf(logFile, __VA_ARGS__); fprintf(logFile, "\n"); fflush(logFile); } while(0)
#else
#define CSLogMemory(...)
#endif

#if LOG_ENABLE_DEBUG
#define CSLogDebug(...) do { FILE *logFile = stderr; fprintf(logFile, "DEBUG: "); fprintf(logFile, __VA_ARGS__); fprintf(logFile, "\n"); fflush(logFile); } while(0)
#else
#define CSLogDebug(...)
#endif

#if LOG_ENABLE_WARNING
#define CSLogWarning(...) do { FILE *logFile = stderr; fprintf(logFile, "%s(%d) ", __FILE__, __LINE__); fprintf(logFile, "WARNING: "); fprintf(logFile, __VA_ARGS__); fprintf(logFile, "\n"); fflush(logFile); } while(0)
#else
#define CSLogWarning(...)
#endif

#if LOG_ENABLE_ERROR
#define CSLogError(...) do { FILE *logFile = stderr; fprintf(logFile, "%s(%d) ", __FILE__, __LINE__); fprintf(logFile, "ERROR: "); fprintf(logFile, __VA_ARGS__); fprintf(logFile, "\n"); fflush(logFile); } while(0)
#else
#define CSLogError(...)
#endif

#if LOG_ENABLE_PRINT
#define CSLogPrint(...) do { FILE *logFile = stderr; fprintf(logFile, __VA_ARGS__); fprintf(logFile, "\n"); fflush(logFile); } while(0)
#else
#define CSLogPrint(...)
#endif

#define CSPanicWithMessage(...) do { FILE *logFile = stderr; fprintf(logFile, "%s(%d) ", __FILE__, __LINE__); fprintf(logFile, "PANIC: "); fprintf(logFile, __VA_ARGS__); fprintf(logFile, "\n"); fflush(logFile); CSPanic(); } while(0)

#ifdef	__cplusplus
}
#endif

#endif	/* _CSLOG_H */

