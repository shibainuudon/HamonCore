/**
 *	@file	hive.hpp
 *
 *	@brief	hive の定義
 */

#ifndef HAMON_HIVE_HIVE_HPP
#define HAMON_HIVE_HIVE_HPP

#include <hamon/hive/hive_fwd.hpp>
#include <hamon/hive/config.hpp>

#if !defined(HAMON_USE_STD_HIVE)

#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/container/detail/container_compatible_range.hpp>
#include <hamon/container/detail/iter_value_type.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/functional/equal_to.hpp>
#include <hamon/functional/less.hpp>
#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/reverse_iterator.hpp>
#include <hamon/memory/allocator_traits.hpp>
#include <hamon/memory/detail/simple_allocator.hpp>
#include <hamon/memory_resource/polymorphic_allocator.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/from_range_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/config.hpp>
#include <initializer_list>

namespace hamon
{

struct hive_limits
{
	hamon::size_t min;
	hamon::size_t max;

	HAMON_CXX11_CONSTEXPR
	hive_limits(hamon::size_t minimum, hamon::size_t maximum) noexcept
		: min(minimum), max(maximum) {}
};

namespace detail
{
template <bool Const>
struct hive_iterator;
}

// 23.3.9 Class template hive[hive]

template <typename T, typename Allocator>
class hive
{
public:
	// types
	using value_type             = T;
	using allocator_type         = Allocator;
	using pointer                = typename hamon::allocator_traits<Allocator>::pointer;
	using const_pointer          = typename hamon::allocator_traits<Allocator>::const_pointer;
	using reference              = value_type&;
	using const_reference        = value_type const&;
	using size_type              = typename hamon::allocator_traits<Allocator>::size_type;
	using difference_type        = typename hamon::allocator_traits<Allocator>::difference_type;
	using iterator               = hamon::detail::hive_iterator<false>;
	using const_iterator         = hamon::detail::hive_iterator<true>;
	using reverse_iterator       = hamon::reverse_iterator<iterator>;
	using const_reverse_iterator = hamon::reverse_iterator<const_iterator>;

	// [hive.cons], construct/copy/destroy
	constexpr
	hive() noexcept(noexcept(Allocator()))
		: hive(Allocator())
	{}

	constexpr explicit
	hive(Allocator const&) noexcept;

	constexpr explicit
	hive(hamon::hive_limits block_limits)
		: hive(block_limits, Allocator())
	{}

	constexpr
	hive(hamon::hive_limits block_limits, Allocator const&);

	constexpr explicit
	hive(size_type n, Allocator const& = Allocator());

	constexpr
	hive(size_type n, hamon::hive_limits block_limits, Allocator const& = Allocator());

	constexpr
	hive(size_type n, T const& value, Allocator const& = Allocator());

	constexpr
	hive(size_type n, T const& value, hamon::hive_limits block_limits, Allocator const& = Allocator());

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr
	hive(InputIterator first, InputIterator last, Allocator const& = Allocator());

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	constexpr
	hive(InputIterator first, InputIterator last, hamon::hive_limits block_limits, Allocator const& = Allocator());

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	constexpr
	hive(hamon::from_range_t, R&& rg, Allocator const& = Allocator());

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	constexpr
	hive(hamon::from_range_t, R&& rg, hamon::hive_limits block_limits, Allocator const& = Allocator());

	constexpr
	hive(hive const& x);

	constexpr
	hive(hive&&) noexcept;

	constexpr
	hive(hive const& x, hamon::type_identity_t<Allocator> const& alloc);

	constexpr
	hive(hive&&, hamon::type_identity_t<Allocator> const& alloc);

	constexpr
	hive(std::initializer_list<T> il, Allocator const& = Allocator());

	constexpr
	hive(std::initializer_list<T> il, hamon::hive_limits block_limits, Allocator const& = Allocator());

	HAMON_CXX20_CONSTEXPR
	~hive();

	HAMON_CXX14_CONSTEXPR hive&
	operator=(hive const& x);

	HAMON_CXX14_CONSTEXPR hive&
	operator=(hive&& x) ;// TODO noexcept(see below);

	HAMON_CXX14_CONSTEXPR hive&
	operator=(std::initializer_list<T>);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	assign(InputIterator first, InputIterator last);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	assign_range(R&& rg);

	HAMON_CXX14_CONSTEXPR void
	assign(size_type n, T const& t);

	HAMON_CXX14_CONSTEXPR void
	assign(std::initializer_list<T>);

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR allocator_type
	get_allocator() const noexcept;

	// iterators
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	begin() noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	begin() const noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	end() noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	end() const noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reverse_iterator
	rbegin() noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator
	rbegin() const noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR reverse_iterator
	rend() noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator
	rend() const noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	cbegin() const noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	cend() const noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator
	crbegin() const noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_reverse_iterator
	crend() const noexcept;

	// [hive.capacity], capacity
	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR bool
	empty() const noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	size() const noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	max_size() const noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR size_type
	capacity() const noexcept;

	HAMON_CXX14_CONSTEXPR void
	reserve(size_type n);

	HAMON_CXX14_CONSTEXPR void
	shrink_to_fit();

	HAMON_CXX14_CONSTEXPR void
	trim_capacity() noexcept;

	HAMON_CXX14_CONSTEXPR void
	trim_capacity(size_type n) noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR hamon::hive_limits
	block_capacity_limits() const noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	static HAMON_CXX11_CONSTEXPR hamon::hive_limits
	block_capacity_default_limits() noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	static HAMON_CXX11_CONSTEXPR hamon::hive_limits
	block_capacity_hard_limits() noexcept;

	HAMON_CXX14_CONSTEXPR void
	reshape(hamon::hive_limits block_limits);

	// [hive.modifiers], modifiers
	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace(Args&&... args);

	template <typename... Args>
	HAMON_CXX14_CONSTEXPR iterator
	emplace_hint(const_iterator hint, Args&&... args);

	HAMON_CXX14_CONSTEXPR iterator
	insert(T const& x);

	HAMON_CXX14_CONSTEXPR iterator
	insert(T&& x);

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, T const& x);

	HAMON_CXX14_CONSTEXPR iterator
	insert(const_iterator hint, T&& x);

	HAMON_CXX14_CONSTEXPR void
	insert(std::initializer_list<T> il);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::container_compatible_range, T, R)>
	HAMON_CXX14_CONSTEXPR void
	insert_range(R&& rg);

	template <HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator)>
	HAMON_CXX14_CONSTEXPR void
	insert(InputIterator first, InputIterator last);

	HAMON_CXX14_CONSTEXPR void
	insert(size_type n, T const& x);

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator position);

	HAMON_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last);

	HAMON_CXX14_CONSTEXPR void
	swap(hive&) ;// TODO noexcept(see below);

	HAMON_CXX14_CONSTEXPR void
	clear() noexcept;

	// [hive.operations], hive operations
	HAMON_CXX14_CONSTEXPR void
	splice(hive& x);

	HAMON_CXX14_CONSTEXPR void
	splice(hive&& x);

	template <typename BinaryPredicate = hamon::equal_to<T>>
	HAMON_CXX14_CONSTEXPR size_type
	unique(BinaryPredicate binary_pred = BinaryPredicate());

	template <typename Compare = hamon::less<T>>
	HAMON_CXX14_CONSTEXPR void
	sort(Compare comp = Compare());

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX14_CONSTEXPR iterator
	get_iterator(const_pointer p) noexcept;

	HAMON_NODISCARD	// nodiscard as an extension
	HAMON_CXX11_CONSTEXPR const_iterator
	get_iterator(const_pointer p) const noexcept;

private:
//	hamon::hive_limits current-limits = implementation-defined;     // exposition only
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator, hamon::allocator<hamon::detail::iter_value_type<InputIterator>>)>
hive(InputIterator, InputIterator, Allocator = Allocator())
->hive<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::detail::cpp17_input_iterator, InputIterator),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator, hamon::allocator<hamon::detail::iter_value_type<InputIterator>>)>
hive(InputIterator, InputIterator, hamon::hive_limits, Allocator = Allocator())
->hive<hamon::detail::iter_value_type<InputIterator>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator, hamon::allocator<ranges::range_value_t<R>>)>
hive(hamon::from_range_t, R&&, Allocator = Allocator())
->hive<ranges::range_value_t<R>, Allocator>;

template <
	HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, R),
	HAMON_CONSTRAINED_PARAM_D(hamon::detail::simple_allocator, Allocator, hamon::allocator<ranges::range_value_t<R>>)>
hive(hamon::from_range_t, R&&, hamon::hive_limits, Allocator = Allocator())
->hive<ranges::range_value_t<R>, Allocator>;

#endif

template <typename T, typename Allocator>
HAMON_CXX14_CONSTEXPR void
swap(hive<T, Allocator>& x, hive<T, Allocator>& y)
noexcept(noexcept(x.swap(y)));

template <typename T, typename Allocator, typename U = T>
HAMON_CXX14_CONSTEXPR
typename hive<T, Allocator>::size_type
erase(hive<T, Allocator>& c, U const& value);

template <typename T, typename Allocator, typename Predicate>
HAMON_CXX14_CONSTEXPR
typename hive<T, Allocator>::size_type
erase_if(hive<T, Allocator>& c, Predicate pred);

namespace pmr
{

template <typename T>
using hive = hamon::hive<T, hamon::pmr::polymorphic_allocator<T>>;

}	// namespace pmr

}	// namespace hamon

#endif

#endif // HAMON_HIVE_HIVE_HPP
