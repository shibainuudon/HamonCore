/**
 *	@file	vector_xyzw.hpp
 *
 *	@brief	vector_xyzw の定義
 */

#ifndef HAMON_QVM_DETAIL_VECTOR_XYZW_HPP
#define HAMON_QVM_DETAIL_VECTOR_XYZW_HPP

#include <hamon/qvm/detail/vector_base.hpp>
#include <hamon/qvm/detail/swizzle_operator.hpp>
#include <cstddef>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T, std::size_t N>
class vector_xyzw : public vector_base<T, N>
{
private:
	using base_type = vector_base<T, N>;
public:
	using base_type::base_type;
};

#if 0
template <typename T>
class vector_xyzw<T, 2> : public vector_base<T, 2>
{
private:
	using base_type = vector_base<T, 2>;
public:
	using base_type::base_type;

	HAMON_QVM_NAMED_ACCESS(x, 0);
	HAMON_QVM_NAMED_ACCESS(y, 1);
	HAMON_QVM_SWIZZLE_OPERATOR((x)(y));
};

template <typename T>
class vector_xyzw<T, 3> : public vector_base<T, 3>
{
private:
	using base_type = vector_base<T, 3>;
public:
	using base_type::base_type;

	HAMON_QVM_NAMED_ACCESS(x, 0);
	HAMON_QVM_NAMED_ACCESS(y, 1);
	HAMON_QVM_NAMED_ACCESS(z, 2);
	HAMON_QVM_SWIZZLE_OPERATOR((x)(y)(z));
};

template <typename T>
class vector_xyzw<T, 4> : public vector_base<T, 4>
{
private:
	using base_type = vector_base<T, 4>;
public:
	using base_type::base_type;

	HAMON_QVM_NAMED_ACCESS(x, 0);
	HAMON_QVM_NAMED_ACCESS(y, 1);
	HAMON_QVM_NAMED_ACCESS(z, 2);
	HAMON_QVM_NAMED_ACCESS(w, 3);
	HAMON_QVM_SWIZZLE_OPERATOR((x)(y)(z)(w));
};
#else
template <typename T>
class vector_xyzw<T, 2> : public vector_base<T, 2>
{
private:
	using base_type = vector_base<T, 2>;
public:
	using base_type::base_type;

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T& x(void)       HAMON_NOEXCEPT { return (*this)[0]; }
	HAMON_NODISCARD HAMON_CONSTEXPR T const& x(void) const HAMON_NOEXCEPT { return (*this)[0]; };
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T& y(void)       HAMON_NOEXCEPT { return (*this)[1]; }
	HAMON_NODISCARD HAMON_CONSTEXPR T const& y(void) const HAMON_NOEXCEPT { return (*this)[1]; };
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxxx(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxxy(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxyx(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxyy(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyxx(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyxy(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyyx(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyyy(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxxx(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxxy(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxyx(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxyy(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyxx(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyxy(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyyx(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyyy(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xxx(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xxy(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xyx(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xyy(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yxx(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yxy(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yyx(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yyy(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> xx(void) const HAMON_NOEXCEPT { return { this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> xy(void) const HAMON_NOEXCEPT { return { this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> yx(void) const HAMON_NOEXCEPT { return { this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> yy(void) const HAMON_NOEXCEPT { return { this->y(), this->y() }; }
};

template <typename T>
class vector_xyzw<T, 3> : public vector_base<T, 3>
{
private:
	using base_type = vector_base<T, 3>;
public:
	using base_type::base_type;

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T& x(void)       HAMON_NOEXCEPT { return (*this)[0]; }
	HAMON_NODISCARD HAMON_CONSTEXPR T const& x(void) const HAMON_NOEXCEPT { return (*this)[0]; };
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T& y(void)       HAMON_NOEXCEPT { return (*this)[1]; }
	HAMON_NODISCARD HAMON_CONSTEXPR T const& y(void) const HAMON_NOEXCEPT { return (*this)[1]; };
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T& z(void)       HAMON_NOEXCEPT { return (*this)[2]; }
	HAMON_NODISCARD HAMON_CONSTEXPR T const& z(void) const HAMON_NOEXCEPT { return (*this)[2]; };
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxxx(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxxy(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxxz(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxyx(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxyy(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxyz(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxzx(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxzy(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxzz(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyxx(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyxy(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyxz(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyyx(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyyy(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyyz(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyzx(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyzy(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyzz(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzxx(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzxy(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzxz(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzyx(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzyy(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzyz(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzzx(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzzy(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzzz(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxxx(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxxy(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxxz(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxyx(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxyy(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxyz(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxzx(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxzy(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxzz(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyxx(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyxy(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyxz(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyyx(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyyy(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyyz(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyzx(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyzy(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyzz(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzxx(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzxy(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzxz(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzyx(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzyy(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzyz(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzzx(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzzy(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzzz(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxxx(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxxy(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxxz(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxyx(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxyy(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxyz(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxzx(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxzy(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxzz(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyxx(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyxy(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyxz(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyyx(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyyy(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyyz(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyzx(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyzy(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyzz(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzxx(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzxy(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzxz(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzyx(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzyy(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzyz(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzzx(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzzy(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzzz(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xxx(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xxy(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xxz(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xyx(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xyy(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xyz(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xzx(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xzy(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xzz(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yxx(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yxy(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yxz(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yyx(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yyy(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yyz(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yzx(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yzy(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yzz(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zxx(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zxy(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zxz(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zyx(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zyy(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zyz(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zzx(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zzy(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zzz(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> xx(void) const HAMON_NOEXCEPT { return { this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> xy(void) const HAMON_NOEXCEPT { return { this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> xz(void) const HAMON_NOEXCEPT { return { this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> yx(void) const HAMON_NOEXCEPT { return { this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> yy(void) const HAMON_NOEXCEPT { return { this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> yz(void) const HAMON_NOEXCEPT { return { this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> zx(void) const HAMON_NOEXCEPT { return { this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> zy(void) const HAMON_NOEXCEPT { return { this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> zz(void) const HAMON_NOEXCEPT { return { this->z(), this->z() }; }
};

template <typename T>
class vector_xyzw<T, 4> : public vector_base<T, 4>
{
private:
	using base_type = vector_base<T, 4>;
public:
	using base_type::base_type;

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T& x(void)       HAMON_NOEXCEPT { return (*this)[0]; }
	HAMON_NODISCARD HAMON_CONSTEXPR T const& x(void) const HAMON_NOEXCEPT { return (*this)[0]; };
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T& y(void)       HAMON_NOEXCEPT { return (*this)[1]; }
	HAMON_NODISCARD HAMON_CONSTEXPR T const& y(void) const HAMON_NOEXCEPT { return (*this)[1]; };
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T& z(void)       HAMON_NOEXCEPT { return (*this)[2]; }
	HAMON_NODISCARD HAMON_CONSTEXPR T const& z(void) const HAMON_NOEXCEPT { return (*this)[2]; };
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T& w(void)       HAMON_NOEXCEPT { return (*this)[3]; }
	HAMON_NODISCARD HAMON_CONSTEXPR T const& w(void) const HAMON_NOEXCEPT { return (*this)[3]; };
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxxx(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxxy(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxxz(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxxw(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxyx(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxyy(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxyz(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxyw(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxzx(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxzy(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxzz(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxzw(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxwx(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxwy(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxwz(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xxww(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyxx(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyxy(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyxz(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyxw(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyyx(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyyy(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyyz(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyyw(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyzx(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyzy(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyzz(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyzw(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xywx(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xywy(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xywz(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xyww(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzxx(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzxy(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzxz(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzxw(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzyx(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzyy(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzyz(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzyw(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzzx(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzzy(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzzz(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzzw(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzwx(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzwy(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzwz(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xzww(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwxx(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwxy(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwxz(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwxw(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwyx(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwyy(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwyz(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwyw(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwzx(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwzy(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwzz(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwzw(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwwx(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwwy(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwwz(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> xwww(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxxx(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxxy(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxxz(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxxw(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxyx(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxyy(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxyz(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxyw(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxzx(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxzy(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxzz(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxzw(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxwx(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxwy(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxwz(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yxww(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyxx(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyxy(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyxz(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyxw(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyyx(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyyy(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyyz(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyyw(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyzx(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyzy(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyzz(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyzw(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yywx(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yywy(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yywz(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yyww(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzxx(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzxy(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzxz(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzxw(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzyx(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzyy(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzyz(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzyw(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzzx(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzzy(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzzz(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzzw(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzwx(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzwy(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzwz(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> yzww(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywxx(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywxy(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywxz(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywxw(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywyx(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywyy(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywyz(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywyw(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywzx(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywzy(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywzz(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywzw(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywwx(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywwy(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywwz(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> ywww(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxxx(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxxy(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxxz(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxxw(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxyx(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxyy(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxyz(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxyw(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxzx(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxzy(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxzz(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxzw(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxwx(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxwy(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxwz(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zxww(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyxx(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyxy(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyxz(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyxw(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyyx(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyyy(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyyz(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyyw(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyzx(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyzy(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyzz(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyzw(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zywx(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zywy(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zywz(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zyww(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzxx(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzxy(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzxz(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzxw(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzyx(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzyy(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzyz(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzyw(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzzx(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzzy(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzzz(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzzw(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzwx(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzwy(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzwz(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zzww(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwxx(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwxy(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwxz(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwxw(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwyx(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwyy(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwyz(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwyw(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwzx(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwzy(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwzz(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwzw(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwwx(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwwy(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwwz(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> zwww(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxxx(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxxy(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxxz(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxxw(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxyx(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxyy(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxyz(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxyw(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxzx(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxzy(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxzz(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxzw(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxwx(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxwy(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxwz(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wxww(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyxx(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyxy(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyxz(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyxw(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyyx(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyyy(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyyz(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyyw(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyzx(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyzy(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyzz(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyzw(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wywx(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wywy(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wywz(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wyww(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzxx(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzxy(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzxz(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzxw(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzyx(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzyy(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzyz(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzyw(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzzx(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzzy(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzzz(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzzw(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzwx(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzwy(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzwz(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wzww(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwxx(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwxy(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwxz(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwxw(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwyx(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwyy(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwyz(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwyw(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwzx(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwzy(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwzz(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwzw(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwwx(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwwy(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwwz(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 4> wwww(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xxx(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xxy(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xxz(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xxw(void) const HAMON_NOEXCEPT { return { this->x(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xyx(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xyy(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xyz(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xyw(void) const HAMON_NOEXCEPT { return { this->x(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xzx(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xzy(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xzz(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xzw(void) const HAMON_NOEXCEPT { return { this->x(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xwx(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xwy(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xwz(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> xww(void) const HAMON_NOEXCEPT { return { this->x(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yxx(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yxy(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yxz(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yxw(void) const HAMON_NOEXCEPT { return { this->y(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yyx(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yyy(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yyz(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yyw(void) const HAMON_NOEXCEPT { return { this->y(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yzx(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yzy(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yzz(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yzw(void) const HAMON_NOEXCEPT { return { this->y(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> ywx(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> ywy(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> ywz(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> yww(void) const HAMON_NOEXCEPT { return { this->y(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zxx(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zxy(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zxz(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zxw(void) const HAMON_NOEXCEPT { return { this->z(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zyx(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zyy(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zyz(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zyw(void) const HAMON_NOEXCEPT { return { this->z(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zzx(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zzy(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zzz(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zzw(void) const HAMON_NOEXCEPT { return { this->z(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zwx(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zwy(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zwz(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> zww(void) const HAMON_NOEXCEPT { return { this->z(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wxx(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wxy(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wxz(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wxw(void) const HAMON_NOEXCEPT { return { this->w(), this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wyx(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wyy(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wyz(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wyw(void) const HAMON_NOEXCEPT { return { this->w(), this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wzx(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wzy(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wzz(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wzw(void) const HAMON_NOEXCEPT { return { this->w(), this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wwx(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wwy(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> wwz(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 3> www(void) const HAMON_NOEXCEPT { return { this->w(), this->w(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> xx(void) const HAMON_NOEXCEPT { return { this->x(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> xy(void) const HAMON_NOEXCEPT { return { this->x(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> xz(void) const HAMON_NOEXCEPT { return { this->x(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> xw(void) const HAMON_NOEXCEPT { return { this->x(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> yx(void) const HAMON_NOEXCEPT { return { this->y(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> yy(void) const HAMON_NOEXCEPT { return { this->y(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> yz(void) const HAMON_NOEXCEPT { return { this->y(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> yw(void) const HAMON_NOEXCEPT { return { this->y(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> zx(void) const HAMON_NOEXCEPT { return { this->z(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> zy(void) const HAMON_NOEXCEPT { return { this->z(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> zz(void) const HAMON_NOEXCEPT { return { this->z(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> zw(void) const HAMON_NOEXCEPT { return { this->z(), this->w() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> wx(void) const HAMON_NOEXCEPT { return { this->w(), this->x() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> wy(void) const HAMON_NOEXCEPT { return { this->w(), this->y() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> wz(void) const HAMON_NOEXCEPT { return { this->w(), this->z() }; }
	HAMON_NODISCARD HAMON_CONSTEXPR vector<T, 2> ww(void) const HAMON_NOEXCEPT { return { this->w(), this->w() }; }
};
#endif

}	// namespace detail

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_DETAIL_VECTOR_XYZW_HPP
