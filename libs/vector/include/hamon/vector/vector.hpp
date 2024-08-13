/**
 *	@file	vector.hpp
 *
 *	@brief	vector の定義
 */

#ifndef HAMON_VECTOR_VECTOR_HPP
#define HAMON_VECTOR_VECTOR_HPP

#include <hamon/vector/config.hpp>

#if defined(HAMON_USE_STD_VECTOR)

#include <vector>

namespace hamon
{

using std::vector;

}	// namespace hamon

#else

#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/lexicographical_compare.hpp>
#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/algorithm/max.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/forward_iterator.hpp>
#include <hamon/iterator/contiguous_iterator_tag.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/iter_const_reference_t.hpp>
#include <hamon/iterator/iter_rvalue_reference_t.hpp>
#include <hamon/iterator/iter_value_t.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/limits/numeric_limits.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/destroy.hpp>
#include <hamon/memory/detail/uninitialized_copy_n_impl.hpp>
#include <hamon/memory/detail/uninitialized_fill_n_impl.hpp>
#include <hamon/memory/detail/uninitialized_move_n_impl.hpp>
#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/detail/container_compatible_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/stdexcept/length_error.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
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

// [sequences.general]/2
template <typename InputIterator>
using iter_value_type = typename hamon::iterator_traits<InputIterator>::value_type;  // exposition only

}	// namespace detail

#if 0

namespace pmr {
template <typename T>
using vector = std::vector<T, polymorphic_allocator<T>>;
}

// [vector.bool], specialization of vector for bool
// [vector.bool.pspc], partial class template specialization vector<bool, Allocator>
template <typename Allocator>
class vector<bool, Allocator>;

template <typename T>
constexpr bool is_vector_bool_reference = see below;          // exposition only

// hash support
template <typename T>
struct hash;

template <typename Allocator>
struct hash<vector<bool, Allocator>>;

// [vector.bool.fmt], formatter specialization for vector<bool>
template <typename T, typename charT>
requires is_vector_bool_reference<T>
struct formatter<T, charT>;

#endif

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

// TODO:
// * vector<bool>の特殊化

// 24.3.11 Class template vector[vector]

template <typename T, typename Allocator = hamon::allocator<T>>
class vector
{
private:
	using AllocTraits = hamon::allocator_traits<Allocator>;

	template <typename U, typename Const>
	struct Iterator
	{
		friend Iterator<U, hamon::negation<Const>>;
		friend class vector;

		using iterator_concept  = hamon::contiguous_iterator_tag;
		using iterator_category = hamon::random_access_iterator_tag;
		using value_type        = U;
		using difference_type   = typename AllocTraits::difference_type;
		using pointer           = hamon::conditional_t<Const::value, U const*, U*>;
		using reference         = hamon::conditional_t<Const::value, U const&, U&>;

		HAMON_CXX11_CONSTEXPR
		Iterator() HAMON_NOEXCEPT
			: m_ptr()
		{}

	private:
		HAMON_CXX11_CONSTEXPR
		Iterator(pointer ptr) HAMON_NOEXCEPT
			: m_ptr(ptr)
		{}

	public:
		template <typename C,
			typename = hamon::enable_if_t<C::value == Const::value || Const::value>>
		HAMON_CXX11_CONSTEXPR
		Iterator(Iterator<U, C> const& i) HAMON_NOEXCEPT
			: m_ptr(const_cast<pointer>(i.m_ptr))
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
		reference operator*() const HAMON_NOEXCEPT
		{
			return *m_ptr;
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
		pointer operator->() const HAMON_NOEXCEPT
		{
			return m_ptr;
		}

		HAMON_CXX14_CONSTEXPR Iterator&
		operator++() HAMON_NOEXCEPT
		{
			++m_ptr;
			return *this;
		}

		HAMON_CXX14_CONSTEXPR Iterator
		operator++(int) HAMON_NOEXCEPT
		{
			auto tmp = *this;
			++*this;
			return tmp;
		}

		HAMON_CXX14_CONSTEXPR Iterator&
		operator--() HAMON_NOEXCEPT
		{
			--m_ptr;
			return *this;
		}

		HAMON_CXX14_CONSTEXPR Iterator
		operator--(int) HAMON_NOEXCEPT
		{
			auto tmp = *this;
			--*this;
			return tmp;
		}

		HAMON_CXX14_CONSTEXPR Iterator&
		operator+=(difference_type n) HAMON_NOEXCEPT
		{
			m_ptr += n;
			return *this;
		}

		HAMON_CXX14_CONSTEXPR Iterator&
		operator-=(difference_type n) HAMON_NOEXCEPT
		{
			m_ptr -= n;
			return *this;
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference
		operator[](difference_type n) const HAMON_NOEXCEPT
		{
			return m_ptr[n];
		}

	private:
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR Iterator
		operator+(Iterator const& i, difference_type n) HAMON_NOEXCEPT
		{
			return Iterator(i.m_ptr + n);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR Iterator
		operator+(difference_type n, Iterator const& i) HAMON_NOEXCEPT
		{
			return Iterator(i.m_ptr + n);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR Iterator
		operator-(Iterator const& i, difference_type n) HAMON_NOEXCEPT
		{
			return Iterator(i.m_ptr - n);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR difference_type
		operator-(Iterator const& lhs, Iterator const& rhs) HAMON_NOEXCEPT
		{
			return static_cast<difference_type>(lhs.m_ptr - rhs.m_ptr);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
		operator==(Iterator const& lhs, Iterator const& rhs) HAMON_NOEXCEPT
		{
			return lhs.m_ptr == rhs.m_ptr;
		}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR hamon::strong_ordering
		operator<=>(Iterator const& lhs, Iterator const& rhs) HAMON_NOEXCEPT
		{
			return lhs.m_ptr <=> rhs.m_ptr;
		}
#else
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
		operator!=(Iterator const& lhs, Iterator const& rhs) HAMON_NOEXCEPT
		{
			return !(lhs == rhs);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
		operator<(Iterator const& lhs, Iterator const& rhs) HAMON_NOEXCEPT
		{
			return lhs.m_ptr < rhs.m_ptr;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
		operator>(Iterator const& lhs, Iterator const& rhs) HAMON_NOEXCEPT
		{
			return rhs < lhs;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
		operator<=(Iterator const& lhs, Iterator const& rhs) HAMON_NOEXCEPT
		{
			return !(rhs < lhs);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
		operator>=(Iterator const& lhs, Iterator const& rhs) HAMON_NOEXCEPT
		{
			return !(lhs < rhs);
		}
#endif
	private:
		pointer m_ptr;
	};

public:
	// types
	using value_type             = T;
	using allocator_type         = Allocator;
	using pointer                = typename AllocTraits::pointer;
	using const_pointer          = typename AllocTraits::const_pointer;
	using reference              = value_type&;
	using const_reference        = value_type const&;
	using size_type              = typename AllocTraits::size_type;       // see [container.requirements]
	using difference_type        = typename AllocTraits::difference_type; // see [container.requirements]
	using iterator               = Iterator<T, hamon::false_type>;        // see [container.requirements]
	using const_iterator         = Iterator<T, hamon::true_type>;         // see [container.requirements]
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;

private:
	struct Impl
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
		size_type	m_size{};
		size_type	m_capacity{};
		pointer		m_data{};

	public:
		HAMON_CXX11_CONSTEXPR
		Impl() HAMON_NOEXCEPT {}

		// コピー禁止
		Impl(Impl const&) = delete;
		Impl& operator=(Impl const&) = delete;

		HAMON_CXX14_CONSTEXPR
		Impl(Impl&& x) HAMON_NOEXCEPT
		{
			m_size     = hamon::exchange(x.m_size,     size_type{0});
			m_capacity = hamon::exchange(x.m_capacity, size_type{0});
			m_data     = hamon::exchange(x.m_data,     nullptr);
		}

		HAMON_CXX14_CONSTEXPR
		Impl& operator=(Impl&& x) HAMON_NOEXCEPT
		{
			Impl(hamon::move(x)).Swap(*this);
			return *this;
		}

		HAMON_CXX11_CONSTEXPR size_type
		MaxSize(allocator_type const& allocator) const HAMON_NOEXCEPT
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

		HAMON_CXX14_CONSTEXPR void Allocate(allocator_type& allocator, size_type new_capacity)
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

		HAMON_CXX14_CONSTEXPR void Deallocate(allocator_type& allocator) HAMON_NOEXCEPT
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
			Impl::UninitializedMoveN(first, n, this->End());
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
		HAMON_CXX14_CONSTEXPR void AppendEmplace(allocator_type& allocator, Args&&... args)
		{
			HAMON_ASSERT(m_capacity >= m_size + 1);
			AllocTraits::construct(allocator, this->End(), hamon::forward<Args>(args)...);
			m_size += 1;
		}

		template <typename Diff, typename... Args>
		HAMON_CXX14_CONSTEXPR void Emplace(allocator_type& allocator, Diff pos_offset, Args&&... args)
		{
			HAMON_ASSERT(m_capacity >= m_size + 1);
			Impl::UninitializedMoveN(
				reverse_iterator(this->End()),
				this->Size() - static_cast<size_type>(pos_offset),
				reverse_iterator(this->End() + 1));
			AllocTraits::construct(allocator, this->Begin() + pos_offset, hamon::forward<Args>(args)...);
			m_size += 1;
		}

		template <typename Diff, typename Iterator>
		HAMON_CXX14_CONSTEXPR void InsertCopyN(Diff pos_offset, Iterator first, size_type n)
		{
			HAMON_ASSERT(m_capacity >= m_size + n);
			Impl::UninitializedMoveN(
				reverse_iterator(this->End()),
				this->Size() - static_cast<size_type>(pos_offset),
				reverse_iterator(this->End() + n));
			hamon::detail::uninitialized_copy_n_impl(first, n, this->Begin() + pos_offset);
			m_size += n;
		}

		template <typename Diff>
		HAMON_CXX14_CONSTEXPR void InsertFillN(Diff pos_offset, size_type n, T const& x)
		{
			HAMON_ASSERT(m_capacity >= m_size + n);
			Impl::UninitializedMoveN(
				reverse_iterator(this->End()),
				this->Size() - static_cast<size_type>(pos_offset),
				reverse_iterator(this->End() + n));
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
			auto const first = this->Begin() + pos_offset;
			auto const last  = first + n;
			hamon::destroy(first, last);
			Impl::UninitializedMoveN(last, this->End() - last, first);
			m_size -= n;
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
		Swap(Impl& x) noexcept
		{
			hamon::swap(m_size,     x.m_size);
			hamon::swap(m_capacity, x.m_capacity);
			hamon::swap(m_data,     x.m_data);
		}
	};

	HAMON_NO_UNIQUE_ADDRESS	allocator_type m_allocator;
	Impl	m_impl;

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
//		return hamon::max(m_impl.Size() + m_impl.Size(), requested_size);	// 2倍
		return hamon::max(m_impl.Size() + m_impl.Size() / 2, requested_size);	// 1.5倍
	}

	template <typename Iterator>
	HAMON_CXX14_CONSTEXPR void AssignCopyN(Iterator first, size_type n)
	{
		auto const new_size = n;

		if (new_size > m_impl.Capacity())
		{
			auto const new_capacity = GrowCapacity(new_size);

			Impl tmp;
			tmp.Allocate(m_allocator, new_capacity);
			tmp.AppendCopyN(first, new_size);
			tmp.Swap(m_impl);
			tmp.DestroyAll();
			tmp.Deallocate(m_allocator);
		}
		else
		{
			auto dst_first = m_impl.Begin();
			auto dst_last = m_impl.End();
			for (; n > 0 && dst_first != dst_last; --n)
			{
				*dst_first = *first;
				++dst_first;
				++first;
			}

			m_impl.PopBackN(static_cast<size_type>(dst_last - dst_first));
			m_impl.AppendCopyN(first, n);
		}
	}

	template <typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void AssignCopy(Iterator first, Sentinel last)
	{
		auto dst_first = m_impl.Begin();
		auto dst_last = m_impl.End();
		for (; first != last && dst_first != dst_last;)
		{
			*dst_first = *first;
			++dst_first;
			++first;
		}

		m_impl.PopBackN(static_cast<size_type>(dst_last - dst_first));
		this->InsertCopy(m_impl.Size(), first, last);
	}

	template <typename Iterator>
	HAMON_CXX14_CONSTEXPR void AssignMoveN(Iterator first, size_type n)
	{
		auto const new_size = n;

		if (new_size > m_impl.Capacity())
		{
			auto const new_capacity = GrowCapacity(new_size);

			Impl tmp;
			tmp.Allocate(m_allocator, new_capacity);
			tmp.AppendMoveN(first, new_size);
			tmp.Swap(m_impl);
			tmp.DestroyAll();
			tmp.Deallocate(m_allocator);
		}
		else
		{
			auto dst_first = m_impl.Begin();
			auto dst_last = m_impl.End();
			for (; n > 0 && dst_first != dst_last; --n)
			{
				*dst_first = hamon::move(*first);
				++dst_first;
				++first;
			}

			m_impl.PopBackN(static_cast<size_type>(dst_last - dst_first));
			m_impl.AppendMoveN(first, n);
		}
	}

	HAMON_CXX14_CONSTEXPR void AssignFillN(size_type n, T const& value)
	{
		auto const new_size = n;

		if (new_size > m_impl.Capacity())
		{
			auto const new_capacity = GrowCapacity(new_size);

			Impl tmp;
			tmp.Allocate(m_allocator, new_capacity);
			tmp.AppendFillN(new_size, value);
			tmp.Swap(m_impl);
			tmp.DestroyAll();
			tmp.Deallocate(m_allocator);
		}
		else
		{
			auto dst_first = m_impl.Begin();
			auto dst_last = m_impl.End();
			for (; n > 0 && dst_first != dst_last; --n)
			{
				*dst_first = value;
				++dst_first;
			}

			m_impl.PopBackN(static_cast<size_type>(dst_last - dst_first));
			m_impl.AppendFillN(n, value);
		}
	}

	template <typename Diff, typename... Args>
	HAMON_CXX14_CONSTEXPR void Emplace(Diff pos_offset, Args&&... args)
	{
		auto const new_size = m_impl.Size() + 1;
		if (new_size > m_impl.Capacity())
		{
			auto const new_capacity = GrowCapacity(new_size);

			// メモリの再確保が必要な場合、強い例外保証のために
			// 一時変数に構築してからswapする。

			Impl tmp;
			tmp.Allocate(m_allocator, new_capacity);
			tmp.AppendMoveN(m_impl.Begin(), static_cast<size_type>(pos_offset));
			tmp.AppendEmplace(m_allocator, hamon::forward<Args>(args)...);
			tmp.AppendMoveN(m_impl.Begin() + pos_offset, m_impl.Size() - static_cast<size_type>(pos_offset));
			tmp.Swap(m_impl);
			tmp.Deallocate(m_allocator);
		}
		else
		{
			m_impl.Emplace(m_allocator, pos_offset, hamon::forward<Args>(args)...);
		}
	}

	template <typename Diff, typename Iterator>
	HAMON_CXX14_CONSTEXPR void InsertCopyN(Diff pos_offset, Iterator first, size_type n)
	{
		auto const new_size = m_impl.Size() + n;
		if (new_size > m_impl.Capacity())
		{
			auto const new_capacity = GrowCapacity(new_size);

			// メモリの再確保が必要な場合、強い例外保証のために
			// 一時変数に構築してからswapする。

			Impl tmp;
			tmp.Allocate(m_allocator, new_capacity);
			tmp.AppendMoveN(m_impl.Begin(), static_cast<size_type>(pos_offset));
			tmp.AppendCopyN(first, n);
			tmp.AppendMoveN(m_impl.Begin() + pos_offset, m_impl.Size() - static_cast<size_type>(pos_offset));
			tmp.Swap(m_impl);
			tmp.Deallocate(m_allocator);
		}
		else
		{
			m_impl.InsertCopyN(pos_offset, first, n);
		}
	}

	template <typename Diff, typename Iterator, typename Sentinel>
	HAMON_CXX14_CONSTEXPR void InsertCopy(Diff pos_offset, Iterator first, Sentinel last)
	{
		for (; first != last; ++first)
		{
			this->Emplace(pos_offset, *first);
			++pos_offset;
		}
	}

	template <typename Diff>
	HAMON_CXX14_CONSTEXPR void InsertFillN(Diff pos_offset, size_type n, T const& x)
	{
		auto const new_size = m_impl.Size() + n;
		if (new_size > m_impl.Capacity())
		{
			auto const new_capacity = GrowCapacity(new_size);

			// メモリの再確保が必要な場合、強い例外保証のために
			// 一時変数に構築してからswapする。

			Impl tmp;
			tmp.Allocate(m_allocator, new_capacity);
			tmp.AppendMoveN(m_impl.Begin(), static_cast<size_type>(pos_offset));
			tmp.AppendFillN(n, x);
			tmp.AppendMoveN(m_impl.Begin() + pos_offset, m_impl.Size() - static_cast<size_type>(pos_offset));
			tmp.Swap(m_impl);
			tmp.Deallocate(m_allocator);
		}
		else
		{
			m_impl.InsertFillN(pos_offset, n, x);
		}
	}

	template <typename InputIterator,
		typename = hamon::enable_if_t<
			hamon::forward_iterator_t<InputIterator>::value>>
	HAMON_CXX14_CONSTEXPR void
	ConstructIter(InputIterator first, InputIterator last, hamon::detail::overload_priority<1>)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(first, last));
		m_impl.Allocate(m_allocator, n);
		m_impl.AppendCopyN(first, n);
	}

	template <typename InputIterator>
	HAMON_CXX14_CONSTEXPR void
	ConstructIter(InputIterator first, InputIterator last, hamon::detail::overload_priority<0>)
	{
		for (; first != last; ++first)
		{
			this->push_back(*first);
		}
	}

	template <typename R,
		typename = hamon::enable_if_t<
			hamon::ranges::forward_range_t<R>::value ||
			hamon::ranges::sized_range_t<R>::value>>
	HAMON_CXX14_CONSTEXPR void
	ConstructRange(R&& rg, hamon::detail::overload_priority<1>)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(rg));
		m_impl.Allocate(m_allocator, n);
		m_impl.AppendCopyN(hamon::ranges::begin(rg), n);
	}

	template <typename R>
	HAMON_CXX14_CONSTEXPR void
	ConstructRange(R&& rg, hamon::detail::overload_priority<0>)
	{
		for (auto first = hamon::ranges::begin(rg); first != hamon::ranges::end(rg); ++first)
		{
			this->push_back(*first);
		}
	}

	template <typename InputIterator,
		typename = hamon::enable_if_t<
			hamon::forward_iterator_t<InputIterator>::value>>
	HAMON_CXX14_CONSTEXPR void
	AssignIter(InputIterator first, InputIterator last, hamon::detail::overload_priority<1>)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(first, last));
		this->AssignCopyN(first, n);
	}

	template <typename InputIterator>
	HAMON_CXX14_CONSTEXPR void
	AssignIter(InputIterator first, InputIterator last, hamon::detail::overload_priority<0>)
	{
		this->AssignCopy(first, last);
	}

	template <typename R,
		typename = hamon::enable_if_t<
			hamon::ranges::forward_range_t<R>::value ||
			hamon::ranges::sized_range_t<R>::value>>
	HAMON_CXX14_CONSTEXPR void
	AssignRange(R&& rg, hamon::detail::overload_priority<1>)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(rg));
		this->AssignCopyN(hamon::ranges::begin(rg), n);
	}

	template <typename R>
	HAMON_CXX14_CONSTEXPR void
	AssignRange(R&& rg, hamon::detail::overload_priority<0>)
	{
		this->AssignCopy(hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

	template <typename Diff, typename InputIterator,
		typename = hamon::enable_if_t<
			hamon::forward_iterator_t<InputIterator>::value>>
	HAMON_CXX14_CONSTEXPR void
	InsertIter(Diff pos_offset, InputIterator first, InputIterator last, hamon::detail::overload_priority<1>)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(first, last));
		this->InsertCopyN(pos_offset, first, n);
	}

	template <typename Diff, typename InputIterator>
	HAMON_CXX14_CONSTEXPR void
	InsertIter(Diff pos_offset, InputIterator first, InputIterator last, hamon::detail::overload_priority<0>)
	{
		this->InsertCopy(pos_offset, first, last);
	}

	template <typename Diff, typename R,
		typename = hamon::enable_if_t<
			hamon::ranges::forward_range_t<R>::value ||
			hamon::ranges::sized_range_t<R>::value>>
	HAMON_CXX14_CONSTEXPR void
	InsertRange(Diff pos_offset, R&& rg, hamon::detail::overload_priority<1>)
	{
		auto const n = static_cast<size_type>(hamon::ranges::distance(rg));
		this->InsertCopyN(pos_offset, hamon::ranges::begin(rg), n);
	}

	template <typename Diff, typename R>
	HAMON_CXX14_CONSTEXPR void
	InsertRange(Diff pos_offset, R&& rg, hamon::detail::overload_priority<0>)
	{
		this->InsertCopy(pos_offset, hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

public:
	// [vector.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	vector() noexcept(noexcept(Allocator()))
		: vector(Allocator())
	{}

	HAMON_CXX11_CONSTEXPR explicit
	vector(Allocator const& a) noexcept
		: m_allocator(a)
	{
		// [vector.cons]/1
	}

	HAMON_CXX14_CONSTEXPR explicit
	vector(size_type n, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// TODO
		// [vector.cons]/3
		// Preconditions: T is Cpp17DefaultInsertable into *this.

		// [vector.cons]/4
		m_impl.Allocate(m_allocator, n);
		m_impl.AppendDefaultN(n);
	}

	HAMON_CXX14_CONSTEXPR
	vector(size_type n, T const& value, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// TODO
		// [vector.cons]/6
		// Preconditions: T is Cpp17CopyInsertable into *this.

		// [vector.cons]/7
		m_impl.Allocate(m_allocator, n);
		m_impl.AppendFillN(n, value);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	vector(InputIterator first, InputIterator last, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [vector.cons]/9,10
		this->ConstructIter(first, last, hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	vector(hamon::from_range_t, R&& rg, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		// [vector.cons]/11,12
		this->ConstructRange(hamon::forward<R>(rg), hamon::detail::overload_priority<1>{});
	}

	HAMON_CXX11_CONSTEXPR
	vector(vector const& x)
		: vector(x, AllocTraits::select_on_container_copy_construction(x.m_allocator))
	{}

	HAMON_CXX11_CONSTEXPR
	vector(vector&& x) noexcept
		: m_allocator(hamon::move(x.m_allocator))
		, m_impl(hamon::move(x.m_impl))
	{}

	HAMON_CXX14_CONSTEXPR
	vector(vector const& x, hamon::type_identity_t<Allocator> const& a)
		: m_allocator(a)
	{
		m_impl.Allocate(m_allocator, x.size());
		m_impl.AppendCopyN(x.begin(), x.size());
	}

	HAMON_CXX14_CONSTEXPR
	vector(vector&& x, hamon::type_identity_t<Allocator> const& a)
		: m_allocator(a)
	{
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (!AllocTraits::is_always_equal::value)
#else
		if           (!AllocTraits::is_always_equal::value)
#endif
		{
			if (a != x.m_allocator)
			{
				m_impl.Allocate(m_allocator, x.size());
				m_impl.AppendMoveN(x.begin(), x.size());
				return;
			}
		}

		m_impl = hamon::move(x.m_impl);
	}

	HAMON_CXX11_CONSTEXPR
	vector(std::initializer_list<T> il, Allocator const& a = Allocator())
		: vector(il.begin(), il.end(), a)
	{}

	HAMON_CXX20_CONSTEXPR
	~vector()
	{
		m_impl.DestroyAll();
		m_impl.Deallocate(m_allocator);
	}

	HAMON_CXX14_CONSTEXPR vector&
	operator=(vector const& x)
	{
		if (hamon::addressof(x) == this)
		{
			return *this;
		}

		this->AssignCopyN(x.begin(), x.size());
		return *this;
	}

	HAMON_CXX14_CONSTEXPR vector&
	operator=(vector&& x) noexcept(
		AllocTraits::propagate_on_container_move_assignment::value ||
		AllocTraits::is_always_equal::value)
	{
		if (hamon::addressof(x) == this)
		{
			return *this;
		}

		constexpr bool no_propagate_allocators =
			!AllocTraits::propagate_on_container_move_assignment::value &&
			!AllocTraits::is_always_equal::value;

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (no_propagate_allocators)
#else
		if           (no_propagate_allocators)
#endif
		{
			if (m_allocator != x.m_allocator)
			{
				this->AssignMoveN(x.begin(), x.size());
				return *this;
			}
		}

		m_impl.Deallocate(m_allocator);
		m_impl = hamon::move(x.m_impl);
		m_allocator = hamon::move(x.m_allocator);

		return *this;
	}

	HAMON_CXX14_CONSTEXPR vector&
	operator=(std::initializer_list<T> il)
	{
		this->assign(il);
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	assign(InputIterator first, InputIterator last)
	{
		this->AssignIter(first, last, hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	assign_range(R&& rg)
	{
		this->AssignRange(hamon::forward<R>(rg), hamon::detail::overload_priority<1>{});
	}

	HAMON_CXX14_CONSTEXPR void
	assign(size_type n, T const& u)
	{
		this->AssignFillN(n, u);
	}

	HAMON_CXX14_CONSTEXPR void
	assign(std::initializer_list<T> il)
	{
		this->assign(il.begin(), il.end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR allocator_type
	get_allocator() const noexcept
	{
		return m_allocator;
	}

	// iterators
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator begin() noexcept
	{
		return iterator(m_impl.Begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept
	{
		return const_iterator(m_impl.Begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator end() noexcept
	{
		return iterator(m_impl.End());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator end() const noexcept
	{
		return const_iterator(m_impl.End());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(this->end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator rbegin() const noexcept
	{
		return const_reverse_iterator(this->end());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reverse_iterator rend() noexcept
	{
		return reverse_iterator(this->begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator rend() const noexcept
	{
		return const_reverse_iterator(this->begin());
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator cbegin() const noexcept
	{
		return this->begin();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator cend() const noexcept
	{
		return this->end();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator crbegin() const noexcept
	{
		return this->rbegin();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator crend() const noexcept
	{
		return this->rend();
	}

	// [vector.capacity], capacity
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool empty() const noexcept
	{
		return this->size() == 0;
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type size() const noexcept
	{
		return m_impl.Size();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type max_size() const noexcept
	{
		return m_impl.MaxSize(m_allocator);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type capacity() const noexcept
	{
		// [vector.capacity]/1
		return m_impl.Capacity();
	}

	HAMON_CXX14_CONSTEXPR void resize(size_type sz)
	{
		if (sz < this->size())
		{
			m_impl.PopBackN(this->size() - sz);
		}
		else if (sz > this->size())
		{
			auto const old_size = this->size();
			auto const new_size = sz;
			if (new_size > this->capacity())
			{
				auto const new_capacity = GrowCapacity(new_size);

				Impl tmp;
				tmp.Allocate(m_allocator, new_capacity);
				tmp.AppendMoveN(m_impl.Begin(), old_size);
				tmp.AppendDefaultN(new_size - old_size);
				tmp.Swap(m_impl);
				tmp.Deallocate(m_allocator);
			}
			else
			{
				m_impl.AppendDefaultN(new_size - old_size);
			}
		}
	}

	HAMON_CXX14_CONSTEXPR void resize(size_type sz, T const& c)
	{
		if (sz < this->size())
		{
			m_impl.PopBackN(this->size() - sz);
		}
		else if (sz > this->size())
		{
			auto const old_size = this->size();
			auto const new_size = sz;
			if (new_size > this->capacity())
			{
				auto const new_capacity = GrowCapacity(new_size);

				Impl tmp;
				tmp.Allocate(m_allocator, new_capacity);
				tmp.AppendMoveN(m_impl.Begin(), old_size);
				tmp.AppendFillN(new_size - old_size, c);
				tmp.Swap(m_impl);
				tmp.Deallocate(m_allocator);
			}
			else
			{
				m_impl.AppendFillN(new_size - old_size, c);
			}
		}
	}

	HAMON_CXX14_CONSTEXPR void reserve(size_type n)
	{
		if (n > this->capacity())
		{
			auto const new_capacity = n;

			Impl tmp;
			tmp.Allocate(m_allocator, new_capacity);
			tmp.AppendMoveN(m_impl.Begin(), m_impl.Size());
			tmp.Swap(m_impl);
			tmp.Deallocate(m_allocator);
		}
	}

	HAMON_CXX14_CONSTEXPR void shrink_to_fit()
	{
		if (this->size() < this->capacity())
		{
			Impl tmp;
			tmp.Allocate(m_allocator, m_impl.Size());
			tmp.AppendMoveN(m_impl.Begin(), m_impl.Size());
			tmp.Swap(m_impl);
			tmp.Deallocate(m_allocator);
		}
	}

	// element access
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reference operator[](size_type n)
	{
		return
			HAMON_ASSERT(n < this->size()),
			this->data()[n];
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reference operator[](size_type n) const
	{
		return
			HAMON_ASSERT(n < this->size()),
			this->data()[n];
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reference at(size_type n)
	{
		return
			n < this->size() ?
			this->data()[n] :
			(hamon::detail::throw_out_of_range("vector::at"), this->data()[n]);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reference at(size_type n) const
	{
		return
			n < this->size() ?
			this->data()[n] :
			(hamon::detail::throw_out_of_range("vector::at"), this->data()[n]);
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reference front()
	{
		return
			HAMON_ASSERT(!this->empty()),
			this->data()[0];
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reference front() const
	{
		return
			HAMON_ASSERT(!this->empty()),
			this->data()[0];
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reference back()
	{
		return
			HAMON_ASSERT(!this->empty()),
			this->data()[this->size() - 1];
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reference back() const
	{
		return
			HAMON_ASSERT(!this->empty()),
			this->data()[this->size() - 1];
	}

	// [vector.data], data access
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR T* data() noexcept
	{
		return m_impl.Begin();
	}

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR T const* data() const noexcept
	{
		return m_impl.Begin();
	}

	// [vector.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR reference emplace_back(Args&&... args)
	{
		auto it = this->emplace(this->cend(), hamon::forward<Args>(args)...);
		return *it;
	}

	HAMON_CXX14_CONSTEXPR void push_back(T const& x)
	{
		this->emplace_back(x);
	}

	HAMON_CXX14_CONSTEXPR void push_back(T&& x)
	{
		this->emplace_back(hamon::move(x));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void append_range(R&& rg)
	{
		this->insert_range(this->cend(), hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR void pop_back()
	{
		m_impl.PopBackN(1);
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(const_iterator position, Args&&... args)
	{
		auto const pos_offset = position - this->begin();
		this->Emplace(pos_offset, hamon::forward<Args>(args)...);
		return this->begin() + pos_offset;
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, T const& x)
	{
		return this->emplace(position, x);
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, T&& x)
	{
		return this->emplace(position, hamon::move(x));
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, size_type n, T const& x)
	{
		auto const pos_offset = position - this->begin();
		this->InsertFillN(pos_offset, n, x);
		return this->begin() + pos_offset;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, InputIterator first, InputIterator last)
	{
		auto const pos_offset = position - this->begin();
		this->InsertIter(pos_offset, first, last, hamon::detail::overload_priority<1>{});
		return this->begin() + pos_offset;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR iterator
	insert_range(const_iterator position, R&& rg)
	{
		auto const pos_offset = position - this->begin();
		this->InsertRange(pos_offset, hamon::forward<R>(rg), hamon::detail::overload_priority<1>{});
		return this->begin() + pos_offset;
	}

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator position, std::initializer_list<T> il)
	{
		return this->insert(position, il.begin(), il.end());
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position)
	{
		return this->erase(position, position + 1);
	}

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
	{
		auto const pos_offset = first - this->begin();
		m_impl.DestroyN(pos_offset, static_cast<size_type>(last - first));
		return this->begin() + pos_offset;
	}

	HAMON_CXX14_CONSTEXPR void
	swap(vector& x) noexcept(
		AllocTraits::propagate_on_container_swap::value ||
		AllocTraits::is_always_equal::value)
	{
		hamon::swap(m_allocator, x.m_allocator);
		m_impl.Swap(x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR void clear() noexcept
	{
		m_impl.DestroyAll();
	}
};

HAMON_WARNING_POP()

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator = hamon::allocator<hamon::detail::iter_value_type<InputIterator>>>
vector(InputIterator, InputIterator, Allocator = Allocator())
	->vector<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator = hamon::allocator<hamon::ranges::range_value_t<R>>>
vector(hamon::from_range_t, R&&, Allocator = Allocator())
	->vector<hamon::ranges::range_value_t<R>, Allocator>;

#endif

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator==(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return x.size() == y.size() &&
		hamon::equal(x.begin(), x.end(), y.begin());
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR hamon::detail::synth_three_way_result<T>
operator<=>(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return hamon::lexicographical_compare_three_way(
		x.begin(), x.end(),
		y.begin(), y.end(),
		hamon::detail::synth_three_way);
}

#else

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator!=(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return !(x == y);
}

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator<(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return hamon::lexicographical_compare(
		x.begin(), x.end(),
		y.begin(), y.end());
}

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator>(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return y < x;
}

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator<=(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return !(x > y);
}

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator>=(vector<T, Allocator> const& x, vector<T, Allocator> const& y)
{
	return !(x < y);
}

#endif

template <typename T, typename Allocator>
HAMON_CXX14_CONSTEXPR void
swap(vector<T, Allocator>& x, vector<T, Allocator>& y)
noexcept(noexcept(x.swap(y)))
{
	x.swap(y);
}

}	// namespace hamon

#include <hamon/serialization/detail/save_vector.hpp>
#include <hamon/serialization/detail/load_vector.hpp>

namespace hamon
{

template <typename Archive, typename T>
void save_value(Archive& oa, hamon::vector<T> const& t)
{
	hamon::serialization::detail::save_vector(oa, t);
}

template <typename Archive, typename T>
void load_value(Archive& ia, hamon::vector<T>& t)
{
	t.clear();
	hamon::serialization::detail::load_vector(ia, t);
}

}	// namespace hamon

#endif

#endif // HAMON_VECTOR_VECTOR_HPP
