/**
 *	@file	transform_view.hpp
 *
 *	@brief	transform_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_TRANSFORM_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_TRANSFORM_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::transform_view;

namespace views {

using std::ranges::views::transform;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/detail/movable_box.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/regular_invocable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/functional/invoke.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/contiguous_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// 26.7.9.2 Class template transform_view[range.transform.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::input_range V, hamon::move_constructible F>
	requires
		hamon::ranges::view<V> && hamon::is_object_v<F> &&
		hamon::regular_invocable<F&, hamon::ranges::range_reference_t<V>> &&
		hamon::detail::can_reference<hamon::invoke_result_t<F&, hamon::ranges::range_reference_t<V>>>
#else
template <typename V, typename F,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::input_range<V>,
		hamon::move_constructible<F>,
		hamon::ranges::view<V>,
		hamon::is_object<F>,
		hamon::regular_invocable<F&, hamon::ranges::range_reference_t<V>>,
		hamon::detail::can_reference<hamon::invoke_result_t<F&, hamon::ranges::range_reference_t<V>>>
	>::value>
>
#endif
class transform_view : public hamon::ranges::view_interface<transform_view<V, F>>
{
private:
	template <bool Const>
	struct sentinel;

	template <bool Const, typename Base, typename = void>
	struct iterator_category_base {};

	// [range.transform.iterator]/2
	template <bool Const, typename Base>
	struct iterator_category_base<Const, Base, hamon::enable_if_t<hamon::ranges::forward_range_t<Base>::value>>
	{
	private:
		// [range.transform.iterator]/2
		using C = typename hamon::iterator_traits<
			hamon::ranges::iterator_t<Base>
		>::iterator_category;

		using InvokeResult = hamon::invoke_result_t<
			hamon::ranges::detail::maybe_const<Const, F>&,
			hamon::ranges::range_reference_t<Base>>;

	public:
		using iterator_category =
			hamon::conditional_t<hamon::is_reference<InvokeResult>::value,
				hamon::conditional_t<hamon::derived_from_t<C, hamon::contiguous_iterator_tag>::value,
					hamon::random_access_iterator_tag,	// [range.transform.iterator]/2.1.1
					C									// [range.transform.iterator]/2.1.2
				>,
				hamon::input_iterator_tag				// [range.transform.iterator]/2.2
			>;
	};

	// [range.transform.iterator], class template transform_view​::​iterator
	template <bool Const>
	struct iterator : public iterator_category_base<Const, hamon::ranges::detail::maybe_const<Const, V>>
	{
#if defined(HAMON_MSVC) || \
	defined(HAMON_GCC_VERSION) && (HAMON_GCC_VERSION < 130000)
		// MSVCとGCC(12まで)は、friend指定してもエラーになってしまうので、
		// 仕方なくpublicにする。
	public:
#else
	private:
		friend iterator<!Const>;
		friend sentinel<Const>;
#endif
		using Parent = hamon::ranges::detail::maybe_const<Const, transform_view>;
		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using I = hamon::ranges::iterator_t<Base>;
		using InvokeResult = hamon::invoke_result_t<
			hamon::ranges::detail::maybe_const<Const, F>&,
			hamon::ranges::range_reference_t<Base>>;

		I m_current = I();
		Parent* m_parent = nullptr;

	public:
		using iterator_concept =
			hamon::conditional_t<hamon::ranges::random_access_range_t<Base>::value,
				hamon::random_access_iterator_tag,	// [range.transform.iterator]/1.1
			hamon::conditional_t<hamon::ranges::bidirectional_range_t<Base>::value,
				hamon::bidirectional_iterator_tag,	// [range.transform.iterator]/1.2
			hamon::conditional_t<hamon::ranges::forward_range_t<Base>::value,
				hamon::forward_iterator_tag,		// [range.transform.iterator]/1.3
				hamon::input_iterator_tag			// [range.transform.iterator]/1.4
		>>>;
		//using iterator_category = see below;                        // not always present
		using value_type = hamon::remove_cvref_t<InvokeResult>;
		using difference_type = hamon::ranges::range_difference_t<Base>;

#if defined(HAMON_HAS_CXX20_CONCEPTS)
		iterator() requires hamon::default_initializable<I> = default;
#else
		template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, I2, I)>
		HAMON_CXX11_CONSTEXPR
		iterator() HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_default_constructible<I2>::value)
		{}
#endif

		HAMON_CXX11_CONSTEXPR
		iterator(Parent& parent, I current) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<I>::value)
			// [range.transform.iterator]/3
			: m_current(hamon::move(current))
			, m_parent(hamon::addressof(parent))
		{}
		
		template <typename I2 = I,
			typename = hamon::enable_if_t<Const &&
				hamon::convertible_to_t<hamon::ranges::iterator_t<V>, I2>::value>>
		HAMON_CXX11_CONSTEXPR
		iterator(iterator<!Const> i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_constructible<I, hamon::ranges::iterator_t<V>>::value)
			// [range.transform.iterator]/4
			: m_current(hamon::move(i.m_current))
			, m_parent(i.m_parent)
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		I const& base() const& HAMON_NOEXCEPT
		{
			// [range.transform.iterator]/5
			return m_current;
		}

		HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		I base() && HAMON_NOEXCEPT_IF(			// noexcept as an extension
			hamon::is_nothrow_move_constructible<I>::value)
		{
			// [range.transform.iterator]/6
			return hamon::move(m_current);
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator*() const
			HAMON_NOEXCEPT_IF_EXPR(hamon::invoke(*m_parent->m_fun, *m_current))
		->decltype(hamon::invoke(*m_parent->m_fun, *m_current))
		{
			return hamon::invoke(*m_parent->m_fun, *m_current);
		}

		HAMON_CXX14_CONSTEXPR
		iterator& operator++()
			HAMON_NOEXCEPT_IF_EXPR(++m_current)	// noexcept as an extension
		{
			// [range.transform.iterator]/7
			++m_current;
			return *this;
		}

	private:
		HAMON_CXX14_CONSTEXPR void
		increment_impl(hamon::detail::overload_priority<0>)
			HAMON_NOEXCEPT_IF_EXPR(++m_current)
		{
			// [range.transform.iterator]/8
			++m_current;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator
		increment_impl(hamon::detail::overload_priority<1>)
			HAMON_NOEXCEPT_IF(
				HAMON_NOEXCEPT_EXPR(++m_current) &&
				hamon::is_nothrow_copy_constructible<I>::value)
		{
			// [range.transform.iterator]/9
			auto tmp = *this;
			++*this;
			return tmp;
		}

	public:
		HAMON_CXX14_CONSTEXPR
		auto operator++(int) HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			increment_impl(hamon::detail::overload_priority<1>{}))
		->decltype(increment_impl(hamon::detail::overload_priority<1>{}))
		{
			return increment_impl(hamon::detail::overload_priority<1>{});
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR
		iterator& operator--()
			HAMON_NOEXCEPT_IF_EXPR(--m_current)	// noexcept as an extension
		{
			// [range.transform.iterator]/10
			--m_current;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR
		iterator operator--(int) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(--m_current) &&
			hamon::is_nothrow_copy_constructible<I>::value)
		{
			// [range.transform.iterator]/11
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR
		iterator& operator+=(difference_type n)
			HAMON_NOEXCEPT_IF_EXPR(m_current += n)	// noexcept as an extension
		{
			// [range.transform.iterator]/12
			m_current += n;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR
		iterator& operator-=(difference_type n)
			HAMON_NOEXCEPT_IF_EXPR(m_current -= n)	// noexcept as an extension
		{
			// [range.transform.iterator]/13
			m_current -= n;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		auto operator[](difference_type n) const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
			hamon::invoke(*m_parent->m_fun, hamon::declval<hamon::ranges::iterator_t<B2>>()[n]))
		->decltype(hamon::invoke(*m_parent->m_fun, hamon::declval<hamon::ranges::iterator_t<B2>>()[n]))
		{
			return hamon::invoke(*m_parent->m_fun, m_current[n]);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::equality_comparable, I2, I)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool		// nodiscard as an extension
		operator==(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current == y.m_current)	// noexcept as an extension
		{
			// [range.transform.iterator]/14
			return x.m_current == y.m_current;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <HAMON_CONSTRAINED_PARAM_D(hamon::equality_comparable, I2, I)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))				// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool		// nodiscard as an extension
		operator<(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current < y.m_current)	// noexcept as an extension
		{
			// [range.transform.iterator]/15
			return x.m_current < y.m_current;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(y < x)					// noexcept as an extension
		{
			// [range.transform.iterator]/16
			return y < x;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator<=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(y < x))				// noexcept as an extension
		{
			// [range.transform.iterator]/17
			return !(y < x);
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator>=(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x < y))				// noexcept as an extension
		{
			// [range.transform.iterator]/18
			return !(x < y);
		}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
		operator<=>(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current <=> y.m_current)	// noexcept as an extension
			requires hamon::ranges::random_access_range<Base> &&
				hamon::three_way_comparable<I>
		{
			// [range.transform.iterator]/19
			return x.m_current <=> y.m_current;
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator+(iterator i, difference_type n)
			HAMON_NOEXCEPT_IF_EXPR(i.m_current + n)		// noexcept as an extension
		{
			// [range.transform.iterator]/20
			return iterator{*i.m_parent, i.m_current + n};
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator+(difference_type n, iterator i)
			HAMON_NOEXCEPT_IF_EXPR(i.m_current + n)		// noexcept as an extension
		{
			// [range.transform.iterator]/20
			return iterator{*i.m_parent, i.m_current + n};
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		iterator operator-(iterator i, difference_type n)
			HAMON_NOEXCEPT_IF_EXPR(i.m_current - n)		// noexcept as an extension
		{
			// [range.transform.iterator]/21
			return iterator{*i.m_parent, i.m_current - n};
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::sized_sentinel_for, I, I2, I)>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current - y.m_current)	// noexcept as an extension
		{
			// [range.transform.iterator]/22
			return x.m_current - y.m_current;
		}
	};

	// [range.transform.sentinel], class template transform_view​::​sentinel
	template <bool Const>
	struct sentinel
	{
	private:
		friend sentinel<!Const>;

		using Parent = hamon::ranges::detail::maybe_const<Const, transform_view>;
		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using Sent = hamon::ranges::sentinel_t<Base>;

		Sent m_end = Sent();

	public:
		sentinel() = default;
		
		HAMON_CXX11_CONSTEXPR explicit
		sentinel(Sent end) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<Sent>::value)
			// [range.transform.sentinel]/1
			: m_end(hamon::move(end))
		{}
		
		template <typename Sent2 = Sent,
			typename = hamon::enable_if_t<Const &&
				hamon::convertible_to_t<hamon::ranges::sentinel_t<V>, Sent2>::value>>
		HAMON_CXX11_CONSTEXPR
		sentinel(sentinel<!Const> i) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_constructible<Sent, hamon::ranges::sentinel_t<V>>::value)
			// [range.transform.sentinel]/2
			: m_end(hamon::move(i.m_end))
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR Sent	// nodiscard as an extension
		base() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<Sent>::value)
		{
			// [range.transform.sentinel]/3
			return m_end;
		}

		template <bool OtherConst,
			typename OtherV = hamon::ranges::detail::maybe_const<OtherConst, V>,
			typename I2 = hamon::ranges::iterator_t<OtherV>,
			typename = hamon::enable_if_t<hamon::sentinel_for_t<Sent, I2>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current == y.m_end)	// noexcept as an extension
		{
			// [range.transform.sentinel]/4
			return x.m_current == y.m_end;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool OtherConst,
			typename OtherV = hamon::ranges::detail::maybe_const<OtherConst, V>,
			typename I2 = hamon::ranges::iterator_t<OtherV>,
			typename = hamon::enable_if_t<hamon::sentinel_for_t<Sent, I2>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}

		template <bool OtherConst,
			typename OtherV = hamon::ranges::detail::maybe_const<OtherConst, V>,
			typename I2 = hamon::ranges::iterator_t<OtherV>,
			typename = hamon::enable_if_t<hamon::sentinel_for_t<Sent, I2>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)	// noexcept as an extension
		{
			return y == x;
		}

		template <bool OtherConst,
			typename OtherV = hamon::ranges::detail::maybe_const<OtherConst, V>,
			typename I2 = hamon::ranges::iterator_t<OtherV>,
			typename = hamon::enable_if_t<hamon::sentinel_for_t<Sent, I2>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		template <bool OtherConst,
			typename OtherV = hamon::ranges::detail::maybe_const<OtherConst, V>,
			typename I2 = hamon::ranges::iterator_t<OtherV>,
			typename = hamon::enable_if_t<hamon::sized_sentinel_for_t<Sent, I2>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::range_difference_t<OtherV>
		operator-(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_current - y.m_end)	// noexcept as an extension
		{
			// [range.transform.sentinel]/5
			return x.m_current - y.m_end;
		}

		template <bool OtherConst,
			typename OtherV = hamon::ranges::detail::maybe_const<OtherConst, V>,
			typename I2 = hamon::ranges::iterator_t<OtherV>,
			typename = hamon::enable_if_t<hamon::sized_sentinel_for_t<Sent, I2>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::ranges::range_difference_t<OtherV>
		operator-(sentinel const& y, iterator<OtherConst> const& x)
			HAMON_NOEXCEPT_IF_EXPR(y.m_end - x.m_current)	// noexcept as an extension
		{
			// [range.transform.sentinel]/6
			return y.m_end - x.m_current;
		}
	};

	HAMON_NO_UNIQUE_ADDRESS	V m_base = V();
	HAMON_NO_UNIQUE_ADDRESS	hamon::ranges::detail::movable_box<F> m_fun;

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	transform_view()
		requires
			hamon::default_initializable<V> &&
			hamon::default_initializable<F>
	= default;
#else
	template <
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V),
		HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, F2, F)>
	HAMON_CXX11_CONSTEXPR
	transform_view()
		HAMON_NOEXCEPT_IF(
			hamon::is_nothrow_default_constructible<V>::value &&
			hamon::is_nothrow_default_constructible<F>::value)
	{}
#endif
	
	HAMON_CXX11_CONSTEXPR explicit
	transform_view(V base, F fun)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<V>::value &&
			hamon::is_nothrow_move_constructible<F>::value)
		// [range.transform.view]/1
		: m_base(hamon::move(base))
		, m_fun(hamon::move(fun))
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

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	iterator<false> begin() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(m_base)) &&
		hamon::is_nothrow_move_constructible<decltype(hamon::ranges::begin(m_base))>::value)
	{
		// [range.transform.view]/2
		return iterator<false>{*this, hamon::ranges::begin(m_base)};
	}

	template <typename V2 = V const,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::range_t<V2>,
			hamon::regular_invocable_t<F const&, hamon::ranges::range_reference_t<V2>>
		>::value>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR			// nodiscard as an extension
	iterator<true> begin() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(m_base)) &&
		hamon::is_nothrow_move_constructible<decltype(hamon::ranges::begin(m_base))>::value)
	{
		// [range.transform.view]/3
		return iterator<true>{*this, hamon::ranges::begin(m_base)};
	}

private:
	HAMON_CXX14_CONSTEXPR sentinel<false>
	end_impl(hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_IF_EXPR(sentinel<false>{hamon::ranges::end(m_base)})
	{
		// [range.transform.view]/4
		return sentinel<false>{hamon::ranges::end(m_base)};
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::common_range, V2, V)>
	HAMON_CXX14_CONSTEXPR iterator<false>
	end_impl(hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_IF_EXPR(iterator<false>{*this, hamon::ranges::end(m_base)})
	{
		// [range.transform.view]/5
		return iterator<false>{*this, hamon::ranges::end(m_base)};
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_CXX11_CONSTEXPR sentinel<true>
	end_const_impl(hamon::detail::overload_priority<0>) const
		HAMON_NOEXCEPT_IF_EXPR(sentinel<true>{hamon::ranges::end(m_base)})
	{
		// [range.transform.view]/6
		return sentinel<true>{hamon::ranges::end(m_base)};
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::common_range, V2, V const)>
	HAMON_CXX11_CONSTEXPR iterator<true>
	end_const_impl(hamon::detail::overload_priority<1>) const
		HAMON_NOEXCEPT_IF_EXPR(iterator<true>{*this, hamon::ranges::end(m_base)})
	{
		// [range.transform.view]/7
		return iterator<true>{*this, hamon::ranges::end(m_base)};
	}

public:
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR		// nodiscard as an extension
	auto end() HAMON_NOEXCEPT_IF_EXPR(			// noexcept as an extension
		end_impl(hamon::detail::overload_priority<1>{}))
	->decltype(end_impl(hamon::detail::overload_priority<1>{}))
	{
		return end_impl(hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const),
		typename = hamon::enable_if_t<
			hamon::regular_invocable_t<F const&, hamon::ranges::range_reference_t<V2>>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto end() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		end_const_impl<V2>(hamon::detail::overload_priority<1>{}))
	->decltype(end_const_impl<V2>(hamon::detail::overload_priority<1>{}))
	{
		return end_const_impl<V2>(hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR 		// nodiscard as an extension
	auto size() HAMON_NOEXCEPT_IF_EXPR(			// noexcept as an extension
		hamon::ranges::size(hamon::declval<V2>()))
	->decltype(hamon::ranges::size(hamon::declval<V2>()))
	{
		return hamon::ranges::size(m_base);
	}
	
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto size() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		hamon::ranges::size(hamon::declval<V2>()))
	->decltype(hamon::ranges::size(hamon::declval<V2>()))
	{
		return hamon::ranges::size(m_base);
	}
};

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R, typename F>
transform_view(R&&, F) -> transform_view<hamon::views::all_t<R>, F>;

#endif

// extension: deduction guides が使えないときのために追加
template <typename R, typename F>
HAMON_CXX11_CONSTEXPR auto
make_transform_view(R&& r, F f)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		transform_view<hamon::views::all_t<R>, F>(hamon::forward<R>(r), f))

namespace views {

namespace detail {

struct transform_fn
{
public:
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R), typename F>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, F&& f) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::make_transform_view(
			hamon::forward<R>(r), hamon::forward<F>(f)))

	template <typename F,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::decay_t<F>, F
		>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(F&& f) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::detail::make_range_adaptor(
			hamon::bind_back(*this, hamon::forward<F>(f))))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::transform_fn transform{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_TRANSFORM_VIEW_HPP
