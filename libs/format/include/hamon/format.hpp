/**
 *	@file	format.hpp
 *
 *	@brief	Format library
 */

#ifndef HAMON_FORMAT_HPP
#define HAMON_FORMAT_HPP

// TODO:
// * stack
// * queue
// * priority_queue
// * chrono
// * filesystem::path
// * thread::id
// * vector<bool>

#include <hamon/format/basic_format_arg.hpp>
#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/basic_format_context.hpp>
#include <hamon/format/basic_format_parse_context.hpp>
#include <hamon/format/basic_format_string.hpp>
#include <hamon/format/config.hpp>
#include <hamon/format/enable_nonlocking_formatter_optimization.hpp>
#include <hamon/format/format.hpp>
#include <hamon/format/formattable.hpp>
#include <hamon/format/formatted_size.hpp>
#include <hamon/format/formatter.hpp>
#include <hamon/format/format_args.hpp>
#include <hamon/format/format_context.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/format/format_kind.hpp>
#include <hamon/format/format_parse_context.hpp>
#include <hamon/format/format_string.hpp>
#include <hamon/format/format_to.hpp>
#include <hamon/format/format_to_n.hpp>
#include <hamon/format/format_to_n_result.hpp>
#include <hamon/format/make_format_args.hpp>
#include <hamon/format/make_wformat_args.hpp>
#include <hamon/format/range_format.hpp>
#include <hamon/format/range_formatter.hpp>
#include <hamon/format/runtime_format.hpp>
#include <hamon/format/vformat.hpp>
#include <hamon/format/vformat_to.hpp>
#include <hamon/format/wformat_args.hpp>
#include <hamon/format/wformat_context.hpp>
#include <hamon/format/wformat_parse_context.hpp>
#include <hamon/format/wformat_string.hpp>

#if 0

namespace std {
// [format.context], class template basic_format_context
//template<class Out, class charT> class basic_format_context;
//using format_context = basic_format_context<unspecified, char>;
//using wformat_context = basic_format_context<unspecified, wchar_t>;

// [format.args], class template basic_format_args
//template<class Context> class basic_format_args;
//using format_args = basic_format_args<format_context>;
//using wformat_args = basic_format_args<wformat_context>;

// [format.fmt.string], class template basic_format_string
//template<class charT, class... Args>
//struct basic_format_string;

//template<class charT> struct runtime-format-string {                  // exposition only
//private:
//	basic_string_view<charT> str;                                       // exposition only
//public:
//	runtime-format-string(basic_string_view<charT> s) noexcept : str(s) {}
//	runtime-format-string(const runtime-format-string&) = delete;
//	runtime-format-string& operator=(const runtime-format-string&) = delete;
//};
//runtime-format-string<char> runtime_format(string_view fmt) noexcept { return fmt; }
//runtime-format-string<wchar_t> runtime_format(wstring_view fmt) noexcept { return fmt; }

//template<class... Args>
//using format_string = basic_format_string<char, type_identity_t<Args>...>;
//template<class... Args>
//using wformat_string = basic_format_string<wchar_t, type_identity_t<Args>...>;

// [format.functions], formatting functions
//template<class... Args>
//string format(format_string<Args...> fmt, Args&&... args);
//template<class... Args>
//wstring format(wformat_string<Args...> fmt, Args&&... args);
//template<class... Args>
//string format(const locale& loc, format_string<Args...> fmt, Args&&... args);
//template<class... Args>
//wstring format(const locale& loc, wformat_string<Args...> fmt, Args&&... args);

//string vformat(string_view fmt, format_args args);
//wstring vformat(wstring_view fmt, wformat_args args);
//string vformat(const locale& loc, string_view fmt, format_args args);
//wstring vformat(const locale& loc, wstring_view fmt, wformat_args args);

//template<class Out, class... Args>
//Out format_to(Out out, format_string<Args...> fmt, Args&&... args);
//template<class Out, class... Args>
//Out format_to(Out out, wformat_string<Args...> fmt, Args&&... args);
//template<class Out, class... Args>
//Out format_to(Out out, const locale& loc, format_string<Args...> fmt, Args&&... args);
//template<class Out, class... Args>
//Out format_to(Out out, const locale& loc, wformat_string<Args...> fmt, Args&&... args);

//template<class Out>
//Out vformat_to(Out out, string_view fmt, format_args args);
//template<class Out>
//Out vformat_to(Out out, wstring_view fmt, wformat_args args);
//template<class Out>
//Out vformat_to(Out out, const locale& loc, string_view fmt, format_args args);
//template<class Out>
//Out vformat_to(Out out, const locale& loc, wstring_view fmt, wformat_args args);

//template<class Out> struct format_to_n_result {
//	Out out;
//	iter_difference_t<Out> size;
//};
//template<class Out, class... Args>
//format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
//									format_string<Args...> fmt, Args&&... args);
//template<class Out, class... Args>
//format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
//									wformat_string<Args...> fmt, Args&&... args);
//template<class Out, class... Args>
//format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
//									const locale& loc, format_string<Args...> fmt,
//									Args&&... args);
//template<class Out, class... Args>
//format_to_n_result<Out> format_to_n(Out out, iter_difference_t<Out> n,
//									const locale& loc, wformat_string<Args...> fmt,
//									Args&&... args);

//template<class... Args>
//size_t formatted_size(format_string<Args...> fmt, Args&&... args);
//template<class... Args>
//size_t formatted_size(wformat_string<Args...> fmt, Args&&... args);
//template<class... Args>
//size_t formatted_size(const locale& loc, format_string<Args...> fmt, Args&&... args);
//template<class... Args>
//size_t formatted_size(const locale& loc, wformat_string<Args...> fmt, Args&&... args);

// [format.formatter], formatter
//template<class T, class charT = char> struct formatter;

// [format.formatter.locking], formatter locking
//template<class T>
//constexpr bool enable_nonlocking_formatter_optimization = false;

// [format.formattable], concept formattable
//template<class T, class charT>
//concept formattable = see below;

//template<class R, class charT>
//concept const-formattable-range =                                   // exposition only
//ranges::input_range<const R> &&
//formattable<ranges::range_reference_t<const R>, charT>;

//template<class R, class charT>
//using fmt-maybe-const =                                             // exposition only
//conditional_t<const-formattable-range<R, charT>, const R, R>;

// [format.parse.ctx], class template basic_format_parse_context
//template<class charT> class basic_format_parse_context;
//using format_parse_context = basic_format_parse_context<char>;
//using wformat_parse_context = basic_format_parse_context<wchar_t>;

// [format.range], formatting of ranges
// [format.range.fmtkind], variable template format_kind
//enum class range_format {
//	disabled,
//	map,
//	set,
//	sequence,
//	string,
//	debug_string
//};

//template<class R>
//constexpr unspecified format_kind = unspecified;
//
//template<ranges::input_range R>
//requires same_as<R, remove_cvref_t<R>>
//constexpr range_format format_kind<R> = see below;

//// [format.range.formatter], class template range_formatter
//template<class T, class charT = char>
//requires same_as<remove_cvref_t<T>, T> && formattable<T, charT>
//class range_formatter;

// [format.range.fmtdef], class template range-default-formatter
//template<range_format K, ranges::input_range R, class charT>
//struct range-default-formatter;                                     // exposition only

// [format.range.fmtmap], [format.range.fmtset], [format.range.fmtstr], specializations for maps, sets, and strings
//template<ranges::input_range R, class charT>
//requires (format_kind<R> != range_format::disabled) &&
//formattable<ranges::range_reference_t<R>, charT>
//struct formatter<R, charT> : range-default-formatter<format_kind<R>, R, charT> { };
//
//template<ranges::input_range R>
//requires (format_kind<R> != range_format::disabled)
//constexpr bool enable_nonlocking_formatter_optimization<R> = false;

// [format.arguments], arguments
// [format.arg], class template basic_format_arg
//template<class Context> class basic_format_arg;

// [format.arg.store], class template format-arg-store
//template<class Context, class... Args> class format-arg-store;        // exposition only

//template<class Context = format_context, class... Args>
//format-arg-store<Context, Args...>
//make_format_args(Args&... fmt_args);
//template<class... Args>
//format-arg-store<wformat_context, Args...>
//make_wformat_args(Args&... args);

// [format.error], class format_error
//class format_error;
}

#endif

#endif // HAMON_FORMAT_HPP
