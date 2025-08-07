/**
 *	@file	basic_format_context.hpp
 *
 *	@brief	basic_format_context の定義
 */

#ifndef HAMON_FORMAT_BASIC_FORMAT_CONTEXT_HPP
#define HAMON_FORMAT_BASIC_FORMAT_CONTEXT_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::basic_format_context;

}	// namespace hamon

#else

#include <hamon/format/basic_format_arg.hpp>
#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/formatter.hpp>
#include <locale>

namespace hamon
{

// 28.5.6.7 Class template basic_format_context[format.context]

template <typename Out, typename charT>
class basic_format_context
{
	hamon::basic_format_args<basic_format_context> args_;      // exposition only
	Out out_;                                           // exposition only

	basic_format_context(basic_format_context const&) = delete;
	basic_format_context& operator=(basic_format_context const&) = delete;

public:
	using iterator = Out;
	using char_type = charT;

	template <typename T>
	using formatter_type = hamon::formatter<T, charT>;

	hamon::basic_format_arg<basic_format_context> arg(size_t id) const noexcept;
	std::locale locale();

	iterator out();
	void advance_to(iterator it);
};

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_CONTEXT_HPP
