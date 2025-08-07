/**
 *	@file	__direct_iterator_buffer.hpp
 *
 *	@brief	__direct_iterator_buffer の定義
 */

#ifndef HAMON_FORMAT___FORMAT___DIRECT_ITERATOR_BUFFER_HPP
#define HAMON_FORMAT___FORMAT___DIRECT_ITERATOR_BUFFER_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format/__output_buffer.hpp>
#include <hamon/stdexcept/length_error.hpp>

namespace hamon
{

namespace __format
{

// A buffer that directly writes to the underlying buffer.
template <class _OutIt, __format::__fmt_char_type _CharT>
class __direct_iterator_buffer : public __format::__output_buffer<_CharT>
{
public:
	[[nodiscard]] explicit __direct_iterator_buffer(_OutIt __out_it)
		: __direct_iterator_buffer {__out_it, nullptr} {}

	[[nodiscard]]
	explicit __direct_iterator_buffer(_OutIt __out_it, __format::__max_output_size* __max_output_size)
		: __output_buffer<_CharT>{/*std::__unwrap_iter*/(__out_it), __buffer_size, __prepare_write, __max_output_size},
		__out_it_(__out_it) {}

	[[nodiscard]] _OutIt __out_it() && { return __out_it_ + this->__size(); }

private:
	// The function format_to expects a buffer large enough for the output. The
	// function format_to_n has its own helper class that restricts the number of
	// write options. So this function class can pretend to have an infinite
	// buffer.
	static constexpr size_t __buffer_size = size_t(-1);

	_OutIt __out_it_;

	static void
	__prepare_write([[maybe_unused]] __format::__output_buffer<_CharT>& __buffer, [[maybe_unused]] size_t __size_hint)
	{
		hamon::detail::throw_length_error("__direct_iterator_buffer");
	}
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___DIRECT_ITERATOR_BUFFER_HPP
