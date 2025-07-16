/**
 *	@file	vector_impl.hpp
 *
 *	@brief	vector_impl の定義
 */

#ifndef HAMON_VECTOR_DETAIL_VECTOR_IMPL_HPP
#define HAMON_VECTOR_DETAIL_VECTOR_IMPL_HPP

#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/lexicographical_compare.hpp>
#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/iter_const_reference_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/make_reverse_iterator.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/limits/numeric_limits.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/memory/detail/equals_allocator.hpp>
#include <hamon/memory/detail/propagate_allocator_on_copy.hpp>
#include <hamon/memory/detail/propagate_allocator_on_move.hpp>
#include <hamon/memory/detail/propagate_allocator_on_swap.hpp>
#include <hamon/memory/detail/uninitialized_copy_n_impl.hpp>
#include <hamon/memory/detail/uninitialized_fill_n_impl.hpp>
#include <hamon/memory/detail/uninitialized_move_n_impl.hpp>
#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/stdexcept/length_error.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

namespace detail
{

template <typename T, typename Allocator>
struct vector_impl
{
private:
	template <typename Iter, typename Size, typename Out,
		typename RvalRef = hamon::iter_rvalue_reference_t<Iter>,
		typename ConstRef = hamon::iter_const_reference_t<Iter>,
		typename OutT = hamon::iter_value_t<Out>,
		typename = hamon::enable_if_t<
			hamon::is_nothrow_constructible<OutT, RvalRef>::value ||
			!hamon::is_constructible<OutT, ConstRef>::value>>
	static HAMON_CXX14_CONSTEXPR void
	UninitializedMoveNImpl(Iter src, Size n, Out dst, hamon::detail::overload_priority<1>)
	{
		hamon::detail::uninitialized_move_n_impl(src, n, dst);
	}

	template <typename Iter, typename Size, typename Out>
	static HAMON_CXX14_CONSTEXPR void
	UninitializedMoveNImpl(Iter src, Size n, Out dst, hamon::detail::overload_priority<0>)
	{
		hamon::detail::uninitialized_copy_n_impl(src, n, dst);
	}

	template <typename Iter, typename Size, typename Out>
	static HAMON_CXX14_CONSTEXPR void
	UninitializedMoveN(Iter src, Size n, Out dst)
	{
		UninitializedMoveNImpl(src, n, dst, hamon::detail::overload_priority<1>{});
	}
private:
	using AllocTraits = hamon::allocator_traits<Allocator>;

	using pointer                = typename AllocTraits::pointer;
	using size_type              = typename AllocTraits::size_type;
	using difference_type        = typename AllocTraits::difference_type;

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
	{
		m_size     = hamon::exchange(x.m_size,     size_type{0});
		m_capacity = hamon::exchange(x.m_capacity, size_type{0});
		m_data     = hamon::exchange(x.m_data,     nullptr);
	}

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

	HAMON_CXX14_CONSTEXPR void Allocate(Allocator& allocator, size_type new_capacity)
	{
		HAMON_ASSERT(m_data == nullptr);
		HAMON_ASSERT(m_capacity == 0u);
		HAMON_ASSERT(m_size == 0u);

		if (new_capacity > this->MaxSize(allocator))
		{
			hamon::detail::throw_length_error("vector");
		}

		m_data = AllocTraits::allocate(allocator, new_capacity);
		m_capacity = new_capacity;
	}

	HAMON_CXX14_CONSTEXPR void Deallocate(Allocator& allocator) HAMON_NOEXCEPT
	{
		if (m_data != nullptr)
		{
			AllocTraits::deallocate(allocator, m_data, m_capacity);
			m_data = nullptr;
		}
		m_capacity = 0;
		m_size = 0;
	}

	template <typename Iterator>
	HAMON_CXX14_CONSTEXPR void AppendMoveN(Iterator first, size_type n)
	{
		HAMON_ASSERT(m_capacity >= m_size + n);
		vector_impl::UninitializedMoveN(first, n, this->End());
		m_size += n;
	}

	template <typename Iterator>
	HAMON_CXX14_CONSTEXPR void AppendCopyN(Iterator first, size_type n)
	{
		HAMON_ASSERT(m_capacity >= m_size + n);
		hamon::detail::uninitialized_copy_n_impl(first, n, this->End());
		m_size += n;
	}

	HAMON_CXX14_CONSTEXPR void AppendDefaultN(size_type n)
	{
		HAMON_ASSERT(m_capacity >= m_size + n);
		hamon::detail::uninitialized_value_construct_n_impl(this->End(), n);
		m_size += n;
	}

	HAMON_CXX14_CONSTEXPR void AppendFillN(size_type n, T const& c)
	{
		HAMON_ASSERT(m_capacity >= m_size + n);
		hamon::detail::uninitialized_fill_n_impl(this->End(), n, c);
		m_size += n;
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR void AppendEmplace(Allocator& allocator, Args&&... args)
	{
		HAMON_ASSERT(m_capacity >= m_size + 1);
		AllocTraits::construct(allocator, this->End(), hamon::forward<Args>(args)...);
		m_size += 1;
	}

	template <typename Diff, typename... Args>
	HAMON_CXX14_CONSTEXPR void Emplace(Allocator& allocator, Diff pos_offset, Args&&... args)
	{
		HAMON_ASSERT(m_capacity >= m_size + 1);
		vector_impl::UninitializedMoveN(
			hamon::make_reverse_iterator(this->End()),
			this->Size() - static_cast<size_type>(pos_offset),
			hamon::make_reverse_iterator(this->End() + 1));
		AllocTraits::construct(allocator, this->Begin() + pos_offset, hamon::forward<Args>(args)...);
		m_size += 1;
	}

	template <typename Diff, typename Iterator>
	HAMON_CXX14_CONSTEXPR void InsertCopyN(Diff pos_offset, Iterator first, size_type n)
	{
		HAMON_ASSERT(m_capacity >= m_size + n);
		vector_impl::UninitializedMoveN(
			hamon::make_reverse_iterator(this->End()),
			this->Size() - static_cast<size_type>(pos_offset),
			hamon::make_reverse_iterator(this->End() + n));
		hamon::detail::uninitialized_copy_n_impl(first, n, this->Begin() + pos_offset);
		m_size += n;
	}

	template <typename Diff>
	HAMON_CXX14_CONSTEXPR void InsertFillN(Diff pos_offset, size_type n, T const& x)
	{
		HAMON_ASSERT(m_capacity >= m_size + n);
		vector_impl::UninitializedMoveN(
			hamon::make_reverse_iterator(this->End()),
			this->Size() - static_cast<size_type>(pos_offset),
			hamon::make_reverse_iterator(this->End() + n));
		hamon::detail::uninitialized_fill_n_impl(this->Begin() + pos_offset, n, x);
		m_size += n;
	}

	HAMON_CXX14_CONSTEXPR void PopBackN(size_type n)
	{
		HAMON_ASSERT(m_size >= n);
		hamon::destroy(this->End() - n, this->End());
		m_size -= n;
	}

	template <typename Diff>
	HAMON_CXX14_CONSTEXPR void DestroyN(Diff pos_offset, size_type n)
	{
		HAMON_ASSERT(m_size >= n);
		if (n != 0)
		{
			auto const first = this->Begin() + pos_offset;
			auto const last  = first + n;
			hamon::destroy(first, last);
			vector_impl::UninitializedMoveN(last, this->End() - last, first);
			m_size -= n;
		}
	}

	HAMON_CXX14_CONSTEXPR void DestroyAll() HAMON_NOEXCEPT
	{
		hamon::destroy(m_data, m_data + m_size);
		m_size = 0;
	}

	HAMON_CXX11_CONSTEXPR pointer Begin() const HAMON_NOEXCEPT
	{
		return m_data;
	}

	HAMON_CXX11_CONSTEXPR pointer End() const HAMON_NOEXCEPT
	{
		return m_data + m_size;
	}

	HAMON_CXX14_CONSTEXPR void
	Swap(vector_impl& x) HAMON_NOEXCEPT
	{
		hamon::swap(m_size,     x.m_size);
		hamon::swap(m_capacity, x.m_capacity);
		hamon::swap(m_data,     x.m_data);
	}
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_VECTOR_DETAIL_VECTOR_IMPL_HPP
