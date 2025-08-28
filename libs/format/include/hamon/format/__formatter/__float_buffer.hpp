/**
 *	@file	__float_buffer.hpp
 *
 *	@brief	__float_buffer の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___FLOAT_BUFFER_HPP
#define HAMON_FORMAT___FORMATTER___FLOAT_BUFFER_HPP

#include <hamon/format/__formatter/__traits.hpp>
#include <hamon/format/__formatter/__float_buffer_size.hpp>
#include <hamon/concepts/floating_point.hpp>
#include <hamon/memory/allocator.hpp>

namespace hamon
{

namespace __formatter
{

/// Helper class to store the conversion buffer.
///
/// Depending on the maximum size required for a value, the buffer is allocated
/// on the stack or the heap.
template <hamon::floating_point _Fp>
class __float_buffer
{
	using _Traits = __formatter::__traits<_Fp>;

public:
	// TODO FMT Improve this constructor to do a better estimate.
	// When using a scientific formatting with a precision of 6 a stack buffer
	// will always suffice. At the moment that isn't important since floats and
	// doubles use a stack buffer, unless the precision used in the format string
	// is large.
	// When supporting long doubles the __max_integral part becomes 4932 which
	// may be too much for some platforms. For these cases a better estimate is
	// required.
	explicit __float_buffer(int __precision)
		: __precision_(__precision != -1 ? __precision : _Traits::__max_fractional)
	{
		// When the precision is larger than _Traits::__max_fractional the digits in
		// the range (_Traits::__max_fractional, precision] will contain the value
		// zero. There's no need to request to_chars to write these zeros:
		// - When the value is large a temporary heap buffer needs to be allocated.
		// - When to_chars writes the values they need to be "copied" to the output:
		//   - char: std::fill on the output iterator is faster than std::copy.
		//   - wchar_t: same argument as char, but additional std::copy won't work.
		//     The input is always a char buffer, so every char in the buffer needs
		//     to be converted from a char to a wchar_t.
		if (__precision_ > _Traits::__max_fractional)
		{
			__num_trailing_zeros_ = __precision_ - _Traits::__max_fractional;
			__precision_          = _Traits::__max_fractional;
		}

		__size_ = __formatter::__float_buffer_size<_Fp>(__precision_);
		if (__size_ > _Traits::__stack_buffer_size)
		{
			// The allocated buffer's contents don't need initialization.
			__begin_ = hamon::allocator<char>{}.allocate(__size_);
		}
		else
		{
			__begin_ = __buffer_;
		}
	}

	~__float_buffer()
	{
		if (__size_ > _Traits::__stack_buffer_size)
		{
			hamon::allocator<char>{}.deallocate(__begin_, __size_);
		}
	}
	__float_buffer(const __float_buffer&)            = delete;
	__float_buffer& operator=(const __float_buffer&) = delete;

	char* begin() const { return __begin_; }
	char* end() const { return __begin_ + __size_; }

	int __precision() const { return __precision_; }
	int __num_trailing_zeros() const { return __num_trailing_zeros_; }
	void __remove_trailing_zeros() { __num_trailing_zeros_ = 0; }
	void __add_trailing_zeros(int __zeros) { __num_trailing_zeros_ += __zeros; }

private:
	int __precision_;
	int __num_trailing_zeros_{0};
	size_t __size_;
	char* __begin_;
	char __buffer_[_Traits::__stack_buffer_size];
};

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___FLOAT_BUFFER_HPP
