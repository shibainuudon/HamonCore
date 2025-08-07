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

#include <hamon/string_view.hpp>

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
	iterator begin_;                                    // exposition only
	iterator end_;                                      // exposition only
	enum indexing { unknown, manual, automatic };       // exposition only
	indexing indexing_;                                 // exposition only
	size_t next_arg_id_;                                // exposition only
	size_t num_args_;                                   // exposition only

public:
	constexpr explicit basic_format_parse_context(hamon::basic_string_view<charT> fmt) noexcept;
	basic_format_parse_context(basic_format_parse_context const&) = delete;
	basic_format_parse_context& operator=(basic_format_parse_context const&) = delete;

	constexpr const_iterator begin() const noexcept;
	constexpr const_iterator end() const noexcept;
	constexpr void advance_to(const_iterator it);

	constexpr size_t next_arg_id();
	constexpr void check_arg_id(size_t id);

	template <typename... Ts>
	constexpr void check_dynamic_spec(size_t id) noexcept;
	constexpr void check_dynamic_spec_integral(size_t id) noexcept;
	constexpr void check_dynamic_spec_string(size_t id) noexcept;
};

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_BASIC_FORMAT_PARSE_CONTEXT_HPP
