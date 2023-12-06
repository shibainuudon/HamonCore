/**
 *	@file	repeat_view.hpp
 *
 *	@brief	repeat_view の定義
 */

#ifndef HAMON_RANGES_VIEWS_REPEAT_VIEW_HPP
#define HAMON_RANGES_VIEWS_REPEAT_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_repeat) && (__cpp_lib_ranges_repeat >= 202207L)

#define HAMON_USE_STD_RANGES_REPEAT_VIEW

namespace hamon {
namespace ranges {

using std::ranges::repeat_view;

namespace views {

using std::ranges::views::repeat;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/detail/movable_box.hpp>
#include <hamon/ranges/detail/to_unsigned_like.hpp>
#include <hamon/ranges/detail/iota_diff_t.hpp>
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/concepts/semiregular.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/iterator/detail/is_signed_integer_like.hpp>
#include <hamon/iterator/detail/is_integer_like.hpp>
#include <hamon/iterator/concepts/weakly_incrementable.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/pair/piecewise_construct_t.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept integer_like_with_usable_difference_type =
	hamon::detail::is_signed_integer_like<T> ||
	(hamon::detail::is_integer_like<T> && hamon::weakly_incrementable<T>);

#else

template <typename T>
struct integer_like_with_usable_difference_type_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<hamon::disjunction<
			hamon::detail::is_signed_integer_like<U>,
			hamon::conjunction<
				hamon::detail::is_integer_like<U>,
				hamon::weakly_incrementable<U>
			>
		>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using integer_like_with_usable_difference_type =
	typename integer_like_with_usable_difference_type_impl<T>::type;

#endif

}	// namespace detail

// 26.6.5.2 Class template repeat_view	[range.repeat.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::move_constructible T, hamon::semiregular Bound = hamon::unreachable_sentinel_t>
requires (hamon::is_object<T>::value && hamon::same_as<T, hamon::remove_cv_t<T>> &&
	(ranges::detail::integer_like_with_usable_difference_type<Bound> ||
	 hamon::same_as<Bound, hamon::unreachable_sentinel_t>))
#else
template <typename T, typename Bound = hamon::unreachable_sentinel_t,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::move_constructible<T>,
		hamon::semiregular<Bound>,
		hamon::is_object<T>,
		hamon::same_as<T, hamon::remove_cv_t<T>>,
		hamon::disjunction<
			ranges::detail::integer_like_with_usable_difference_type<Bound>,
			hamon::same_as<Bound, hamon::unreachable_sentinel_t>
		>
	>::value>
>
#endif
class repeat_view : public view_interface<repeat_view<T, Bound>>
{
private:
	// [range.repeat.iterator], class repeat_view​::​iterator
	struct iterator
	{
	private:
		friend repeat_view;

	private:
		using index_type = hamon::conditional_t<
			hamon::same_as_t<Bound, hamon::unreachable_sentinel_t>::value,
				hamon::ptrdiff_t,
				Bound>;
		T const* m_value = nullptr;
		index_type m_current = index_type();

		HAMON_CXX11_CONSTEXPR explicit
		iterator(T const* value, index_type b = index_type())
			HAMON_NOEXCEPT	// noexcept as an extension
			// [range.repeat.iterator]/3
			: m_value(value)
			, m_current(hamon::move(b))
		{
#if defined(HAMON_HAS_CXX14_CONSTEXPR)
			// [range.repeat.iterator]/2
			HAMON_ASSERT((
				hamon::same_as_t<Bound, hamon::unreachable_sentinel_t>::value ||
				b >= 0));
#endif
		}

	public:
		using iterator_concept = hamon::random_access_iterator_tag;
		using iterator_category = hamon::random_access_iterator_tag;
		using value_type = T;
		// [range.repeat.iterator]/1
		using difference_type = hamon::conditional_t<
			hamon::detail::is_signed_integer_like_t<index_type>::value,
				index_type,
				hamon::ranges::detail::iota_diff_t<index_type>>;

		iterator() = default;

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const&	// nodiscard as an extension
		operator*() const HAMON_NOEXCEPT
		{
			// [range.repeat.iterator]/4
			return *m_value;
		}

		HAMON_CXX14_CONSTEXPR iterator&
		operator++() HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.repeat.iterator]/5
			++m_current;
			return *this;
		}

		HAMON_CXX14_CONSTEXPR iterator
		operator++(int) HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.repeat.iterator]/6
			auto tmp = *this;
			++*this;
			return tmp;
		}

		HAMON_CXX14_CONSTEXPR iterator&
		operator--() HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.repeat.iterator]/7
			HAMON_ASSERT((
				hamon::same_as_t<Bound, hamon::unreachable_sentinel_t>::value ||
				m_current > 0));

			// [range.repeat.iterator]/8
			--m_current;
			return *this;
		}

		HAMON_CXX14_CONSTEXPR iterator
		operator--(int) HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.repeat.iterator]/9
			auto tmp = *this;
			--*this;
			return tmp;
		}

		HAMON_CXX14_CONSTEXPR iterator&
		operator+=(difference_type n) HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.repeat.iterator]/10
			HAMON_ASSERT((
				hamon::same_as_t<Bound, hamon::unreachable_sentinel_t>::value ||
				m_current + n >= 0));

			// [range.repeat.iterator]/11
			m_current += n;
			return *this;
		}

		HAMON_CXX14_CONSTEXPR iterator&
		operator-=(difference_type n) HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.repeat.iterator]/12
			HAMON_ASSERT((
				hamon::same_as_t<Bound, hamon::unreachable_sentinel_t>::value ||
				m_current - n >= 0));

			// [range.repeat.iterator]/13
			m_current -= n;
			return *this;
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const&	// nodiscard as an extension
		operator[](difference_type n) const HAMON_NOEXCEPT
		{
			// [range.repeat.iterator]/14
			return *(*this + n);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator const& x, iterator const& y) HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.repeat.iterator]/15
			return x.m_current == y.m_current;
		}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
		operator<=>(iterator const& x, iterator const& y) HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.repeat.iterator]/16
			return x.m_current <=> y.m_current;
		}
#else
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator const& x, iterator const& y) HAMON_NOEXCEPT	// noexcept as an extension
		{
			return !(x == y);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator<(iterator const& x, iterator const& y) HAMON_NOEXCEPT	// noexcept as an extension
		{
			return x.m_current < y.m_current;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator>(iterator const& x, iterator const& y) HAMON_NOEXCEPT	// noexcept as an extension
		{
			return y < x;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator<=(iterator const& x, iterator const& y) HAMON_NOEXCEPT	// noexcept as an extension
		{
			return !(y < x);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator>=(iterator const& x, iterator const& y) HAMON_NOEXCEPT	// noexcept as an extension
		{
			return !(x < y);
		}
#endif

		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR iterator	// nodiscard as an extension
		operator+(iterator i, difference_type n) HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.repeat.iterator]/17
			i += n;
			return i;
		}

		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR iterator	// nodiscard as an extension
		operator+(difference_type n, iterator i) HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.repeat.iterator]/17
			i += n;
			return i;
		}

		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR iterator	// nodiscard as an extension
		operator-(iterator i, difference_type n) HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.repeat.iterator]/18
			i -= n;
			return i;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR difference_type	// nodiscard as an extension
		operator-(iterator const& x, iterator const& y) HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.repeat.iterator]/19
			return static_cast<difference_type>(x.m_current) -
				static_cast<difference_type>(y.m_current);
		}
	};

	ranges::detail::movable_box<T> m_value;	// [range.move.wrap]
	Bound m_bound = Bound();

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	repeat_view() requires hamon::default_initializable<T> = default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, T2, T)>
	HAMON_CXX11_CONSTEXPR
	repeat_view()
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_default_constructible<T>::value &&
			hamon::is_nothrow_default_constructible<Bound>::value)
	{}
#endif

	template <HAMON_CONSTRAINED_PARAM_D(hamon::copy_constructible, T2, T)>
	HAMON_CXX11_CONSTEXPR explicit
	repeat_view(T const& value, Bound bound = Bound())
//	requires hamon::copy_constructible<T>
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_copy_constructible<T>::value)
		// [range.repeat.view]/2
		: m_value(value), m_bound(hamon::move(bound))
	{}

	HAMON_CXX11_CONSTEXPR explicit
	repeat_view(T&& value, Bound bound = Bound())
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_move_constructible<T>::value)
		// [range.repeat.view]/4
		: m_value(hamon::move(value)), m_bound(hamon::move(bound))
	{}

	template <typename... TArgs, typename... BoundArgs,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::constructible_from_t<T, TArgs...>,
			hamon::constructible_from_t<Bound, BoundArgs...>
		>::value>
	>
//	requires
//		hamon::constructible_from<T, TArgs...> &&
//		hamon::constructible_from<Bound, BoundArgs...>
	HAMON_CXX11_CONSTEXPR explicit
	repeat_view(hamon::piecewise_construct_t,
		hamon::tuple<TArgs...> value_args,
		hamon::tuple<BoundArgs...> bound_args = hamon::tuple<>{})
		HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_constructible<T, TArgs...>::value &&
			hamon::is_nothrow_constructible<Bound, BoundArgs...>::value)
		// [range.repeat.view]/5
		: m_value(hamon::make_from_tuple<T>(hamon::move(value_args)))
		, m_bound(hamon::make_from_tuple<Bound>(hamon::move(bound_args)))
	{}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR iterator	// nodiscard as an extension
	begin() const HAMON_NOEXCEPT	// noexcept as an extension
	{
		// [range.repeat.view]/6
		return iterator(hamon::addressof(*m_value));
	}

#if defined(HAMON_HAS_CXX20_CONCEPTS)
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR iterator	// nodiscard as an extension
	end() const HAMON_NOEXCEPT	// noexcept as an extension
		requires (!hamon::same_as<Bound, hamon::unreachable_sentinel_t>)
	{
		// [range.repeat.view]/7
		return iterator(hamon::addressof(*m_value), m_bound);
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::unreachable_sentinel_t	// nodiscard as an extension
	end() const HAMON_NOEXCEPT
	{
		// [range.repeat.view]/8
		return hamon::unreachable_sentinel;
	}
#else
private:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::same_as, hamon::unreachable_sentinel_t, Bound2, Bound)>
	HAMON_CXX11_CONSTEXPR hamon::unreachable_sentinel_t
	end_impl(hamon::detail::overload_priority<1>) const HAMON_NOEXCEPT
	{
		return hamon::unreachable_sentinel;
	}

	HAMON_CXX11_CONSTEXPR iterator
	end_impl(hamon::detail::overload_priority<0>) const HAMON_NOEXCEPT	// noexcept as an extension
	{
		return iterator(hamon::addressof(*m_value), m_bound);
	}

public:
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	end() const HAMON_NOEXCEPT	// noexcept as an extension
	->decltype(end_impl(hamon::detail::overload_priority<1>{}))
	{
		return end_impl(hamon::detail::overload_priority<1>{});
	}
#endif

	template <typename Bound2 = Bound,
		typename = hamon::enable_if_t<
			hamon::negation<hamon::same_as_t<Bound2, hamon::unreachable_sentinel_t>>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	size() const HAMON_NOEXCEPT	// noexcept as an extension
	->decltype(ranges::detail::to_unsigned_like(hamon::declval<Bound2>()))
//	requires (!hamon::same_as<Bound, hamon::unreachable_sentinel_t>)
	{
		// [range.repeat.view]/9
		return ranges::detail::to_unsigned_like(m_bound);
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
template <typename T, typename Bound>
repeat_view(T, Bound) -> repeat_view<T, Bound>;
#endif

namespace views {

namespace detail {

struct repeat_fn
{
	// [range.repeat.overview]/2

	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::ranges::repeat_view<hamon::remove_cvref_t<T>>
	operator()(T&& e) const
		HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::repeat_view<hamon::remove_cvref_t<T>>(hamon::forward<T>(e)))
	{
		//return hamon::ranges::repeat_view(hamon::forward<T>(e));
		return hamon::ranges::repeat_view<hamon::remove_cvref_t<T>>(hamon::forward<T>(e));
	}

	template <typename T, typename U>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR hamon::ranges::repeat_view<hamon::remove_cvref_t<T>, hamon::remove_cvref_t<U>>
	operator()(T&& e, U&& f) const
		HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::repeat_view<hamon::remove_cvref_t<T>, hamon::remove_cvref_t<U>>(hamon::forward<T>(e), hamon::forward<U>(f)))
	{
		//return hamon::ranges::repeat_view(hamon::forward<T>(e), hamon::forward<U>(f));
		return hamon::ranges::repeat_view<hamon::remove_cvref_t<T>, hamon::remove_cvref_t<U>>(hamon::forward<T>(e), hamon::forward<U>(f));
	}
};

}	// namespace detail

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::repeat_fn repeat{};

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_VIEWS_REPEAT_VIEW_HPP
