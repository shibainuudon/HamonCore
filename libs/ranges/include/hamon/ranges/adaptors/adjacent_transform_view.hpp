/**
 *	@file	adjacent_transform_view.hpp
 *
 *	@brief	adjacent_transform_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_ADJACENT_TRANSFORM_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_ADJACENT_TRANSFORM_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_zip) && (__cpp_lib_ranges_zip >= 202110L)

#define HAMON_USE_STD_RANGES_ADJACENT_TRANSFORM_VIEW

#include <hamon/cstddef/size_t.hpp>

namespace hamon {
namespace ranges {

using std::ranges::adjacent_transform_view;

namespace views {

using std::ranges::views::adjacent_transform;
using std::ranges::views::pairwise_transform;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/adjacent_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/adaptors/zip_transform_view.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/detail/movable_box.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/regular_invocable.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/detail/can_reference.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

#define HAMON_NOEXCEPT_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	{ return __VA_ARGS__; }

namespace hamon {
namespace ranges {

namespace detail {

template <typename T, hamon::size_t>
using repeat_type_helper = T;

template <typename F, typename T, typename Seq>
struct regular_invocable_with_repeated_type_impl;

template <typename F, typename T, hamon::size_t... Is>
struct regular_invocable_with_repeated_type_impl<F, T, hamon::index_sequence<Is...>>
	: hamon::regular_invocable_t<F, repeat_type_helper<T, Is>...>
{};

template <typename F, typename T, hamon::size_t N>
using regular_invocable_with_repeated_type_t =
	typename regular_invocable_with_repeated_type_impl<F, T, hamon::make_index_sequence<N>>::type;

template <typename F, typename T, typename Seq>
struct invoke_result_with_repeated_type_impl;

template <typename F, typename T, hamon::size_t... Is>
struct invoke_result_with_repeated_type_impl<F, T, hamon::index_sequence<Is...>>
{
	using type = hamon::invoke_result_t<F, repeat_type_helper<T, Is>...>;
};

template <typename F, typename T, hamon::size_t N>
using invoke_result_with_repeated_type_t =
	typename invoke_result_with_repeated_type_impl<F, T, hamon::make_index_sequence<N>>::type;

}	// namespace detail

// 26.7.27.2 Class template adjacent_transform_view[range.adjacent.transform.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::forward_range V, hamon::move_constructible F, hamon::size_t N>
	requires hamon::ranges::view<V> && (N > 0) && hamon::is_object_v<F> &&
		hamon::ranges::detail::regular_invocable_with_repeated_type_t<
			F&, hamon::ranges::range_reference_t<V>, N>::value &&
		hamon::detail::can_reference<hamon::ranges::detail::invoke_result_with_repeated_type_t<
			F&, hamon::ranges::range_reference_t<V>, N>>
#else
template <typename V, typename F, hamon::size_t N,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::forward_range_t<V>,
		hamon::move_constructible_t<F>,
		hamon::ranges::view_t<V>,
		hamon::bool_constant<(N > 0)>,
		hamon::is_object<F>,
		hamon::ranges::detail::regular_invocable_with_repeated_type_t<
			F&, hamon::ranges::range_reference_t<V>, N>
	>::value>,
	typename = hamon::enable_if_t<
		hamon::detail::can_reference<hamon::ranges::detail::invoke_result_with_repeated_type_t<
			F&, hamon::ranges::range_reference_t<V>, N>>::value>>
#endif
class adjacent_transform_view : public hamon::ranges::view_interface<adjacent_transform_view<V, F, N>>
{
private:
	HAMON_NO_UNIQUE_ADDRESS hamon::ranges::detail::movable_box<F> m_fun;
	HAMON_NO_UNIQUE_ADDRESS hamon::ranges::adjacent_view<V, N> m_inner;

	using InnerView = hamon::ranges::adjacent_view<V, N>;

	template <bool Const>
	using InnerIterator = hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, InnerView>>;

	template <bool Const>
	using InnerSentinel = hamon::ranges::sentinel_t<hamon::ranges::detail::maybe_const<Const, InnerView>>;

	// [range.adjacent.transform.iterator], class template adjacent_transform_view​::​iterator
	template <bool Const>
	class iterator
	{
	private:
		friend adjacent_transform_view;

		using Parent = hamon::ranges::detail::maybe_const<Const, adjacent_transform_view>;
		using Base = hamon::ranges::detail::maybe_const<Const, V>;

		Parent* m_parent = nullptr;
		InnerIterator<Const> m_inner;

		HAMON_CXX11_CONSTEXPR
		iterator(Parent& parent, InnerIterator<Const> inner)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_move_constructible<InnerIterator<Const>>::value)
			// [range.adjacent.transform.iterator]/2
			: m_parent(hamon::addressof(parent))
			, m_inner(hamon::move(inner))
		{}

		using InvokeResult = hamon::ranges::detail::invoke_result_with_repeated_type_t<
			hamon::ranges::detail::maybe_const<Const, F>&,
			hamon::ranges::range_reference_t<Base>,
			N>;

		using C = typename hamon::iterator_traits<hamon::ranges::iterator_t<Base>>::iterator_category;
	public:
		using iterator_category =
			hamon::conditional_t<!hamon::is_reference<InvokeResult>::value,
				hamon::input_iterator_tag,
			hamon::conditional_t<hamon::derived_from_t<C, hamon::random_access_iterator_tag>::value,
				hamon::random_access_iterator_tag,
			hamon::conditional_t<hamon::derived_from_t<C, hamon::bidirectional_iterator_tag>::value,
				hamon::bidirectional_iterator_tag,
			hamon::conditional_t<hamon::derived_from_t<C, hamon::forward_iterator_tag>::value,
				hamon::forward_iterator_tag,
				hamon::input_iterator_tag
			>>>>;

		using iterator_concept = typename InnerIterator<Const>::iterator_concept;
		using value_type = hamon::remove_cvref_t<InvokeResult>;
		using difference_type = hamon::ranges::range_difference_t<Base>;

		iterator() = default;

		template <typename I2 = InnerIterator<Const>,
			typename = hamon::enable_if_t<
				Const && hamon::convertible_to_t<InnerIterator<false>, I2>::value>>
		HAMON_CXX11_CONSTEXPR
		iterator(iterator<!Const> i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_convertible<InnerIterator<false>, I2>::value)
			// [range.adjacent.transform.iterator]/3
			: m_parent(i.m_parent)
			, m_inner(hamon::move(i.m_inner))
		{}

	private:
		template <typename F2>
		struct dereference_fn
		{
			F2& fun;

			template <typename... Is>
			HAMON_CXX11_CONSTEXPR auto operator()(Is const&... iters) const
				HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::invoke(fun, *iters...))
		};

		template <typename F2, typename I2>
		static HAMON_CXX11_CONSTEXPR auto
		dereference_impl(F2& fun, I2 const& inner, hamon::detail::overload_priority<1>)
			// [range.adjacent.transform.iterator]/4
			HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::apply(	// noexcept as an extension
				dereference_fn<F2>{fun},
				hamon::ranges::detail::adjacent_view_iterator_access::get_current(inner)))

		template <typename F2, typename I2>
		static void
		dereference_impl(F2& fun, I2 const& inner, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT;

	public:
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator*() const
			HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
				dereference_impl(*m_parent->m_fun, m_inner, hamon::detail::overload_priority<1>{}))

		HAMON_CXX14_CONSTEXPR iterator&
		operator++() HAMON_NOEXCEPT_IF_EXPR(++m_inner)	// noexcept as an extension
		{
			// [range.adjacent.transform.iterator]/6
			++m_inner;
			return *this;
		}

		HAMON_CXX14_CONSTEXPR iterator
		operator++(int) HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_copy_constructible<iterator>::value &&
			HAMON_NOEXCEPT_EXPR(++*this))
		{
			// [range.adjacent.transform.iterator]/7
			auto tmp = *this;
			++*this;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator--() HAMON_NOEXCEPT_IF_EXPR(--m_inner)	// noexcept as an extension
		{
			// [range.adjacent.transform.iterator]/8
			--m_inner;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator
		operator--(int) HAMON_NOEXCEPT_IF(		// noexcept as an extension
			hamon::is_nothrow_copy_constructible<iterator>::value &&
			HAMON_NOEXCEPT_EXPR(--*this))
		{
			// [range.adjacent.transform.iterator]/9
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator+=(difference_type x)
			HAMON_NOEXCEPT_IF_EXPR(m_inner += x)	// noexcept as an extension
		{
			// [range.adjacent.transform.iterator]/10
			m_inner += x;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator-=(difference_type x)
			HAMON_NOEXCEPT_IF_EXPR(m_inner -= x)	// noexcept as an extension
		{
			// [range.adjacent.transform.iterator]/11
			m_inner -= x;
			return *this;
		}

	private:
		template <typename F2>
		struct subscript_fn
		{
			F2& fun;
			difference_type const& n;

			template <typename... Is>
			HAMON_CXX11_CONSTEXPR auto operator()(Is const&... iters) const
				HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::invoke(fun, iters[n]...))
		};

		template <typename F2, typename I2>
		static HAMON_CXX11_CONSTEXPR auto
		subscript_impl(difference_type n, F2& fun, I2 const& inner, hamon::detail::overload_priority<1>)
			// [range.adjacent.transform.iterator]/12
			HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::apply(	// noexcept as an extension
				subscript_fn<F2>{fun, n},
				hamon::ranges::detail::adjacent_view_iterator_access::get_current(inner)))

		template <typename F2, typename I2>
		static void
		subscript_impl(difference_type n, F2& fun, I2 const& inner, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT;

	public:
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator[](difference_type n) const
			HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
				subscript_impl(n, *m_parent->m_fun, m_inner, hamon::detail::overload_priority<1>{}))

	private:
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, iterator const& y)
			// [range.adjacent.transform.iterator]/14
			HAMON_NOEXCEPT_RETURN(x.m_inner == y.m_inner)	// noexcept as an extension

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))	// noexcept as an extension
#endif
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<(iterator const& x, iterator const& y)
			// [range.adjacent.transform.iterator]/14
			HAMON_NOEXCEPT_RETURN(x.m_inner < y.m_inner)	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>(iterator const& x, iterator const& y)
			// [range.adjacent.transform.iterator]/14
			HAMON_NOEXCEPT_RETURN(x.m_inner > y.m_inner)	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<=(iterator const& x, iterator const& y)
			// [range.adjacent.transform.iterator]/14
			HAMON_NOEXCEPT_RETURN(x.m_inner <= y.m_inner)	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>=(iterator const& x, iterator const& y)
			// [range.adjacent.transform.iterator]/14
			HAMON_NOEXCEPT_RETURN(x.m_inner >= y.m_inner)	// noexcept as an extension

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator<=>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_inner <=> y.m_inner)	// noexcept as an extension
			requires hamon::ranges::random_access_range<Base> &&
				hamon::three_way_comparable<InnerIterator<Const>>
		{
			// [range.adjacent.transform.iterator]/14
			return x.m_inner <=> y.m_inner;
		}
#endif
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator+(iterator const& i, difference_type n)
			// [range.adjacent.transform.iterator]/15
			HAMON_NOEXCEPT_RETURN(iterator(*i.m_parent, i.m_inner + n))	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator+(difference_type n, iterator const& i)
			// [range.adjacent.transform.iterator]/15
			HAMON_NOEXCEPT_RETURN(iterator(*i.m_parent, i.m_inner + n))	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator-(iterator const& i, difference_type n)
			// [range.adjacent.transform.iterator]/16
			HAMON_NOEXCEPT_RETURN(iterator(*i.m_parent, i.m_inner - n))	// noexcept as an extension

		template <HAMON_CONSTRAINED_PARAM_D(hamon::sized_sentinel_for, InnerIterator<Const>, I2, InnerIterator<Const>)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& x, iterator const& y)
			// [range.adjacent.transform.iterator]/17
			HAMON_NOEXCEPT_RETURN(x.m_inner - y.m_inner)	// noexcept as an extension
	};

	// [range.adjacent.transform.sentinel], class template adjacent_transform_view​::​sentinel
	template <bool Const>
	class sentinel
	{
	private:
		friend adjacent_transform_view;

		template <bool OtherConst>
		using InnerDifferenceT =
			hamon::ranges::range_difference_t<hamon::ranges::detail::maybe_const<OtherConst, InnerView>>;

		HAMON_NO_UNIQUE_ADDRESS InnerSentinel<Const> m_inner;

		HAMON_CXX11_CONSTEXPR explicit
		sentinel(InnerSentinel<Const> inner) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<InnerSentinel<Const>>::value)
			// [range.adjacent.transform.sentinel]/1
			: m_inner(hamon::move(inner))
		{}

	public:
		sentinel() = default;

		template <typename S2 = InnerSentinel<Const>,
			typename = hamon::enable_if_t<
				Const && hamon::convertible_to_t<InnerSentinel<false>, S2>::value>>
		HAMON_CXX11_CONSTEXPR
		sentinel(sentinel<!Const> i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_convertible<InnerSentinel<false>, S2>::value)
			// [range.adjacent.transform.sentinel]/2
			: m_inner(hamon::move(i.m_inner))
		{}

	private:
		template <bool OtherConst>
		HAMON_CXX11_CONSTEXPR bool
		equal_impl(iterator<OtherConst> const& x) const
			// [range.adjacent.transform.sentinel]/3
			HAMON_NOEXCEPT_RETURN(x.m_inner == m_inner)	// noexcept as an extension

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<InnerSentinel<Const>, InnerIterator<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_RETURN(y.equal_impl(x))	// noexcept as an extension

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<InnerSentinel<Const>, InnerIterator<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))	// noexcept as an extension

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<InnerSentinel<Const>, InnerIterator<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_RETURN(y == x)	// noexcept as an extension

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<InnerSentinel<Const>, InnerIterator<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_RETURN(!(x == y))	// noexcept as an extension
#endif
		template <bool OtherConst>
		HAMON_CXX11_CONSTEXPR InnerDifferenceT<OtherConst>
		distance_impl(iterator<OtherConst> const& x) const
			// [range.adjacent.transform.sentinel]/4
			HAMON_NOEXCEPT_RETURN(x.m_inner - m_inner)	// noexcept as an extension

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<InnerSentinel<Const>, InnerIterator<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		InnerDifferenceT<OtherConst>
		operator-(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_RETURN(y.distance_impl(x))	// noexcept as an extension

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<InnerSentinel<Const>, InnerIterator<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		InnerDifferenceT<OtherConst>
		operator-(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_RETURN(-x.distance_impl(y))	// noexcept as an extension
	};

public:
	adjacent_transform_view() = default;

	HAMON_CXX11_CONSTEXPR explicit
	adjacent_transform_view(V base, F fun) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value &&
		hamon::is_nothrow_move_constructible<F>::value)
		// [range.adjacent.transform.view]/1
		: m_fun(hamon::move(fun))
		, m_inner(hamon::move(base))
	{}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::copy_constructible, IV2, InnerView)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	V base() const& HAMON_NOEXCEPT_RETURN(	// noexcept as an extension
		m_inner.base())

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	V base() && HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
		hamon::move(m_inner).base())

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator<false> begin()
		HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
			iterator<false>(*this, m_inner.begin()))

	template <
		HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, IV2, InnerView const),
		typename V2 = V const, typename T = hamon::ranges::range_reference_t<V2>,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::regular_invocable_with_repeated_type_t<F const&, T, N>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	iterator<true> begin() const
		HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
			iterator<true>(*this, m_inner.begin()))

private:
	template <typename This, bool Const = hamon::is_const<This>::value,
		HAMON_CONSTRAINED_PARAM(hamon::ranges::common_range, IV2)>
	static HAMON_CXX11_CONSTEXPR iterator<Const>
	end_impl(This* this_, IV2& inner, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
			iterator<Const>(*this_, inner.end()))

	template <typename This, bool Const = hamon::is_const<This>::value,
		typename IV2>
	static HAMON_CXX11_CONSTEXPR sentinel<Const>
	end_impl(This*, IV2& inner, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
			sentinel<Const>(inner.end()))

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto end() HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		end_impl(this, m_inner, hamon::detail::overload_priority<1>{}))
	->decltype(end_impl(this, m_inner, hamon::detail::overload_priority<1>{}))
	{
		return end_impl(this, m_inner, hamon::detail::overload_priority<1>{});
	}

	template <
		HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, IV2, InnerView const),
		typename V2 = V const, typename T = hamon::ranges::range_reference_t<V2>,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::regular_invocable_with_repeated_type_t<F const&, T, N>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto end() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		end_impl(this, hamon::declval<IV2&>(), hamon::detail::overload_priority<1>{}))
	->decltype(end_impl(this, hamon::declval<IV2&>(), hamon::detail::overload_priority<1>{}))
	{
		return end_impl(this, m_inner, hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, IV2, InnerView)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	decltype(hamon::declval<IV2&>().size())
	size() HAMON_NOEXCEPT_RETURN(			// noexcept as an extension
		m_inner.size())

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, IV2, InnerView const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	decltype(hamon::declval<IV2&>().size())
	size() const HAMON_NOEXCEPT_RETURN(		// noexcept as an extension
		m_inner.size())
};

namespace views {

namespace detail {

// 26.7.27.1 Overview[range.adjacent_transform.transform.overview]

template <hamon::size_t N>
struct adjacent_transform_fn
{
private:
	template <typename R, typename F,
		hamon::size_t N2 = N, typename = hamon::enable_if_t<N2 == 0>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&&, F&& f, hamon::detail::overload_priority<1>)
		// [range.adjacent_transform.transform.overview]/2.1
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::views::zip_transform(hamon::forward<F>(f)))

	template <typename R, typename F>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, F&& f, hamon::detail::overload_priority<0>)
		// [range.adjacent_transform.transform.overview]/2.2
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::adjacent_transform_view<hamon::views::all_t<R>, hamon::decay_t<F>, N>(
				hamon::forward<R>(r), hamon::forward<F>(f)))

public:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R), typename F>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, F&& f) const
		// [range.adjacent_transform.transform.overview]/2
		HAMON_NOEXCEPT_DECLTYPE_RETURN(impl(
			hamon::forward<R>(r),
			hamon::forward<F>(f),
			hamon::detail::overload_priority<1>{}))

	template <typename F,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::decay_t<F>, F>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(F&& f) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::detail::make_range_adaptor(
				hamon::bind_back(*this, hamon::forward<F>(f))))
};

} // namespace detail

inline namespace cpo
{

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <hamon::size_t N>
HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::adjacent_transform_fn<N> adjacent_transform {};

#else

// variable templates が使えない場合は、関数として実装する。
template <hamon::size_t N, typename... Args>
HAMON_CXX11_CONSTEXPR auto adjacent_transform(Args&&... args)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		detail::adjacent_transform_fn<N>{}(hamon::forward<Args>(args)...))

#endif

HAMON_INLINE_VAR HAMON_CONSTEXPR
auto pairwise_transform = detail::adjacent_transform_fn<2> {};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN
#undef HAMON_NOEXCEPT_RETURN

#endif

#endif // HAMON_RANGES_ADAPTORS_ADJACENT_TRANSFORM_VIEW_HPP
