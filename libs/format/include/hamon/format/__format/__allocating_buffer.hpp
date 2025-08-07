/**
 *	@file	__allocating_buffer.hpp
 *
 *	@brief	__allocating_buffer の定義
 */

#ifndef HAMON_FORMAT___FORMAT___ALLOCATING_BUFFER_HPP
#define HAMON_FORMAT___FORMAT___ALLOCATING_BUFFER_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format/__output_buffer.hpp>
#include <hamon/format/__format/__max_output_size.hpp>
#include <hamon/algorithm/copy_n.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/string.hpp>

namespace hamon
{

namespace __format
{

// A dynamically growing buffer.
template <__format::__fmt_char_type _CharT>
class __allocating_buffer : public __format::__output_buffer<_CharT>
{
public:
	__allocating_buffer(const __allocating_buffer&)            = delete;
	__allocating_buffer& operator=(const __allocating_buffer&) = delete;

	[[nodiscard]] __allocating_buffer() : __allocating_buffer {nullptr} {}

	[[nodiscard]]
	explicit __allocating_buffer(__format::__max_output_size* __max_output_size)
		: __output_buffer<_CharT> {__small_buffer_, __buffer_size_, __prepare_write, __max_output_size}
	{}

	~__allocating_buffer()
	{
		if (__ptr_ != __small_buffer_)
		{
			_Alloc{}.deallocate(__ptr_, this->__capacity());
		}
	}

	[[nodiscard]] hamon::basic_string_view<_CharT> __view() { return {__ptr_, this->__size()}; }

private:
	using _Alloc = hamon::allocator<_CharT>;

	// Since allocating is expensive the class has a small internal buffer. When
	// its capacity is exceeded a dynamic buffer will be allocated.
	static constexpr size_t __buffer_size_ = 256;
	_CharT __small_buffer_[__buffer_size_];

	_CharT* __ptr_ {__small_buffer_};

	void __grow_buffer(size_t __capacity)
	{
		if (__capacity < __buffer_size_)
		{
			return;
		}

//		_LIBCPP_ASSERT_INTERNAL(__capacity > this->__capacity(), "the buffer must grow");

		// _CharT is an implicit lifetime type so can be used without explicit
		// construction or destruction.
		_Alloc __alloc;
		auto __result = hamon::allocator_traits<_Alloc>::allocate_at_least(__alloc, __capacity);
		hamon::copy_n(__ptr_, this->__size(), __result.ptr);
		if (__ptr_ != __small_buffer_)
		{
			__alloc.deallocate(__ptr_, this->__capacity());
		}

		__ptr_ = __result.ptr;
		this->__buffer_moved(__ptr_, __result.count);
	}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_GCC("-Wconversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-float-conversion")

	void __prepare_write(size_t __size_hint)
	{
		__grow_buffer(hamon::max<size_t>(this->__capacity() + __size_hint, static_cast<size_t>(this->__capacity() * 1.6)));
	}

HAMON_WARNING_POP()

	static void __prepare_write(__format::__output_buffer<_CharT>& __buffer, size_t __size_hint)
	{
		static_cast<__allocating_buffer<_CharT>&>(__buffer).__prepare_write(__size_hint);
	}
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___ALLOCATING_BUFFER_HPP
