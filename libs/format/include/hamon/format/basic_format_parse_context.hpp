/**
 *	@file	basic_format_parse_context.hpp
 *
 *	@brief	basic_format_parse_context の定義
 */

#ifndef HAMON_FORMAT_BASIC_FORMAT_PARSE_CONTEXT_HPP
#define HAMON_FORMAT_BASIC_FORMAT_PARSE_CONTEXT_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::basic_format_parse_context;

}	// namespace hamon

#else

#include <hamon/format/format_error.hpp>
#include <hamon/string_view.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>

namespace hamon
{

// 28.5.6.6 Class template basic_format_parse_context[format.parse.ctx]

template <typename charT>
class basic_format_parse_context
{
public:
	using char_type = charT;
	using const_iterator = typename hamon::basic_string_view<charT>::const_iterator;
	using iterator = const_iterator;

private:
	iterator begin_;
	iterator end_;
	enum indexing { unknown, manual, automatic };
	indexing indexing_;
	size_t next_arg_id_;
	size_t num_args_;

private:
public:	// TODO
	constexpr explicit
	basic_format_parse_context(hamon::basic_string_view<charT> fmt, hamon::size_t num_args) noexcept
		: begin_(fmt.begin())
		, end_(fmt.end())
		, indexing_(unknown)
		, next_arg_id_(0)
		, num_args_(num_args)
	{}

public:
	constexpr explicit
	basic_format_parse_context(hamon::basic_string_view<charT> fmt) noexcept
		// [format.parse.ctx]/3
		: begin_(fmt.begin())
		, end_(fmt.end())
		, indexing_(unknown)
		, next_arg_id_(0)
		, num_args_(0)
	{}

	basic_format_parse_context(basic_format_parse_context const&) = delete;
	basic_format_parse_context& operator=(basic_format_parse_context const&) = delete;

	constexpr const_iterator begin() const noexcept
	{
		// [format.parse.ctx]/4
		return begin_;
	}

	constexpr const_iterator end() const noexcept
	{
		// [format.parse.ctx]/5
		return end_;
	}

	constexpr void advance_to(const_iterator it)
	{
		// [format.parse.ctx]/7
		begin_ = it;
	}

	constexpr size_t next_arg_id()
	{
		// [format.parse.ctx]/9
		if (indexing_ == manual)
		{
			hamon::detail::throw_format_error("mixing of automatic and manual argument indexing");
		}

		// [format.parse.ctx]/8
		if (indexing_ == unknown)
		{
			indexing_ = automatic;
		}

		// [format.parse.ctx]/10
		if (hamon::is_constant_evaluated() && next_arg_id_ >= num_args_)
		{
			hamon::detail::throw_format_error("invalid arg-id in format string");
		}

		// [format.parse.ctx]/8
		return next_arg_id_++;
	}

	constexpr void check_arg_id(size_t id)
	{
		// [format.parse.ctx]/12
		if (indexing_ == automatic)
		{
			hamon::detail::throw_format_error("mixing of automatic and manual argument indexing");
		}

		// [format.parse.ctx]/11
		if (indexing_ == unknown)
		{
			indexing_ = manual;
		}

		// [format.parse.ctx]/13
		if (hamon::is_constant_evaluated() && id >= num_args_)
		{
			hamon::detail::throw_format_error("invalid arg-id in format string");
		}
	}

	// TODO
	template <typename... Ts>
	constexpr void check_dynamic_spec(size_t id) noexcept;

	// TODO
	constexpr void check_dynamic_spec_integral(size_t id) noexcept;

	// TODO
	constexpr void check_dynamic_spec_string(size_t id) noexcept;
};

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_PARSE_CONTEXT_HPP
