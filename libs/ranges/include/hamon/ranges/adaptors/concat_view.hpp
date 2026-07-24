/**
 *	@file	concat_view.hpp
 *
 *	@brief	concat_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_CONCAT_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_CONCAT_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using hamon::ranges::concat_view;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/all.hpp>
#include <hamon/ranges/adaptors/detail/all_bidirectional.hpp>
#include <hamon/ranges/adaptors/detail/all_forward.hpp>
#include <hamon/ranges/adaptors/detail/all_random_access.hpp>
#include <hamon/ranges/adaptors/detail/concatable.hpp>
#include <hamon/ranges/adaptors/detail/concat_reference_t.hpp>
#include <hamon/ranges/adaptors/detail/concat_rvalue_reference_t.hpp>
#include <hamon/ranges/adaptors/detail/concat_value_t.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/concepts/approximately_sized_range.hpp>
#include <hamon/ranges/concepts/common_range.hpp>
#include <hamon/ranges/concepts/input_range.hpp>
#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/detail/maybe_const.hpp>
#include <hamon/ranges/detail/tuple_transform.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/range_difference_t.hpp>
#include <hamon/ranges/range_reference_t.hpp>
#include <hamon/ranges/range_rvalue_reference_t.hpp>
#include <hamon/ranges/reserve_hint.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/utility/detail/make_unsigned_like_t.hpp>
#include <hamon/ranges/utility/detail/simple_view.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/compare/concepts/three_way_comparable.hpp>
#include <hamon/compare/concepts/three_way_comparable_with.hpp>
#include <hamon/concepts/common_reference_with.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/detail/constraint.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/swap.hpp>
#include <hamon/concepts/swappable_with.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/concepts/indirectly_swappable.hpp>
#include <hamon/iterator/concepts/sized_sentinel_for.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/iterator_traits.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/iterator/ranges/distance.hpp>
#include <hamon/iterator/ranges/iter_move.hpp>
#include <hamon/iterator/ranges/iter_swap.hpp>
#include <hamon/tuple.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/common_type.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/detail/all.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_convertible.hpp>
#include <hamon/type_traits/is_nothrow_invocable.hpp>
#include <hamon/type_traits/is_reference.hpp>
#include <hamon/type_traits/nth.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place_index_t.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/variant.hpp>
#include <hamon/assert.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// 25.7.18.2 Class template concat_view[range.concat.view]

namespace detail {

template <typename R0, typename... Rs>
struct all_but_last_common : public hamon::conjunction<
	hamon::bool_constant<hamon::ranges::common_range<R0>>,
	all_but_last_common<Rs...>>
{};

template <typename R0>
struct all_but_last_common<R0> : public hamon::true_type {};

// [range.concat.view]/3
template <bool Const, typename... Rs>
HAMON_CONCEPT_OR_BOOL concat_is_random_access =
	hamon::ranges::detail::all_random_access<Const, Rs...> &&
	hamon::ranges::detail::all_but_last_common<hamon::ranges::detail::maybe_const<Const, Rs>...>::value;

// [range.concat.view]/4
template <bool Const, typename... Rs>
HAMON_CONCEPT_OR_BOOL concat_is_bidirectional =
	hamon::ranges::detail::all_bidirectional<Const, Rs...> &&
	hamon::ranges::detail::all_but_last_common<hamon::ranges::detail::maybe_const<Const, Rs>...>::value;

template <typename R0, typename... Rs>
struct all_but_first_sized
	: public hamon::detail::all<hamon::ranges::sized_range<Rs>...> {};

}	// namespace detail

// 古いバージョンのclangにおいて、iter_swapの再定義エラーになる場合があるので
// inline namespace で囲む。
inline namespace concat_view_ns
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::input_range... Views>
	requires (hamon::ranges::view<Views> && ...) && (sizeof...(Views) > 0) &&
		hamon::ranges::detail::concatable<Views...>
#else
template <typename... Views>
#endif
class concat_view : public hamon::ranges::view_interface<concat_view<Views...>>
{
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	static_assert(hamon::detail::all_v<hamon::ranges::input_range<Views>...>, "");
	static_assert(hamon::detail::all_v<hamon::ranges::view<Views>...>, "");
	static_assert(sizeof...(Views) > 0, "");
	static_assert(hamon::ranges::detail::concatable<Views...>, "");
#endif

private:
	hamon::tuple<Views...> views_;

private:
	// [range.concat.iterator]/2
	template <bool Const, typename... Cs>
	struct iterator_category_base_impl
	{
		using type =
			hamon::conditional_t<
				hamon::detail::all_v<
					hamon::derived_from<Cs, hamon::random_access_iterator_tag>...,
					hamon::ranges::detail::concat_is_random_access<Const, Views...>
				>,
				hamon::random_access_iterator_tag,		// [range.concat.iterator]/2.2.1
			hamon::conditional_t<
				hamon::detail::all_v<
					hamon::derived_from<Cs, hamon::bidirectional_iterator_tag>...,
					hamon::ranges::detail::concat_is_bidirectional<Const, Views...>
				>,
				hamon::bidirectional_iterator_tag,		// [range.concat.iterator]/2.2.2
			hamon::conditional_t<
				hamon::detail::all_v<hamon::derived_from<Cs, hamon::forward_iterator_tag>...>,
				hamon::forward_iterator_tag,			// [range.concat.iterator]/2.2.3
				hamon::input_iterator_tag				// [range.concat.iterator]/2.2.4
			>>>;
	};

	template <bool Const, bool = hamon::ranges::detail::all_forward<Const, Views...>>
	struct iterator_category_base
	{
		using iterator_category =
			hamon::conditional_t<
				!hamon::is_reference_v<
					hamon::ranges::detail::concat_reference_t<
						hamon::ranges::detail::maybe_const<Const, Views>...
					>
				>,
				hamon::input_iterator_tag,	// [range.concat.iterator]/2.1
				typename iterator_category_base_impl<	// [range.concat.iterator]/2.2
					Const,
					typename hamon::iterator_traits<
						hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<Const, Views>>
					>::iterator_category...>::type
			>;
	};

	template <bool Const>
	struct iterator_category_base<Const, false>
	{};

	// 25.7.18.3 Class concat_view::iterator[range.concat.iterator]
	template <bool Const>
	class iterator : public iterator_category_base<Const>
	{
	private:
		friend concat_view;

		template <bool C, typename V>
		using IteratorT = hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<C, V>>;

		template <bool C, typename V>
		using SentinelT = hamon::ranges::sentinel_t<hamon::ranges::detail::maybe_const<C, V>>;

	public:
		//using iterator_category = see below;	// not always present

		// [range.concat.iterator]/1
		using iterator_concept =
			hamon::conditional_t<
				hamon::ranges::detail::concat_is_random_access<Const, Views...>,
				hamon::random_access_iterator_tag,	// [range.concat.iterator]/1.1
			hamon::conditional_t<
				hamon::ranges::detail::concat_is_bidirectional<Const, Views...>,
				hamon::bidirectional_iterator_tag,	// [range.concat.iterator]/1.2
			hamon::conditional_t<
				hamon::ranges::detail::all_forward<Const, Views...>,
				hamon::forward_iterator_tag,		// [range.concat.iterator]/1.3
				hamon::input_iterator_tag			// [range.concat.iterator]/1.4
			>>>;

		using value_type = hamon::ranges::detail::concat_value_t<hamon::ranges::detail::maybe_const<Const, Views>...>;

		using difference_type = hamon::common_type_t<hamon::ranges::range_difference_t<hamon::ranges::detail::maybe_const<Const, Views>>...>;

	private:
		using base_iter = hamon::variant<IteratorT<Const, Views>...>;

		hamon::ranges::detail::maybe_const<Const, concat_view>* parent_ = nullptr;
		base_iter it_;

	private:
		// operator==() 内で it.parent_->views_ と記述すると、
		// privateメンバにアクセスしているというエラーになる(Clang以外)。
		// それを回避するためにこの関数が必要。
		constexpr decltype(auto) get_parent_view() const
		{
			return (parent_->views_);
		}

	private:
		// [range.concat.iterator]/3
		template <hamon::size_t N, typename = hamon::enable_if_t<(N < (sizeof...(Views) - 1))>>
		HAMON_CXX14_CONSTEXPR void satisfy_impl(hamon::detail::overload_priority<1>)
		{
			if (hamon::get<N>(it_) == hamon::ranges::end(hamon::get<N>(parent_->views_)))
			{
				it_.template emplace<N + 1>(hamon::ranges::begin(hamon::get<N + 1>(parent_->views_)));
				satisfy<N + 1>();
			}
		}

		template <hamon::size_t N>
		HAMON_CXX14_CONSTEXPR void satisfy_impl(hamon::detail::overload_priority<0>)
		{
		}

		template <hamon::size_t N>
		HAMON_CXX14_CONSTEXPR void satisfy()
		{
			satisfy_impl<N>(hamon::detail::overload_priority<1>{});
		}

		// [range.concat.iterator]/4
		template <hamon::size_t N, typename = hamon::enable_if_t<N == 0>>
		HAMON_CXX14_CONSTEXPR void prev_impl(hamon::detail::overload_priority<1>)
		{
			--hamon::get<0>(it_);
		}

		template <hamon::size_t N>
		HAMON_CXX14_CONSTEXPR void prev_impl(hamon::detail::overload_priority<0>)
		{
			if (hamon::get<N>(it_) == hamon::ranges::begin(hamon::get<N>(parent_->views_)))
			{
				it_.template emplace<N - 1>(hamon::ranges::end(hamon::get<N - 1>(parent_->views_)));
				prev<N - 1>();
			}
			else
			{
				--hamon::get<N>(it_);
			}
		}

		template <hamon::size_t N>
		HAMON_CXX14_CONSTEXPR void prev()
		{
			prev_impl<N>(hamon::detail::overload_priority<1>{});
		}

		// [range.concat.iterator]/5
		template <hamon::size_t N, typename = hamon::enable_if_t<(N == (sizeof...(Views) - 1))>>
		HAMON_CXX14_CONSTEXPR void advance_fwd_impl(difference_type /*offset*/, difference_type steps, hamon::detail::overload_priority<1>)
		{
			using underlying_diff_type = hamon::iter_difference_t<hamon::variant_alternative_t<N, base_iter>>;
			hamon::get<N>(it_) += static_cast<underlying_diff_type>(steps);
		}

		template <hamon::size_t N>
		HAMON_CXX14_CONSTEXPR void advance_fwd_impl(difference_type offset, difference_type steps, hamon::detail::overload_priority<0>)
		{
			using underlying_diff_type = hamon::iter_difference_t<hamon::variant_alternative_t<N, base_iter>>;
			auto n_size = hamon::ranges::distance(hamon::get<N>(parent_->views_));
			if (offset + steps < n_size)
			{
				hamon::get<N>(it_) += static_cast<underlying_diff_type>(steps);
			}
			else
			{
				it_.template emplace<N + 1>(hamon::ranges::begin(hamon::get<N + 1>(parent_->views_)));
				advance_fwd<N + 1>(0, offset + steps - n_size);
			}
		}

		template <hamon::size_t N>
		HAMON_CXX14_CONSTEXPR void advance_fwd(difference_type offset, difference_type steps)
		{
			advance_fwd_impl<N>(offset, steps, hamon::detail::overload_priority<1>{});
		}

		// [range.concat.iterator]/6
		template <hamon::size_t N, typename = hamon::enable_if_t<(N == 0)>>
		HAMON_CXX14_CONSTEXPR void advance_bwd_impl(difference_type /*offset*/, difference_type steps, hamon::detail::overload_priority<1>)
		{
			using underlying_diff_type = hamon::iter_difference_t<hamon::variant_alternative_t<N, base_iter>>;
			hamon::get<N>(it_) -= static_cast<underlying_diff_type>(steps);
		}

		template <hamon::size_t N>
		HAMON_CXX14_CONSTEXPR void advance_bwd_impl(difference_type offset, difference_type steps, hamon::detail::overload_priority<0>)
		{
			using underlying_diff_type = hamon::iter_difference_t<hamon::variant_alternative_t<N, base_iter>>;
			if (offset >= steps)
			{
				hamon::get<N>(it_) -= static_cast<underlying_diff_type>(steps);
			}
			else
			{
				auto prev_size = hamon::ranges::distance(hamon::get<N - 1>(parent_->views_));
				it_.template emplace<N - 1>(hamon::ranges::end(hamon::get<N - 1>(parent_->views_)));
				advance_bwd<N - 1>(prev_size, steps - offset);
			}
		}

		template <hamon::size_t N>
		HAMON_CXX14_CONSTEXPR void advance_bwd(difference_type offset, difference_type steps)
		{
			advance_bwd_impl<N>(offset, steps, hamon::detail::overload_priority<1>{});
		}

	private:
		template <hamon::size_t I, typename F, typename = hamon::enable_if_t<(I < (sizeof...(Views) - 1))>>
		static HAMON_CXX14_CONSTEXPR auto invoke_with_runtime_index_impl(F&& f, hamon::size_t i, hamon::detail::overload_priority<1>)
		{
			if (I == i)
			{
				return f.template operator()<I>();
			}
			return invoke_with_runtime_index_impl<I + 1>(hamon::forward<F>(f), i, hamon::detail::overload_priority<1>{});
		}

		template <hamon::size_t I, typename F>
		static HAMON_CXX14_CONSTEXPR auto invoke_with_runtime_index_impl(F&& f, hamon::size_t i, hamon::detail::overload_priority<0>)
		{
			HAMON_ASSERT(I == i);
			return f.template operator()<I>();
		}

		template <typename F>
		static HAMON_CXX14_CONSTEXPR auto invoke_with_runtime_index(F&& f, hamon::size_t i)
		{
			return invoke_with_runtime_index_impl<0>(hamon::forward<F>(f), i, hamon::detail::overload_priority<1>{});
		}

#if defined(HAMON_MSVC)
	public:	// MSVCではprivateにするとなぜかエラーになる
#else
	private:
#endif
		template <typename... Args,
			typename = hamon::enable_if_t<
				hamon::constructible_from<base_iter, Args&&...>>>
		HAMON_CXX11_CONSTEXPR explicit
		iterator(hamon::ranges::detail::maybe_const<Const, concat_view>* parent, Args&&... args)
//			requires hamon::constructible_from<base_iter, Args&&...>
			// [range.concat.iterator]/7
			: parent_(parent)
			, it_(hamon::forward<Args>(args)...)
		{}

	private:
		struct get_base_iter_t
		{
			iterator<!Const>& it;

			template <hamon::size_t i>
			HAMON_CXX11_CONSTEXPR auto operator()() const
			{
				return base_iter(hamon::in_place_index<i>, hamon::get<i>(hamon::move(it.it_)));
			}
		};

	public:
		iterator() = default;

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				C2 &&
				hamon::detail::all_v<hamon::convertible_to<
					hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<!C2, Views>>,
					hamon::ranges::iterator_t<hamon::ranges::detail::maybe_const<C2, Views>>
				>...
			>>>
		HAMON_CXX11_CONSTEXPR
		iterator(iterator<!Const> it)
//			requires Const &&
//				(hamon::convertible_to<hamon::ranges::iterator_t<Views>, hamon::ranges::iterator_t<const Views>> && ...)
			// [range.concat.iterator]/9
			: parent_(it.parent_)
			, it_(invoke_with_runtime_index(get_base_iter_t{it}, it.it_.index()))
		{
			// [range.concat.iterator]/8
			HAMON_ASSERT(!it.it_.valueless_by_exception());
		}

	private:
		template <typename Reference>
		struct dereference_t
		{
			template <typename T>
			HAMON_CXX11_CONSTEXPR Reference operator()(T&& it) const
			{
				return static_cast<Reference>(*it);
			}
		};

	public:
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		decltype(auto) operator*() const
		{
			// [range.concat.iterator]/10
			HAMON_ASSERT(!it_.valueless_by_exception());

			// [range.concat.iterator]/11
			using reference = hamon::ranges::detail::concat_reference_t<hamon::ranges::detail::maybe_const<Const, Views>...>;
			return hamon::visit(dereference_t<reference>{}, it_);
		}

	private:
		struct pre_increment_t
		{
			iterator* this_;

			template <hamon::size_t i>
			HAMON_CXX14_CONSTEXPR auto operator()() const
			{
				++hamon::get<i>(this_->it_);
				this_->satisfy<i>();
			}
		};

		struct pre_decrement_t
		{
			iterator* this_;

			template <hamon::size_t i>
			HAMON_CXX14_CONSTEXPR auto operator()() const
			{
				this_->prev<i>();
			}
		};

		struct advance_t
		{
			iterator* this_;
			difference_type n;

			template <hamon::size_t i>
			HAMON_CXX14_CONSTEXPR auto operator()() const
			{
				auto const offset = hamon::get<i>(this_->it_) -
					hamon::ranges::begin(hamon::get<i>(this_->parent_->views_));
				if (n > 0)
				{
					this_->advance_fwd<i>(offset, n);
				}
				else if (n < 0)
				{
					this_->advance_bwd<i>(offset, -n);
				}
			}
		};

	public:
		HAMON_CXX14_CONSTEXPR
		iterator& operator++()
		{
			// [range.concat.iterator]/12
			HAMON_ASSERT(!it_.valueless_by_exception());

			// [range.concat.iterator]/13
			invoke_with_runtime_index(pre_increment_t{this}, it_.index());

			return *this;
		}

	private:
		HAMON_CXX14_CONSTEXPR
		void post_increment(hamon::detail::overload_priority<0>)
		{
			// [range.concat.iterator]/14
			++*this; 
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_forward<C2, Views...>>>
		HAMON_CXX14_CONSTEXPR
		iterator post_increment(hamon::detail::overload_priority<1>)
//			requires hamon::ranges::detail::all_forward<Const, Views...>
		{
			// [range.concat.iterator]/15
			auto tmp = *this;
			++*this;
			return tmp;
		}

	public:
		HAMON_CXX14_CONSTEXPR
		auto operator++(int)
		{
			return post_increment(hamon::detail::overload_priority<1>{});
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::concat_is_bidirectional<C2, Views...>>>
		HAMON_CXX14_CONSTEXPR
		iterator& operator--()
//			requires hamon::ranges::detail::concat_is_bidirectional<Const, Views...>
		{
			// [range.concat.iterator]/16
			HAMON_ASSERT(!it_.valueless_by_exception());

			// [range.concat.iterator]/17
			invoke_with_runtime_index(pre_decrement_t{this}, it_.index());

			return *this;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::concat_is_bidirectional<C2, Views...>>>
		HAMON_CXX14_CONSTEXPR
		iterator operator--(int)
//			requires hamon::ranges::detail::concat_is_bidirectional<Const, Views...>
		{
			// [range.concat.iterator]/18
			auto tmp = *this;
			--*this;
			return tmp;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::concat_is_random_access<C2, Views...>>>
		HAMON_CXX14_CONSTEXPR
		iterator& operator+=(difference_type n)
//			requires hamon::ranges::detail::concat_is_random_access<Const, Views...>
		{
			// [range.concat.iterator]/19
			HAMON_ASSERT(!it_.valueless_by_exception());

			// [range.concat.iterator]/20
			invoke_with_runtime_index(advance_t{this, n}, it_.index());

			return *this;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::concat_is_random_access<C2, Views...>>>
		HAMON_CXX14_CONSTEXPR
		iterator& operator-=(difference_type n)
//			requires hamon::ranges::detail::concat_is_random_access<Const, Views...>
		{
			// [range.concat.iterator]/21
			*this += -n;
			return *this;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::concat_is_random_access<C2, Views...>>>
		HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		decltype(auto) operator[](difference_type n) const
//			requires hamon::ranges::detail::concat_is_random_access<Const, Views...>
		{
			// [range.concat.iterator]/22
			return *((*this) + n);
		}

	private:
		template <bool C2 = Const,
			typename = hamon::enable_if_t<hamon::detail::all_v<
				hamon::equality_comparable<IteratorT<C2, Views>>...>>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		bool operator==(const iterator& x, const iterator& y)
//			requires (hamon::equality_comparable<IteratorT<Const, Views>> && ...)
		{
			// [range.concat.iterator]/23
			HAMON_ASSERT(!x.it_.valueless_by_exception());
			HAMON_ASSERT(!y.it_.valueless_by_exception());

			// [range.concat.iterator]/24
			return x.it_ == y.it_;
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool C2 = Const,
			typename = hamon::enable_if_t<hamon::detail::all_v<
				hamon::equality_comparable<IteratorT<C2, Views>>...>>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		bool operator!=(const iterator& x, const iterator& y)
//			requires (hamon::equality_comparable<IteratorT<Const, Views>> && ...)
		{
			return !(x == y);
		}
#endif

		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		bool operator==(const iterator& it, hamon::default_sentinel_t)
		{
			// [range.concat.iterator]/25
			HAMON_ASSERT(!it.it_.valueless_by_exception());

			// [range.concat.iterator]/26
			constexpr auto last_idx = sizeof...(Views) - 1;
			return it.it_.index() == last_idx &&
				hamon::get<last_idx>(it.it_) == hamon::ranges::end(hamon::get<last_idx>(it.get_parent_view()));
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		bool operator!=(const iterator& x, hamon::default_sentinel_t y)
		{
			return !(x == y);
		}

		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		bool operator==(hamon::default_sentinel_t x, const iterator& y)
		{
			return y == x;
		}

		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		bool operator!=(hamon::default_sentinel_t x, const iterator& y)
		{
			return !(x == y);
		}
#endif

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access<C2, Views...>>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		bool operator<(const iterator& x, const iterator& y)
//			requires hamon::ranges::detail::all_random_access<Const, Views...>
		{
			// [range.concat.iterator]/27
			HAMON_ASSERT(!x.it_.valueless_by_exception());
			HAMON_ASSERT(!y.it_.valueless_by_exception());

			// [range.concat.iterator]/28,29
			return x.it_ < y.it_;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access<C2, Views...>>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		bool operator>(const iterator& x, const iterator& y)
//			requires hamon::ranges::detail::all_random_access<Const, Views...>
		{
			// [range.concat.iterator]/27
			HAMON_ASSERT(!x.it_.valueless_by_exception());
			HAMON_ASSERT(!y.it_.valueless_by_exception());

			// [range.concat.iterator]/28,29
			return x.it_ > y.it_;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access<C2, Views...>>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		bool operator<=(const iterator& x, const iterator& y)
//			requires hamon::ranges::detail::all_random_access<Const, Views...>
		{
			// [range.concat.iterator]/27
			HAMON_ASSERT(!x.it_.valueless_by_exception());
			HAMON_ASSERT(!y.it_.valueless_by_exception());

			// [range.concat.iterator]/28,29
			return x.it_ <= y.it_;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access<C2, Views...>>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		bool operator>=(const iterator& x, const iterator& y)
//			requires hamon::ranges::detail::all_random_access<Const, Views...>
		{
			// [range.concat.iterator]/27
			HAMON_ASSERT(!x.it_.valueless_by_exception());
			HAMON_ASSERT(!y.it_.valueless_by_exception());

			// [range.concat.iterator]/28,29
			return x.it_ >= y.it_;
		}

#if defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::all_random_access<C2, Views...> &&
				hamon::detail::all_v<hamon::three_way_comparable<IteratorT<C2, Views>>...>
			>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		auto operator<=>(const iterator& x, const iterator& y)
//			requires (hamon::ranges::detail::all_random_access<Const, Views...> &&
//				(hamon::three_way_comparable<IteratorT<Const, Views>> && ...))
		{
			// [range.concat.iterator]/27
			HAMON_ASSERT(!x.it_.valueless_by_exception());
			HAMON_ASSERT(!y.it_.valueless_by_exception());

			// [range.concat.iterator]/28,29
			return x.it_ <=> y.it_;
		}
#endif

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::concat_is_random_access<C2, Views...>>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator+(const iterator& it, difference_type n)
//			requires hamon::ranges::detail::concat_is_random_access<Const, Views...>
		{
			// [range.concat.iterator]/30
			auto temp = it;
			temp += n;
			return temp;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::concat_is_random_access<C2, Views...>>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator+(difference_type n, const iterator& it)
//			requires hamon::ranges::detail::concat_is_random_access<Const, Views...>
		{
			// [range.concat.iterator]/31
			return it + n;
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::concat_is_random_access<C2, Views...>>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		iterator operator-(const iterator& it, difference_type n)
//			requires hamon::ranges::detail::concat_is_random_access<Const, Views...>
		{
			// [range.concat.iterator]/32
			auto temp = it;
			temp -= n;
			return temp;
		}

	private:
		template <hamon::size_t I, hamon::size_t N, typename ViewsTuple, typename = hamon::enable_if_t<(I < N)>>
		static HAMON_CXX11_CONSTEXPR difference_type
		sum_of_sizes_impl(ViewsTuple const& views, hamon::detail::overload_priority<1>)
		{
			return sum_of_sizes<I + 1, N>(views) +
				static_cast<difference_type>(hamon::ranges::size(hamon::get<I>(views)));
		}

		template <hamon::size_t I, hamon::size_t N, typename ViewsTuple>
		static HAMON_CXX11_CONSTEXPR difference_type
		sum_of_sizes_impl(ViewsTuple const& /*views*/, hamon::detail::overload_priority<0>)
		{
			return 0;
		}

		template <hamon::size_t I, hamon::size_t N, typename ViewsTuple>
		static HAMON_CXX11_CONSTEXPR difference_type
		sum_of_sizes(ViewsTuple const& views)
		{
			return sum_of_sizes_impl<I, N>(views, hamon::detail::overload_priority<1>{});
		}

	private:
		template <hamon::size_t ix>
		struct subtract1_t
		{
			const iterator& x;
			const iterator& y;

			template <hamon::size_t iy, typename = hamon::enable_if_t<(ix > iy)>>
			HAMON_CXX14_CONSTEXPR auto
			impl(hamon::detail::overload_priority<2>) const
			{
				// [range.concat.iterator]/34.1
				auto dy = hamon::ranges::distance(hamon::get<iy>(y.it_), hamon::ranges::end(hamon::get<iy>(y.parent_->views_)));
				auto dx = hamon::ranges::distance(hamon::ranges::begin(hamon::get<ix>(x.parent_->views_)), hamon::get<ix>(x.it_));

				difference_type s = iterator::sum_of_sizes<iy + 1, ix>(x.parent_->views_);

				return dy + s + dx;
			}

			template <hamon::size_t iy, typename = hamon::enable_if_t<(ix < iy)>>
			HAMON_CXX14_CONSTEXPR auto
			impl(hamon::detail::overload_priority<1>) const
			{
				// [range.concat.iterator]/34.2
				return -(y - x);
			}

			template <hamon::size_t iy>
			HAMON_CXX14_CONSTEXPR auto
			impl(hamon::detail::overload_priority<0>) const
			{
				// [range.concat.iterator]/34.3
				return hamon::get<ix>(x.it_) - hamon::get<iy>(y.it_);
			}

			template <hamon::size_t iy>
			HAMON_CXX14_CONSTEXPR auto operator()() const
			{
				return impl<iy>(hamon::detail::overload_priority<2>{});
			}
		};

		struct subtract2_t
		{
			const iterator& x;
			const iterator& y;

			template <hamon::size_t ix>
			HAMON_CXX11_CONSTEXPR auto operator()() const
			{
				return iterator::invoke_with_runtime_index(subtract1_t<ix>{x, y}, y.it_.index());
			}
		};

		struct subtract3_t
		{
			const iterator& x;

			template <hamon::size_t ix>
			HAMON_CXX14_CONSTEXPR auto operator()() const
			{
				auto dx = hamon::ranges::distance(hamon::get<ix>(x.it_), hamon::ranges::end(hamon::get<ix>(x.parent_->views_)));
				difference_type s = iterator::sum_of_sizes<ix + 1, sizeof...(Views)>(x.parent_->views_);
				return -(dx + s);
			}
		};

	private:
		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::ranges::detail::concat_is_random_access<C2, Views...>>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(const iterator& x, const iterator& y)
//			requires hamon::ranges::detail::concat_is_random_access<Const, Views...>
		{
			// [range.concat.iterator]/33
			HAMON_ASSERT(!x.it_.valueless_by_exception());
			HAMON_ASSERT(!y.it_.valueless_by_exception());

			// [range.concat.iterator]/34
			return iterator::invoke_with_runtime_index(subtract2_t{x, y}, x.it_.index());
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::detail::all_v<hamon::sized_sentinel_for<SentinelT<C2, Views>, IteratorT<C2, Views>>...> &&
				detail::all_but_first_sized<hamon::ranges::detail::maybe_const<C2, Views>...>::value>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(const iterator& x, hamon::default_sentinel_t)
			// [range.concat.iterator]/37	
//			requires
//				(hamon::sized_sentinel_for<SentinelT<Const, Views>, IteratorT<Const, Views>> && ...) &&
//				detail::all_but_first_sized<hamon::ranges::detail::maybe_const<Const, Views>...>::value
		{
			// [range.concat.iterator]/35
			HAMON_ASSERT(!x.it_.valueless_by_exception());

			// [range.concat.iterator]/36
			return iterator::invoke_with_runtime_index(subtract3_t{x}, x.it_.index());
		}

		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::detail::all_v<hamon::sized_sentinel_for<SentinelT<C2, Views>, IteratorT<C2, Views>>...> &&
				detail::all_but_first_sized<hamon::ranges::detail::maybe_const<C2, Views>...>::value>>
		HAMON_NODISCARD friend HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
		difference_type operator-(hamon::default_sentinel_t, const iterator& x)
			// [range.concat.iterator]/39
//			requires
//				(hamon::sized_sentinel_for<SentinelT<Const, Views>, IteratorT<Const, Views>> && ...) &&
//				detail::all_but_first_sized<hamon::ranges::detail::maybe_const<Const, Views>...>::value
		{
			// [range.concat.iterator]/38
			return -(x - hamon::default_sentinel);
		}

	private:
		// [range.concat.iterator]/41
		template <typename ResultType>
		struct iter_move_t
		{
			template <typename T>
			HAMON_CXX11_CONSTEXPR ResultType operator()(T const& i) const
			{
				return static_cast<ResultType>(hamon::ranges::iter_move(i));
			}
		};

	private:
		HAMON_NODISCARD friend HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
		decltype(auto) iter_move(const iterator& it)
			// [range.concat.iterator]/42
			noexcept((hamon::detail::all_v<
				(hamon::is_nothrow_invocable_v<
					decltype(hamon::ranges::iter_move),
					const IteratorT<Const, Views>&
				> &&
				hamon::is_nothrow_convertible_v<
					hamon::ranges::range_rvalue_reference_t<hamon::ranges::detail::maybe_const<Const, Views>>,
					hamon::ranges::detail::concat_rvalue_reference_t<hamon::ranges::detail::maybe_const<Const, Views>...>
				>)...>))
		{
			// [range.concat.iterator]/40
			HAMON_ASSERT(!it.it_.valueless_by_exception());

			using result_type = hamon::ranges::detail::concat_rvalue_reference_t<hamon::ranges::detail::maybe_const<Const, Views>...>;

			// [range.concat.iterator]/41
			return hamon::visit(iter_move_t<result_type>{}, it.it_);
		}

	private:
		// [range.concat.iterator]/44
		struct iter_swap_t
		{
			const iterator& x;
			const iterator& y;

			template <typename T>
			HAMON_CXX14_CONSTEXPR void operator()(T const& it1, T const& it2) const
			{
				hamon::ranges::iter_swap(it1, it2);
			}

			template <typename T, typename U>
			HAMON_CXX14_CONSTEXPR void operator()(T const&, U const&) const
			{
				hamon::ranges::swap(*x, *y);
			}
		};

	private:
		template <bool C2 = Const,
			typename = hamon::enable_if_t<
				hamon::swappable_with<hamon::iter_reference_t<iterator>, hamon::iter_reference_t<iterator>> &&
				hamon::detail::all_v<hamon::indirectly_swappable<IteratorT<C2, Views>>...>
			>>
		friend HAMON_CXX14_CONSTEXPR
		void iter_swap(const iterator& x, const iterator& y)
			// [range.concat.iterator]/45
			// noexcept(noexcept(hamon::ranges::swap(*x, *y)) && ... && noexcept(hamon::ranges::iter_swap(its, its)))
			// operator*() が noexcept 指定されていないので、上の条件が満たされることは無い
			// 
			// [range.concat.iterator]/45
//			requires hamon::swappable_with<hamon::iter_reference_t<iterator>, hamon::iter_reference_t<iterator>> &&
//				(... && hamon::indirectly_swappable<IteratorT<Const, Views>>)
		{
			// [range.concat.iterator]/43
			HAMON_ASSERT(!x.it_.valueless_by_exception());
			HAMON_ASSERT(!y.it_.valueless_by_exception());

			// [range.concat.iterator]/44
			hamon::visit(iter_swap_t{x, y}, x.it_, y.it_);
		}
	};

public:
	HAMON_CXX11_CONSTEXPR concat_view() = default;

	HAMON_CXX11_CONSTEXPR explicit
	concat_view(Views... views)
		// [range.concat.view]/5
		: views_(hamon::move(views)...)
	{}

	template <bool C2 = false,
		typename = hamon::enable_if_t<!hamon::detail::all_v<
			hamon::ranges::detail::simple_view<hamon::ranges::detail::maybe_const<C2, Views>>...>>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator<false> begin()
//		requires (!(hamon::ranges::detail::simple_view<Views> && ...))
	{
		// [range.concat.view]/6
		iterator<false> it(this, hamon::in_place_index<0>, hamon::ranges::begin(hamon::get<0>(views_)));
		it.template satisfy<0>();
		return it;
	}

	template <bool C2 = true,
		typename = hamon::enable_if_t<
			hamon::detail::all_v<hamon::ranges::range<hamon::ranges::detail::maybe_const<C2, Views>>...> &&
			hamon::ranges::detail::concatable<hamon::ranges::detail::maybe_const<C2, Views>...>>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	iterator<true> begin() const
//		requires (hamon::ranges::range<const Views> && ...) && hamon::ranges::detail::concatable<const Views...>
	{
		// [range.concat.view]/6
		iterator<true> it(this, hamon::in_place_index<0>, hamon::ranges::begin(hamon::get<0>(views_)));
		it.template satisfy<0>();
		return it;
	}

private:
	// [range.concat.view]/7
	template <bool IsConst, typename This, hamon::size_t N = sizeof...(Views),
		typename = hamon::enable_if_t<
			hamon::ranges::detail::all_forward<IsConst, Views...> &&
			hamon::ranges::common_range<hamon::ranges::detail::maybe_const<IsConst, hamon::nth_t<N - 1, Views...>>>>>
	static HAMON_CXX11_CONSTEXPR auto end_impl(This this_, hamon::detail::overload_priority<1>)
	{
		return iterator<IsConst>(this_, hamon::in_place_index<N - 1>, hamon::ranges::end(hamon::get<N - 1>(this_->views_)));
	}

	template <bool IsConst, typename This>
	static HAMON_CXX11_CONSTEXPR auto end_impl(This, hamon::detail::overload_priority<0>)
	{
		return hamon::default_sentinel;
	}

public:
	template <bool C2 = false,
		typename = hamon::enable_if_t<!hamon::detail::all_v<
			hamon::ranges::detail::simple_view<hamon::ranges::detail::maybe_const<C2, Views>>...>>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto end()
//		requires (!(hamon::ranges::detail::simple_view<Views> && ...))
	{
		return end_impl<false>(this, hamon::detail::overload_priority<1>{});
	}

	template <bool C2 = true,
		typename = hamon::enable_if_t<
			hamon::detail::all_v<hamon::ranges::range<hamon::ranges::detail::maybe_const<C2, Views>>...> &&
			hamon::ranges::detail::concatable<hamon::ranges::detail::maybe_const<C2, Views>...>>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto end() const
//		requires (hamon::ranges::range<const Views> && ...) && hamon::ranges::detail::concatable<const Views...>
	{
		return end_impl<true>(this, hamon::detail::overload_priority<1>{});
	}

private:
	struct sum_unsigned_like
	{
#if defined(HAMON_HAS_CXX17_FOLD_EXPRESSIONS)
		template <typename... Args, typename CT = hamon::ranges::detail::make_unsigned_like_t<hamon::common_type_t<Args...>>>
		HAMON_CXX11_CONSTEXPR CT operator()(Args... sizes) const
		{
			return (CT(sizes) + ...);
		}
#else
		template <typename CT, typename T>
		HAMON_CXX11_CONSTEXPR CT impl(T s) const
		{
			return CT(s);
		}

		template <typename CT, typename T, typename... Rest>
		HAMON_CXX11_CONSTEXPR CT impl(T s, Rest... rest) const
		{
			return CT(s) + impl<CT>(rest...);
		}

		template <typename... Args>
		HAMON_CXX11_CONSTEXPR auto operator()(Args... sizes) const
		{
			using CT = hamon::ranges::detail::make_unsigned_like_t<hamon::common_type_t<Args...>>;
			return impl<CT>(sizes...);
		}
#endif
	};

public:
	template <bool C2 = false,
		typename = hamon::enable_if_t<hamon::detail::all_v<
			hamon::ranges::sized_range<hamon::ranges::detail::maybe_const<C2, Views>>...>>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto size()
//		requires (hamon::ranges::sized_range<Views> && ...)
	{
		// [range.concat.view]/8
		return hamon::apply(sum_unsigned_like{},
			hamon::ranges::detail::tuple_transform(hamon::ranges::size, views_));
	}

	template <bool C2 = true,
		typename = hamon::enable_if_t<hamon::detail::all_v<
			hamon::ranges::sized_range<hamon::ranges::detail::maybe_const<C2, Views>>...>>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto size() const
//		requires (hamon::ranges::sized_range<const Views> && ...)
	{
		// [range.concat.view]/8
		return hamon::apply(sum_unsigned_like{},
			hamon::ranges::detail::tuple_transform(hamon::ranges::size, views_));
	}

	template <bool C2 = false,
		typename = hamon::enable_if_t<hamon::detail::all_v<
			hamon::ranges::approximately_sized_range<hamon::ranges::detail::maybe_const<C2, Views>>...>>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	auto reserve_hint()
//		requires (hamon::ranges::approximately_sized_range<Views> && ...)
	{
		// [range.concat.view]/9
		return hamon::apply(sum_unsigned_like{},
			hamon::ranges::detail::tuple_transform(hamon::ranges::reserve_hint, views_));
	}

	template <bool C2 = true,
		typename = hamon::enable_if_t<hamon::detail::all_v<
			hamon::ranges::approximately_sized_range<hamon::ranges::detail::maybe_const<C2, Views>>...>>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	auto reserve_hint() const
//		requires (hamon::ranges::approximately_sized_range<const Views> && ...)
	{
		// [range.concat.view]/9
		return hamon::apply(sum_unsigned_like{},
			hamon::ranges::detail::tuple_transform(hamon::ranges::reserve_hint, views_));
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename... R>
concat_view(R&&...) -> concat_view<hamon::views::all_t<R>...>;

#endif

}	// inline namespace concat_view_ns

namespace views {
namespace detail {

// [range.concat.overview]/2
struct concat_fn : public hamon::ranges::range_adaptor_closure<concat_fn>
{
	// [range.concat.overview]/2.1
	template <HAMON_CONSTRAINT(hamon::ranges::input_range, R)>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	auto operator()(R&& t) const
	{
		return hamon::views::all(hamon::forward<R>(t));
	}

	// [range.concat.overview]/2.2
	template <typename... Ts>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR
	auto operator()(Ts&&... ts) const
#if defined(HAMON_HAS_CXX20_CONCEPTS)
		requires requires { concat_view(hamon::declval<Ts>()...); }
#else
	// TODO
#endif
	{
		return concat_view<hamon::views::all_t<Ts>...>(hamon::forward<Ts>(ts)...);
	}
};

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::concat_fn concat{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_CONCAT_VIEW_HPP
