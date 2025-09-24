/**
 *	@file	valarray_transcend.hpp
 *
 *	@brief	valarray の定義
 */

#ifndef HAMON_VALARRAY_DETAIL_VALARRAY_TRANSCEND_HPP
#define HAMON_VALARRAY_DETAIL_VALARRAY_TRANSCEND_HPP

#include <hamon/cmath/abs.hpp>
#include <hamon/cmath/acos.hpp>
#include <hamon/cmath/asin.hpp>
#include <hamon/cmath/atan.hpp>
#include <hamon/cmath/atan2.hpp>
#include <hamon/cmath/cos.hpp>
#include <hamon/cmath/cosh.hpp>
#include <hamon/cmath/exp.hpp>
#include <hamon/cmath/log.hpp>
#include <hamon/cmath/log10.hpp>
#include <hamon/cmath/pow.hpp>
#include <hamon/cmath/sin.hpp>
#include <hamon/cmath/sinh.hpp>
#include <hamon/cmath/sqrt.hpp>
#include <hamon/cmath/tan.hpp>
#include <hamon/cmath/tanh.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 29.6.3.3 Transcendentals[valarray.transcend]

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
abs(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = abs(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
acos(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = acos(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
asin(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = asin(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
atan(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = atan(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
atan2(valarray<T> const& x, valarray<T> const& y)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = atan2(x[i], y[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
atan2(valarray<T> const& x, typename valarray<T>::value_type const& y)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = atan2(x[i], y);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
atan2(typename valarray<T>::value_type const& x, valarray<T> const& y)
{
	hamon::size_t const size = y.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = atan2(x, y[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
cos(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = cos(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
cosh(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = cosh(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
exp(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = exp(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
log(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = log(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
log10(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = log10(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
pow(valarray<T> const& x, valarray<T> const& y)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = pow(x[i], y[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
pow(valarray<T> const& x, typename valarray<T>::value_type const& y)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = pow(x[i], y);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
pow(typename valarray<T>::value_type const& x, valarray<T> const& y)
{
	hamon::size_t const size = y.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = pow(x, y[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
sin(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = sin(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
sinh(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = sinh(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
sqrt(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = sqrt(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
tan(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = tan(x[i]);
	}
	return result;
}

template <typename T>
HAMON_NODISCARD HAMON_CXX20_CONSTEXPR valarray<T>
tanh(valarray<T> const& x)
{
	hamon::size_t const size = x.size();
	valarray<T> result(size);
	for (hamon::size_t i = 0; i < size; ++i)
	{
		result[i] = tanh(x[i]);
	}
	return result;
}

}	// namespace hamon

#endif // HAMON_VALARRAY_DETAIL_VALARRAY_TRANSCEND_HPP
