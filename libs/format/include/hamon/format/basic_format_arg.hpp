/**
 *	@file	basic_format_arg.hpp
 *
 *	@brief	basic_format_arg の定義
 */

#ifndef HAMON_FORMAT_BASIC_FORMAT_ARG_HPP
#define HAMON_FORMAT_BASIC_FORMAT_ARG_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::basic_format_arg;

}	// namespace hamon

#else

#include <hamon/string_view.hpp>
#include <hamon/variant.hpp>

namespace hamon
{

// 28.5.8.1 Class template basic_format_arg[format.arg]

template <typename Context>
class basic_format_arg
{
public:
	class handle;

private:
	using char_type = typename Context::char_type;                              // exposition only

	hamon::variant<hamon::monostate, bool, char_type,
		int, unsigned int, long long int, unsigned long long int,
		float, double, long double,
		const char_type*, hamon::basic_string_view<char_type>,
		const void*, handle> value;                                         // exposition only

	template <typename T>
	explicit basic_format_arg(T& v) noexcept;                 // exposition only

public:
	basic_format_arg() noexcept;

	explicit operator bool() const noexcept;

	//template <typename Visitor>
	//decltype(auto) visit(this basic_format_arg arg, Visitor&& vis);

	//template <typename R, typename Visitor>
	//R visit(this basic_format_arg arg, Visitor&& vis);
};

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_ARG_HPP
