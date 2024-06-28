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

#include <hamon/compare/detail/synth_three_way.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/detail/container_compatible_range.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/negation.hpp>
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


// 24.3.8 Class template deque[deque]

template <typename T, typename Allocator = std::allocator<T>>
class deque
{
private:
	using AllocTraits = std::allocator_traits<Allocator>;

	template <typename U, typename Const>
	struct Iterator
	{
		friend Iterator<U, hamon::negation<Const>>;
		friend class deque;

		using iterator_concept  = hamon::random_access_iterator_tag;
		using iterator_category = hamon::random_access_iterator_tag;
		using value_type        = U;
		using difference_type   = typename AllocTraits::difference_type;
		using pointer           = hamon::conditional_t<Const::value, U const*, U*>;
		using reference         = hamon::conditional_t<Const::value, U const&, U&>;

		HAMON_CXX11_CONSTEXPR
		Iterator() HAMON_NOEXCEPT
			: m_offset()
		{}

	private:
		HAMON_CXX11_CONSTEXPR
		Iterator(difference_type offset) HAMON_NOEXCEPT
			: m_offset(offset)
		{}

	public:
		template <typename C,
			typename = hamon::enable_if_t<C::value == Const::value || Const::value>>
		HAMON_CXX11_CONSTEXPR
		Iterator(Iterator<U, C> const& i) HAMON_NOEXCEPT
			: m_offset(i.m_offset)
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
		reference operator*() const HAMON_NOEXCEPT;

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
			return Iterator(i.m_offset + n);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR Iterator
		operator+(difference_type n, Iterator const& i) HAMON_NOEXCEPT
		{
			return Iterator(i.m_offset + n);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR Iterator
		operator-(Iterator const& i, difference_type n) HAMON_NOEXCEPT
		{
			return Iterator(i.m_offset - n);
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

	// [deque.cons], construct/copy/destroy
	deque() : deque(Allocator()) {}

	explicit deque(Allocator const&);

	explicit deque(size_type n, Allocator const& = Allocator());

	deque(size_type n, T const& value, Allocator const& = Allocator());

	template <typename InputIterator>
	deque(InputIterator first, InputIterator last, Allocator const& = Allocator());

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	deque(hamon::from_range_t, R&& rg, Allocator const& = Allocator());

	deque(deque const& x);

	deque(deque&&);

	deque(deque const&, type_identity_t<Allocator> const&);

	deque(deque&&, type_identity_t<Allocator> const&);

	deque(std::initializer_list<T>, Allocator const& = Allocator());

	~deque();

	deque& operator=(deque const& x);

	deque& operator=(deque&& x)
		noexcept(AllocTraits::is_always_equal::value);

	deque& operator=(std::initializer_list<T>);

	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	void assign_range(R&& rg);

	void assign(size_type n, T const& t);

	void assign(std::initializer_list<T>);

	allocator_type get_allocator() const noexcept;

	// iterators
	iterator begin() noexcept;

	const_iterator begin() const noexcept;

	iterator end() noexcept;

	const_iterator end() const noexcept;

	reverse_iterator rbegin() noexcept;

	const_reverse_iterator rbegin() const noexcept;

	reverse_iterator rend() noexcept;

	const_reverse_iterator rend() const noexcept;

	const_iterator cbegin() const noexcept;

	const_iterator cend() const noexcept;

	const_reverse_iterator crbegin() const noexcept;

	const_reverse_iterator crend() const noexcept;

	// [deque.capacity], capacity
	[[nodiscard]] bool empty() const noexcept;

	size_type size() const noexcept;

	size_type max_size() const noexcept;

	void resize(size_type sz);

	void resize(size_type sz, T const& c);

	void shrink_to_fit();

	// element access
	reference operator[](size_type n);

	const_reference operator[](size_type n) const;

	reference at(size_type n);

	const_reference at(size_type n) const;

	reference front();

	const_reference front() const;

	reference back();

	const_reference back() const;

	// [deque.modifiers], modifiers
	template <typename... Args>
	reference emplace_front(Args&&... args);

	template <typename... Args>
	reference emplace_back(Args&&... args);

	template <typename... Args>
	iterator emplace(const_iterator position, Args&&... args);

	void push_front(T const& x);

	void push_front(T&& x);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	void prepend_range(R&& rg);

	void push_back(T const& x);

	void push_back(T&& x);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	void append_range(R&& rg);

	iterator insert(const_iterator position, T const& x);

	iterator insert(const_iterator position, T&& x);

	iterator insert(const_iterator position, size_type n, T const& x);

	template <typename InputIterator>
	iterator insert(const_iterator position, InputIterator first, InputIterator last);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	iterator insert_range(const_iterator position, R&& rg);

	iterator insert(const_iterator position, std::initializer_list<T>);

	void pop_front();

	void pop_back();

	iterator erase(const_iterator position);

	iterator erase(const_iterator first, const_iterator last);

	void swap(deque&)
		noexcept(AllocTraits::is_always_equal::value);

	void clear() noexcept;
};

namespace detail
{

// [sequences.general]/2
template <typename InputIterator>
using iter_value_type = typename hamon::iterator_traits<InputIterator>::value_type;  // exposition only

}	// namespace detail

template <typename InputIterator, typename Allocator = std::allocator<hamon::detail::iter_value_type<InputIterator>>>
deque(InputIterator, InputIterator, Allocator = Allocator())
->deque<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <hamon::ranges::input_range R, typename Allocator = std::allocator<hamon::ranges::range_value_t<R>>>
deque(from_range_t, R&&, Allocator = Allocator())
->deque<hamon::ranges::range_value_t<R>, Allocator>;

template <typename T, typename Allocator>
bool operator==(deque<T, Allocator> const& x, deque<T, Allocator> const& y);

template <typename T, typename Allocator>
hamon::detail::synth_three_way_result<T>
operator<=>(deque<T, Allocator> const&x, deque<T, Allocator> const&y);

template <typename T, typename Allocator>
void swap(deque<T, Allocator>& x, deque<T, Allocator>& y)
noexcept(noexcept(x.swap(y)));

}	// namespace hamon

#endif

#endif // HAMON_DEQUE_DEQUE_HPP
