/**
 *	@file	deque.hpp
 *
 *	@brief	deque の定義
 */

#ifndef HAMON_DEQUE_DEQUE_HPP
#define HAMON_DEQUE_DEQUE_HPP

#include <hamon/deque/config.hpp>

#if defined(HAMON_USE_STD_DEQUE)

#include <deque>

namespace hamon
{

using std::deque;

}	// namespace hamon

#else

#include <hamon/algorithm/equal.hpp>
#include <hamon/algorithm/lexicographical_compare.hpp>
#include <hamon/algorithm/lexicographical_compare_three_way.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/algorithm/move.hpp>
#include <hamon/algorithm/move_backward.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/detail/iter_value_type.hpp>
#include <hamon/iterator/make_move_iterator.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/limits.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/memory/allocator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/destroy_at.hpp>
#include <hamon/memory/detail/equals_allocator.hpp>
#include <hamon/memory/detail/propagate_allocator_on_copy.hpp>
#include <hamon/memory/detail/propagate_allocator_on_move.hpp>
#include <hamon/memory/detail/propagate_allocator_on_swap.hpp>
#include <hamon/memory/detail/uninitialized_move_impl.hpp>
#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>
#include <hamon/memory/pointer_traits.hpp>
#include <hamon/memory/to_address.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/stdexcept/out_of_range.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_move_assignable.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/utility/exchange.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/swap.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

namespace hamon
{

#if 0

// 24.3.3 Header <deque> synopsis[deque.syn]

namespace pmr
{
template <typename T>
using deque = std::deque<T, polymorphic_allocator<T>>;
}

#endif

// 24.3.8 Class template deque[deque]

template <typename T, typename Allocator = hamon::allocator<T>>
class deque
{
private:
	using AllocTraits = hamon::allocator_traits<Allocator>;

	struct Impl;

	template <typename U, typename Const>
	struct Iterator
	{
	private:
		friend Iterator<U, hamon::negation<Const>>;
		friend class deque;
		using deque_ptr = hamon::conditional_t<Const::value, Impl const*, Impl*>;

	public:
		//using iterator_concept  = hamon::random_access_iterator_tag;
		using iterator_category = hamon::random_access_iterator_tag;
		using value_type        = U;
		using difference_type   = typename AllocTraits::difference_type;
		using pointer           = hamon::conditional_t<Const::value, U const*, U*>;
		using reference         = hamon::conditional_t<Const::value, U const&, U&>;

		HAMON_CXX11_CONSTEXPR
		Iterator() HAMON_NOEXCEPT
			: m_deque()
			, m_offset()
		{}

	private:
		HAMON_CXX11_CONSTEXPR
		Iterator(deque_ptr p, difference_type offset) HAMON_NOEXCEPT
			: m_deque(p)
			, m_offset(offset)
		{}

	public:
		template <typename C,
			typename = hamon::enable_if_t<C::value == Const::value || Const::value>>
		HAMON_CXX11_CONSTEXPR
		Iterator(Iterator<U, C> const& i) HAMON_NOEXCEPT
			: m_deque(i.m_deque)
			, m_offset(i.m_offset)
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
		reference operator*() const HAMON_NOEXCEPT
		{
			return m_deque->Subscript(m_offset);
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
		pointer operator->() const HAMON_NOEXCEPT
		{
			return hamon::pointer_traits<pointer>::pointer_to(**this);
		}

		HAMON_CXX14_CONSTEXPR Iterator&
		operator++() HAMON_NOEXCEPT
		{
			++m_offset;
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
			--m_offset;
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
			m_offset += n;
			return *this;
		}

		HAMON_CXX14_CONSTEXPR Iterator&
		operator-=(difference_type n) HAMON_NOEXCEPT
		{
			m_offset -= n;
			return *this;
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR reference
		operator[](difference_type n) const HAMON_NOEXCEPT
		{
			return *(*this + n);
		}

	private:
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR Iterator
		operator+(Iterator const& i, difference_type n) HAMON_NOEXCEPT
		{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4308)	// 負の整数定数が符号なしの型に変換されました。
			return Iterator(i.m_deque, i.m_offset + n);
HAMON_WARNING_POP()
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR Iterator
		operator+(difference_type n, Iterator const& i) HAMON_NOEXCEPT
		{
			return Iterator(i.m_deque, i.m_offset + n);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR Iterator
		operator-(Iterator const& i, difference_type n) HAMON_NOEXCEPT
		{
			return Iterator(i.m_deque, i.m_offset - n);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR difference_type
		operator-(Iterator const& lhs, Iterator const& rhs) HAMON_NOEXCEPT
		{
			return lhs.m_offset - rhs.m_offset;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool
		operator==(Iterator const& lhs, Iterator const& rhs) HAMON_NOEXCEPT
		{
			return lhs.m_offset == rhs.m_offset;
		}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR hamon::strong_ordering
		operator<=>(Iterator const& lhs, Iterator const& rhs) HAMON_NOEXCEPT
		{
			return lhs.m_offset <=> rhs.m_offset;
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
			return lhs.m_offset < rhs.m_offset;
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
		deque_ptr		m_deque;
		difference_type m_offset;
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

	static_assert(hamon::is_same<typename allocator_type::value_type, value_type>::value, "[container.alloc.reqmts]/5");

private:
	struct Impl
	{
	private:
		using MapAllocator = typename AllocTraits::template rebind_alloc<typename AllocTraits::pointer>;
		using MapAllocTraits = hamon::allocator_traits<MapAllocator>;

		static const size_type BlockSize = 8;

		T**             m_map{};
		size_type       m_map_size{};
		difference_type m_start{};
		difference_type m_end{};

	public:
		HAMON_CXX11_CONSTEXPR
		Impl() HAMON_NOEXCEPT {}

		// コピー禁止
		Impl(Impl const&) = delete;
		Impl& operator=(Impl const&) = delete;

		HAMON_CXX14_CONSTEXPR
		Impl(Impl&& x) HAMON_NOEXCEPT
		{
			m_map      = hamon::exchange(x.m_map,      nullptr);
			m_map_size = hamon::exchange(x.m_map_size, size_type{0});
			m_start    = hamon::exchange(x.m_start,    difference_type{0});
			m_end      = hamon::exchange(x.m_end,      difference_type{0});
		}

		HAMON_CXX14_CONSTEXPR
		Impl& operator=(Impl&& x) HAMON_NOEXCEPT
		{
			Impl(hamon::move(x)).Swap(*this);
			return *this;
		}

		HAMON_CXX14_CONSTEXPR void
		Swap(Impl& x) HAMON_NOEXCEPT
		{
			hamon::swap(m_map,      x.m_map);
			hamon::swap(m_map_size, x.m_map_size);
			hamon::swap(m_start,    x.m_start);
			hamon::swap(m_end,      x.m_end);
		}

		HAMON_CXX14_CONSTEXPR iterator Begin() HAMON_NOEXCEPT
		{
			return iterator(this, m_start);
		}

		HAMON_CXX11_CONSTEXPR const_iterator Begin() const HAMON_NOEXCEPT
		{
			return const_iterator(this, m_start);
		}

		HAMON_CXX14_CONSTEXPR iterator End() HAMON_NOEXCEPT
		{
			return iterator(this, m_end);
		}

		HAMON_CXX11_CONSTEXPR const_iterator End() const HAMON_NOEXCEPT
		{
			return const_iterator(this, m_end);
		}

		HAMON_CXX14_CONSTEXPR reverse_iterator RBegin() HAMON_NOEXCEPT
		{
			return reverse_iterator(this->End());
		}

		HAMON_CXX11_CONSTEXPR const_reverse_iterator RBegin() const HAMON_NOEXCEPT
		{
			return const_reverse_iterator(this->End());
		}

		HAMON_CXX14_CONSTEXPR reverse_iterator REnd() HAMON_NOEXCEPT
		{
			return reverse_iterator(this->Begin());
		}

		HAMON_CXX11_CONSTEXPR const_reverse_iterator REnd() const HAMON_NOEXCEPT
		{
			return const_reverse_iterator(this->Begin());
		}

		HAMON_CXX14_CONSTEXPR reference Subscript(difference_type n) HAMON_NOEXCEPT
		{
			return m_map[static_cast<size_type>(n) / BlockSize][static_cast<size_type>(n) % BlockSize];
		}

		HAMON_CXX11_CONSTEXPR const_reference Subscript(difference_type n) const HAMON_NOEXCEPT
		{
			return m_map[static_cast<size_type>(n) / BlockSize][static_cast<size_type>(n) % BlockSize];
		}
	private:
		HAMON_CXX14_CONSTEXPR pointer GetPtr(difference_type n) HAMON_NOEXCEPT
		{
			return &m_map[static_cast<size_type>(n) / BlockSize][static_cast<size_type>(n) % BlockSize];
		}
	public:
		HAMON_CXX11_CONSTEXPR size_type
		MaxSize(allocator_type const& allocator) const HAMON_NOEXCEPT
		{
			return hamon::min(
				static_cast<size_type>(hamon::numeric_limits<difference_type>::max()),
				static_cast<size_type>(AllocTraits::max_size(allocator)));
		}

		HAMON_CXX11_CONSTEXPR size_type Size() const HAMON_NOEXCEPT
		{
			return static_cast<size_type>(m_end - m_start);
		}
	private:
		HAMON_CXX11_CONSTEXPR size_type Capacity() const HAMON_NOEXCEPT
		{
			return m_map_size * BlockSize;
		}
	public:
		HAMON_CXX14_CONSTEXPR void Clear(allocator_type& allocator)
		{
			for (difference_type i = m_start; i < m_end; ++i)
			{
				hamon::destroy_at(GetPtr(i));
			}

			for (size_type i = 0; i < m_map_size; ++i)
			{
				AllocTraits::deallocate(allocator, m_map[i], BlockSize);
			}

			if (m_map != nullptr)
			{
				MapAllocator map_allocator(allocator);
				MapAllocTraits::deallocate(map_allocator, m_map, m_map_size);
				m_map = nullptr;
			}
			m_map_size = 0;
			m_start = 0;
			m_end = 0;
		}

		template <typename... Args>
		HAMON_CXX14_CONSTEXPR void EmplaceBack(allocator_type& allocator, Args&&... args)
		{
			if (m_end == static_cast<difference_type>(this->Capacity()))
			{
				auto const new_map_size = m_map_size + 1;
				MapAllocator map_allocator(allocator);
				auto new_map = MapAllocTraits::allocate(map_allocator, new_map_size);
				hamon::detail::uninitialized_value_construct_n_impl(new_map, new_map_size);
				for (size_type i = 0; i < new_map_size; ++i)
				{
					if (i < m_map_size)
					{
						new_map[i] = m_map[i];
					}
					else
					{
						new_map[i] = AllocTraits::allocate(allocator, BlockSize);
					}
				}

				if (m_map != nullptr)
				{
					MapAllocTraits::deallocate(map_allocator, m_map, m_map_size);
				}
				m_map = new_map;
				m_map_size = new_map_size;
			}

			AllocTraits::construct(allocator, GetPtr(m_end), hamon::forward<Args>(args)...);
			++m_end;
		}

		template <typename... Args>
		HAMON_CXX14_CONSTEXPR void EmplaceFront(allocator_type& allocator, Args&&... args)
		{
			if (m_start == 0)
			{
				auto const new_map_size = m_map_size + 1;
				MapAllocator map_allocator(allocator);
				auto new_map = MapAllocTraits::allocate(map_allocator, new_map_size);
				hamon::detail::uninitialized_value_construct_n_impl(new_map, new_map_size);
				for (size_type i = 0; i < m_map_size; ++i)
				{
					new_map[i + 1] = m_map[i];
				}
				new_map[0] = AllocTraits::allocate(allocator, BlockSize);

				if (m_map != nullptr)
				{
					MapAllocTraits::deallocate(map_allocator, m_map, m_map_size);
				}
				m_map = new_map;
				m_map_size = new_map_size;

				m_start += BlockSize;
				m_end += BlockSize;
			}

			AllocTraits::construct(allocator, GetPtr(m_start - 1), hamon::forward<Args>(args)...);
			--m_start;
		}

		template <typename... Args>
		HAMON_CXX14_CONSTEXPR void Emplace(allocator_type& allocator, difference_type pos, Args&&... args)
		{
			auto const sz = static_cast<difference_type>(this->Size());

			if (pos == 0)
			{
				this->EmplaceFront(allocator, hamon::forward<Args>(args)...);
			}
			else if (pos == sz)
			{
				this->EmplaceBack(allocator, hamon::forward<Args>(args)...);
			}
			else
			{
				// 移動する要素数が少なくなるように、前方または後方に移動する
				if (pos <= (sz / 2))
				{
					this->EmplaceFront(allocator, hamon::move(*this->Begin()));
					auto dst = this->Begin() + 1;
					auto first = dst + 1;
					auto last = dst + pos;
					dst = hamon::detail::uninitialized_move_impl(first, last, dst).out;
					AllocTraits::construct(allocator, hamon::to_address(dst), hamon::forward<Args>(args)...);
				}
				else
				{
					this->EmplaceBack(allocator, hamon::move(*this->RBegin()));
					auto dst = this->RBegin() + 1;
					auto first = dst + 1;
					auto last = dst + (sz - pos);
					dst = hamon::detail::uninitialized_move_impl(first, last, dst).out;
					AllocTraits::construct(allocator, hamon::to_address(dst), hamon::forward<Args>(args)...);
				}
			}
		}

		template <typename Iterator, typename Sentinel>
		HAMON_CXX14_CONSTEXPR void AppendIter(allocator_type& allocator, Iterator first, Sentinel last)
		{
			for (; first != last; ++first)
			{
				this->EmplaceBack(allocator, *first);
			}
		}

		HAMON_CXX14_CONSTEXPR void AppendFillN(allocator_type& allocator, size_type n, T const& t)
		{
			for (; n > 0; --n)
			{
				this->EmplaceBack(allocator, t);
			}
		}

		template <typename Iterator, typename Sentinel>
		HAMON_CXX14_CONSTEXPR void InsertIter(allocator_type& allocator, difference_type pos, Iterator first, Sentinel last)
		{
			for (; first != last; ++first)
			{
				this->Emplace(allocator, pos, *first);
				++pos;
			}
		}

		HAMON_CXX14_CONSTEXPR void InsertFillN(allocator_type& allocator, difference_type pos, size_type n, T const& t)
		{
			for (; n > 0; --n)
			{
				this->Emplace(allocator, pos, t);
				++pos;
			}
		}

		HAMON_CXX14_CONSTEXPR void PopBackN(allocator_type& allocator, size_type n)
		{
			HAMON_ASSERT(n <= this->Size());

			for (; n > 0; --n)
			{
				AllocTraits::destroy(allocator, GetPtr(m_end - 1));
				--m_end;
			}
		}

		HAMON_CXX14_CONSTEXPR void PopFrontN(allocator_type& allocator, size_type n)
		{
			HAMON_ASSERT(n <= this->Size());

			for (; n > 0; --n)
			{
				AllocTraits::destroy(allocator, GetPtr(m_start));
				++m_start;
			}
		}

		HAMON_CXX14_CONSTEXPR void DestroyN(allocator_type& allocator, difference_type pos, size_type n)
		{
			HAMON_ASSERT(n <= this->Size());

			auto const first = this->Begin() + pos;
			auto const last  = first + static_cast<difference_type>(n);

			if (first - this->Begin() < this->End() - last)
			{
				hamon::move_backward(this->Begin(), first, last);
				PopFrontN(allocator, n);
			}
			else
			{
				hamon::move(last, this->End(), first);
				PopBackN(allocator, n);
			}
		}

		template <typename Iterator, typename Sentinel>
		HAMON_CXX14_CONSTEXPR void AssignIter(allocator_type& allocator, Iterator first, Sentinel last)
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
			this->AppendIter(allocator, first, last);
		}

		HAMON_CXX14_CONSTEXPR void AssignFillN(allocator_type& allocator, size_type n, T const& t)
		{
			auto dst_first = this->Begin();
			auto dst_last = this->End();
			for (; n > 0 && dst_first != dst_last;)
			{
				*dst_first = t;
				++dst_first;
				--n;
			}
			this->PopBackN(allocator, static_cast<size_type>(dst_last - dst_first));
			this->AppendFillN(allocator, n, t);
		}

		template <typename... Args>
		HAMON_CXX14_CONSTEXPR void Resize(allocator_type& allocator, size_type sz, Args&&... args)
		{
			if (sz < this->Size())
			{
				this->PopBackN(allocator, this->Size() - sz);
			}

			while (this->Size() < sz)
			{
				this->EmplaceBack(allocator, hamon::forward<Args>(args)...);
			}
		}
	};

	HAMON_NO_UNIQUE_ADDRESS	allocator_type m_allocator;
	Impl	m_impl;

public:
	// [deque.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	deque() : deque(Allocator()) {}

	HAMON_CXX11_CONSTEXPR explicit
	deque(Allocator const& a)
		: m_allocator(a)
	{}

	HAMON_CXX14_CONSTEXPR explicit
	deque(size_type n, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		this->resize(n);
	}

	HAMON_CXX14_CONSTEXPR
	deque(size_type n, T const& value, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		this->resize(n, value);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR
	deque(InputIterator first, InputIterator last, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		m_impl.AppendIter(m_allocator, first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR
	deque(hamon::from_range_t, R&& rg, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		m_impl.AppendIter(m_allocator, hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

	HAMON_CXX11_CONSTEXPR
	deque(deque const& x)
		: deque(x, AllocTraits::select_on_container_copy_construction(x.m_allocator))
	{}

	HAMON_CXX11_CONSTEXPR
	deque(deque&& x) HAMON_NOEXCEPT	// noexcept as an extension
		: m_allocator(hamon::move(x.m_allocator))
		, m_impl(hamon::move(x.m_impl))
	{}

	HAMON_CXX14_CONSTEXPR
	deque(deque const& x, type_identity_t<Allocator> const& a)
		: m_allocator(a)
	{
		m_impl.AppendIter(m_allocator, hamon::ranges::begin(x), hamon::ranges::end(x));
	}

	HAMON_CXX14_CONSTEXPR
	deque(deque&& x, type_identity_t<Allocator> const& a)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::allocator_traits<Allocator>::is_always_equal::value)
		: m_allocator(a)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			m_impl.AppendIter(m_allocator,
				hamon::make_move_iterator(hamon::ranges::begin(x)),
				hamon::make_move_iterator(hamon::ranges::end(x)));
			return;
		}

		m_impl = hamon::move(x.m_impl);
	}

	HAMON_CXX11_CONSTEXPR
	deque(std::initializer_list<T> il, Allocator const& a = Allocator())
		: deque(il.begin(), il.end(), a)
	{}

	HAMON_CXX20_CONSTEXPR
	~deque()
	{
		this->clear();
	}

	HAMON_CXX14_CONSTEXPR deque& operator=(deque const& x)
	{
		if (hamon::addressof(x) == this)
		{
			return *this;
		}

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (AllocTraits::propagate_on_container_copy_assignment::value)
#else
		if           (AllocTraits::propagate_on_container_copy_assignment::value)
#endif
		{
			if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
			{
				// アロケータを伝播させる場合は、
				// 今のアロケータで確保した要素を破棄しなければいけない
				this->clear();

				// アロケータを伝播
				hamon::detail::propagate_allocator_on_copy(m_allocator, x.m_allocator);
			}
		}

		m_impl.AssignIter(m_allocator, hamon::ranges::begin(x), hamon::ranges::end(x));

		return *this;
	}

	HAMON_CXX14_CONSTEXPR deque& operator=(deque&& x)
		HAMON_NOEXCEPT_IF(AllocTraits::is_always_equal::value)
	{
		if (hamon::addressof(x) == this)
		{
			return *this;
		}

#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (!AllocTraits::propagate_on_container_move_assignment::value)
#else
		if           (!AllocTraits::propagate_on_container_move_assignment::value)
#endif
		{
			if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
			{
				// アロケータを伝播させない場合は、
				// 要素をムーブ代入しなければいけない = 要素をstealすることはできない。
				m_impl.AssignIter(m_allocator,
					hamon::make_move_iterator(hamon::ranges::begin(x)),
					hamon::make_move_iterator(hamon::ranges::end(x)));	// may throw
				return *this;
			}
		}

		// 今の要素を破棄
		this->clear();

		// アロケータを伝播
		hamon::detail::propagate_allocator_on_move(m_allocator, x.m_allocator);

		// 要素をsteal
		m_impl = hamon::move(x.m_impl);

		return *this;
	}

	HAMON_CXX14_CONSTEXPR deque& operator=(std::initializer_list<T> il)
	{
		this->assign(il);
		return *this;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void assign(InputIterator first, InputIterator last)
	{
		m_impl.AssignIter(m_allocator, first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void assign_range(R&& rg)
	{
		m_impl.AssignIter(m_allocator, hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

	HAMON_CXX14_CONSTEXPR void assign(size_type n, T const& t)
	{
		m_impl.AssignFillN(m_allocator, n, t);
	}

	HAMON_CXX14_CONSTEXPR void assign(std::initializer_list<T> il)
	{
		this->assign(il.begin(), il.end());
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	allocator_type get_allocator() const HAMON_NOEXCEPT
	{
		return m_allocator;
	}

	// iterators
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator begin() HAMON_NOEXCEPT
	{
		return m_impl.Begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator begin() const HAMON_NOEXCEPT
	{
		return m_impl.Begin();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator end() HAMON_NOEXCEPT
	{
		return m_impl.End();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator end() const HAMON_NOEXCEPT
	{
		return m_impl.End();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reverse_iterator rbegin() HAMON_NOEXCEPT
	{
		return m_impl.RBegin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator rbegin() const HAMON_NOEXCEPT
	{
		return m_impl.RBegin();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reverse_iterator rend() HAMON_NOEXCEPT
	{
		return m_impl.REnd();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator rend() const HAMON_NOEXCEPT
	{
		return m_impl.REnd();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cbegin() const HAMON_NOEXCEPT
	{
		return this->begin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_iterator cend() const HAMON_NOEXCEPT
	{
		return this->end();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator crbegin() const HAMON_NOEXCEPT
	{
		return this->rbegin();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reverse_iterator crend() const HAMON_NOEXCEPT
	{
		return this->rend();
	}

	// [deque.capacity], capacity
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	bool empty() const HAMON_NOEXCEPT
	{
		return this->size() == 0;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type size() const HAMON_NOEXCEPT
	{
		return m_impl.Size();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	size_type max_size() const HAMON_NOEXCEPT
	{
		return m_impl.MaxSize(m_allocator);
	}

	HAMON_CXX14_CONSTEXPR void resize(size_type sz)
	{
		m_impl.Resize(m_allocator, sz);
	}

	HAMON_CXX14_CONSTEXPR void resize(size_type sz, T const& c)
	{
		m_impl.Resize(m_allocator, sz, c);
	}

	HAMON_CXX14_CONSTEXPR void shrink_to_fit()
	{
		// TODO
	}

	// element access
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reference operator[](size_type n) HAMON_NOEXCEPT	// noexcept as an extension
	{
		return HAMON_ASSERT(n < this->size()),
			this->begin()[static_cast<difference_type>(n)];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reference operator[](size_type n) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return HAMON_ASSERT(n < this->size()),
			this->begin()[static_cast<difference_type>(n)];
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reference at(size_type n)
	{
		return n < this->size() ? (*this)[n] :
			(hamon::detail::throw_out_of_range("deque::at"), (*this)[n]);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reference at(size_type n) const
	{
		return n < this->size() ? (*this)[n] :
			(hamon::detail::throw_out_of_range("deque::at"), (*this)[n]);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reference front() HAMON_NOEXCEPT	// noexcept as an extension
	{
		return (*this)[0];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reference front() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return (*this)[0];
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	reference back() HAMON_NOEXCEPT	// noexcept as an extension
	{
		return (*this)[this->size() - 1];
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	const_reference back() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return (*this)[this->size() - 1];
	}

	// [deque.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR reference emplace_front(Args&&... args)
	{
		m_impl.EmplaceFront(m_allocator, hamon::forward<Args>(args)...);
		return this->front();
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR reference emplace_back(Args&&... args)
	{
		m_impl.EmplaceBack(m_allocator, hamon::forward<Args>(args)...);
		return this->back();
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator emplace(const_iterator position, Args&&... args)
	{
		auto const pos_offset = position - this->begin();
		m_impl.Emplace(m_allocator, pos_offset, hamon::forward<Args>(args)...);
		return this->begin() + pos_offset;
	}

	HAMON_CXX14_CONSTEXPR void push_front(T const& x)
	{
		this->emplace_front(x);
	}

	HAMON_CXX14_CONSTEXPR void push_front(T&& x)
	{
		this->emplace_front(hamon::move(x));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void prepend_range(R&& rg)
	{
		this->insert_range(this->cbegin(), hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR void push_back(T const& x)
	{
		m_impl.EmplaceBack(m_allocator, x);
	}

	HAMON_CXX14_CONSTEXPR void push_back(T&& x)
	{
		m_impl.EmplaceBack(m_allocator, hamon::move(x));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void append_range(R&& rg)
	{
		this->insert_range(this->cend(), hamon::forward<R>(rg));
	}

	HAMON_CXX14_CONSTEXPR iterator insert(const_iterator position, T const& x)
	{
		return this->emplace(position, x);
	}

	HAMON_CXX14_CONSTEXPR iterator insert(const_iterator position, T&& x)
	{
		return this->emplace(position, hamon::move(x));
	}

	HAMON_CXX14_CONSTEXPR iterator insert(const_iterator position, size_type n, T const& x)
	{
		auto const pos_offset = position - this->begin();
		m_impl.InsertFillN(m_allocator, pos_offset, n, x);
		return this->begin() + pos_offset;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR iterator insert(const_iterator position, InputIterator first, InputIterator last)
	{
		auto const pos_offset = position - this->begin();
		m_impl.InsertIter(m_allocator, pos_offset, first, last);
		return this->begin() + pos_offset;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR iterator insert_range(const_iterator position, R&& rg)
	{
		auto const pos_offset = position - this->begin();
		m_impl.InsertIter(m_allocator, pos_offset, hamon::ranges::begin(rg), hamon::ranges::end(rg));
		return this->begin() + pos_offset;
	}

	HAMON_CXX14_CONSTEXPR iterator insert(const_iterator position, std::initializer_list<T> il)
	{
		return this->insert(position, il.begin(), il.end());
	}

	HAMON_CXX14_CONSTEXPR void pop_front() HAMON_NOEXCEPT	// noexcept as an extension
	{
		m_impl.PopFrontN(m_allocator, 1);
	}

	HAMON_CXX14_CONSTEXPR void pop_back() HAMON_NOEXCEPT	// noexcept as an extension
	{
		m_impl.PopBackN(m_allocator, 1);
	}

	HAMON_CXX14_CONSTEXPR iterator erase(const_iterator position)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_assignable<T>::value)	// noexcept as an extension
	{
		return this->erase(position, position + 1);
	}

	HAMON_CXX14_CONSTEXPR iterator erase(const_iterator first, const_iterator last)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_assignable<T>::value)	// noexcept as an extension
	{
		auto const pos_offset = first - this->begin();
		m_impl.DestroyN(m_allocator, pos_offset, static_cast<size_type>(last - first));
		return this->begin() + pos_offset;
	}

	HAMON_CXX14_CONSTEXPR void swap(deque& x)
		HAMON_NOEXCEPT_IF(AllocTraits::is_always_equal::value)
	{
		if (!hamon::detail::equals_allocator(m_allocator, x.m_allocator))
		{
			hamon::detail::propagate_allocator_on_swap(m_allocator, x.m_allocator);
		}
		m_impl.Swap(x.m_impl);
	}

	HAMON_CXX14_CONSTEXPR void clear() HAMON_NOEXCEPT
	{
		m_impl.Clear(m_allocator);
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator = hamon::allocator<hamon::detail::iter_value_type<InputIterator>>>
deque(InputIterator, InputIterator, Allocator = Allocator())
->deque<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator = hamon::allocator<hamon::ranges::range_value_t<R>>>
deque(from_range_t, R&&, Allocator = Allocator())
->deque<hamon::ranges::range_value_t<R>, Allocator>;

#endif

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator==(deque<T, Allocator> const& x, deque<T, Allocator> const& y)
{
	return x.size() == y.size() &&
		hamon::equal(x.begin(), x.end(), y.begin());
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR hamon::detail::synth_three_way_result<T>
operator<=>(deque<T, Allocator> const&x, deque<T, Allocator> const&y)
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
operator!=(deque<T, Allocator> const& x, deque<T, Allocator> const& y)
{
	return !(x == y);
}

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator<(deque<T, Allocator> const& x, deque<T, Allocator> const& y)
{
	return hamon::lexicographical_compare(
		x.begin(), x.end(),
		y.begin(), y.end());
}

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator>(deque<T, Allocator> const& x, deque<T, Allocator> const& y)
{
	return y < x;
}

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator<=(deque<T, Allocator> const& x, deque<T, Allocator> const& y)
{
	return !(x > y);
}

template <typename T, typename Allocator>
HAMON_NODISCARD	// nodiscard as an extension
HAMON_CXX11_CONSTEXPR bool
operator>=(deque<T, Allocator> const& x, deque<T, Allocator> const& y)
{
	return !(x < y);
}

#endif

template <typename T, typename Allocator>
HAMON_CXX14_CONSTEXPR void
swap(deque<T, Allocator>& x, deque<T, Allocator>& y)
HAMON_NOEXCEPT_IF_EXPR(x.swap(y))
{
	x.swap(y);
}

}	// namespace hamon

HAMON_WARNING_POP()

#endif

#endif // HAMON_DEQUE_DEQUE_HPP
