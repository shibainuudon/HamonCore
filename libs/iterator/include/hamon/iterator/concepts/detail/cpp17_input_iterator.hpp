/**
 *	@file	cpp17_input_iterator.hpp
 *
 *	@brief	cpp17_input_iterator の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_INPUT_ITERATOR_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_INPUT_ITERATOR_HPP

#include <hamon/iterator/concepts/detail/cpp17_iterator.hpp>
#include <hamon/iterator/incrementable_traits.hpp>
#include <hamon/iterator/indirectly_readable_traits.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/signed_integral.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Iter>
concept cpp17_input_iterator =
	cpp17_iterator<Iter> &&
	hamon::equality_comparable<Iter> &&
	requires(Iter it)
	{
		typename hamon::incrementable_traits<Iter>::difference_type;
		typename hamon::indirectly_readable_traits<Iter>::value_type;
		typename hamon::common_reference_t<
			hamon::iter_reference_t<Iter>&&,
			typename hamon::indirectly_readable_traits<Iter>::value_type&
		>;
		typename hamon::common_reference_t<
			decltype(*it++)&&,
			typename hamon::indirectly_readable_traits<Iter>::value_type&
		>;
		requires hamon::signed_integral<typename hamon::incrementable_traits<Iter>::difference_type>;
	};

#else

namespace cpp17_input_iterator_detail
{

template <typename Iter>
struct cpp17_input_iterator_impl
{
private:
	template <typename I2,
		typename = hamon::enable_if_t<cpp17_iterator<I2>::value>,
		typename = hamon::enable_if_t<hamon::equality_comparable<I2>::value>,
		typename D = typename hamon::incrementable_traits<I2>::difference_type,
		typename V = typename hamon::indirectly_readable_traits<I2>::value_type,
		typename = hamon::common_reference_t<hamon::iter_reference_t<I2>&&, V&>,
		typename = hamon::common_reference_t<decltype(*hamon::declval<I2&>()++)&&, V&>,
		typename = hamon::enable_if_t<hamon::signed_integral<D>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename I2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Iter>(0));
};

}	// namespace cpp17_input_iterator_detail

template <typename Iter>
using cpp17_input_iterator =
	typename cpp17_input_iterator_detail::cpp17_input_iterator_impl<Iter>::type;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_CPP17_INPUT_ITERATOR_HPP
