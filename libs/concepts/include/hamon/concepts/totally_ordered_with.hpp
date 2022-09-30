/**
 *	@file	totally_ordered_with.hpp
 *
 *	@brief	totally_ordered_with の定義
 */

#ifndef HAMON_CONCEPTS_TOTALLY_ORDERED_WITH_HPP
#define HAMON_CONCEPTS_TOTALLY_ORDERED_WITH_HPP

#include <hamon/concepts/config.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::totally_ordered_with;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

#include <hamon/concepts/totally_ordered.hpp>
#include <hamon/concepts/equality_comparable_with.hpp>
#include <hamon/concepts/detail/cref.hpp>
#include <hamon/concepts/detail/partially_ordered_with.hpp>
#include <hamon/type_traits/common_reference.hpp>

namespace hamon
{

template <typename T, typename U>
concept totally_ordered_with =
	hamon::totally_ordered<T> &&
	hamon::totally_ordered<U> &&
	hamon::equality_comparable_with<T, U> &&
	hamon::totally_ordered<hamon::common_reference_t<detail::cref<T>, detail::cref<U>>> &&
	detail::partially_ordered_with<T, U>;

}	// namespace hamon

#else

#include <hamon/concepts/totally_ordered.hpp>
#include <hamon/concepts/equality_comparable_with.hpp>
#include <hamon/concepts/detail/cref.hpp>
#include <hamon/concepts/detail/partially_ordered_with.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T, typename U>
struct totally_ordered_with_impl
{
private:
	template <typename T2, typename U2>
	static auto test(int) -> hamon::conjunction<
		hamon::totally_ordered<T2>,
		hamon::totally_ordered<U2>,
		hamon::equality_comparable_with<T2, U2>,
		hamon::totally_ordered<hamon::common_reference_t<detail::cref<T2>, detail::cref<U2>>>,
		detail::partially_ordered_with<T2, U2>>;

	template <typename T2, typename U2>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T, U>(0));
};

}	// namespace detail

template <typename T, typename U>
using totally_ordered_with =
	typename detail::totally_ordered_with_impl<T, U>::type;

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T, typename U>
using totally_ordered_with_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::totally_ordered_with<T, U>>;
#else
	hamon::totally_ordered_with<T, U>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_TOTALLY_ORDERED_WITH_HPP
