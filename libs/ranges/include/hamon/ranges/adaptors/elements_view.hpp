/**
 *	@file	elements_view.hpp
 *
 *	@brief	elements_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_ELEMENTS_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_ELEMENTS_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

#include <hamon/cstddef/size_t.hpp>

namespace hamon {
namespace ranges {

using std::ranges::elements_view;
using std::ranges::keys_view;
using std::ranges::values_view;

namespace views {
inline namespace cpo {

using std::ranges::views::elements;
using std::ranges::views::keys;
using std::ranges::views::values;

// variable templates が使える場合も使えない場合も、
// hamon::views::elements_t<N>{}
// の形で使えるようにする。
template <hamon::size_t N>
using elements_t = decltype(elements<N>);

}	// inline namespace cpo
}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/tuple/concepts/tuple_like.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_lvalue_reference.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>

namespace hamon {
namespace ranges {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T, hamon::size_t N>
concept has_tuple_element =
	hamon::tuple_like<T> && N < hamon::tuple_size<T>::value;

template <typename T, hamon::size_t N>
concept returnable_element =
	hamon::is_reference<T>::value ||
	hamon::move_constructible<hamon::tuple_element_t<N, T>>;

#else

template <typename T, hamon::size_t N>
using has_tuple_element = hamon::bool_constant<
	hamon::tuple_like_t<T>::value &&
	(N < hamon::tuple_size<T>::value)
>;

template <typename T, hamon::size_t N>
struct returnable_element_impl
{
private:
	template <typename T2, hamon::size_t N2,
		typename E = hamon::tuple_element_t<N2, T2>,
		typename = hamon::enable_if_t<
			hamon::move_constructible<E>::value>>
	static auto test(int) -> hamon::true_type;

	template <typename T2, hamon::size_t N2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T, N>(0));
};

template <typename T, hamon::size_t N>
using returnable_element = hamon::disjunction<
	hamon::is_reference<T>,
	typename returnable_element_impl<T, N>::type
>;

#endif

// 26.7.22.2 Class template elements_view[range.elements.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::input_range V, hamon::size_t N>
	requires hamon::ranges::view<V> &&
		has_tuple_element<hamon::ranges::range_value_t<V>, N> &&
		has_tuple_element<hamon::remove_reference_t<hamon::ranges::range_reference_t<V>>, N> &&
		returnable_element<hamon::ranges::range_reference_t<V>, N>
#else
template <typename V, hamon::size_t N,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::input_range_t<V>,
		hamon::ranges::view_t<V>,
		has_tuple_element<hamon::ranges::range_value_t<V>, N>,
		has_tuple_element<hamon::remove_reference_t<hamon::ranges::range_reference_t<V>>, N>,
		returnable_element<hamon::ranges::range_reference_t<V>, N>
	>::value>>
#endif
class elements_view : public hamon::ranges::view_interface<elements_view<V, N>>
{
private:
	template <bool>
	class iterator;

	template <bool>
	class sentinel;

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	elements_view()
		requires hamon::default_initializable<V>
	= default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V)>
	HAMON_CXX11_CONSTEXPR elements_view()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<V>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	elements_view(V base) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
		// [range.elements.view]/1
		: m_base(hamon::move(base))
	{}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::copy_constructible, V2, V)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	V base() const& HAMON_NOEXCEPT_IF(		// noexcept as an extension
		hamon::is_nothrow_copy_constructible<V>::value)
	{
		return m_base;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	V base() && HAMON_NOEXCEPT_IF(			// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
	{
		return hamon::move(m_base);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator<false> begin() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(hamon::declval<V2&>())) &&
		hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V2>>::value)
	{
		return iterator<false>(hamon::ranges::begin(m_base));
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	iterator<true> begin() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(hamon::declval<V2&>())) &&
		hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V2>>::value)
	{
		return iterator<true>(hamon::ranges::begin(m_base));
	}

private:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::common_range, V2, V)>
	HAMON_CXX14_CONSTEXPR iterator<false>
	end_impl(hamon::detail::overload_priority<1>)
	{
		return iterator<false>{hamon::ranges::end(m_base)};
	}

	HAMON_CXX14_CONSTEXPR sentinel<false>
	end_impl(hamon::detail::overload_priority<0>)
	{
		return sentinel<false>{hamon::ranges::end(m_base)};
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::common_range, V2, V const)>
	HAMON_CXX11_CONSTEXPR iterator<true>
	end_const_impl(hamon::detail::overload_priority<1>) const
	{
		return iterator<true>{hamon::ranges::end(m_base)};
	}

	HAMON_CXX11_CONSTEXPR sentinel<true>
	end_const_impl(hamon::detail::overload_priority<0>) const
	{
		return sentinel<true>{hamon::ranges::end(m_base)};
	}

public:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto end() HAMON_NOEXCEPT_IF(			// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::end(hamon::declval<V2&>())) &&
		hamon::is_nothrow_move_constructible<hamon::ranges::sentinel_t<V2>>::value)
	->decltype(end_impl(hamon::detail::overload_priority<1>{}))
	{
		return end_impl(hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto end() const HAMON_NOEXCEPT_IF(		// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::end(hamon::declval<V2&>())) &&
		hamon::is_nothrow_move_constructible<hamon::ranges::sentinel_t<V2>>::value)
	->decltype(end_const_impl(hamon::detail::overload_priority<1>{}))
	{
		return end_const_impl(hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto size() HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
		hamon::ranges::size(hamon::declval<V2&>()))
	->decltype(hamon::ranges::size(hamon::declval<V2&>()))
	{
		return hamon::ranges::size(m_base);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto size() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		hamon::ranges::size(hamon::declval<V2&>()))
	->decltype(hamon::ranges::size(hamon::declval<V2&>()))
	{
		return hamon::ranges::size(m_base);
	}

private:
	// [range.elements.iterator]/2
	template <typename Base,
		bool = hamon::ranges::forward_range_t<Base>::value>
	struct iterator_category_base
	{
	private:
		using BaseIter = hamon::ranges::iterator_t<Base>;
		using C = typename hamon::iterator_traits<BaseIter>::iterator_category;
		using U = decltype(hamon::adl_get<N>(*hamon::declval<BaseIter>()));
	public:
		using iterator_category =
			hamon::conditional_t<!hamon::is_lvalue_reference<U>::value,
				hamon::input_iterator_tag,			// [range.elements.iterator]/2.1
			hamon::conditional_t<hamon::derived_from_t<C, hamon::random_access_iterator_tag>::value,
				hamon::random_access_iterator_tag,	// [range.elements.iterator]/2.2
				C									// [range.elements.iterator]/2.3
			>>;
	};

	template <typename Base>
	struct iterator_category_base<Base, false>
	{};

	// [range.elements.iterator], class template elements_view​::​iterator
	template <bool Const>
	class iterator
		: public iterator_category_base<hamon::ranges::detail::maybe_const<Const, V>>
	{
	private:
		friend iterator<!Const>;
		friend sentinel<Const>;
		friend sentinel<!Const>;

		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using BaseIter = hamon::ranges::iterator_t<Base>;

		HAMON_NO_UNIQUE_ADDRESS BaseIter m_current = BaseIter();

	private:
		// [range.elements.iterator]/3
		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				hamon::is_reference<hamon::ranges::range_reference_t<B2>>::value>>
		static HAMON_CXX11_CONSTEXPR auto
		get_element_impl(BaseIter const& i, hamon::detail::overload_priority<1>)
			HAMON_NOEXCEPT_IF_EXPR(hamon::adl_get<N>(*i))
		->decltype(hamon::adl_get<N>(*i))
		{
			return hamon::adl_get<N>(*i);
		}

		template <typename B2 = Base,
			typename E = hamon::remove_cv_t<
				hamon::tuple_element_t<N, hamon::ranges::range_reference_t<B2>>>>
		static HAMON_CXX11_CONSTEXPR E
		get_element_impl(BaseIter const& i, hamon::detail::overload_priority<0>)
			HAMON_NOEXCEPT_IF_EXPR(static_cast<E>(hamon::adl_get<N>(*i)))
		{
			return static_cast<E>(hamon::adl_get<N>(*i));
		}

		static HAMON_CXX11_CONSTEXPR auto
		get_element(BaseIter const& i) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			get_element_impl(i, hamon::detail::overload_priority<1>{}))
		->decltype(get_element_impl(i, hamon::detail::overload_priority<1>{}))
		{
			return get_element_impl(i, hamon::detail::overload_priority<1>{});
		}

	public:
		using iterator_concept =
			hamon::conditional_t<hamon::ranges::random_access_range_t<Base>::value,
				hamon::random_access_iterator_tag,	// [range.elements.iterator]/1.1
			hamon::conditional_t<hamon::ranges::bidirectional_range_t<Base>::value,
				hamon::bidirectional_iterator_tag,	// [range.elements.iterator]/1.2
			hamon::conditional_t<hamon::ranges::forward_range_t<Base>::value,
				hamon::forward_iterator_tag,		// [range.elements.iterator]/1.3
				hamon::input_iterator_tag			// [range.elements.iterator]/1.4
			>>>;
		//using iterator_category = see below;                // not always present
		using value_type = hamon::remove_cvref_t<hamon::tuple_element_t<N, hamon::ranges::range_value_t<Base>>>;
		using difference_type = hamon::ranges::range_difference_t<Base>;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
		iterator()
			requires hamon::default_initializable<BaseIter>
		= default;
#else
		template <typename I2 = BaseIter,
			typename = hamon::enable_if_t<
				hamon::default_initializable_t<I2>::value>>
		HAMON_CXX11_CONSTEXPR iterator()
			HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<I2>::value)
		{}
#endif

		HAMON_CXX11_CONSTEXPR explicit
		iterator(BaseIter current) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<BaseIter>::value)
			// [range.elements.iterator]/4
			: m_current(hamon::move(current))
		{}

		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				Const &&
				hamon::convertible_to_t<
					hamon::ranges::iterator_t<V>,
					hamon::ranges::iterator_t<B2>
				>::value>>
		HAMON_CXX11_CONSTEXPR
		iterator(iterator<!Const> i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_constructible<BaseIter, hamon::ranges::iterator_t<V>>::value)
			// [range.elements.iterator]/5
			: m_current(hamon::move(i.m_current))
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		BaseIter const& base() const& HAMON_NOEXCEPT
		{
			// [range.elements.iterator]/6
			return m_current;
		}

		HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		BaseIter base() && HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<BaseIter>::value)
		{
			// [range.elements.iterator]/7
			return hamon::move(m_current);
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator*() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			get_element(hamon::declval<BaseIter const&>()))
		->decltype(get_element(hamon::declval<BaseIter const&>()))
		{
			return get_element(m_current);
		}

		HAMON_CXX14_CONSTEXPR iterator&
		operator++() HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			++hamon::declval<BaseIter&>())
		{
			// [range.elements.iterator]/8
			++m_current;
			return *this;
		}

	private:
		HAMON_CXX14_CONSTEXPR void
		post_increment_impl(hamon::detail::overload_priority<0>)
			HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
				++hamon::declval<BaseIter&>())
		{
			// [range.elements.iterator]/9
			++m_current;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator
		post_increment_impl(hamon::detail::overload_priority<1>)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(++hamon::declval<BaseIter&>()) &&
				hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
			// [range.elements.iterator]/10
			auto temp = *this;
			++m_current;
			return temp;
		}

	public:
		HAMON_CXX14_CONSTEXPR auto
		operator++(int) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			post_increment_impl(hamon::detail::overload_priority<1>{}))
		->decltype(post_increment_impl(hamon::detail::overload_priority<1>{}))
		{
			return post_increment_impl(hamon::detail::overload_priority<1>{});
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator--() HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			--hamon::declval<BaseIter&>())
		{
			// [range.elements.iterator]/11
			--m_current;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator
		operator--(int) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(--hamon::declval<BaseIter&>()) &&
			hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
			// [range.elements.iterator]/12
			auto temp = *this;
			--m_current;
			return temp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator+=(difference_type n) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::declval<BaseIter&>() += hamon::declval<difference_type>())
		{
			// [range.elements.iterator]/13
			m_current += n;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator-=(difference_type n) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::declval<BaseIter&>() -= hamon::declval<difference_type>())
		{
			// [range.elements.iterator]/14
			m_current -= n;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator[](difference_type n) const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			get_element(hamon::declval<hamon::ranges::iterator_t<B2> const&>() + n))
		->decltype(get_element(hamon::declval<hamon::ranges::iterator_t<B2> const&>() + n))
		{
			return get_element(m_current + n);
		}

	private:
		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				hamon::equality_comparable_t<hamon::ranges::iterator_t<B2>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, iterator const& y) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::declval<BaseIter const&>() == hamon::declval<BaseIter const&>())
		{
			// [range.elements.iterator]/15
			return x.m_current == y.m_current;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				hamon::equality_comparable_t<hamon::ranges::iterator_t<B2>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<(iterator const& x, iterator const& y) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::declval<BaseIter const&>() < hamon::declval<BaseIter const&>())
		{
			// [range.elements.iterator]/16
			return x.m_current < y.m_current;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(y < x)		// noexcept as an extension
		{
			// [range.elements.iterator]/17
			return y < x;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(y < x))	// noexcept as an extension
		{
			// [range.elements.iterator]/18
			return !(y < x);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x < y))	// noexcept as an extension
		{
			// [range.elements.iterator]/19
			return !(x < y);
		}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator<=>(iterator const& x, iterator const& y) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::declval<BaseIter const&>() <=> hamon::declval<BaseIter const&>())
			requires
				hamon::ranges::random_access_range<Base> &&
				hamon::three_way_comparable<BaseIter>
		{
			// [range.elements.iterator]/20
			return x.m_current <=> y.m_current;
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator+(iterator const& x, difference_type y) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(hamon::declval<BaseIter&>() += hamon::declval<difference_type>()) &&
			hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
			// [range.elements.iterator]/21
			return iterator{x} += y;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator+(difference_type x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(y + x)	// noexcept as an extension
		{
			// [range.elements.iterator]/22
			return y + x;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator-(iterator const& x, difference_type y) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(hamon::declval<BaseIter&>() -= hamon::declval<difference_type>()) &&
			hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
			// [range.elements.iterator]/23
			return iterator{x} -= y;
		}

		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<
					hamon::ranges::iterator_t<B2>,
					hamon::ranges::iterator_t<B2>
				>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(						// noexcept as an extension
				hamon::declval<BaseIter const&>() - hamon::declval<BaseIter const&>())
		{
			// [range.elements.iterator]/24
			return x.m_current - y.m_current;
		}
	};

	// [range.elements.sentinel], class template elements_view​::​sentinel
	template <bool Const>
	class sentinel
	{
	private:
		friend sentinel<!Const>;

		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using BaseSent = hamon::ranges::sentinel_t<Base>;

		template <bool OtherConst>
		using BaseIter = hamon::ranges::iterator_t<
			hamon::ranges::detail::maybe_const<OtherConst, V>>;

		HAMON_NO_UNIQUE_ADDRESS BaseSent m_end = BaseSent();

	public:
		sentinel() = default;

		HAMON_CXX11_CONSTEXPR explicit
		sentinel(BaseSent end) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<BaseSent>::value)
			// [range.elements.sentinel]/1
			: m_end(hamon::move(end))
		{}

		template <typename B2 = Base,
			typename = hamon::enable_if_t<
				Const &&
				hamon::convertible_to_t<
					hamon::ranges::sentinel_t<V>,
					hamon::ranges::sentinel_t<B2>
				>::value>>
		HAMON_CXX11_CONSTEXPR
		sentinel(sentinel<!Const> other) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_constructible<BaseSent, hamon::ranges::sentinel_t<V>>::value)
			// [range.elements.sentinel]/2
			: m_end(hamon::move(other.m_end))
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
		BaseSent base() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<BaseSent>::value)
		{
			// [range.elements.sentinel]/3
			return m_end;
		}

	private:
		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, BaseIter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.base() == y.m_end)	// noexcept as an extension
		{
			// [range.elements.sentinel]/4
			return x.base() == y.m_end;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, BaseIter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))			// noexcept as an extension
		{
			return !(x == y);
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, BaseIter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)				// noexcept as an extension
		{
			return y == x;
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, BaseIter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))			// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<BaseSent, BaseIter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::range_difference_t<hamon::ranges::detail::maybe_const<OtherConst, V>>
		operator-(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.base() - y.m_end)	// noexcept as an extension
		{
			// [range.elements.sentinel]/5
			return x.base() - y.m_end;
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<BaseSent, BaseIter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::range_difference_t<hamon::ranges::detail::maybe_const<OtherConst, V>>
		operator-(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_end - y.base())	// noexcept as an extension
		{
			// [range.elements.sentinel]/6
			return x.m_end - y.base();
		}
	};

	HAMON_NO_UNIQUE_ADDRESS V m_base = V();
};

// enable_borrowed_range の特殊化
template <typename T, hamon::size_t N>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(T),
	hamon::ranges::elements_view<T, N>);

namespace views {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 26.7.22.1 Overview[range.elements.overview]

template <hamon::size_t N>
struct elements_fn : public hamon::ranges::range_adaptor_closure<elements_fn<N>>
{
	// [range.elements.overview]/2
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	auto operator()(R&& r) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::elements_view<hamon::views::all_t<R>, N>{ hamon::forward<R>(r) })
};

} // namespace detail

inline namespace cpo
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <hamon::size_t N>
HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::elements_fn<N> elements{};

#endif

// variable templates が使える場合も使えない場合も、
// hamon::views::elements_t<N>{}
// の形で使えるようにする。
template <hamon::size_t N>
using elements_t = detail::elements_fn<N>;

HAMON_INLINE_VAR HAMON_CONSTEXPR
auto keys = detail::elements_fn<0>{};

HAMON_INLINE_VAR HAMON_CONSTEXPR
auto values = detail::elements_fn<1>{};

}	// inline namespace cpo

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_ELEMENTS_VIEW_HPP
