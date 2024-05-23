/**
 *	@file	enumerate_view.hpp
 *
 *	@brief	enumerate_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_ENUMERATE_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_ENUMERATE_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES) && \
	defined(__cpp_lib_ranges_enumerate) && (__cpp_lib_ranges_enumerate >= 202302L)

namespace hamon {
namespace ranges {

using std::ranges::enumerate_view;

namespace views {

using std::ranges::views::enumerate;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/bidirectional_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/forward_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/range_value_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/compare/strong_ordering.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename R>
concept range_with_movable_references =
	hamon::ranges::input_range<R> &&
	hamon::move_constructible<hamon::ranges::range_reference_t<R>> &&
	hamon::move_constructible<hamon::ranges::range_rvalue_reference_t<R>>;

#else

template <typename R>
struct range_with_movable_references_impl
{
private:
	template <typename R2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::input_range_t<R2>,
			hamon::move_constructible_t<hamon::ranges::range_reference_t<R2>>,
			hamon::move_constructible_t<hamon::ranges::range_rvalue_reference_t<R2>>
		>::value>>
	static auto test(int) -> hamon::true_type;

	template <typename R2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<R>(0));
};

template <typename R>
using range_with_movable_references =
	typename range_with_movable_references_impl<R>::type;

#endif

}	// namespace detail

inline namespace enumerate_view_ns
{

// 26.7.23.2 Class template enumerate_view[range.enumerate.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::view V>
	requires hamon::ranges::detail::range_with_movable_references<V>
#else
template <typename V,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::view_t<V>,
		hamon::ranges::detail::range_with_movable_references<V>
	>::value>>
#endif
class enumerate_view : public hamon::ranges::view_interface<enumerate_view<V>>
{
private:
	HAMON_NO_UNIQUE_ADDRESS V m_base = V();

	// [range.enumerate.iterator], class template enumerate_view​::​iterator
	template <bool Const>
	class iterator
	{
	private:
		friend enumerate_view;

		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using BaseIter = hamon::ranges::iterator_t<Base>;
		using BaseReference = hamon::ranges::range_reference_t<Base>;
		using BaseRvalueReference = hamon::ranges::range_rvalue_reference_t<Base>;

	public:
		using iterator_category = hamon::input_iterator_tag;
		using iterator_concept =
			hamon::conditional_t<hamon::ranges::random_access_range_t<Base>::value,
				hamon::random_access_iterator_tag,
			hamon::conditional_t<hamon::ranges::bidirectional_range_t<Base>::value,
				hamon::bidirectional_iterator_tag,
			hamon::conditional_t<hamon::ranges::forward_range_t<Base>::value,
				hamon::forward_iterator_tag,
				hamon::input_iterator_tag
			>>>;
		using difference_type = hamon::ranges::range_difference_t<Base>;
		using value_type = hamon::tuple<difference_type, hamon::ranges::range_value_t<Base>>;

	private:
		using reference_type =
			hamon::tuple<difference_type, BaseReference>;

		HAMON_NO_UNIQUE_ADDRESS BaseIter m_current = BaseIter();
		difference_type m_pos = 0;

		HAMON_CXX11_CONSTEXPR explicit
		iterator(BaseIter current, difference_type pos)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_move_constructible<BaseIter>::value)
			// [range.enumerate.iterator]/2
			: m_current(hamon::move(current))
			, m_pos(pos)
		{}

	public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
		iterator()
			requires hamon::default_initializable<BaseIter>
		= default;
#else
		template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, I2, BaseIter)>
		HAMON_CXX11_CONSTEXPR iterator()
			HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<BaseIter>::value)
		{}
#endif

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
			// [range.enumerate.iterator]/3
			: m_current(hamon::move(i.m_current))
			, m_pos(i.m_pos)
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		BaseIter const& base() const& HAMON_NOEXCEPT
		{
			// [range.enumerate.iterator]/4
			return m_current;
		}

		HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		BaseIter base() && HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<BaseIter>::value)
		{
			// [range.enumerate.iterator]/5
			return hamon::move(m_current);
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type index() const HAMON_NOEXCEPT
		{
			// [range.enumerate.iterator]/6
			return m_pos;
		}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		reference_type operator*() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
            HAMON_NOEXCEPT_EXPR(*hamon::declval<BaseIter const&>()) &&
			hamon::is_nothrow_copy_constructible<BaseReference>::value)
		{
			return reference_type(m_pos, *m_current);
		}

		HAMON_CXX14_CONSTEXPR iterator&
		operator++() HAMON_NOEXCEPT_IF_EXPR(++hamon::declval<BaseIter&>())	// noexcept as an extension
		{
			// [range.enumerate.iterator]/7
			++m_current;
			++m_pos;
			return *this;
		}

	private:
		HAMON_CXX14_CONSTEXPR void
		post_increment_impl(hamon::detail::overload_priority<0>)
			HAMON_NOEXCEPT_IF_EXPR(++hamon::declval<BaseIter&>())	// noexcept as an extension
		{
			// [range.enumerate.iterator]/8
			++*this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::forward_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator
		post_increment_impl(hamon::detail::overload_priority<1>)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(++hamon::declval<BaseIter&>()) &&
				hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
			// [range.enumerate.iterator]/9
			auto temp = *this;
			++*this;
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
		operator--() HAMON_NOEXCEPT_IF_EXPR(--hamon::declval<BaseIter&>())	// noexcept as an extension
		{
			// [range.enumerate.iterator]/10
			--m_current;
			--m_pos;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::bidirectional_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator
		operator--(int) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			HAMON_NOEXCEPT_EXPR(--hamon::declval<BaseIter&>()) &&
			hamon::is_nothrow_copy_constructible<BaseIter>::value)
		{
			// [range.enumerate.iterator]/11
			auto temp = *this;
			--*this;
			return temp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator+=(difference_type n)
			HAMON_NOEXCEPT_IF_EXPR(hamon::declval<BaseIter&>() += n)	// noexcept as an extension
		{
			// [range.enumerate.iterator]/12
			m_current += n;
			m_pos += n;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_CXX14_CONSTEXPR iterator&
		operator-=(difference_type n)
			HAMON_NOEXCEPT_IF_EXPR(hamon::declval<BaseIter&>() -= n)	// noexcept as an extension
		{
			// [range.enumerate.iterator]/13
			m_current -= n;
			m_pos -= n;
			return *this;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		reference_type operator[](difference_type n) const
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(hamon::declval<BaseIter const&>()[n]) &&
				hamon::is_nothrow_copy_constructible<BaseReference>::value)
		{
			return reference_type(m_pos + n, m_current[n]);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator==(iterator const& x, iterator const& y) HAMON_NOEXCEPT
		{
			// [range.enumerate.iterator]/14
			return x.m_pos == y.m_pos;
		}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::strong_ordering
		operator<=>(iterator const& x, iterator const& y) HAMON_NOEXCEPT
		{
			// [range.enumerate.iterator]/15
			return x.m_pos <=> y.m_pos;
		}
#else
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator!=(iterator const& x, iterator const& y) HAMON_NOEXCEPT
		{
			return !(x == y);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<(iterator const& x, iterator const& y) HAMON_NOEXCEPT
		{
			return x.m_pos < y.m_pos;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>(iterator const& x, iterator const& y) HAMON_NOEXCEPT
		{
			return y < x;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator<=(iterator const& x, iterator const& y) HAMON_NOEXCEPT
		{
			return !(x > y);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		bool operator>=(iterator const& x, iterator const& y) HAMON_NOEXCEPT
		{
			return !(x < y);
		}
#endif

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator+(iterator const& x, difference_type y)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(hamon::declval<iterator&>() += y) &&
				hamon::is_nothrow_copy_constructible<iterator>::value)
		{
			// [range.enumerate.iterator]/16
			auto temp = x;
			temp += y;
			return temp;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator+(difference_type x, iterator const& y)
			HAMON_NOEXCEPT_IF_EXPR(y + x)	// noexcept as an extension
		{
			// [range.enumerate.iterator]/17
			return y + x;
		}

		template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::random_access_range, B2, Base)>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator-(iterator const& x, difference_type y)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				HAMON_NOEXCEPT_EXPR(hamon::declval<iterator&>() -= y) &&
				hamon::is_nothrow_copy_constructible<iterator>::value)
		{
			// [range.enumerate.iterator]/18
			auto temp = x;
			temp -= y;
			return temp;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(iterator const& x, iterator const& y) HAMON_NOEXCEPT
		{
			// [range.enumerate.iterator]/19
			return x.m_pos - y.m_pos;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		hamon::tuple<difference_type, BaseRvalueReference>
		iter_move(iterator const& i) HAMON_NOEXCEPT_IF(
			HAMON_NOEXCEPT_EXPR(hamon::ranges::iter_move(i.m_current)) &&
			hamon::is_nothrow_move_constructible<BaseRvalueReference>::value)
		{
			return hamon::tuple<difference_type, BaseRvalueReference>(
				i.m_pos, hamon::ranges::iter_move(i.m_current));
		}
	};

	// [range.enumerate.sentinel], class template enumerate_view​::​sentinel
	template <bool Const>
	class sentinel
	{
	private:
		friend enumerate_view;

		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using BaseSent = hamon::ranges::sentinel_t<Base>;

		template <bool OtherConst>
		using BaseIterT =
			hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<OtherConst, V>>;

		template <bool OtherConst>
		using BaseDifferenceT =
			hamon::ranges::range_difference_t<hamon::ranges::detail::maybe_const<OtherConst, V>>;

		HAMON_NO_UNIQUE_ADDRESS BaseSent m_end = BaseSent();

		HAMON_CXX11_CONSTEXPR explicit
		sentinel(BaseSent end) HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<BaseSent>::value)
			// [range.enumerate.sentinel]/1
			: m_end(hamon::move(end))
		{}

	public:
		sentinel() = default;

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
			// [range.enumerate.sentinel]/2
			: m_end(hamon::move(other.m_end))
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
		BaseSent base() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<BaseSent>::value)
		{
			// [range.enumerate.sentinel]/3
			return m_end;
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, BaseIterT<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(bool(x.base() == y.m_end))	// noexcept as an extension
		{
			// [range.enumerate.sentinel]/4
			return x.base() == y.m_end;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, BaseIterT<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, BaseIterT<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)	// noexcept as an extension
		{
			return y == x;
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, BaseIterT<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(x == y))	// noexcept as an extension
		{
			return !(x == y);
		}
#endif

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<BaseSent, BaseIterT<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		BaseDifferenceT<OtherConst>
		operator-(iterator<OtherConst> const& x, sentinel const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.base() - y.m_end)	// noexcept as an extension
		{
			// [range.enumerate.sentinel]/5
			return x.base() - y.m_end;
		}

		template <bool OtherConst,
			typename = hamon::enable_if_t<
				hamon::sized_sentinel_for_t<BaseSent, BaseIterT<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		BaseDifferenceT<OtherConst>
		operator-(sentinel const& x, iterator<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(x.m_end - y.base())	// noexcept as an extension
		{
			// [range.enumerate.sentinel]/6
			return x.m_end - y.base();
		}
	};

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	HAMON_CXX11_CONSTEXPR enumerate_view()
		requires hamon::default_initializable<V>
	= default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V)>
	HAMON_CXX11_CONSTEXPR enumerate_view()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<V>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	enumerate_view(V base) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		hamon::is_nothrow_move_constructible<V>::value)
		// [range.enumerate.view]/1
		: m_base(hamon::move(base))
	{}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator<false> begin() HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(hamon::declval<V2&>())) &&
		hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V2>>::value)
	{
		return iterator<false>(hamon::ranges::begin(m_base), 0);
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::range_with_movable_references, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	iterator<true> begin() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::begin(hamon::declval<V2&>())) &&
		hamon::is_nothrow_move_constructible<hamon::ranges::iterator_t<V2>>::value)
	{
		return iterator<true>(hamon::ranges::begin(m_base), 0);
	}

private:
	template <typename V2,
		typename = hamon::enable_if_t<hamon::conjunction<
			hamon::ranges::common_range_t<V2>,
			hamon::ranges::sized_range_t<V2>
		>::value>,
		bool UseConst = hamon::is_const<hamon::remove_reference_t<V2>>::value>
	static HAMON_CXX14_CONSTEXPR iterator<UseConst>
	end_impl(V2& base, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::end(hamon::declval<V2&>())) &&
		HAMON_NOEXCEPT_EXPR(hamon::ranges::distance(hamon::declval<V2&>())) &&
		hamon::is_nothrow_move_constructible<hamon::ranges::sentinel_t<V2>>::value)
	{
		return iterator<UseConst>(hamon::ranges::end(base), hamon::ranges::distance(base));
	}

	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::input_range, V2),
		bool UseConst = hamon::is_const<hamon::remove_reference_t<V2>>::value>
	static HAMON_CXX14_CONSTEXPR sentinel<UseConst>
	end_impl(V2& base, hamon::detail::overload_priority<0>) HAMON_NOEXCEPT_IF(	// noexcept as an extension
		HAMON_NOEXCEPT_EXPR(hamon::ranges::end(hamon::declval<V2&>())) &&
		hamon::is_nothrow_move_constructible<hamon::ranges::sentinel_t<V2>>::value)
	{
		return sentinel<UseConst>(hamon::ranges::end(base));
	}

public:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto end() HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
		end_impl(hamon::declval<V2&>(), hamon::detail::overload_priority<1>{}))
	->decltype(end_impl(hamon::declval<V2&>(), hamon::detail::overload_priority<1>{}))
	{
		return end_impl(m_base, hamon::detail::overload_priority<1>{});
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::range_with_movable_references, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
	auto end() const HAMON_NOEXCEPT_IF_EXPR(	// noexcept as an extension
		end_impl(hamon::declval<V2&>(), hamon::detail::overload_priority<1>{}))
	->decltype(end_impl(hamon::declval<V2&>(), hamon::detail::overload_priority<1>{}))
	{
		return end_impl(m_base, hamon::detail::overload_priority<1>{});
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
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R>
enumerate_view(R&&) -> enumerate_view<hamon::views::all_t<R>>;

#endif

}	// inline namespace enumerate_view_ns

// enable_borrowed_range の特殊化
template <typename View>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(View),
	hamon::ranges::enumerate_view<View>);

namespace views {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 26.7.23.1 Overview[range.enumerate.overview]

struct enumerate_fn : public hamon::ranges::range_adaptor_closure<enumerate_fn>
{
	// [range.enumerate.overview]/2
	template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	auto operator()(R&& r) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::enumerate_view<hamon::views::all_t<R>>{ hamon::forward<R>(r) })
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::enumerate_fn enumerate {};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_ENUMERATE_VIEW_HPP
