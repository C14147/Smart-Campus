#pragma once

// Platform adaptation for ClassroomManager (Windows/Android only)
#if !defined(Q_OS_WIN) && !defined(Q_OS_ANDROID)
#error "ClassroomManager is only supported on Windows and Android platforms."
#endif
