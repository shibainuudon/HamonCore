/**
 *	@file	take_view.hpp
 *
 *	@brief	take_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_TAKE_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_TAKE_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::take_view;

namespace views {

using std::ranges::views::take;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/detail/range_adaptor.hpp>
#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/random_access_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/factories/iota_view.hpp>
#include <hamon/ranges/factories/repeat_view.hpp>
#include <hamon/ranges/factories/detail/is_specialization_of_empty_view.hpp>
#include <hamon/ranges/factories/detail/is_specialization_of_iota_view.hpp>
#include <hamon/ranges/factories/detail/is_specialization_of_repeat_view.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/utility/subrange.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/algorithm/min.hpp>
#include <hamon/algorithm/ranges/min.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/concepts/detail/is_specialization_of_subrange.hpp>
#include <hamon/detail/decay_copy.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/functional/bind_back.hpp>
#include <hamon/iterator/counted_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/make_counted_iterator.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/span.hpp>
#include <hamon/span/detail/is_specialization_of_span.hpp>
#include <hamon/string_view.hpp>
#include <hamon/string_view/detail/is_specialization_of_basic_string_view.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_const.hpp>
#include <hamon/type_traits/is_nothrow_constructible.hpp>
#include <hamon/type_traits/is_nothrow_copy_constructible.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/type_traits/is_nothrow_move_constructible.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>
#include <hamon/assert.hpp>

namespace hamon {

namespace ranges {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::view, V)>
class take_view : public hamon::ranges::view_interface<take_view<V>>
{
private:
	HAMON_NO_UNIQUE_ADDRESS V m_base = V();
	hamon::ranges::range_difference_t<V> m_count = 0;

	// [range.take.sentinel], class template take_view​::​sentinel
	template <bool Const>
	class sentinel
	{
	private:
		friend sentinel<!Const>;

		using Base = hamon::ranges::detail::maybe_const<Const, V>;
		using BaseSent = hamon::ranges::sentinel_t<Base>;

		template <bool OtherConst>
		using Iter = hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<OtherConst, V>>;

		template <bool OtherConst>
		using CI = hamon::counted_iterator<Iter<OtherConst>>;

		BaseSent end_ = BaseSent();

	public:
		sentinel() = default;

		HAMON_CXX11_CONSTEXPR explicit
		sentinel(BaseSent end)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_move_constructible<BaseSent>::value)
			// [range.take.sentinel]/1
			: end_(hamon::move(end))
		{}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<C2 &&
				hamon::convertible_to_t<hamon::ranges::sentinel_t<V>, BaseSent>::value>>
		HAMON_CXX11_CONSTEXPR
		sentinel(sentinel<!Const> s)
			HAMON_NOEXCEPT_IF(	// noexcept as an extension
				hamon::is_nothrow_constructible<BaseSent, hamon::ranges::sentinel_t<V>>::value)
			// [range.take.sentinel]/2
			: end_(hamon::move(s.end_))
		{}

		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR		// nodiscard as an extension
		BaseSent base() const HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_copy_constructible<BaseSent>::value)
		{
			// [range.take.sentinel]/3
			return end_;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(CI<Const> const& y, sentinel const& x)
			HAMON_NOEXCEPT_IF_EXPR(y.count() == 0 || y.base() == x.end_)	// noexcept as an extension
		{
			// [range.take.sentinel]/4
			return y.count() == 0 || y.base() == x.end_;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(CI<Const> const& y, sentinel const& x)
			HAMON_NOEXCEPT_IF_EXPR(!(y == x))				// noexcept as an extension
		{
			return !(y == x);
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(sentinel const& x, CI<Const> const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)					// noexcept as an extension
		{
			return y == x;
		}

		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(sentinel const& x, CI<Const> const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(y == x))				// noexcept as an extension
		{
			return !(y == x);
		}
#endif

		template <bool OtherConst = !Const,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, Iter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(CI<OtherConst> const& y, sentinel const& x)
			HAMON_NOEXCEPT_IF_EXPR(y.count() == 0 || y.base() == x.end_)	// noexcept as an extension
		{
			// [range.take.sentinel]/4
			return y.count() == 0 || y.base() == x.end_;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool OtherConst = !Const,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, Iter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(CI<OtherConst> const& y, sentinel const& x)
			HAMON_NOEXCEPT_IF_EXPR(!(y == x))				// noexcept as an extension
		{
			return !(y == x);
		}

		template <bool OtherConst = !Const,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, Iter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator==(sentinel const& x, CI<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(y == x)					// noexcept as an extension
		{
			return y == x;
		}

		template <bool OtherConst = !Const,
			typename = hamon::enable_if_t<
				hamon::sentinel_for_t<BaseSent, Iter<OtherConst>>::value>>
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
		operator!=(sentinel const& x, CI<OtherConst> const& y)
			HAMON_NOEXCEPT_IF_EXPR(!(y == x))				// noexcept as an extension
		{
			return !(y == x);
		}
#endif
	};

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	take_view() requires hamon::default_initializable<V> = default;
#else
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, V2, V)>
	HAMON_CXX11_CONSTEXPR
	take_view()
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<V2>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR explicit
	take_view(V base, hamon::ranges::range_difference_t<V> count)
		HAMON_NOEXCEPT_IF(	// noexcept as an extension
			hamon::is_nothrow_move_constructible<V>::value)
		// [range.take.view]/2
		: m_base(hamon::move(base))
		, m_count(count)
	{
#if HAMON_CXX_STANDARD >= 14
		// [range.take.view]/1
		HAMON_ASSERT(count >= 0);
#endif
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

private:
	template <typename V2, typename This,
		typename = hamon::enable_if_t<
			hamon::ranges::sized_range_t<V2>::value &&
			hamon::ranges::random_access_range_t<V2>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	begin_impl(This* this_, hamon::detail::overload_priority<3>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::begin(this_->m_base))

	template <typename V2, typename This,
		typename = hamon::enable_if_t<hamon::ranges::sized_range_t<V2>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	begin_impl(This* this_, hamon::detail::overload_priority<2>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::make_counted_iterator(
			hamon::ranges::begin(this_->m_base),
			hamon::ranges::range_difference_t<V2>(this_->size())))

	template <typename V2, typename This,
		typename = hamon::enable_if_t<
			hamon::sized_sentinel_for_t<
				hamon::ranges::sentinel_t<V2>, hamon::ranges::iterator_t<V2>
			>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	begin_impl(This* this_, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::make_counted_iterator(
			hamon::ranges::begin(this_->m_base),
			hamon::min(this_->m_count, hamon::ranges::end(this_->m_base) - hamon::ranges::begin(this_->m_base))))

	template <typename V2, typename This,
		typename = hamon::enable_if_t<
			hamon::ranges::range_t<V2>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	begin_impl(This* this_, hamon::detail::overload_priority<0>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::make_counted_iterator(hamon::ranges::begin(this_->m_base), this_->m_count))

public:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto		// nodiscard as an extension
	begin() HAMON_NOEXCEPT_DECLTYPE_RETURN(			// noexcept as an extension
		begin_impl<V2>(this, hamon::detail::overload_priority<3>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto		// nodiscard as an extension
	begin() const HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		begin_impl<V2>(this, hamon::detail::overload_priority<3>{}))

private:
	template <typename V2, typename This,
		typename = hamon::enable_if_t<
			hamon::ranges::sized_range_t<V2>::value &&
			hamon::ranges::random_access_range_t<V2>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	end_impl(This* this_, hamon::detail::overload_priority<3>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::begin(this_->m_base) + hamon::ranges::range_difference_t<V2>(this_->size()))

	template <typename V2, typename This,
		typename = hamon::enable_if_t<
			hamon::ranges::sized_range_t<V2>::value>>
	static HAMON_CXX11_CONSTEXPR hamon::default_sentinel_t
	end_impl(This* /*this_*/, hamon::detail::overload_priority<2>) HAMON_NOEXCEPT
	{
		return hamon::default_sentinel;
	}

	template <typename V2, typename This,
		typename = hamon::enable_if_t<
			hamon::sized_sentinel_for_t<
				hamon::ranges::sentinel_t<V2>, hamon::ranges::iterator_t<V2>
			>::value>>
	static HAMON_CXX11_CONSTEXPR hamon::default_sentinel_t
	end_impl(This* /*this_*/, hamon::detail::overload_priority<1>) HAMON_NOEXCEPT
	{
		return hamon::default_sentinel;
	}

	template <typename V2, typename This,
		typename = hamon::enable_if_t<
			hamon::ranges::range_t<V2>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	end_impl(This* this_, hamon::detail::overload_priority<0>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		sentinel<hamon::is_const<V2>::value>
		{
			hamon::ranges::end(this_->m_base)
		})

public:
	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::detail::not_simple_view, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	end() HAMON_NOEXCEPT_DECLTYPE_RETURN(		// noexcept as an extension
		end_impl<V2>(this, hamon::detail::overload_priority<3>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	end() const HAMON_NOEXCEPT_DECLTYPE_RETURN(	// noexcept as an extension
		end_impl<V2>(this, hamon::detail::overload_priority<3>{}))

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V)>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	size() HAMON_NOEXCEPT_IF_EXPR(				// noexcept as an extension
		hamon::ranges::size(hamon::declval<V2>()))
	->decltype(hamon::ranges::size(hamon::declval<V2>()))
	{
		return hamon::ranges::min(
			hamon::ranges::size(m_base),
			static_cast<decltype(hamon::ranges::size(m_base))>(m_count));
	}

	template <HAMON_CONSTRAINED_PARAM_D(hamon::ranges::sized_range, V2, V const)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	size() const HAMON_NOEXCEPT_IF_EXPR(		// noexcept as an extension
		hamon::ranges::size(hamon::declval<V2>()))
	->decltype(hamon::ranges::size(hamon::declval<V2>()))
	{
		return hamon::ranges::min(
			hamon::ranges::size(m_base),
			static_cast<decltype(hamon::ranges::size(m_base))>(m_count));
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename R>
take_view(R&&, hamon::ranges::range_difference_t<R>)
-> take_view<hamon::views::all_t<R>>;

#endif

// extension: deduction guides が使えないときのために追加
template <typename R>
HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
make_take_view(R&& r, hamon::ranges::range_difference_t<R> count)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		take_view<hamon::views::all_t<R>>(hamon::forward<R>(r), count))

// enable_borrowed_range の特殊化
template <typename T>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(T),
	hamon::ranges::take_view<T>);

namespace views {

namespace detail {

struct take_fn
{
private:
	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename = hamon::enable_if_t<
			hamon::detail::is_specialization_of_empty_view<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& /*count*/, hamon::detail::overload_priority<7>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.take.overview]2.1
		hamon::detail::decay_copy(hamon::forward<R>(r)))

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::ranges::random_access_range_t<T>::value &&
			hamon::ranges::sized_range_t<T>::value &&
			hamon::detail::is_specialization_of_span<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& count, hamon::detail::overload_priority<6>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.take.overview]2.2.1
		hamon::span<typename T::element_type>
		{
			hamon::ranges::begin(r),
			hamon::ranges::begin(r) + hamon::min<D>(hamon::ranges::distance(r), hamon::forward<N>(count))
		})

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::ranges::random_access_range_t<T>::value &&
			hamon::ranges::sized_range_t<T>::value &&
			hamon::detail::is_specialization_of_basic_string_view<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& count, hamon::detail::overload_priority<5>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.take.overview]2.2.2
		T {
			hamon::ranges::begin(r),
			hamon::ranges::begin(r) + hamon::min<D>(hamon::ranges::distance(r), hamon::forward<N>(count))
		})

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::ranges::random_access_range_t<T>::value &&
			hamon::ranges::sized_range_t<T>::value &&
			hamon::detail::is_specialization_of_subrange<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& count, hamon::detail::overload_priority<4>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.take.overview]2.2.3
		hamon::ranges::subrange<hamon::ranges::iterator_t<T>>
		{
			hamon::ranges::begin(r),
			hamon::ranges::begin(r) + hamon::min<D>(hamon::ranges::distance(r), hamon::forward<N>(count))
		})

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::ranges::random_access_range_t<T>::value &&
			hamon::ranges::sized_range_t<T>::value &&
			hamon::detail::is_specialization_of_iota_view<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& count, hamon::detail::overload_priority<3>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.take.overview]2.3
		hamon::views::iota(
			*hamon::ranges::begin(r),
			*(hamon::ranges::begin(r) + hamon::min<D>(hamon::ranges::distance(r), hamon::forward<N>(count)))))

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::detail::is_specialization_of_repeat_view<T>::value &&
			hamon::ranges::sized_range_t<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& count, hamon::detail::overload_priority<2>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.take.overview]2.4.1
		hamon::views::repeat(*r.begin(), hamon::min<D>(hamon::ranges::distance(r), hamon::forward<N>(count))))

	template <typename R, typename N,
		typename T = hamon::remove_cvref_t<R>,
		typename D = hamon::ranges::range_difference_t<R>,
		typename = hamon::enable_if_t<
			hamon::detail::is_specialization_of_repeat_view<T>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& count, hamon::detail::overload_priority<1>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.take.overview]2.4.2
		hamon::views::repeat(*r.begin(), static_cast<D>(hamon::forward<N>(count))))

	template <typename R, typename N>
	static HAMON_CXX11_CONSTEXPR auto
	impl(R&& r, N&& count, hamon::detail::overload_priority<0>)
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		// [range.take.overview]2.5
		hamon::ranges::make_take_view(hamon::forward<R>(r), hamon::forward<N>(count)))

public:
	template <
		HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R),
		HAMON_CONSTRAINED_PARAM(hamon::convertible_to, hamon::ranges::range_difference_t<R>, N)
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(R&& r, N&& count) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(impl(
		hamon::forward<R>(r),
		hamon::forward<N>(count),
		hamon::detail::overload_priority<7>{}))

	template <typename T,
		typename = hamon::enable_if_t<
			hamon::constructible_from_t<hamon::decay_t<T>, T
		>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T&& count) const
	HAMON_NOEXCEPT_DECLTYPE_RETURN(
		hamon::ranges::detail::make_range_adaptor(
			hamon::bind_back(*this, hamon::forward<T>(count))))
};

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::take_fn take{};

}	// inline namespace cpo

}	// namespace views

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_TAKE_VIEW_HPP
