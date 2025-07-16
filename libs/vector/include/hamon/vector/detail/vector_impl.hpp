/**
 *	@file	vector_impl.hpp
 *
 *	@brief	vector_impl の定義
 */

#ifndef HAMON_VECTOR_DETAIL_VECTOR_IMPL_HPP
#define HAMON_VECTOR_DETAIL_VECTOR_IMPL_HPP

#include <hamon/algorithm/max.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/make_reverse_iterator.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/limits/numeric_limits.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/destroy_impl.hpp>
#include <hamon/memory/detail/uninitialized_copy_n_impl.hpp>
#include <hamon/memory/detail/uninitialized_fill_n_impl.hpp>
#include <hamon/memory/detail/uninitialized_move_if_noexcept_n.hpp>
#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/stdexcept/length_error.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

template <typename T, typename Allocator>
struct vector_impl
{
private:
	using AllocTraits = hamon::allocator_traits<Allocator>;

	using pointer         = typename AllocTraits::pointer;
	using size_type       = typename AllocTraits::size_type;
	using difference_type = typename AllocTraits::difference_type;

private:
	size_type	m_size{};
	size_type	m_capacity{};
	pointer		m_data{};

public:
	HAMON_CXX11_CONSTEXPR
	vector_impl() HAMON_NOEXCEPT {}

	// コピー禁止
	vector_impl(vector_impl const&) = delete;
	vector_impl& operator=(vector_impl const&) = delete;

	HAMON_CXX14_CONSTEXPR
	vector_impl(vector_impl&& x) HAMON_NOEXCEPT
		: m_size    (hamon::exchange(x.m_size,     size_type{0}))
		, m_capacity(hamon::exchange(x.m_capacity, size_type{0}))
		, m_data    (hamon::exchange(x.m_data,     nullptr))
	{}

	HAMON_CXX14_CONSTEXPR
	vector_impl& operator=(vector_impl&& x) HAMON_NOEXCEPT
	{
		vector_impl(hamon::move(x)).Swap(*this);
		return *this;
	}

	HAMON_CXX11_CONSTEXPR size_type
	MaxSize(Allocator const& allocator) const HAMON_NOEXCEPT
	{
		return hamon::min(
			static_cast<size_type>(hamon::numeric_limits<difference_type>::max()),
			static_cast<size_type>(AllocTraits::max_size(allocator)));
	}

	HAMON_CXX11_CONSTEXPR
	size_type Size() const HAMON_NOEXCEPT
	{
		return m_size;
	}

	HAMON_CXX11_CONSTEXPR
	size_type Capacity() const HAMON_NOEXCEPT
	{
		return m_capacity;
	}

	HAMON_CXX11_CONSTEXPR pointer Begin() const HAMON_NOEXCEPT
	{
		return m_data;
	}

	HAMON_CXX11_CONSTEXPR pointer End() const HAMON_NOEXCEPT
	{
		return m_data + m_size;
	}

private:
	HAMON_CXX11_CONSTEXPR size_type
	GrowCapacity(size_type requested_size) const
	{
		// メモリを再確保する場合、指数的にサイズを大きくすることによって、
		// 要素の挿入が償却定数時間になる。
		// 今のサイズの何倍にするのがいいかは議論がある。
		// https://www.kmonos.net/wlog/111.html
		// https://inamori.hateblo.jp/entry/20100718/p1
		// https://groups.google.com/g/comp.lang.c++.moderated/c/asH_VojWKJw
//		return hamon::max(m_size + m_size, requested_size);	// 2倍
		return hamon::max(m_size + m_size / 2, requested_size);	// 1.5倍
	}

public:
	HAMON_CXX14_CONSTEXPR void
	Reallocate(Allocator& allocator, size_type new_capacity)
	{
		HAMON_ASSERT(new_capacity >= m_size);

		if (new_capacity > this->MaxSize(allocator))
		{
			hamon::detail::throw_length_error("vector");
		}

		auto data = AllocTraits::allocate(allocator, new_capacity);

		if (m_data != nullptr)
		{
			hamon::detail::uninitialized_move_if_noexcept_n(allocator, m_data, m_size, data);
		}

		auto const size = m_size;

		this->Clear(allocator);
		this->Deallocate(allocator);

		m_data = data;
		m_capacity = new_capacity;
		m_size = size;
	}

	HAMON_CXX14_CONSTEXPR void
	Reserve(Allocator& allocator, size_type n)
	{
		if (n > m_capacity)
		{
			this->Reallocate(allocator, n);
		}
	}

private:
	HAMON_CXX14_CONSTEXPR void
	MoveBackward(Allocator& allocator, difference_type pos_offset, size_type n)
	{
		HAMON_ASSERT(m_capacity >= m_size + n);
		hamon::detail::uninitialized_move_if_noexcept_n(allocator,
			hamon::make_reverse_iterator(this->End()),
			this->Size() - static_cast<size_type>(pos_offset),
			hamon::make_reverse_iterator(this->End() + n));
	}

public:
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void
	Emplace(Allocator& allocator, difference_type pos_offset, Args&&... args)
	{
		auto const new_size = m_size + 1;
		if (new_size > m_capacity)
		{
			auto const new_capacity = this->GrowCapacity(new_size);

			// メモリの再確保が必要な場合、強い例外保証のために
			// 一時変数に構築してからswapする。

			vector_impl tmp;
			tmp.Reserve(allocator, new_capacity);
			tmp.AppendMoveIfNoexceptN(allocator, this->Begin(), static_cast<size_type>(pos_offset));

			AllocTraits::construct(allocator, tmp.End(), hamon::forward<Args>(args)...);
			tmp.m_size += 1;

			tmp.AppendMoveIfNoexceptN(allocator, this->Begin() + pos_offset, this->Size() - static_cast<size_type>(pos_offset));
			tmp.Swap(*this);
			tmp.Destroy(allocator);
		}
		else
		{
			this->MoveBackward(allocator, pos_offset, 1);
			AllocTraits::construct(allocator, this->Begin() + pos_offset, hamon::forward<Args>(args)...);
			m_size += 1;
		}
	}

private:
	template <typename InputIterator>
	HAMON_CXX14_CONSTEXPR void
	InsertCopyN(Allocator& allocator, difference_type pos_offset, InputIterator first, size_type n)
	{
		auto const new_size = m_size + n;
		if (new_size > m_capacity)
		{
			auto const new_capacity = this->GrowCapacity(new_size);

			// メモリの再確保が必要な場合、強い例外保証のために
			// 一時変数に構築してからswapする。

			vector_impl tmp;
			tmp.Reserve(allocator, new_capacity);
			tmp.AppendMoveIfNoexceptN(allocator, this->Begin(), static_cast<size_type>(pos_offset));
			tmp.AppendCopyN(allocator, first, n);
			tmp.AppendMoveIfNoexceptN(allocator, this->Begin() + pos_offset, this->Size() - static_cast<size_type>(pos_offset));
			tmp.Swap(*this);
			tmp.Destroy(allocator);
		}
		else
		{
			this->MoveBackward(allocator, pos_offset, n);
			hamon::detail::uninitialized_copy_n_impl(allocator, first, n, this->Begin() + pos_offset);
			m_size += n;
		}
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	InsertIterSent(Allocator& allocator, difference_type pos_offset, Iterator first, Sentinel last)
	{
		for (; first != last; ++first)
		{
			this->Emplace(allocator, pos_offset, *first);
			++pos_offset;
		}
	}

	template <typename InputIterator,
		typename = hamon::enable_if_t<
			hamon::forward_iterator_t<InputIterator>::value>>
	HAMON_CXX14_CONSTEXPR void
	InsertIterImpl(Allocator& allocator, difference_type pos_offset, InputIterator first, InputIterator last, hamon::detail::overload_priority<1>)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(first, last));
		this->InsertCopyN(allocator, pos_offset, hamon::move(first), n);
	}

	template <typename InputIterator>
	HAMON_CXX14_CONSTEXPR void
	InsertIterImpl(Allocator& allocator, difference_type pos_offset, InputIterator first, InputIterator last, hamon::detail::overload_priority<0>)
	{
		this->InsertIterSent(allocator, pos_offset, hamon::move(first), hamon::move(last));
	}

	template <typename Range,
		typename = hamon::enable_if_t<
			hamon::ranges::forward_range_t<Range>::value ||
			hamon::ranges::sized_range_t<Range>::value>>
	HAMON_CXX14_CONSTEXPR void
	InsertRangeImpl(Allocator& allocator, difference_type pos_offset, Range&& rg, hamon::detail::overload_priority<1>)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(rg));
		this->InsertCopyN(allocator, pos_offset, hamon::ranges::begin(rg), n);
	}

	template <typename Range>
	HAMON_CXX14_CONSTEXPR void
	InsertRangeImpl(Allocator& allocator, difference_type pos_offset, Range&& rg, hamon::detail::overload_priority<0>)
	{
		this->InsertIterSent(allocator, pos_offset, hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

public:
	template <typename InputIterator>
	HAMON_CXX14_CONSTEXPR void
	InsertIter(Allocator& allocator, difference_type pos_offset, InputIterator first, InputIterator last)
	{
		InsertIterImpl(allocator, pos_offset, hamon::move(first), hamon::move(last), hamon::detail::overload_priority<1>{});
	}

	template <typename Range>
	HAMON_CXX14_CONSTEXPR void
	InsertRange(Allocator& allocator, difference_type pos_offset, Range&& rg)
	{
		InsertRangeImpl(allocator, pos_offset, hamon::forward<Range>(rg), hamon::detail::overload_priority<1>{});
	}

private:
	template <typename InputIterator>
	HAMON_CXX14_CONSTEXPR void
	AssignCopyN(Allocator& allocator, InputIterator first, size_type n)
	{
		auto const new_size = n;
		if (new_size > m_capacity)
		{
			auto const new_capacity = this->GrowCapacity(new_size);

			// メモリの再確保が必要な場合、強い例外保証のために
			// 一時変数に構築してからswapする。

			vector_impl tmp;
			tmp.Reserve(allocator, new_capacity);
			tmp.AppendCopyN(allocator, first, new_size);
			tmp.Swap(*this);
			tmp.Destroy(allocator);
		}
		else
		{
			auto dst_first = this->Begin();
			auto dst_last = this->End();
			for (; n > 0 && dst_first != dst_last; --n)
			{
				*dst_first = *first;
				++dst_first;
				++first;
			}
			this->PopBackN(allocator, static_cast<size_type>(dst_last - dst_first));
			this->AppendCopyN(allocator, first, n);
		}
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void
	AssignIterSent(Allocator& allocator, Iterator first, Sentinel last)
	{
		auto dst_first = this->Begin();
		auto dst_last = this->End();
		for (; first != last && dst_first != dst_last;)
		{
			*dst_first = *first;
			++dst_first;
			++first;
		}

		this->PopBackN(allocator, static_cast<size_type>(dst_last - dst_first));
		this->InsertIterSent(allocator, static_cast<difference_type>(this->Size()), first, last);
	}

	template <typename InputIterator,
		typename = hamon::enable_if_t<
			hamon::forward_iterator_t<InputIterator>::value>>
	HAMON_CXX14_CONSTEXPR void
	AssignIterImpl(Allocator& allocator, InputIterator first, InputIterator last, hamon::detail::overload_priority<1>)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(first, last));
		this->AssignCopyN(allocator, hamon::move(first), n);
	}

	template <typename InputIterator>
	HAMON_CXX14_CONSTEXPR void
	AssignIterImpl(Allocator& allocator, InputIterator first, InputIterator last, hamon::detail::overload_priority<0>)
	{
		this->AssignIterSent(allocator, hamon::move(first), hamon::move(last));
	}

	template <typename Range,
		typename = hamon::enable_if_t<
			hamon::ranges::forward_range_t<Range>::value ||
			hamon::ranges::sized_range_t<Range>::value>>
	HAMON_CXX14_CONSTEXPR void
	AssignRangeImpl(Allocator& allocator, Range&& rg, hamon::detail::overload_priority<1>)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(rg));
		this->AssignCopyN(allocator, hamon::ranges::begin(rg), n);
	}

	template <typename Range>
	HAMON_CXX14_CONSTEXPR void
	AssignRangeImpl(Allocator& allocator, Range&& rg, hamon::detail::overload_priority<0>)
	{
		this->AssignIterSent(allocator, hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

public:
	template <typename InputIterator>
	HAMON_CXX14_CONSTEXPR void
	AssignIter(Allocator& allocator, InputIterator first, InputIterator last)
	{
		AssignIterImpl(allocator, hamon::move(first), hamon::move(last), hamon::detail::overload_priority<1>{});
	}

	template <typename Range>
	HAMON_CXX14_CONSTEXPR void
	AssignRange(Allocator& allocator, Range&& rg)
	{
		AssignRangeImpl(allocator, hamon::forward<Range>(rg), hamon::detail::overload_priority<1>{});
	}

	template <typename InputIterator>
	HAMON_CXX14_CONSTEXPR void AppendMoveIfNoexceptN(Allocator& allocator, InputIterator first, size_type n)
	{
		HAMON_ASSERT(m_capacity >= m_size + n);
		hamon::detail::uninitialized_move_if_noexcept_n(allocator, first, n, this->End());
		m_size += n;
	}

private:
	template <typename InputIterator>
	HAMON_CXX14_CONSTEXPR void
	AppendCopyN(Allocator& allocator, InputIterator first, size_type n)
	{
		HAMON_ASSERT(m_capacity >= m_size + n);
		hamon::detail::uninitialized_copy_n_impl(allocator, first, n, this->End());
		m_size += n;
	}

	HAMON_CXX14_CONSTEXPR void
	AppendDefaultN(Allocator& allocator, size_type n)
	{
		HAMON_ASSERT(m_capacity >= m_size + n);
		hamon::detail::uninitialized_value_construct_n_impl(allocator, this->End(), n);
		m_size += n;
	}

	HAMON_CXX14_CONSTEXPR void
	AppendFillN(Allocator& allocator, size_type n, T const& value)
	{
		HAMON_ASSERT(m_capacity >= m_size + n);
		hamon::detail::uninitialized_fill_n_impl(allocator, this->End(), n, value);
		m_size += n;
	}

public:
	HAMON_CXX14_CONSTEXPR void
	Resize(Allocator& allocator, size_type sz)
	{
		// [vector.capacity]/16
		// Remarks: If an exception is thrown other than by the move constructor of a non-Cpp17CopyInsertable T,
		// there are no effects.

		if (sz < this->Size())
		{
			this->PopBackN(allocator, this->Size() - sz);
		}
		else if (sz > this->Capacity())
		{
			vector_impl tmp;
			tmp.Reserve(allocator, sz);
			tmp.AppendMoveIfNoexceptN(allocator, this->Begin(), this->Size());
			tmp.AppendDefaultN(allocator, sz - this->Size());
			tmp.Swap(*this);
			tmp.Destroy(allocator);
		}
		else if (sz > this->Size())
		{
			this->AppendDefaultN(allocator, sz - this->Size());
		}
	}

	HAMON_CXX14_CONSTEXPR void
	Resize(Allocator& allocator, size_type sz, T const& c)
	{
		// [vector.capacity]/19
		// Remarks: If an exception is thrown, there are no effects.

		if (sz < this->Size())
		{
			this->PopBackN(allocator, this->Size() - sz);
		}
		else if (sz > this->Capacity())
		{
			vector_impl tmp;
			tmp.Reserve(allocator, sz);
			tmp.AppendMoveIfNoexceptN(allocator, this->Begin(), this->Size());
			tmp.AppendFillN(allocator, sz - this->Size(), c);
			tmp.Swap(*this);
			tmp.Destroy(allocator);
		}
		else if (sz > this->Size())
		{
			this->AppendFillN(allocator, sz - this->Size(), c);
		}
	}

	HAMON_CXX14_CONSTEXPR void
	EraseN(Allocator& allocator, difference_type pos_offset, size_type n)
	{
		HAMON_ASSERT(m_size >= n);

		if (n != 0)
		{
			auto const first = this->Begin() + pos_offset;
			auto const last  = first + n;
			hamon::detail::destroy_impl(allocator, first, last);
			hamon::detail::uninitialized_move_if_noexcept_n(allocator, last, this->End() - last, first);
			m_size -= n;
		}
	}

	HAMON_CXX14_CONSTEXPR void
	PopBackN(Allocator& allocator, size_type n) HAMON_NOEXCEPT
	{
		HAMON_ASSERT(n <= this->Size());

		hamon::detail::destroy_impl(allocator, this->End() - n, this->End());
		m_size -= n;
	}

	HAMON_CXX14_CONSTEXPR void
	Clear(Allocator& allocator) HAMON_NOEXCEPT
	{
		hamon::detail::destroy_impl(allocator, this->Begin(), this->End());
		m_size = 0;
	}

private:
	HAMON_CXX14_CONSTEXPR void
	Deallocate(Allocator& allocator) HAMON_NOEXCEPT
	{
		if (m_data != nullptr)
		{
			AllocTraits::deallocate(allocator, m_data, m_capacity);
		}

		m_data = nullptr;
		m_capacity = 0;
	}

public:
	HAMON_CXX14_CONSTEXPR void
	Destroy(Allocator& allocator) HAMON_NOEXCEPT
	{
		this->Clear(allocator);
		this->Deallocate(allocator);
	}

	HAMON_CXX14_CONSTEXPR void
	Swap(vector_impl& x) HAMON_NOEXCEPT
	{
		hamon::swap(m_size,     x.m_size);
		hamon::swap(m_capacity, x.m_capacity);
		hamon::swap(m_data,     x.m_data);
	}
};

HAMON_WARNING_POP()

}	// namespace detail

}	// namespace hamon

#endif // HAMON_VECTOR_DETAIL_VECTOR_IMPL_HPP
