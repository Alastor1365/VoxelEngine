#pragma once
#include<spdlog/spdlog.h>

namespace VoxelEngine
{
#ifdef NDEBUG

#define Log_info(...)
#define Log_warn(...)
#define Log_error(...)
#define Log_crit(...)

#else

#define Log_info(...) spdlog::info(__VA_ARGS__)
#define Log_warn(...) spdlog::warn(__VA_ARGS__)
#define Log_error(...) spdlog::error(__VA_ARGS__)
#define Log_crit(...) spdlog::critical(__VA_ARGS__)

#endif

}