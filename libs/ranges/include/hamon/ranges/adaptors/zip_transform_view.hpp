/**
 *	@file	zip_transform_view.hpp
 *
 *	@brief	zip_transform_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_ZIP_TRANSFORM_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_ZIP_TRANSFORM_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_zip) && (__cpp_lib_ranges_zip >= 202110L)

#define HAMON_USE_STD_RANGES_ZIP_TRANSFORM_VIEW

namespace hamon {
namespace ranges {

using std::ranges::zip_transform_view;

namespace views {

using std::ranges::views::zip_transform;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/zip_view.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/detail/movable_box.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/factories/empty_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/regular_invocable.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/detail/can_reference.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/tuple/apply.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/is_void.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace hamon {
namespace ranges {

// 26.7.25.2 Class template zip_transform_view[range.zip.transform.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::move_constructible F, hamon::ranges::input_range... Views>
	requires
		(hamon::ranges::view<Views> && ...) &&
		(sizeof...(Views) > 0) &&
		hamon::is_object_v<F> &&
		hamon::regular_invocable<F&, hamon::ranges::range_reference_t<Views>...> &&
		hamon::detail::can_reference<hamon::invoke_result_t<F&, hamon::ranges::range_reference_t<Views>...>>
#else
// C++20 Concepts が使えないとき、
// テンプレートパラメータパックはテンプレートパラメータリストの最後でなければならないので、
// enable_if で制約することができない。
template <typename F, typename... Views>
#endif
class zip_transform_view : public hamon::ranges::view_interface<zip_transform_view<F, Views...>>
{
private:
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	static_assert(hamon::move_constructible_t<F>::value, "");
	static_assert(hamon::conjunction<hamon::ranges::input_range_t<Views>...>::value, "");
	static_assert(hamon::conjunction<hamon::ranges::view_t<Views>...>::value, "");
	static_assert(sizeof...(Views) > 0, "");
	static_assert(hamon::is_object<F>::value, "");
	static_assert(hamon::regular_invocable_t<F&, hamon::ranges::range_reference_t<Views>...>::value, "");
	static_assert(hamon::detail::can_reference<hamon::invoke_result_t<F&, hamon::ranges::range_reference_t<Views>...>>::value, "");
#endif

	HAMON_NO_UNIQUE_ADDRESS hamon::ranges::detail::movable_box<F> m_fun;
	HAMON_NO_UNIQUE_ADDRESS hamon::ranges::zip_view<Views...> m_zip;

	using InnerView = hamon::ranges::zip_view<Views...>;

	template <bool Const>
	using ziperator = hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, InnerView>>;
	template <bool Const>
	using zentinel = hamon::ranges::sentinel_t<hamon::ranges::detail::maybe_const<Const, InnerView>>;
	template <bool Const>
	using zifference = hamon::ranges::range_difference_t<hamon::ranges::detail::maybe_const<Const, InnerView>>;

	// [range.zip.transform.iterator]/1
	template <bool Const,
		bool = hamon::ranges::forward_range_t<hamon::ranges::detail::maybe_const<Const, InnerView>>::value>
	struct iterator_category_base
	{
	private:
		// [range.zip.transform.iterator]/1.1
		using R = hamon::invoke_result_t<
			hamon::ranges::detail::maybe_const<Const, F>&,
			hamon::ranges::range_reference_t<hamon::ranges::detail::maybe_const<Const, Views>>...>;

		// [range.zip.transform.iterator]/1.2
		template <typename View>
		using C = typename hamon::iterator_traits<
			hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, View>>
		>::iterator_category;

	public:
		using iterator_category =
			hamon::conditional_t<!hamon::is_reference<R>::value,
				hamon::input_iterator_tag,	// [range.zip.transform.iterator]/1.1
			hamon::conditional_t<hamon::conjunction<hamon::derived_from_t<C<Views>, hamon::random_access_iterator_tag>...>::value,
				hamon::random_access_iterator_tag,	// [range.zip.transform.iterator]/1.2.1
			hamon::conditional_t<hamon::conjunction<hamon::derived_from_t<C<Views>, hamon::bidirectional_iterator_tag>...>::value,
				hamon::bidirectional_iterator_tag,	// [range.zip.transform.iterator]/1.2.2
			hamon::conditional_t<hamon::conjunction<hamon::derived_from_t<C<Views>, hamon::forward_iterator_tag>...>::value,
				hamon::forward_iterator_tag,		// [range.zip.transform.iterator]/1.2.3
				hamon::input_iterator_tag			// [range.zip.transform.iterator]/1.2.4
			>>>>;
	};

	template <bool Const>
	struct iterator_category_base<Const, false>
	{};

	// [range.zip.transform.iterator], class template zip_transform_view​::​iterator
	template <bool Const>
	class iterator : public iterator_category_base<Const>
	{
	private:
		friend zip_transform_view;

		using Parent = hamon::ranges::detail::maybe_const<Const, zip_transform_view>;
		using Base = hamon::ranges::detail::maybe_const<Const, InnerView>;

		Parent* m_parent = nullptr;
		HAMON_NO_UNIQUE_ADDRESS ziperator<Const> m_inner;

		HAMON_CXX11_CONSTEXPR
		iterator(Parent& parent, ziperator<Const> inner) noexcept(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<ziperator<Const>>::value)
			// [range.zip.transform.iterator]/2
			: m_parent(hamon::addressof(parent))
			, m_inner(hamon::move(inner))
		{}

	public:
		//using iterator_category = see below;                        // not always present
		using iterator_concept = typename ziperator<Const>::iterator_concept;
		using value_type = hamon::remove_cvref_t<
			hamon::invoke_result_t<
				hamon::ranges::detail::maybe_const<Const, F>&,
				hamon::ranges::range_reference_t<hamon::ranges::detail::maybe_const<Const, Views>>...
			>>;
		using difference_type = hamon::ranges::range_difference_t<Base>;

		iterator() = default;

		template <bool C2 = Const,
			typename = hamon::enable_if_t<C2 &&
				hamon::convertible_to_t<ziperator<false>, ziperator<C2>>::value>>
		HAMON_CXX11_CONSTEXPR
		iterator(iterator<!Const> i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_convertible<ziperator<false>, ziperator<C2>>::value)
			// [range.zip.transform.iterator]/3
			: m_parent(i.m_parent)
			, m_inner(hamon::move(i.m_inner))
		{}

	private:
		struct dereference_fn
		{
			F const& fun;

			template <typename... Is>
			HAMON_CXX11_CONSTEXPR auto operator()(Is const&... iters) const
				HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::invoke(fun, *iters...))
		};

	public:
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator*() const
			// [range.zip.transform.iterator]/5
			// TODO
			//noexcept(noexcept(hamon::invoke(*m_parent->m_fun, *std​::​get<Is>(m_inner.current_)...)))
			// [range.zip.transform.iterator]/4
			HAMON_NOEXCEPT_DECLTYPE_RETURN(hamon::apply(
				dereference_fn{*m_parent->m_fun},
				hamon::ranges::detail::zip_view_iterator_access::get_current(m_inner)))

		HAMON_CXX14_CONSTEXPR iterator& operator++()
			HAMON_NOEXCEPT_IF_EXPR(++m_inner)	// noexcept as an extension
		{
			// [range.zip.transform.iterator]/6
			++m_inner;
			return *this;
		}

	private:
		HAMON_CXX14_CONSTEXPR void
		post_increment(hamon::detail::overload_priority<0>)
			HAMON_NOEXCEPT_IF_EXPR(++m_inner)	// noexcept as an extension
		{
			// [range.zip.transform.iterator]/7
			++m_inner;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator
		post_increment(hamon::detail::overload_priority<1>)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_copy_constructible<ziperator<Const>>::value &&
				HAMON_NOEXCEPT_EXPR(++m_inner))
		{
			// [range.zip.transform.iterator]/8
			auto tmp = *this;
			++m_inner;
			return tmp;
		}

	public:
		HAMON_CXX14_CONSTEXPR auto operator++(int)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			post_increment(hamon::detail::overload_priority<1>{}))

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator& operator--()
			HAMON_NOEXCEPT_IF_EXPR(--m_inner)	// noexcept as an extension
		{
			// [range.zip.transform.iterator]/9
			--m_inner;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator operator--(int)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_copy_constructible<ziperator<Const>>::value &&
				HAMON_NOEXCEPT_EXPR(--m_inner))
		{
			// [range.zip.transform.iterator]/10
			auto tmp = *this;
			--m_inner;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator& operator+=(difference_type x)
			HAMON_NOEXCEPT_IF_EXPR(m_inner += x)	// noexcept as an extension
		{
			// [range.zip.transform.iterator]/11
			m_inner += x;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator& operator-=(difference_type x)
			HAMON_NOEXCEPT_IF_EXPR(m_inner -= x)	// noexcept as an extension
		{
			// [range.zip.transform.iterator]/12
			m_inner -= x;
			return *this;
		}

	private:
		struct subscript_fn
		{
			F const& fun;
			difference_type const& n;

			template <typename... Is>
			HAMON_CXX11_CONSTEXPR auto operator()(Is const&... iters) const
			HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
				hamon::invoke(fun, iters[hamon::iter_difference_t<Is>(n)]...))
		};

		template <typename F2, typename I2>
		static HAMON_CXX11_CONSTEXPR auto
		subscript_impl(F2 const& fun, difference_type n, I2 const& iter, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
			hamon::apply(subscript_fn{fun, n}, iter))

		template <typename F2, typename I2>
		static void
		subscript_impl(F2 const& fun, difference_type n, I2 const& iter, hamon::detail::overload_priority<0>);

	public:
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator[](difference_type n) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(		// noexcept as an extension
			// [range.zip.transform.iterator]/13
			subscript_impl(*m_parent->m_fun, n,
				hamon::ranges::detail::zip_view_iterator_access::get_current(m_inner),
				hamon::detail::overload_priority<1>{}))

	private:
		template <HAMON_CONSTRAINED_PARAM_D(hamon::equality_comparable, I2, ziperator<Const>)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_inner == y.m_inner)	// noexcept as an extension
		{
			// [range.zip.transform.iterator]/14
			// [range.zip.transform.iterator]/15
			return x.m_inner == y.m_inner;
		}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator<=>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_inner <=> y.m_inner)	// noexcept as an extension
		{
			// [range.zip.transform.iterator]/14
			// [range.zip.transform.iterator]/15
			return x.m_inner <=> y.m_inner;
		}
#else

		template <HAMON_CONSTRAINED_PARAM_D(hamon::equality_comparable, I2, ziperator<Const>)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_inner < y.m_inner)	// noexcept as an extension
		{
			return x.m_inner < y.m_inner;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(y < x)	// noexcept as an extension
		{
			return y < x;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x > y))	// noexcept as an extension
		{
			return !(x > y);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x < y))	// noexcept as an extension
		{
			return !(x < y);
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator+(iterator const& i, difference_type n)
			HAMON_NOEXCEPT_IF_EXPR(iterator(*i.m_parent, i.m_inner + n))	// noexcept as an extension
		{
			// [range.zip.transform.iterator]/16
			return iterator(*i.m_parent, i.m_inner + n);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator+(difference_type n, iterator const& i)
			HAMON_NOEXCEPT_IF_EXPR(iterator(*i.m_parent, i.m_inner + n))	// noexcept as an extension
		{
			// [range.zip.transform.iterator]/16
			return iterator(*i.m_parent, i.m_inner + n);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator-(iterator const& i, difference_type n)
			HAMON_NOEXCEPT_IF_EXPR(iterator(*i.m_parent, i.m_inner - n))	// noexcept as an extension
		{
			// [range.zip.transform.iterator]/17
			return iterator(*i.m_parent, i.m_inner - n);
		}

		template <typename I2 = ziperator<Const>,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<I2, I2>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_inner - y.m_inner)	// noexcept as an extension
		{
			// [range.zip.transform.iterator]/18
			return x.m_inner - y.m_inner;
		}
	};

	// [range.zip.transform.sentinel], class template zip_transform_view​::​sentinel
	template <bool Const>
	class sentinel
	{
	private:
		friend zip_transform_view;

		HAMON_NO_UNIQUE_ADDRESS zentinel<Const> m_inner;

		HAMON_CXX11_CONSTEXPR explicit
		sentinel(zentinel<Const> inner) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<zentinel<Const>>::value)
			// [range.zip.transform.sentinel]/1
			: m_inner(inner)
		{}

	public:
		sentinel() = default;

		template <bool C2 = Const,
			typename = hamon::enable_if_t<C2 &&
				hamon::convertible_to_t<zentinel<false>, zentinel<C2>>::value>>
		HAMON_CXX11_CONSTEXPR
		sentinel(sentinel<!Const> i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_convertible<zentinel<false>, zentinel<C2>>::value)
			// [range.zip.transform.sentinel]/2
			: m_inner(hamon::move(i.m_inner))
		{}

	private:
		template <bool OtherConst>
		HAMON_CXX11_CONSTEXPR bool
		equal_impl(iterator<OtherConst> const& x) const
			HAMON_NOEXCEPT_IF_EXPR(x.m_inner == m_inner)	// noexcept as an extension
		{
			// [range.zip.transform.sentinel]/3
			return x.m_inner == m_inner;
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<zentinel<Const>, ziperator<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(y.equal_impl(x))	// noexcept as an extension
		{
			return y.equal_impl(x);
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<zentinel<Const>, ziperator<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<zentinel<Const>, ziperator<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)	// noexcept as an extension
		{
			return y == x;
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<zentinel<Const>, ziperator<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		template <bool OtherConst>
		HAMON_CXX11_CONSTEXPR zifference<OtherConst>
		distance_impl(iterator<OtherConst> const& x) const
			HAMON_NOEXCEPT_IF_EXPR(x.m_inner - m_inner)	// noexcept as an extension
		{
			// [range.zip.transform.sentinel]/4
			return x.m_inner - m_inner;
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<zentinel<Const>, ziperator<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		zifference<OtherConst>
		operator-(iterator<OtherConst> const& x, sentinel const& y)
		HAMON_NOEXCEPT_IF_EXPR(y.distance_impl(x))		// noexcept as an extension
		{
			return y.distance_impl(x);
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<zentinel<Const>, ziperator<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		zifference<OtherConst>
		operator-(sentinel const& x, iterator<OtherConst> const& y)
		HAMON_NOEXCEPT_IF_EXPR(-x.distance_impl(y))		// noexcept as an extension
		{
			return -x.distance_impl(y);
		}
	};

private:
	template <bool C2>
	using RegularInvocable =
		hamon::regular_invocable_t<
			F const&,
			hamon::ranges::range_reference_t<
				hamon::ranges::detail::maybe_const<C2, Views>
			>...
		>;

	template <typename>
	struct always_true : public hamon::true_type {};

public:
	zip_transform_view() = default;

	HAMON_CXX11_CONSTEXPR explicit
	zip_transform_view(F fun, Views... views)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<F>::value &&
			hamon::is_nothrow_constructible<InnerView, hamon::remove_reference_t<Views>&&...>::value)
		// [range.zip.transform.view]/1
		: m_fun(hamon::move(fun))
		, m_zip(hamon::move(views)...)
	{}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator<false> begin()
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			iterator<false>(*this, m_zip.begin()))
	{
		return iterator<false>(*this, m_zip.begin());
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, InnerView const),
		typename = hamon::enable_if_t<RegularInvocable<always_true<V2>::value>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	iterator<true> begin() const
		HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
			iterator<true>(*this, m_zip.begin()))
	{
		return iterator<true>(*this, m_zip.begin());
	}

private:
	template <typename This, typename V2,
		bool Const = hamon::is_const<This>::value,
		typename = hamon::enable_if_t<
			hamon::ranges::common_range_t<V2>::value &&
			RegularInvocable<Const>::value>>
	static HAMON_CXX11_CONSTEXPR iterator<Const>
	end_impl(This* this_, V2& zip, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_IF_EXPR(iterator<Const>(*this_, zip.end()))	// noexcept as an extension
	{
		return iterator<Const>(*this_, zip.end());
	}

	template <typename This, typename V2,
		bool Const = hamon::is_const<This>::value,
		typename = hamon::enable_if_t<
			hamon::ranges::range_t<V2>::value &&
			RegularInvocable<Const>::value>>
	static HAMON_CXX11_CONSTEXPR sentinel<Const>
	end_impl(This* /*this_*/, V2& zip, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(sentinel<Const>(zip.end()))	// noexcept as an extension
	{
		return sentinel<Const>(zip.end());
	}

	template <typename This, typename V2>
	static void end_impl(This*, V2&, hamon::detail::overload_priority<0>);

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto // nodiscard as an extension
	end() HAMON_NOEXCEPT_DECLTYPE_RETURN(      // noexcept as an extension
		end_impl(this, m_zip, hamon::detail::overload_priority<2>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, InnerView const),
		typename = hamon::enable_if_t<RegularInvocable<always_true<V2>::value>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto  // nodiscard as an extension
	end() const HAMON_NOEXCEPT_DECLTYPE_RETURN( // noexcept as an extension
		end_impl(this, m_zip, hamon::detail::overload_priority<2>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, InnerView)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto  // nodiscard as an extension
	size() HAMON_NOEXCEPT_IF_EXPR(m_zip.size()) // noexcept as an extension
	->decltype(hamon::declval<V2&>().size())
	{
		return m_zip.size();
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, InnerView const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto        // nodiscard as an extension
	size() const HAMON_NOEXCEPT_IF_EXPR(m_zip.size()) // noexcept as an extension
	->decltype(hamon::declval<V2&>().size())
	{
		return m_zip.size();
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename F, typename... Rs>
zip_transform_view(F, Rs&&...) -> zip_transform_view<F, hamon::views::all_t<Rs>...>;

#endif

namespace views {

namespace detail {

// 26.7.25.1 Overview[range.zip.transform.overview]

struct zip_transform_fn
{
private:
	template <typename F,
		// [range.zip.transform.overview]/2.1
		typename FD = hamon::decay_t<F>,
		typename R = hamon::decay_t<hamon::invoke_result_t<FD&>>,
		// [range.zip.transform.overview]2.1.1
		typename = hamon::enable_if_t<
			hamon::move_constructible_t<FD>::value &&
			hamon::regular_invocable_t<FD&>::value &&
			!hamon::is_void<R>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(hamon::detail::overload_priority<1>, F&& /*f*/)
		// [range.zip.transform.overview]2.1.2
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::ranges::empty_view<R>{})

	template <typename F, typename... Args,
		typename = hamon::enable_if_t<(sizeof...(Args) > 0)>,
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		typename = hamon::enable_if_t<hamon::regular_invocable_t<
			F&, hamon::ranges::range_reference_t<hamon::views::all_t<Args>>...>::value>,
		typename = hamon::enable_if_t<hamon::detail::can_reference<hamon::invoke_result_t<
			F&, hamon::ranges::range_reference_t<hamon::views::all_t<Args>>...>>::value>,
#endif
		typename ZTV = hamon::ranges::zip_transform_view<F, hamon::views::all_t<Args>...>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(hamon::detail::overload_priority<0>, F&& f, Args&&... args)
		// [range.zip.transform.overview]2.2
		HAMON_NOEXCEPT_DECLTYPE_RETURN(ZTV(
			hamon::forward<F>(f),
			hamon::forward<Args>(args)...))

public:
	template <typename F, typename... Args>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	auto operator()(F&& f, Args&&... args) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(impl(
			hamon::detail::overload_priority<1>{},
			hamon::forward<F>(f),
			hamon::forward<Args>(args)...))
};

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::zip_transform_fn zip_transform{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

#endif

#endif // HAMON_RANGES_ADAPTORS_ZIP_TRANSFORM_VIEW_HPP
