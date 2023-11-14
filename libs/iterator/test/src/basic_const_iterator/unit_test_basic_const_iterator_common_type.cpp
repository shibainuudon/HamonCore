/**
 *	@file	unit_test_basic_const_iterator_common_type.cpp
 *
 *	@brief	common_type のテスト
 *
 *	template<class T, common_with<T> U>
 *		requires input_iterator<common_type_t<T, U>>
 *	struct common_type<basic_const_iterator<T>, U> {                                  // freestanding
 *		using type = basic_const_iterator<common_type_t<T, U>>;
 *	};
 *
 *	template<class T, common_with<T> U>
 *		requires input_iterator<common_type_t<T, U>>
 *	struct common_type<U, basic_const_iterator<T>> {                                  // freestanding
 *		using type = basic_const_iterator<common_type_t<T, U>>;
 *	};
 *
 *	template<class T, common_with<T> U>
 *		requires input_iterator<common_type_t<T, U>>
 *	struct common_type<basic_const_iterator<T>, basic_const_iterator<U>> {            // freestanding
 *		using type = basic_const_iterator<common_type_t<T, U>>;
 *	};
 */

#include <hamon/iterator/basic_const_iterator.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/common_type.hpp>

static_assert(hamon::is_same<hamon::basic_const_iterator<int      *>, hamon::common_type_t<int      *, hamon::basic_const_iterator<int      *>>>::value, "");
static_assert(hamon::is_same<hamon::basic_const_iterator<int const*>, hamon::common_type_t<int      *, hamon::basic_const_iterator<int const*>>>::value, "");
//static_assert(hamon::is_same<hamon::basic_const_iterator<int const*>, hamon::common_type_t<int const*, hamon::basic_const_iterator<int      *>>>::value, "");
static_assert(hamon::is_same<hamon::basic_const_iterator<int const*>, hamon::common_type_t<int const*, hamon::basic_const_iterator<int const*>>>::value, "");

static_assert(hamon::is_same<hamon::basic_const_iterator<int      *>, hamon::common_type_t<hamon::basic_const_iterator<int      *>, int      *>>::value, "");
//static_assert(hamon::is_same<hamon::basic_const_iterator<int const*>, hamon::common_type_t<hamon::basic_const_iterator<int      *>, int const*>>::value, "");
static_assert(hamon::is_same<hamon::basic_const_iterator<int const*>, hamon::common_type_t<hamon::basic_const_iterator<int const*>, int      *>>::value, "");
static_assert(hamon::is_same<hamon::basic_const_iterator<int const*>, hamon::common_type_t<hamon::basic_const_iterator<int const*>, int const*>>::value, "");

static_assert(hamon::is_same<hamon::basic_const_iterator<int      *>, hamon::common_type_t<hamon::basic_const_iterator<int      *>, hamon::basic_const_iterator<int      *>>>::value, "");
static_assert(hamon::is_same<hamon::basic_const_iterator<int const*>, hamon::common_type_t<hamon::basic_const_iterator<int      *>, hamon::basic_const_iterator<int const*>>>::value, "");
static_assert(hamon::is_same<hamon::basic_const_iterator<int const*>, hamon::common_type_t<hamon::basic_const_iterator<int const*>, hamon::basic_const_iterator<int      *>>>::value, "");
static_assert(hamon::is_same<hamon::basic_const_iterator<int const*>, hamon::common_type_t<hamon::basic_const_iterator<int const*>, hamon::basic_const_iterator<int const*>>>::value, "");
