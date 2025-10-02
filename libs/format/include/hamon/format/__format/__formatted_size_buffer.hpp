/**
 *	@file	__formatted_size_buffer.hpp
 *
 *	@brief	__formatted_size_buffer の定義
 */

#ifndef HAMON_FORMAT___FORMAT___FORMATTED_SIZE_BUFFER_HPP
#define HAMON_FORMAT___FORMAT___FORMATTED_SIZE_BUFFER_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format/__output_buffer.hpp>
#include <hamon/memory/addressof.hpp>

namespace hamon
{

namespace __format
{

// A buffer that counts the number of insertions.
//
// Since formatted_size only needs to know the size, the output itself is
// discarded.
template <__format::__fmt_char_type _CharT>
class __formatted_size_buffer : private __format::__output_buffer<_CharT>
{
public:
	using _Base = __format::__output_buffer<_CharT>;

	[[nodiscard]] __formatted_size_buffer()
		: _Base{ nullptr, 0, __prepare_write, hamon::addressof(__max_output_size_) }
	{
	}

	[[nodiscard]] auto __make_output_iterator()
	{
		return _Base::__make_output_iterator();
	}

	// This function does not need to be r-value qualified, however this is
	// consistent with similar objects.
	[[nodiscard]] size_t __result() &&
	{
		return __max_output_size_.__code_units_written();
	}

private:
	__max_output_size __max_output_size_{ 0 };

	static void
	__prepare_write([[maybe_unused]] __format::__output_buffer<_CharT>& __buffer, [[maybe_unused]] size_t __size_hint)
	{
		//// Note this function does not satisfy the requirement of giving a 1 code unit buffer.
		//_LIBCPP_ASSERT_INTERNAL(
		//	false, "Since __max_output_size_.__max_size_ == 0 there should never be call to this function.");
	}
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___FORMATTED_SIZE_BUFFER_HPP
