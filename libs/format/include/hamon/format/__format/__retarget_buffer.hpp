﻿/**
 *	@file	__retarget_buffer.hpp
 *
 *	@brief	__retarget_buffer の定義
 */

#ifndef HAMON_FORMAT___FORMAT___RETARGET_BUFFER_HPP
#define HAMON_FORMAT___FORMAT___RETARGET_BUFFER_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/algorithm/transform.hpp>
#include <hamon/detail/exception_guard.hpp>
#include <hamon/iterator/concepts/contiguous_iterator.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/construct_at.hpp>
#include <hamon/memory/destroy_n.hpp>
#include <hamon/memory/uninitialized_copy_n.hpp>
#include <hamon/memory/uninitialized_default_construct_n.hpp>
#include <hamon/memory/uninitialized_fill_n.hpp>
#include <hamon/memory/uninitialized_move_n.hpp>
#include <hamon/string_view.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace __format
{

// A dynamically growing buffer intended to be used for retargeting a context.
//
// P2286 Formatting ranges adds range formatting support. It allows the user to
// specify the minimum width for the entire formatted range.  The width of the
// range is not known until the range is formatted. Formatting is done to an
// output_iterator so there's no guarantee it would be possible to add the fill
// to the front of the output. Instead the range is formatted to a temporary
// buffer and that buffer is formatted as a string.
//
// There is an issue with that approach, the format context used in
// std::formatter<T>::format contains the output iterator used as part of its
// type. So using this output iterator means there needs to be a new format
// context and the format arguments need to be retargeted to the new context.
// This retargeting is done by a basic_format_context specialized for the
// __iterator of this container.
//
// This class uses its own buffer management, since using vector
// would lead to a circular include with formatter for vector<bool>.
template <__format::__fmt_char_type _CharT>
class __retarget_buffer
{
	using _Alloc = hamon::allocator<_CharT>;

public:
	using value_type = _CharT;

	struct __iterator
	{
		using difference_type = ptrdiff_t;
		using value_type      = _CharT;

		constexpr explicit __iterator(__retarget_buffer& __buffer)
			: __buffer_(hamon::addressof(__buffer)) {}

		constexpr __iterator& operator=(const _CharT& __c)
		{
			__buffer_->push_back(__c);
			return *this;
		}

		constexpr __iterator& operator=(_CharT&& __c)
		{
			__buffer_->push_back(__c);
			return *this;
		}

		constexpr __iterator& operator*() { return *this; }
		constexpr __iterator& operator++() { return *this; }
		constexpr __iterator operator++(int) { return *this; }
		__retarget_buffer* __buffer_;
	};

	__retarget_buffer(const __retarget_buffer&)            = delete;
	__retarget_buffer& operator=(const __retarget_buffer&) = delete;

	explicit __retarget_buffer(size_t __size_hint)
	{
		// When the initial size is very small a lot of resizes happen
		// when elements added. So use a hard-coded minimum size.
		//
		// Note a size < 2 will not work
		// - 0 there is no buffer, while push_back requires 1 empty element.
		// - 1 multiplied by the grow factor is 1 and thus the buffer never
		//   grows.
//		auto __result = std::__allocate_at_least(__alloc_, hamon::max(__size_hint, 256 / sizeof(_CharT)));
		auto __result = hamon::allocator_traits<_Alloc>::allocate_at_least(__alloc_, hamon::max(__size_hint, 256 / sizeof(_CharT)));
		__ptr_        = __result.ptr;
		__capacity_   = __result.count;
	}

	~__retarget_buffer()
	{
		hamon::destroy_n(__ptr_, __size_);
		hamon::allocator_traits<_Alloc>::deallocate(__alloc_, __ptr_, __capacity_);
	}

	__iterator __make_output_iterator() { return __iterator {*this}; }

	void push_back(_CharT __c)
	{
		hamon::construct_at(__ptr_ + __size_, __c);
		++__size_;

		if (__size_ == __capacity_)
		{
			__grow_buffer();
		}
	}

	template <__format::__fmt_char_type _InCharT>
	void __copy(hamon::basic_string_view<_InCharT> __str)
	{
		size_t __n = __str.size();
		if (__size_ + __n >= __capacity_)
		{
			// Push_back requires the buffer to have room for at least one character.
			__grow_buffer(__size_ + __n + 1);
		}

		hamon::uninitialized_copy_n(__str.data(), __n, __ptr_ + __size_);
		__size_ += __n;
	}

	template <hamon::contiguous_iterator _Iterator,
		class _UnaryOperation,
		__format::__fmt_char_type _InCharT = typename hamon::iterator_traits<_Iterator>::value_type>
	void __transform(_Iterator __first, _Iterator __last, _UnaryOperation __operation)
	{
//		_LIBCPP_ASSERT_INTERNAL(__first <= __last, "not a valid range");

		size_t __n = static_cast<size_t>(__last - __first);
		if (__size_ + __n >= __capacity_)
		{
			// Push_back requires the buffer to have room for at least one character.
			__grow_buffer(__size_ + __n + 1);
		}

		hamon::uninitialized_default_construct_n(__ptr_ + __size_, __n);
		hamon::transform(__first, __last, __ptr_ + __size_, hamon::move(__operation));
		__size_ += __n;
	}

	void __fill(size_t __n, _CharT __value)
	{
		if (__size_ + __n >= __capacity_)
		{
			// Push_back requires the buffer to have room for at least one character.
			__grow_buffer(__size_ + __n + 1);
		}

		hamon::uninitialized_fill_n(__ptr_ + __size_, __n, __value);
		__size_ += __n;
	}

	hamon::basic_string_view<_CharT> __view() { return {__ptr_, __size_}; }

private:
	void __grow_buffer() { __grow_buffer(__capacity_ * 1.6); }

	void __grow_buffer(size_t __capacity)
	{
//		_LIBCPP_ASSERT_INTERNAL(__capacity > __capacity_, "the buffer must grow");
//		auto __result = std::__allocate_at_least(__alloc_, __capacity);
		auto __result = hamon::allocator_traits<_Alloc>::allocate_at_least(__alloc_, __capacity);
		auto __guard  = hamon::detail::make_exception_guard([&] {
			hamon::allocator_traits<_Alloc>::deallocate(__alloc_, __result.ptr, __result.count);
		});
		// This shouldn't throw, but just to be safe. Note that at -O1 this
		// guard is optimized away so there is no runtime overhead.
		hamon::uninitialized_move_n(__ptr_, __size_, __result.ptr);
		__guard.complete();
		hamon::destroy_n(__ptr_, __size_);
		hamon::allocator_traits<_Alloc>::deallocate(__alloc_, __ptr_, __capacity_);

		__ptr_      = __result.ptr;
		__capacity_ = __result.count;
	}
	HAMON_NO_UNIQUE_ADDRESS _Alloc __alloc_;
	_CharT* __ptr_;
	size_t __capacity_;
	size_t __size_ {0};
};


}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___RETARGET_BUFFER_HPP
