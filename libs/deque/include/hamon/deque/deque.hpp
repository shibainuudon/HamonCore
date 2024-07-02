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
#include <hamon/cmath/ranges/round_up.hpp>
#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/compare.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/memory.hpp>
#include <hamon/memory/detail/uninitialized_value_construct_n_impl.hpp>
#include <hamon/ranges.hpp>
#include <hamon/ranges/detail/container_compatible_range.hpp>
#include <hamon/stdexcept.hpp>
#include <hamon/type_traits.hpp>
#include <hamon/utility.hpp>
#include <hamon/config.hpp>
#include <initializer_list>
#include <memory>	// allocator, allocator_traits

namespace hamon
{

#if 0

// 24.3.3 Header <deque> synopsis[deque.syn]

// [deque], class template deque
template <typename T, typename Allocator = std::allocator<T>>
class deque;

template <typename T, typename Allocator>
bool operator==(deque<T, Allocator> const& x, deque<T, Allocator> const& y);

template <typename T, typename Allocator>
hamon::detail::synth_three_way_result<T>
operator<=>(deque<T, Allocator> const&x, deque<T, Allocator> const&y);

template <typename T, typename Allocator>
void swap(deque<T, Allocator>& x, deque<T, Allocator>& y)
noexcept(noexcept(x.swap(y)));

// [deque.erasure], erasure
template <typename T, typename Allocator, typename U = T>
typename deque<T, Allocator>::size_type
erase(deque<T, Allocator>& c, U const& value);

template <typename T, typename Allocator, typename Predicate>
typename deque<T, Allocator>::size_type
erase_if(deque<T, Allocator>& c, Predicate pred);

namespace pmr
{
template <typename T>
using deque = std::deque<T, polymorphic_allocator<T>>;
}

#endif

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4702)	// 制御が渡らないコードです。

// 24.3.8 Class template deque[deque]

template <typename T, typename Allocator = std::allocator<T>>
class deque
{
private:
	using AllocTraits = std::allocator_traits<Allocator>;

	template <typename U, typename Const>
	struct Iterator
	{
	private:
		friend Iterator<U, hamon::negation<Const>>;
		friend class deque;
		using deque_ptr = hamon::conditional_t<Const::value, deque const*, deque*>;

	public:
		using iterator_concept  = hamon::random_access_iterator_tag;
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
			return (*m_deque)[m_offset];
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
		pointer operator->() const HAMON_NOEXCEPT
		{
			return std::pointer_traits<pointer>::pointer_to(**this);
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
			return Iterator(i.m_deque, i.m_offset + n);
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
			return static_cast<difference_type>(lhs.m_offset - rhs.m_offset);
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

private:
	struct Impl
	{
	private:
		static const size_type BlockSize = 8;

		T**			m_map{};
		size_type	m_map_size{};
		size_type	m_start_offset{};
		size_type	m_end_offset{};

	public:
		HAMON_CXX11_CONSTEXPR
		Impl() HAMON_NOEXCEPT {}

		// コピー禁止
		Impl(Impl const&) = delete;
		Impl& operator=(Impl const&) = delete;

		HAMON_CXX14_CONSTEXPR
		Impl(Impl&& x) HAMON_NOEXCEPT
		{
			m_map          = hamon::exchange(x.m_map,          nullptr);
			m_map_size     = hamon::exchange(x.m_map_size,     size_type{0});
			m_start_offset = hamon::exchange(x.m_start_offset, size_type{0});
			m_end_offset   = hamon::exchange(x.m_end_offset,   size_type{0});
		}

		HAMON_CXX14_CONSTEXPR
		Impl& operator=(Impl&& x) HAMON_NOEXCEPT
		{
			Impl(hamon::move(x)).Swap(*this);
			return *this;
		}

		HAMON_CXX14_CONSTEXPR void
		Swap(Impl& x) noexcept
		{
			hamon::swap(m_map,          x.m_map);
			hamon::swap(m_map_size,     x.m_map_size);
			hamon::swap(m_start_offset, x.m_start_offset);
			hamon::swap(m_end_offset,   x.m_end_offset);
		}

		constexpr reference operator[](size_type n) noexcept
		{
			const auto i = m_start_offset + n;
			return m_map[i / BlockSize][i % BlockSize];
		}

		constexpr const_reference operator[](size_type n) const noexcept
		{
			const auto i = m_start_offset + n;
			return m_map[i / BlockSize][i % BlockSize];
		}
	private:
		constexpr pointer GetPtr(size_type n) noexcept
		{
			const auto i = m_start_offset + n;
			return &m_map[i / BlockSize][i % BlockSize];
		}
	public:
		constexpr size_type Size() const noexcept
		{
			return m_end_offset - m_start_offset;
		}
	private:
		constexpr size_type Capacity() const noexcept
		{
			return m_map_size * BlockSize;
		}
	public:
		constexpr void Clear(allocator_type& allocator)
		{
			for (size_type i = 0; i < this->Size(); ++i)
			{
				hamon::destroy_at(GetPtr(i));
			}
			for (size_type i = 0; i < m_map_size; ++i)
			{
				AllocTraits::deallocate(allocator, m_map[i], BlockSize);
			}

			if (m_map != nullptr)
			{
				delete[] m_map;	// TODO
				m_map = nullptr;
			}
			m_map_size = 0;
			m_start_offset = 0;
			m_end_offset = 0;
		}

		template <typename... Args>
		constexpr void EmplaceBack(allocator_type& allocator, Args&&... args)
		{
			if (m_end_offset == this->Capacity())
			{
				auto const new_map_size = m_map_size + 1;
				auto new_map = new T*[new_map_size];
				for (size_type i = 0; i < new_map_size; ++i)
				{
					if (i < m_map_size)
					{
						new_map[i] = m_map[i];
					}
					else
					{
						new_map[i] = allocator.allocate(BlockSize);
					}
				}

				if (m_map != nullptr)
				{
					delete[] m_map;
				}
				m_map = new_map;
				m_map_size = new_map_size;
			}

			AllocTraits::construct(allocator, GetPtr(m_end_offset), hamon::forward<Args>(args)...);
			++m_end_offset;
		}

		constexpr void PopBack(allocator_type& allocator)
		{
			HAMON_ASSERT(m_start_offset < m_end_offset);
			AllocTraits::destroy(allocator, GetPtr(m_end_offset - 1));
			--m_end_offset;
		}
	};

	HAMON_NO_UNIQUE_ADDRESS	allocator_type m_allocator;
	Impl	m_impl;

private:
	template <typename... Args>
	constexpr void EmplaceBack(Args&&... args)
	{
		m_impl.EmplaceBack(m_allocator, hamon::forward<Args>(args)...);
	}

	template <typename Iterator, typename Sentinel>
	constexpr void ConstructIter(Iterator first, Sentinel last)
	{
		for (; first != last; ++first)
		{
			this->EmplaceBack(*first);
		}
	}

public:
	// [deque.cons], construct/copy/destroy
	HAMON_CXX11_CONSTEXPR
	deque() : deque(Allocator()) {}

	HAMON_CXX11_CONSTEXPR explicit
	deque(Allocator const& a)
		: m_allocator(a)
	{}

	constexpr explicit
	deque(size_type n, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		this->resize(n);
	}

	constexpr
	deque(size_type n, T const& value, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		this->resize(n, value);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr
	deque(InputIterator first, InputIterator last, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		this->ConstructIter(first, last);
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	constexpr
	deque(hamon::from_range_t, R&& rg, Allocator const& a = Allocator())
		: m_allocator(a)
	{
		this->ConstructIter(hamon::ranges::begin(rg), hamon::ranges::end(rg));
	}

	HAMON_CXX11_CONSTEXPR
	deque(deque const& x)
		: deque(x, AllocTraits::select_on_container_copy_construction(x.m_allocator))
	{}

	HAMON_CXX11_CONSTEXPR
	deque(deque&& x)
		: m_allocator(hamon::move(x.m_allocator))
		, m_impl(hamon::move(x.m_impl))
	{}

	constexpr
	deque(deque const& x, type_identity_t<Allocator> const& a)
		: m_allocator(a)
	{
		this->ConstructIter(hamon::ranges::begin(x), hamon::ranges::end(x));
	}

	constexpr
	deque(deque&& x, type_identity_t<Allocator> const& a)
		: m_allocator(a)
	{
		// TODO
		(void)x;

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

		// TODO

		return *this;
	}

	HAMON_CXX14_CONSTEXPR deque& operator=(deque&& x)
		noexcept(AllocTraits::is_always_equal::value)
	{
		if (hamon::addressof(x) == this)
		{
			return *this;
		}

		// TODO

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
		// TODO
		(void)first;
		(void)last;
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void assign_range(R&& rg)
	{
		// TODO
		(void)rg;
	}

	HAMON_CXX14_CONSTEXPR void assign(size_type n, T const& t)
	{
		// TODO
		(void)n;
		(void)t;
	}

	HAMON_CXX14_CONSTEXPR void assign(std::initializer_list<T> il)
	{
		this->assign(il.begin(), il.end());
	}

	HAMON_CXX11_CONSTEXPR allocator_type get_allocator() const noexcept
	{
		return m_allocator;
	}

	// iterators
	HAMON_CXX14_CONSTEXPR iterator begin() noexcept
	{
		return iterator(this, 0);
	}

	HAMON_CXX11_CONSTEXPR const_iterator begin() const noexcept
	{
		return const_iterator(this, 0);
	}

	HAMON_CXX14_CONSTEXPR iterator end() noexcept
	{
		return iterator(this, this->size());
	}

	HAMON_CXX11_CONSTEXPR const_iterator end() const noexcept
	{
		return const_iterator(this, this->size());
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator rbegin() noexcept
	{
		return reverse_iterator(this->end());
	}

	HAMON_CXX11_CONSTEXPR const_reverse_iterator rbegin() const noexcept
	{
		return const_reverse_iterator(this->end());
	}

	HAMON_CXX14_CONSTEXPR reverse_iterator rend() noexcept
	{
		return reverse_iterator(this->begin());
	}

	HAMON_CXX11_CONSTEXPR const_reverse_iterator rend() const noexcept
	{
		return const_reverse_iterator(this->begin());
	}

	HAMON_CXX11_CONSTEXPR const_iterator cbegin() const noexcept
	{
		return this->begin();
	}

	HAMON_CXX11_CONSTEXPR const_iterator cend() const noexcept
	{
		return this->end();
	}

	HAMON_CXX11_CONSTEXPR const_reverse_iterator crbegin() const noexcept
	{
		return this->rbegin();
	}

	HAMON_CXX11_CONSTEXPR const_reverse_iterator crend() const noexcept
	{
		return this->rend();
	}

	// [deque.capacity], capacity
	[[nodiscard]] HAMON_CXX11_CONSTEXPR bool empty() const noexcept
	{
		return this->size() == 0;
	}

	HAMON_CXX11_CONSTEXPR size_type size() const noexcept
	{
		return m_impl.Size();
	}

	HAMON_CXX11_CONSTEXPR size_type max_size() const noexcept;

	HAMON_CXX14_CONSTEXPR void resize(size_type sz)
	{
		while (this->size() > sz)
		{
			this->pop_back();
		}

		while (this->size() < sz)
		{
			this->EmplaceBack();
		}
	}

	HAMON_CXX14_CONSTEXPR void resize(size_type sz, T const& c)
	{
		while (this->size() > sz)
		{
			this->pop_back();
		}

		while (this->size() < sz)
		{
			this->EmplaceBack(c);
		}
	}

	HAMON_CXX14_CONSTEXPR void shrink_to_fit()
	{
		// TODO
	}

	// element access
	HAMON_CXX14_CONSTEXPR reference operator[](size_type n)
	{
		return HAMON_ASSERT(n < this->size()), m_impl[n];
	}

	HAMON_CXX11_CONSTEXPR const_reference operator[](size_type n) const
	{
		return HAMON_ASSERT(n < this->size()), m_impl[n];
	}

	HAMON_CXX14_CONSTEXPR reference at(size_type n)
	{
		return
			n < this->size() ?
			m_impl[n] :
			(hamon::detail::throw_out_of_range("deque::at"), m_impl[n]);
	}

	HAMON_CXX11_CONSTEXPR const_reference at(size_type n) const
	{
		return
			n < this->size() ?
			m_impl[n] :
			(hamon::detail::throw_out_of_range("deque::at"), m_impl[n]);
	}

	HAMON_CXX14_CONSTEXPR reference front()
	{
		return HAMON_ASSERT(!this->empty()), m_impl[0];
	}

	HAMON_CXX11_CONSTEXPR const_reference front() const
	{
		return HAMON_ASSERT(!this->empty()), m_impl[0];
	}

	HAMON_CXX14_CONSTEXPR reference back()
	{
		return HAMON_ASSERT(!this->empty()), m_impl[this->size() - 1];
	}

	HAMON_CXX11_CONSTEXPR const_reference back() const
	{
		return HAMON_ASSERT(!this->empty()), m_impl[this->size() - 1];
	}

	// [deque.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR reference emplace_front(Args&&... args);

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR reference emplace_back(Args&&... args)
	{
		this->EmplaceBack(hamon::forward<Args>(args)...);
		return this->back();
	}

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator emplace(const_iterator position, Args&&... args);

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
		this->EmplaceBack(x);
	}

	HAMON_CXX14_CONSTEXPR void push_back(T&& x)
	{
		this->EmplaceBack(hamon::move(x));
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

	HAMON_CXX14_CONSTEXPR iterator insert(const_iterator position, size_type n, T const& x);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR iterator insert(const_iterator position, InputIterator first, InputIterator last);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR iterator insert_range(const_iterator position, R&& rg);

	HAMON_CXX14_CONSTEXPR iterator insert(const_iterator position, std::initializer_list<T> il)
	{
		return this->insert(position, il.begin(), il.end());
	}

	HAMON_CXX14_CONSTEXPR void pop_front();

	HAMON_CXX14_CONSTEXPR void pop_back()
	{
		m_impl.PopBack(m_allocator);
	}

	HAMON_CXX14_CONSTEXPR iterator erase(const_iterator position)
	{
		return this->erase(position, position + 1);
	}

	HAMON_CXX14_CONSTEXPR iterator erase(const_iterator first, const_iterator last);

	HAMON_CXX14_CONSTEXPR void swap(deque&)
		noexcept(AllocTraits::is_always_equal::value);

	HAMON_CXX14_CONSTEXPR void clear() noexcept
	{
		m_impl.Clear(m_allocator);
	}
};

HAMON_WARNING_POP()

namespace detail
{

// [sequences.general]/2
template <typename InputIterator>
using iter_value_type = typename hamon::iterator_traits<InputIterator>::value_type;  // exposition only

}	// namespace detail

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	typename Allocator = std::allocator<hamon::detail::iter_value_type<InputIterator>>>
deque(InputIterator, InputIterator, Allocator = Allocator())
->deque<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	typename Allocator = std::allocator<hamon::ranges::range_value_t<R>>>
deque(from_range_t, R&&, Allocator = Allocator())
->deque<hamon::ranges::range_value_t<R>, Allocator>;

#endif

template <typename T, typename Allocator>
HAMON_CXX11_CONSTEXPR bool
operator==(deque<T, Allocator> const& x, deque<T, Allocator> const& y)
{
	return x.size() == y.size() &&
		hamon::equal(x.begin(), x.end(), y.begin());
}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T, typename Allocator>
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
HAMON_CXX11_CONSTEXPR bool
operator!=(deque<T, Allocator> const& x, deque<T, Allocator> const& y)
{
	return !(x == y);
}

template <typename T, typename Allocator>
HAMON_CXX11_CONSTEXPR bool
operator<(deque<T, Allocator> const& x, deque<T, Allocator> const& y)
{
	return hamon::lexicographical_compare(
		x.begin(), x.end(),
		y.begin(), y.end());
}

template <typename T, typename Allocator>
HAMON_CXX11_CONSTEXPR bool
operator>(deque<T, Allocator> const& x, deque<T, Allocator> const& y)
{
	return y < x;
}

template <typename T, typename Allocator>
HAMON_CXX11_CONSTEXPR bool
operator<=(deque<T, Allocator> const& x, deque<T, Allocator> const& y)
{
	return !(x > y);
}

template <typename T, typename Allocator>
HAMON_CXX11_CONSTEXPR bool
operator>=(deque<T, Allocator> const& x, deque<T, Allocator> const& y)
{
	return !(x < y);
}

#endif

template <typename T, typename Allocator>
HAMON_CXX14_CONSTEXPR void
swap(deque<T, Allocator>& x, deque<T, Allocator>& y)
noexcept(noexcept(x.swap(y)))
{
	x.swap(y);
}

}	// namespace hamon

#endif

#endif // HAMON_DEQUE_DEQUE_HPP
