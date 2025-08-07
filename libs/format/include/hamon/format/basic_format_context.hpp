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

#if 1

// 28.5.6.7 Class template basic_format_context[format.context]

template <typename Out, typename charT>
	requires hamon::output_iterator<Out, charT const&>
class basic_format_context
{
private:
	hamon::basic_format_args<basic_format_context> args_;
	Out out_;
#  if 1//_LIBCPP_HAS_LOCALIZATION
	hamon::optional<std::locale> loc_;
#endif

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

#  if 1//_LIBCPP_HAS_LOCALIZATION
	std::locale locale()
	{
		// [format.context]/7
		if (!loc_)
		{
			loc_ = std::locale{};
		}
		return *loc_;
	}
#  endif

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
//#  if _LIBCPP_HAS_LOCALIZATION
	template <class _OtherOutIt, class _OtherCharT>
	friend basic_format_context<_OtherOutIt, _OtherCharT>
//	__format_context_create(_OtherOutIt, hamon::basic_format_args<basic_format_context<_OtherOutIt, _OtherCharT>>, hamon::optional<std::locale>&&);
	__format_context_create(_OtherOutIt, hamon::basic_format_args<basic_format_context<_OtherOutIt, _OtherCharT>>, std::locale const&);

	// Note: the Standard doesn't specify the required constructors.
	explicit basic_format_context(
//		Out __out_it, hamon::basic_format_args<basic_format_context> __args, hamon::optional<std::locale>&& __loc)
		Out __out_it, hamon::basic_format_args<basic_format_context> __args, std::locale const& __loc)
//		: args_(__args), out_(hamon::move(__out_it)), loc_(hamon::move(__loc)) {}
		: args_(__args), out_(hamon::move(__out_it)), loc_(__loc) {}
//#  else
	template <class _OtherOutIt, class _OtherCharT>
	friend basic_format_context<_OtherOutIt, _OtherCharT>
	__format_context_create(_OtherOutIt, hamon::basic_format_args<basic_format_context<_OtherOutIt, _OtherCharT>>);

	explicit basic_format_context(Out __out_it, hamon::basic_format_args<basic_format_context> __args)
		: args_(__args), out_(hamon::move(__out_it)) {}
//#  endif
};

#endif

#if 0
template <class _OutIt, class _CharT>
	requires hamon::output_iterator<_OutIt, const _CharT&>
class basic_format_context
{
public:
	using iterator  = _OutIt;
	using char_type = _CharT;
	template <class _Tp>
	using formatter_type = hamon::formatter<_Tp, _CharT>;

	hamon::basic_format_arg<basic_format_context> arg(size_t __id) const noexcept
	{
		return __args_.get(__id);
	}

#  if _LIBCPP_HAS_LOCALIZATION
	std::locale locale()
	{
		if (!__loc_)
		{
			__loc_ = std::locale {};
		}
		return *__loc_;
	}
#  endif

	iterator out() { return hamon::move(__out_it_); }
	void advance_to(iterator __it) { __out_it_ = hamon::move(__it); }

private:
	iterator __out_it_;
	hamon::basic_format_args<basic_format_context> __args_;
#  if _LIBCPP_HAS_LOCALIZATION

	// The Standard doesn't specify how the locale is stored.
	// [format.context]/6
	// std::locale locale();
	//   Returns: The locale passed to the formatting function if the latter
	//   takes one, and std::locale() otherwise.
	// This is done by storing the locale of the constructor in this optional. If
	// locale() is called and the optional has no value the value will be created.
	// This allows the implementation to lazily create the locale.
	// TODO FMT Validate whether lazy creation is the best solution.
	hamon::optional<std::locale> __loc_;

	template <class _OtherOutIt, class _OtherCharT>
	friend basic_format_context<_OtherOutIt, _OtherCharT>
	__format_context_create(_OtherOutIt, hamon::basic_format_args<basic_format_context<_OtherOutIt, _OtherCharT>>, hamon::optional<std::locale>&&);

	// Note: the Standard doesn't specify the required constructors.
	explicit basic_format_context(
		_OutIt __out_it, hamon::basic_format_args<basic_format_context> __args, hamon::optional<std::locale>&& __loc)
		: __out_it_(hamon::move(__out_it)), __args_(__args), __loc_(hamon::move(__loc)) {}
#  else
	template <class _OtherOutIt, class _OtherCharT>
	friend basic_format_context<_OtherOutIt, _OtherCharT>
	__format_context_create(_OtherOutIt, hamon::basic_format_args<basic_format_context<_OtherOutIt, _OtherCharT>>);

	explicit basic_format_context(_OutIt __out_it, hamon::basic_format_args<basic_format_context> __args)
		: __out_it_(hamon::move(__out_it)), __args_(__args) {}
#  endif

public:
	basic_format_context(const basic_format_context&)            = delete;
	basic_format_context& operator=(const basic_format_context&) = delete;
};
#endif

}	// namespace hamon

#include <hamon/format/formatter.hpp>

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_CONTEXT_HPP
