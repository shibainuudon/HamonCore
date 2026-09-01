/**
 *	@file	ostream.hpp
 *
 *	@brief	OStream library
 */

#ifndef HAMON_OSTREAM_HPP
#define HAMON_OSTREAM_HPP

#include <hamon/ostream/basic_ostream.hpp>
#include <hamon/ostream/endl.hpp>
#include <hamon/ostream/ends.hpp>
#include <hamon/ostream/flush.hpp>
#include <hamon/ostream/ostream.hpp>
#include <hamon/ostream/wostream.hpp>

#if 0	// TODO
// [ostream.manip], standard basic_ostream manipulators
template <typename charT, typename traits>
basic_ostream<charT, traits>& emit_on_flush(basic_ostream<charT, traits>& os);
template <typename charT, typename traits>
basic_ostream<charT, traits>& noemit_on_flush(basic_ostream<charT, traits>& os);
template <typename charT, typename traits>
basic_ostream<charT, traits>& flush_emit(basic_ostream<charT, traits>& os);

// [ostream.formatted.print], print functions
template <typename... Args>
void print(ostream& os, format_string<Args...> fmt, Args&&... args);
template <typename... Args>
void println(ostream& os, format_string<Args...> fmt, Args&&... args);
void println(ostream& os);

void vprint_unicode(ostream& os, string_view fmt, format_args args);
void vprint_nonunicode(ostream& os, string_view fmt, format_args args);
#endif

#endif // HAMON_OSTREAM_HPP
