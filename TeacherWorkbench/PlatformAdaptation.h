#pragma once

// Platform adaptation for TeacherWorkbench (Windows/macOS/Android only)
#if !defined(Q_OS_WIN) && !defined(Q_OS_MAC) && !defined(Q_OS_ANDROID)
#error "TeacherWorkbench is only supported on Windows, macOS, and Android platforms."
#endif
