#pragma once

// Platform adaptation for CampusCore (Linux/Windows only)
#if !defined(Q_OS_WIN) && !defined(Q_OS_LINUX)
#error "CampusCore is only supported on Windows and Linux platforms."
#endif
