/**
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

#include <hamon/format/detail/__basic_format_arg_value.hpp>
#include <hamon/format/__format/__determine_arg_t.hpp>
#include <hamon/format/formatter.hpp>
#include <hamon/format/basic_format_arg.hpp>
#include <hamon/format/basic_format_context.hpp>
#include <hamon/format/format_error.hpp>
#include <hamon/format/other/__visit_format_arg.hpp>
#include <hamon/concepts/same_as.hpp>

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
	void __grow_buffer() { __grow_buffer(static_cast<size_t>(static_cast<double>(__capacity_) * 1.6)); }

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

// A specialization for __retarget_buffer
//
// See __retarget_buffer for the motivation for this specialization.
//
// This context holds a reference to the instance of the basic_format_context
// that is retargeted. It converts a formatting argument when it is requested
// during formatting. It is expected that the usage of the arguments is rare so
// the lookups are not expected to be used often. An alternative would be to
// convert all elements during construction.
//
// The elements of the retargets context are only used when an underlying
// formatter uses a locale specific formatting or an formatting argument is
// part for the format spec. For example
//   format("{:256:{}}", input, 8);
// Here the width of an element in input is determined dynamically.
// Note when the top-level element has no width the retargeting is not needed.
template <class _CharT>
class basic_format_context<typename __format::__retarget_buffer<_CharT>::__iterator, _CharT>
{
public:
	using iterator = typename __format::__retarget_buffer<_CharT>::__iterator;
	using char_type = _CharT;
	template <class _Tp>
	using formatter_type = hamon::formatter<_Tp, _CharT>;

	template <class _Context>
	explicit basic_format_context(iterator __out_it, _Context& __ctx)
		: __out_it_(hamon::move(__out_it)),
#  if 1//_LIBCPP_HAS_LOCALIZATION
		__loc_([](void* __c) { return static_cast<_Context*>(__c)->locale(); }),
#  endif
		__ctx_(hamon::addressof(__ctx)),
		__arg_([](void* __c, size_t __id) {
		auto __visitor = [&](auto __arg) -> hamon::basic_format_arg<basic_format_context> {
			if constexpr (hamon::same_as<decltype(__arg), monostate>)
			{
				return {};
			}
			else if constexpr (hamon::same_as<decltype(__arg), typename hamon::basic_format_arg<_Context>::handle>)
			{
				// At the moment it's not possible for formatting to use a re-targeted handle.
				// TODO FMT add this when support is needed.
				hamon::detail::throw_format_error("Re-targeting handle not supported");
			}
			else
				return hamon::basic_format_arg<basic_format_context>{
					__format::__determine_arg_t<basic_format_context, decltype(__arg)>(),
					hamon::detail::__basic_format_arg_value<basic_format_context>(__arg)};
		};
#  if _LIBCPP_STD_VER >= 26 && _LIBCPP_HAS_EXPLICIT_THIS_PARAMETER
		return static_cast<_Context*>(__c)->arg(__id).visit(hamon::move(__visitor));
#  else
//		_LIBCPP_SUPPRESS_DEPRECATED_PUSH
			return hamon::__visit_format_arg(hamon::move(__visitor), static_cast<_Context*>(__c)->arg(__id));
//		_LIBCPP_SUPPRESS_DEPRECATED_POP
#  endif // _LIBCPP_STD_VER >= 26 && _LIBCPP_HAS_EXPLICIT_THIS_PARAMETER
	}) {
	}

	hamon::basic_format_arg<basic_format_context> arg(size_t __id) const noexcept
	{
		return __arg_(__ctx_, __id);
	}
#  if 1//_LIBCPP_HAS_LOCALIZATION
	std::locale locale() { return __loc_(__ctx_); }
#  endif
	iterator out() { return hamon::move(__out_it_); }
	void advance_to(iterator __it) { __out_it_ = hamon::move(__it); }

private:
	iterator __out_it_;

#  if 1//_LIBCPP_HAS_LOCALIZATION
	std::locale(*__loc_)(void* __ctx);
#  endif

	void* __ctx_;
	hamon::basic_format_arg<basic_format_context>(*__arg_)(void* __ctx, size_t __id);
};

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___RETARGET_BUFFER_HPP
