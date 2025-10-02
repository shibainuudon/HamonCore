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

#include <hamon/format/basic_format_context_fwd.hpp>
#include <hamon/format/basic_format_arg.hpp>
#include <hamon/format/basic_format_args.hpp>
#include <hamon/format/formatter_fwd.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/iterator/concepts/output_iterator.hpp>
#include <hamon/optional.hpp>
#include <hamon/utility/move.hpp>
#include <locale>

namespace hamon
{

// 28.5.6.7 Class template basic_format_context[format.context]

template <typename Out, typename charT>
	requires hamon::output_iterator<Out, charT const&>
class basic_format_context
{
private:
	hamon::basic_format_args<basic_format_context> args_;
	Out out_;
	hamon::optional<std::locale> loc_;

private:
	basic_format_context(basic_format_context const&) = delete;
	basic_format_context& operator=(basic_format_context const&) = delete;

public:
	using iterator = Out;
	using char_type = charT;
	template <typename T>
	using formatter_type = hamon::formatter<T, charT>;

	hamon::basic_format_arg<basic_format_context>
	arg(hamon::size_t id) const noexcept
	{
		// [format.context]/6
		return args_.get(id);
	}

	std::locale locale()
	{
		// [format.context]/7
		if (!loc_)
		{
			loc_ = std::locale{};
		}
		return *loc_;
	}

	iterator out()
	{
		// [format.context]/8
		return hamon::move(out_);
	}

	void advance_to(iterator it)
	{
		// [format.context]/9
		out_ = hamon::move(it);
	}

private:
	template <class _OtherOutIt, class _OtherCharT>
	friend basic_format_context<_OtherOutIt, _OtherCharT>
	__format_context_create(_OtherOutIt, hamon::basic_format_args<basic_format_context<_OtherOutIt, _OtherCharT>>, std::locale const&);

	// Note: the Standard doesn't specify the required constructors.
	explicit basic_format_context(
		Out __out_it, hamon::basic_format_args<basic_format_context> __args, std::locale const& __loc)
		: args_(__args), out_(hamon::move(__out_it)), loc_(__loc) {}

	template <class _OtherOutIt, class _OtherCharT>
	friend basic_format_context<_OtherOutIt, _OtherCharT>
	__format_context_create(_OtherOutIt, hamon::basic_format_args<basic_format_context<_OtherOutIt, _OtherCharT>>);

	explicit basic_format_context(Out __out_it, hamon::basic_format_args<basic_format_context> __args)
		: args_(__args), out_(hamon::move(__out_it)) {}
};

}	// namespace hamon

#include <hamon/format/formatter.hpp>

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_CONTEXT_HPP
