/**
 *	@file	unit_test_iterator_common_iterator_instantiate.cpp
 *
 *	@brief	インスタンス化可能かどうかのテスト
 *
 *	template<input_or_output_iterator I, sentinel_for<I> S>
 *		requires (!same_as<I, S> && copyable<I>)
 *	class common_iterator;
 */

#include <hamon/iterator/common_iterator.hpp>
#include <hamon/iterator/concepts/input_or_output_iterator.hpp>
#include <hamon/iterator/concepts/sentinel_for.hpp>
#include <hamon/iterator/unreachable_sentinel_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/concepts/copyable.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/void_t.hpp>
#include "ranges_test.hpp"

namespace hamon_iterator_test {
namespace common_iterator_test {
namespace instantiate_test {

template <typename T>
struct NoCopyIterator
{
	using difference_type = hamon::ptrdiff_t;
	NoCopyIterator& operator++();
	void            operator++(int);
	T               operator*();
	NoCopyIterator(NoCopyIterator &&) = default;
	NoCopyIterator(NoCopyIterator const&) = delete;
	NoCopyIterator& operator=(NoCopyIterator &&) = default;
	NoCopyIterator& operator=(NoCopyIterator const&) = delete;
};

static_assert( hamon::input_or_output_iterator_t<NoCopyIterator<int>>::value, "");
static_assert(!hamon::copyable_t<NoCopyIterator<int>>::value, "");
static_assert( hamon::movable_t<NoCopyIterator<int>>::value, "");
static_assert( hamon::sentinel_for_t<hamon::unreachable_sentinel_t, NoCopyIterator<int>>::value, "");

template <typename I, typename S, typename = void>
struct CanInstantiate
	: hamon::false_type {};

template <typename I, typename S>
struct CanInstantiate<I, S, hamon::void_t<hamon::common_iterator<I, S>>>
	: hamon::true_type {};

static_assert(!CanInstantiate<int*, int*>::value, "");	// requires !same_as<I, S>
static_assert( CanInstantiate<int*, int const*>::value, "");
static_assert( CanInstantiate<int*, test_sentinel<int*>>::value, "");
static_assert( CanInstantiate<int*, hamon::unreachable_sentinel_t>::value, "");
static_assert(!CanInstantiate<incrementable_wrapper<int>, hamon::unreachable_sentinel_t>::value, "");			// requires input_or_output_iterator<I>
static_assert( CanInstantiate<input_or_output_iterator_wrapper<int>, test_sentinel<input_or_output_iterator_wrapper<int>>>::value, "");
static_assert( CanInstantiate<input_iterator_wrapper<int>, test_sentinel<input_iterator_wrapper<int>>>::value, "");
static_assert(!CanInstantiate<input_iterator_wrapper<int>, test_sentinel<input_iterator_wrapper<int const>>>::value, "");	// requires sentinel_for<S, I>
static_assert( CanInstantiate<input_iterator_wrapper<int>, hamon::unreachable_sentinel_t>::value, "");
static_assert(!CanInstantiate<NoCopyIterator<int>, hamon::unreachable_sentinel_t>::value, "");								// requires copyable<I>

}	// namespace instantiate_test
}	// namespace common_iterator_test
}	// namespace hamon_iterator_test
