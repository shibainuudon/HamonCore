/**
 *	@file	unit_test_ios_streamoff.cpp
 *
 *	@brief	streamoff のテスト
 */

#include <hamon/ios/streamoff.hpp>
#include <hamon/type_traits/is_integral.hpp>
#include <hamon/type_traits/is_signed.hpp>

static_assert(hamon::is_integral_v<hamon::streamoff>, "");
static_assert(hamon::is_signed_v<hamon::streamoff>, "");
