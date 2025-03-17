/**
 *	@file	windows.hpp
 *
 *	@brief	windows.h をインクルードするためのファイル
 */

#ifndef HAMON_CHRONO_DETAIL_WINDOWS_HPP
#define HAMON_CHRONO_DETAIL_WINDOWS_HPP

#include <hamon/config.hpp>

#if defined(HAMON_PLATFORM_WIN32)
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif
#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#include <windows.h>
#endif

#endif // HAMON_CHRONO_DETAIL_WINDOWS_HPP
