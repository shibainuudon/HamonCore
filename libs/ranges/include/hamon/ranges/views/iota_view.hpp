/**
 *	@file	iota_view.hpp
 *
 *	@brief	iota_view の定義
 */

#ifndef HAMON_RANGES_VIEWS_IOTA_VIEW_HPP
#define HAMON_RANGES_VIEWS_IOTA_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::iota_view;

namespace views {

using std::ranges::views::iota;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/views/view_interface.hpp>
#include <hamon/ranges/detail/to_unsigned_like.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/totally_ordered.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/semiregular.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/weakly_equality_comparable_with.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/incrementable.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/detail/is_integer_like.hpp>
#include <hamon/iterator/detail/is_signed_integer_like.hpp>
#include <hamon/iterator/unreachable_sentinel.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>

#include <hamon/concepts/signed_integral.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon {
namespace ranges {

namespace detail {

// [range.iota.view]/1
template <typename W>
using iota_diff_t =
	hamon::conditional_t<!hamon::is_integral<W>::value,
		hamon::iter_difference_t<W>,	// [range.iota.view]/1.1
	hamon::conditional_t<(sizeof(hamon::iter_difference_t<W>) > sizeof(W)),
		hamon::iter_difference_t<W>,	// [range.iota.view]/1.1
	hamon::conditional_t<(sizeof(hamon::ptrdiff_t) > sizeof(W)),
		hamon::ptrdiff_t,				// [range.iota.view]/1.2, 1,3	// TODO
		long long
	>>>;

#if defined(HAMON_HAS_CXX20_CONCEPTS)

// [range.iota.view]/2
template <typename I>
concept decrementable =
	hamon::incrementable<I> &&
	requires(I i)
	{
		{ --i } -> hamon::same_as<I&>;
		{ i-- } -> hamon::same_as<I>;
	};

template <typename I>
using decrementable_t = hamon::bool_constant<decrementable<I>>;

#else

template <typename I>
struct decrementable_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<hamon::incrementable_t<I2>::value>,
		typename R1 = decltype(--hamon::declval<I2&>()),
		typename R2 = decltype(hamon::declval<I2&>()--)
	>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as_t<R1, I2&>,
		hamon::same_as_t<R2, I2>
	>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

template <typename I>
using decrementable =
	typename decrementable_impl<I>::type;

template <typename I>
using decrementable_t = decrementable<I>;

#endif

#if defined(HAMON_HAS_CXX20_CONCEPTS)

// [range.iota.view]/5
template <typename I>
concept advanceable =
	detail::decrementable<I> &&
	hamon::totally_ordered<I> &&
	requires(I i, I const j, detail::iota_diff_t<I> const n)
	{
		{ i += n } -> hamon::same_as<I&>;
		{ i -= n } -> hamon::same_as<I&>;
		I(j + n);
		I(n + j);
		I(j - n);
		{ j - j } -> hamon::convertible_to<detail::iota_diff_t<I>>;
	};

template <typename I>
using advanceable_t = hamon::bool_constant<advanceable<I>>;

#else

template <typename I>
struct advanceable_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<detail::decrementable_t<I2>::value>,
		typename = hamon::enable_if_t<hamon::totally_ordered_t<I2>::value>,
		typename D = detail::iota_diff_t<I2>,
		typename R1 = decltype(hamon::declval<I2&>() += hamon::declval<D>()),
		typename R2 = decltype(hamon::declval<I2&>() -= hamon::declval<D>()),
		typename = decltype(I2(hamon::declval<I2 const>() + hamon::declval<D>())),
		typename = decltype(I2(hamon::declval<D>() + hamon::declval<I2 const>())),
		typename = decltype(I2(hamon::declval<I2 const>() - hamon::declval<D>())),
		typename R3 = decltype(hamon::declval<I2 const>() - hamon::declval<I2 const>())
	>
	static auto test(int) -> hamon::conjunction<
		hamon::same_as_t<R1, I2&>,
		hamon::same_as_t<R2, I2&>,
		hamon::convertible_to_t<R3, D>
	>;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<I>(0));
};

template <typename I>
using advanceable =
	typename advanceable_impl<I>::type;

template <typename I>
using advanceable_t = advanceable<I>;

#endif

template <typename W, typename = void>
struct iota_view_iterator_category
{
};

template <typename W>
struct iota_view_iterator_category<W,
	hamon::enable_if_t<
		hamon::incrementable_t<W>::value &&
		hamon::integral_t<detail::iota_diff_t<W>>::value
	>>
{
	// present only if W models incrementable and
	// IOTA-DIFF-T(W) is an integral type
	using iterator_category = hamon::input_iterator_tag;
};

}	// namespace detail

// 26.6.4.2 Class template iota_view	[range.iota.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::weakly_incrementable W, hamon::semiregular Bound = hamon::unreachable_sentinel_t>
	requires hamon::detail::weakly_equality_comparable_with<W, Bound> && hamon::copyable<W>
#else
template <
	typename W, typename Bound = hamon::unreachable_sentinel_t,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::weakly_incrementable<W>,
		hamon::semiregular<Bound>,
		hamon::detail::weakly_equality_comparable_with<W, Bound>,
		hamon::copyable<W>
	>::value>
>
#endif
class iota_view : public ranges::view_interface<iota_view<W, Bound>>
{
private:
	struct sentinel;

	// [range.iota.iterator], class iota_view​::​iterator
	struct iterator : detail::iota_view_iterator_category<W>
	{
#if defined(HAMON_MSVC) || \
	defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000)
		// MSVCとGCC(12まで)は、friend指定してもエラーになってしまうので、
		// 仕方なくpublicにする。
	public:
#else
	private:
		friend iota_view;
		friend sentinel;
#endif
		W m_value = W();

	public:
		// [range.iota.iterator]/1
		using iterator_concept =
			hamon::conditional_t<detail::advanceable_t<W>::value,
				hamon::random_access_iterator_tag,	// [range.iota.iterator]/1.1
			hamon::conditional_t<detail::decrementable_t<W>::value,
				hamon::bidirectional_iterator_tag,	// [range.iota.iterator]/1.2
			hamon::conditional_t<hamon::incrementable_t<W>::value,
				hamon::forward_iterator_tag,		// [range.iota.iterator]/1.3
			    hamon::input_iterator_tag			// [range.iota.iterator]/1.4
			>>>;

		// using iterator_category = hamon::input_iterator_tag;	// defined in iota_view_iterator_category
		using value_type = W;
		using difference_type = detail::iota_diff_t<W>;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
		iterator() requires hamon::default_initializable<W> = default;
#else
		template <HAMON_CONSTRAINED_PARAM_D(default_initializable, W2, W)>
		HAMON_CXX11_CONSTEXPR
		iterator()
			HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<W>::value)
		{}
#endif

		HAMON_CXX11_CONSTEXPR explicit
		iterator(W value)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_move_constructible<W>::value)
			// [range.iota.iterator]/3
			: m_value(hamon::move(value))
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR W	// nodiscard as an extension
		operator*() const
			HAMON_NOEXCEPT_IF(hamon::is_nothrow_copy_constructible<W>::value)
		{
			// [range.iota.iterator]/4
			return m_value;
		}

		HAMON_CXX14_CONSTEXPR iterator&
		operator++()
			HAMON_NOEXCEPT_IF_EXPR(++m_value)	// noexcept as an extension
		{
			// [range.iota.iterator]/6
			++m_value;
			return *this;
		}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
		HAMON_CXX14_CONSTEXPR void
		operator++(int)
			HAMON_NOEXCEPT_IF_EXPR(++m_value)	// noexcept as an extension
		{
			// [range.iota.iterator]/7
			++*this;
		}

		HAMON_CXX14_CONSTEXPR iterator
		operator++(int)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_copy_constructible<iterator>::value &&
				HAMON_NOEXCEPT_EXPR(++m_value))
			requires hamon::incrementable<W>
		{
			// [range.iota.iterator]/8
			auto tmp = *this;
			++*this;
			return tmp;
		}
#else
	private:
		template <HAMON_CONSTRAINED_PARAM_D(hamon::incrementable, W2, W)>
		HAMON_CXX14_CONSTEXPR iterator
		increment_impl(hamon::detail::overload_priority<1>)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_copy_constructible</*iterator*/W2>::value &&
				HAMON_NOEXCEPT_EXPR(++m_value))
		{
			auto tmp = *this;
			++*this;
			return tmp;
		}

		HAMON_CXX14_CONSTEXPR void
		increment_impl(hamon::detail::overload_priority<0>)
			HAMON_NOEXCEPT_IF_EXPR(++m_value)	// noexcept as an extension
		{
			++*this;
		}

	public:
		HAMON_CXX14_CONSTEXPR auto
		operator++(int) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			increment_impl(hamon::detail::overload_priority<1>{}))
		->decltype(increment_impl(hamon::detail::overload_priority<1>{}))
		{
			return increment_impl(hamon::detail::overload_priority<1>{});
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(detail::decrementable, W2, W)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator--()
			HAMON_NOEXCEPT_IF_EXPR(--m_value)	// noexcept as an extension
			//requires detail::decrementable<W>
		{
			// [range.iota.iterator]/9
			--m_value;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(detail::decrementable, W2, W)>
		HAMON_CXX14_CONSTEXPR iterator
		operator--(int)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_copy_constructible<iterator>::value &&
				HAMON_NOEXCEPT_EXPR(--m_value))
			//requires detail::decrementable<W>
		{
			// [range.iota.iterator]/10
			auto tmp = *this;
			--*this;
			return tmp;
		}

	private:
		// [range.iota.iterator]/11
		template <typename W2,
			typename = hamon::enable_if_t<
				hamon::detail::is_integer_like_t<W2>::value &&
				!hamon::detail::is_signed_integer_like_t<W2>::value>>
		static HAMON_CXX14_CONSTEXPR void
		advance_forward(W2& value, difference_type n, hamon::detail::overload_priority<1>)
			HAMON_NOEXCEPT_IF(
				HAMON_NOEXCEPT_EXPR(value += static_cast<W2>(n)) &&
				HAMON_NOEXCEPT_EXPR(value -= static_cast<W2>(-n)))
		{
			if (n >= difference_type(0))
			{
				value += static_cast<W2>(n);
			}
			else
			{
				value -= static_cast<W2>(-n);
			}
		}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
HAMON_WARNING_DISABLE_GCC("-Wconversion")
		template <typename W2>
		static HAMON_CXX14_CONSTEXPR void
		advance_forward(W2& value, difference_type n, hamon::detail::overload_priority<0>)
			HAMON_NOEXCEPT_IF_EXPR(value += n)
		{
			value += n;
		}
HAMON_WARNING_POP()

		// [range.iota.iterator]/12
		template <typename W2,
			typename = hamon::enable_if_t<
				hamon::detail::is_integer_like_t<W2>::value &&
				!hamon::detail::is_signed_integer_like_t<W2>::value>>
		static HAMON_CXX14_CONSTEXPR void
		advance_backward(W2& value, difference_type n, hamon::detail::overload_priority<1>)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(value -= static_cast<W2>(n)) &&
				HAMON_NOEXCEPT_EXPR(value += static_cast<W2>(-n)))
		{
			if (n >= difference_type(0))
			{
				value -= static_cast<W2>(n);
			}
			else
			{
				value += static_cast<W2>(-n);
			}
		}

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
HAMON_WARNING_DISABLE_GCC("-Wconversion")
		template <typename W2>
		static HAMON_CXX14_CONSTEXPR void
		advance_backward(W2& value, difference_type n, hamon::detail::overload_priority<0>)
			HAMON_NOEXCEPT_IF_EXPR(value -= n)
		{
			value -= n;
		}
HAMON_WARNING_POP()

	public:
		template <HAMON_CONSTRAINED_PARAM_D(detail::advanceable, W2, W)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator+=(difference_type n)
			HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
				advance_forward(m_value, n, hamon::detail::overload_priority<1>{}))
			//requires detail::advanceable<W>
		{
			advance_forward(m_value, n, hamon::detail::overload_priority<1>{});
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(detail::advanceable, W2, W)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator-=(difference_type n)
			HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
				advance_backward(m_value, n, hamon::detail::overload_priority<1>{}))
			//requires detail::advanceable<W>
		{
			advance_backward(m_value, n, hamon::detail::overload_priority<1>{});
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(detail::advanceable, W2, W)>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR W	// nodiscard as an extension
		operator[](difference_type n) const
			HAMON_NOEXCEPT_IF_EXPR(W(m_value + n))	// noexcept as an extension
			//requires detail::advanceable<W>
		{
			// [range.iota.iterator]/13
			return W(m_value + n);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::equality_comparable, W2, W)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_value == y.m_value)	// noexcept as an extension
			//requires hamon::equality_comparable<W>
		{
			// [range.iota.iterator]/14
			return x.m_value == y.m_value;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <HAMON_CONSTRAINED_PARAM_D(hamon::equality_comparable, W2, W)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::totally_ordered, W2, W)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator<(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_value < y.m_value)	// noexcept as an extension
			//requires hamon::totally_ordered<W>
		{
			// [range.iota.iterator]/15
			return x.m_value < y.m_value;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::totally_ordered, W2, W)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(y < x)	// noexcept as an extension
			//requires hamon::totally_ordered<W>
		{
			// [range.iota.iterator]/16
			return y < x;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::totally_ordered, W2, W)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator<=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(y < x))	// noexcept as an extension
			//requires hamon::totally_ordered<W>
		{
			// [range.iota.iterator]/17
			return !(y < x);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::totally_ordered, W2, W)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator>=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x < y))	// noexcept as an extension
			//requires hamon::totally_ordered<W>
		{
			// [range.iota.iterator]/18
			return !(x < y);
		}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
		operator<=>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_value <=> y.m_value)	// noexcept as an extension
			requires hamon::totally_ordered<W> && hamon::three_way_comparable<W>
		{
			// [range.iota.iterator]/19
			return x.m_value <=> y.m_value;
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(detail::advanceable, W2, W)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR iterator	// nodiscard as an extension
		operator+(iterator i, difference_type n)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_move_constructible<iterator>::value &&
				HAMON_NOEXCEPT_EXPR(i += n))
			//requires detail::advanceable<W>
		{
			// [range.iota.iterator]/20
			i += n;
			return i;
		}

		template <HAMON_CONSTRAINED_PARAM_D(detail::advanceable, W2, W)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR iterator	// nodiscard as an extension
		operator+(difference_type n, iterator i)
			HAMON_NOEXCEPT_IF_EXPR(i + n)	// noexcept as an extension
			//requires detail::advanceable<W>
		{
			// [range.iota.iterator]/21
			return i + n;
		}

		template <HAMON_CONSTRAINED_PARAM_D(detail::advanceable, W2, W)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR iterator	// nodiscard as an extension
		operator-(iterator i, difference_type n)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_move_constructible<iterator>::value &&
				HAMON_NOEXCEPT_EXPR(i -= n))
			//requires detail::advanceable<W>
		{
			// [range.iota.iterator]/22
			i -= n;
			return i;
		}

	private:
		// [range.iota.iterator]/23
		template <typename W2 = W,
			typename = hamon::enable_if_t<
				hamon::detail::is_integer_like_t<W2>::value &&
				hamon::detail::is_signed_integer_like_t<W2>::value>>
		friend HAMON_CXX11_CONSTEXPR difference_type
		subtract(iterator const& x, iterator const& y, hamon::detail::overload_priority<2>)
		{
			using D = difference_type;
			return D(D(x.m_value) - D(y.m_value));
		}

		template <typename W2 = W,
			typename = hamon::enable_if_t<
				hamon::detail::is_integer_like_t<W2>::value &&
				!hamon::detail::is_signed_integer_like_t<W2>::value>>
		friend HAMON_CXX11_CONSTEXPR difference_type
		subtract(iterator const& x, iterator const& y, hamon::detail::overload_priority<1>)
		{
			using D = difference_type;
			return (y.m_value > x.m_value) ?
				D(-D(y.m_value - x.m_value)) :
				D(x.m_value - y.m_value);
		}

		template <typename W2 = W,
			typename = hamon::enable_if_t<
				!hamon::detail::is_integer_like_t<W2>::value>>
		friend HAMON_CXX11_CONSTEXPR difference_type
		subtract(iterator const& x, iterator const& y, hamon::detail::overload_priority<0>)
		{
			return x.m_value - y.m_value;
		}

	public:
		template <HAMON_CONSTRAINED_PARAM_D(detail::advanceable, W2, W)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR difference_type	// nodiscard as an extension
		operator-(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_value - y.m_value)	// noexcept as an extension
			//requires detail::advanceable<W>
		{
			return subtract(x, y, hamon::detail::overload_priority<2>{});
		}
	};

	// [range.iota.sentinel], class iota_view​::​sentinel
	struct sentinel
	{
	private:
		Bound m_bound = Bound();

	public:
		sentinel() = default;

		HAMON_CXX11_CONSTEXPR explicit
		sentinel(Bound bound)
			HAMON_NOEXCEPT_IF(		// noexcept as an extension
				hamon::is_nothrow_move_constructible<Bound>::value)
			// [range.iota.sentinel]/1
			: m_bound(hamon::move(bound))
		{}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_value == y.m_bound)	// noexcept as an extension
		{
			// [range.iota.sentinel]/2
			return x.m_value == y.m_bound;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(sentinel const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)	// noexcept as an extension
		{
			return y == x;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(sentinel const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::sized_sentinel_for, W, Bound2, Bound)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR iter_difference_t<W>	// nodiscard as an extension
		operator-(iterator const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_value - y.m_bound)	// noexcept as an extension
			//requires hamon::sized_sentinel_for<Bound, W>
		{
			// [range.iota.sentinel]/3
			return x.m_value - y.m_bound;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::sized_sentinel_for, W, Bound2, Bound)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR iter_difference_t<W>	// nodiscard as an extension
		operator-(sentinel const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(y - x)	// noexcept as an extension
			//requires hamon::sized_sentinel_for<Bound, W>
		{
			// [range.iota.sentinel]/4
			return -(y - x);
		}

		friend iota_view;
	};

	W m_value = W();
	Bound m_bound = Bound();

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	iota_view() requires hamon::default_initializable<W> = default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(default_initializable, W2, W)>
	HAMON_CXX11_CONSTEXPR
	iota_view()
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_default_constructible<W>::value &&
			hamon::is_nothrow_default_constructible<Bound>::value)
	{}
#endif
	
	HAMON_CXX11_CONSTEXPR explicit
	iota_view(W value)
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_move_constructible<W>::value &&
			hamon::is_nothrow_default_constructible<Bound>::value)
		// [range.iota.view]/7
		: m_value(hamon::move(value))
	{}

	HAMON_CXX11_CONSTEXPR explicit
	iota_view(hamon::type_identity_t<W> value, hamon::type_identity_t<Bound> bound)
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_move_constructible<W>::value &&
			hamon::is_nothrow_move_constructible<Bound>::value)
		// [range.iota.view]/9
		: m_value(hamon::move(value))
		, m_bound(hamon::move(bound))
	{}

private:
	using last_type =
		hamon::conditional_t<hamon::same_as_t<W, Bound>::value,
			iterator,						// [range.iota.view]/11.1
		hamon::conditional_t<hamon::same_as_t<Bound, hamon::unreachable_sentinel_t>::value,
			hamon::unreachable_sentinel_t,	// [range.iota.view]/11.2
			sentinel						// [range.iota.view]/11.3
		>>;

	struct iterator_ctor_tag {};

	HAMON_CXX11_CONSTEXPR explicit
	iota_view(iterator_ctor_tag, iterator& first, iterator& last)
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			iota_view(hamon::move(first.m_value), hamon::move(last.m_value)))
		// [range.iota.view]/10.1
		: iota_view(hamon::move(first.m_value), hamon::move(last.m_value))
	{}

	HAMON_CXX11_CONSTEXPR explicit
	iota_view(iterator_ctor_tag, iterator& first, hamon::unreachable_sentinel_t& last)
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			iota_view(hamon::move(first.m_value), hamon::move(last)))
		// [range.iota.view]/10.2
		: iota_view(hamon::move(first.m_value), hamon::move(last))
	{}

	HAMON_CXX11_CONSTEXPR explicit
	iota_view(iterator_ctor_tag, iterator& first, sentinel& last)
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			iota_view(hamon::move(first.m_value), hamon::move(last.m_bound)))
		// [range.iota.view]/10.3
		: iota_view(hamon::move(first.m_value), hamon::move(last.m_bound))
	{}

public:
	// [range.iota.view]/10
	HAMON_CXX11_CONSTEXPR explicit
	iota_view(iterator first, last_type last)
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			iota_view(iterator_ctor_tag{}, first, last))
		: iota_view(iterator_ctor_tag{}, first, last)
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR iterator	// nodiscard as an extension
	begin() const
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<W>::value)
	{
		// [range.iota.view]/12
		return iterator{m_value};
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	end() const
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<Bound>::value)
	{
		// [range.iota.view]/13
		if constexpr (hamon::same_as_t<Bound, hamon::unreachable_sentinel_t>::value)
		{
			return hamon::unreachable_sentinel;
		}
		else
		{
			return sentinel{m_bound};
		}
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR iterator	// nodiscard as an extension
	end() const
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<Bound>::value)
		requires hamon::same_as<W, Bound>
	{
		// [range.iota.view]/14
		return iterator{m_bound};
	}
#else
private:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::same_as, Bound, W2, W)>
	HAMON_CXX11_CONSTEXPR iterator
	end_impl(hamon::detail::overload_priority<2>) const
	{
		return iterator{m_bound};
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::same_as, hamon::unreachable_sentinel_t, Bound2, Bound)>
	HAMON_CXX11_CONSTEXPR hamon::unreachable_sentinel_t
	end_impl(hamon::detail::overload_priority<1>) const
	{
		return hamon::unreachable_sentinel;
	}

	HAMON_CXX11_CONSTEXPR sentinel
	end_impl(hamon::detail::overload_priority<0>) const
	{
		return sentinel{m_bound};
	}

public:
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	end() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_copy_constructible<Bound>::value)
	->decltype(end_impl(hamon::detail::overload_priority<2>{}))
	{
		return end_impl(hamon::detail::overload_priority<2>{});
	}
#endif

private:
	// [range.iota.view]/15
	template <typename W2, typename Bound2,
		typename = hamon::enable_if_t<
			hamon::detail::is_integer_like_t<W2>::value &&
			hamon::detail::is_integer_like_t<Bound2>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	size_impl(W2 const& value, Bound2 const& bound, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
	->decltype(detail::to_unsigned_like(bound) - detail::to_unsigned_like(value))
	{
HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4146)	// 符号付きの値を代入する変数は、符号付き型にキャストしなければなりません
		return
			(value < 0) ?
				((bound < 0) ?
					detail::to_unsigned_like(-value) - detail::to_unsigned_like(-bound) :
					detail::to_unsigned_like(bound) + detail::to_unsigned_like(-value)) :
				detail::to_unsigned_like(bound) - detail::to_unsigned_like(value);
HAMON_WARNING_POP()
	}

	template <typename W2, typename Bound2>
	static HAMON_CXX11_CONSTEXPR auto
	size_impl(W2 const& value, Bound2 const& bound, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_IF_EXPR(
			detail::to_unsigned_like(bound - value))
	->decltype(detail::to_unsigned_like(bound - value))
	{
		return detail::to_unsigned_like(bound - value);
	}

public:
	template <typename W2 = W, typename Bound2 = Bound,
		typename = hamon::enable_if_t<hamon::disjunction<
			hamon::conjunction<hamon::same_as_t<W2, Bound2>, detail::advanceable_t<W2>>,
			hamon::conjunction<hamon::detail::is_integer_like_t<W2>, hamon::detail::is_integer_like_t<Bound2>>,
			hamon::sized_sentinel_for_t<Bound2, W2>
		>::value>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	size() const HAMON_NOEXCEPT_IF_EXPR(
		size_impl(hamon::declval<W2>(), hamon::declval<Bound2>(), hamon::detail::overload_priority<1>{}))	// noexcept as an extension
	->decltype(size_impl(hamon::declval<W2>(), hamon::declval<Bound2>(), hamon::detail::overload_priority<1>{}))
		// [range.iota.view]/16
		//requires (hamon::same_as<W, Bound> && detail::advanceable<W>) ||
		//	(hamon::detail::is_integer_like<W> && hamon::detail::is_integer_like<Bound>) ||
		//	hamon::sized_sentinel_for<Bound, W>
	{
		return size_impl(m_value, m_bound, hamon::detail::overload_priority<1>{});
	}
};

template <typename W, typename Bound>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon::ranges::iota_view<W, Bound>);

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename W, typename Bound,
	typename = hamon::enable_if_t<hamon::disjunction<
		hamon::negation<hamon::detail::is_integer_like_t<W>>,
		hamon::negation<hamon::detail::is_integer_like_t<Bound>>,
		hamon::is_same<hamon::detail::is_signed_integer_like_t<W>, hamon::detail::is_signed_integer_like_t<Bound>>
	>::value>
>
	//requires (
	//	!hamon::detail::is_integer_like<W> ||
	//	!hamon::detail::is_integer_like<Bound> ||
	//	(hamon::detail::is_signed_integer_like<W> == hamon::detail::is_signed_integer_like<Bound>))
iota_view(W, Bound) -> iota_view<W, Bound>;

#endif

namespace views {

namespace detail {

struct iota_fn
{
	// [range.iota.overview]/2

	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::ranges::iota_view<hamon::remove_cvref_t<T>>
	operator()(T&& e) const
		HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::iota_view<hamon::remove_cvref_t<T>>(hamon::forward<T>(e)))
	{
		//return hamon::ranges::iota_view(hamon::forward<T>(e));
		return hamon::ranges::iota_view<hamon::remove_cvref_t<T>>(hamon::forward<T>(e));
	}

	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::ranges::iota_view<hamon::remove_cvref_t<T>, hamon::remove_cvref_t<U>>
	operator()(T&& e, U&& f) const
		HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::iota_view<hamon::remove_cvref_t<T>, hamon::remove_cvref_t<U>>(hamon::forward<T>(e), hamon::forward<U>(f)))
	{
		//return hamon::ranges::iota_view(hamon::forward<T>(e), hamon::forward<U>(f));
		return hamon::ranges::iota_view<hamon::remove_cvref_t<T>, hamon::remove_cvref_t<U>>(hamon::forward<T>(e), hamon::forward<U>(f));
	}
};

}	// namespace detail

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::iota_fn iota{};

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_VIEWS_IOTA_VIEW_HPP
