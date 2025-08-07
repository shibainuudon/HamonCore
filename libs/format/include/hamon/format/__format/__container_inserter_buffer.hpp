/**
 *	@file	__container_inserter_buffer.hpp
 *
 *	@brief	__container_inserter_buffer の定義
 */

#ifndef HAMON_FORMAT___FORMAT___CONTAINER_INSERTER_BUFFER_HPP
#define HAMON_FORMAT___FORMAT___CONTAINER_INSERTER_BUFFER_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format/__output_buffer.hpp>
#include <hamon/format/__format/__back_insert_iterator_container.hpp>
#include <hamon/iterator/back_inserter.hpp>

namespace hamon
{

namespace __format
{

// A buffer that writes its output to the end of a container.
template <class _OutIt, __format::__fmt_char_type _CharT>
class __container_inserter_buffer : public __format::__output_buffer<_CharT>
{
public:
	[[nodiscard]] explicit __container_inserter_buffer(_OutIt __out_it)
		: __container_inserter_buffer {__out_it, nullptr} {}

	[[nodiscard]]
	explicit __container_inserter_buffer(_OutIt __out_it, __format::__max_output_size* __max_output_size)
		: __output_buffer<_CharT> {__small_buffer_, __buffer_size, __prepare_write, __max_output_size},
		__container_ {__out_it.__get_container()} {}

	[[nodiscard]] auto __out_it() && {
		__container_->insert(__container_->end(), __small_buffer_, __small_buffer_ + this->__size());
		return hamon::back_inserter(*__container_);
	}

private:
	typename __format::__back_insert_iterator_container<_OutIt>::type* __container_;

	// This class uses a fixed size buffer and appends the elements in
	// __buffer_size chunks. An alternative would be to use an allocating buffer
	// and append the output in a single write operation. Benchmarking showed no
	// performance difference.
	static constexpr size_t __buffer_size = 256;
	_CharT __small_buffer_[__buffer_size];

	void __prepare_write()
	{
		__container_->insert(__container_->end(), __small_buffer_, __small_buffer_ + this->__size());
		this->__buffer_flushed();
	}

	static void
	__prepare_write(__format::__output_buffer<_CharT>& __buffer, [[maybe_unused]] size_t __size_hint)
	{
		static_cast<__container_inserter_buffer<_OutIt, _CharT>&>(__buffer).__prepare_write();
	}
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___CONTAINER_INSERTER_BUFFER_HPP
