/**
 *	@file	unit_test_ios_streamsize.cpp
 *
 *	@brief	streamsize のテスト
 */

#include <hamon/ios/streamsize.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_signed.hpp>

static_assert(hamon::is_integral_v<hamon::streamsize>, "");
static_assert(hamon::is_signed_v<hamon::streamsize>, "");
