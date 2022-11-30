/**
 *	@file	vector.hpp
 *
 *	@brief	vector の定義
 */

#ifndef HAMON_QVM_VECTOR_VECTOR_HPP
#define HAMON_QVM_VECTOR_VECTOR_HPP

#include <hamon/qvm/vector/vector_fwd.hpp>
#include <hamon/qvm/vector/vector_cat.hpp>
#include <hamon/qvm/detail/vector_xyzw.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/disjunction.hpp>
#include <hamon/type_traits/is_implicitly_constructible.hpp>
#include <hamon/type_traits/accumulation.hpp>
#include <hamon/utility/make_index_sequence.hpp>
#include <hamon/config.hpp>
#include <cstddef>
#include <type_traits>

namespace hamon
{

namespace qvm
{

namespace detail
{

template <typename T, typename = hamon::enable_if_t<std::is_arithmetic<T>::value>>
HAMON_CONSTEXPR vector<T, 1> to_vector(T const& v)
{
	return vector<T, 1>{v};
}

template <typename T, std::size_t N>
HAMON_CONSTEXPR vector<T, N> to_vector(vector<T, N> const& v)
{
	return v;
}

}	// namespace detail

template <typename T, std::size_t N>
class vector : public hamon::qvm::detail::vector_xyzw<T, N>
{
private:
	using base_type = hamon::qvm::detail::vector_xyzw<T, N>;

public:
	using value_type             = typename base_type::value_type;
	using pointer                = typename base_type::pointer;
	using const_pointer          = typename base_type::const_pointer;
	using reference              = typename base_type::reference;
	using const_reference        = typename base_type::const_reference;
	using size_type              = typename base_type::size_type;
	using difference_type        = typename base_type::difference_type;
	using iterator               = typename base_type::iterator;
	using const_iterator         = typename base_type::const_iterator;
	using reverse_iterator       = typename base_type::reverse_iterator;
	using const_reverse_iterator = typename base_type::const_reverse_iterator;

	static const size_type static_size = N;

public:
	/**
	 *	@brief	デフォルトコンストラクタ
	 */
	HAMON_CONSTEXPR
	vector() HAMON_NOEXCEPT
		: base_type{}
	{}
	
	/**
	 *	@brief	スカラー型1つのコンストラクタ
	 *
	 *	全ての要素に引数がコピーされる
	 */
	explicit HAMON_CONSTEXPR
	vector(T const& v) HAMON_NOEXCEPT
		: vector{ v, hamon::make_index_sequence<N>{} }
	{}

	/**
	 *	@brief	スカラー型N個のコンストラクタ
	 */
	template <typename... Args,
		hamon::enable_if_t<
			(sizeof...(Args) != 1) &&
			(sizeof...(Args) == N) &&
			hamon::conjunction<
				hamon::is_implicitly_constructible<T, Args>...
			>::value
		>* = nullptr
	>
	HAMON_CONSTEXPR
	vector(Args const&... args) HAMON_NOEXCEPT
		: base_type{args...}
	{}

	/**
	 *	@brief	スカラー型またはベクトル型を受け取るコンストラクタ
	 * 
	 *	全ての引数に含まれる要素を順番に連結し、ベクトル型を生成します。
	 *	連結した要素数がNのときのみオーバーロード候補になります。
	 */
	template <typename... Args,
		typename = hamon::enable_if_t<
			(sizeof...(Args) != 1) &&
			(sizeof...(Args) != N)
		>,
		typename Concatnated =
			decltype(vector_cat(detail::to_vector(std::declval<Args>())...)),
		typename = hamon::enable_if_t<
			Concatnated::static_size == N
		>
	>
	explicit HAMON_CONSTEXPR
	vector(Args const&... args) HAMON_NOEXCEPT
		: vector{ vector_cat(detail::to_vector(args)...) }
	{}

	/**
	 *	@brief	vector<U, N>からのコンストラクタ
	 */
	template <
		typename U,
		typename = hamon::enable_if_t<
			hamon::is_implicitly_constructible<T, U>::value
		>
	>
	HAMON_CONSTEXPR
	vector(vector<U, N> const& rhs) HAMON_NOEXCEPT
		: base_type{ rhs }
	{}

private:
	template <std::size_t I>
	static HAMON_CONSTEXPR T const&
	swallow(T const& v) HAMON_NOEXCEPT
	{
		return v;
	}

	template <std::size_t... Is>
	HAMON_CONSTEXPR
	vector(T const& v, hamon::index_sequence<Is...>) HAMON_NOEXCEPT
		: base_type{ swallow<Is>(v)... }
	{}
};

}	// namespace qvm

}	// namespace hamon

#endif // HAMON_QVM_VECTOR_VECTOR_HPP
