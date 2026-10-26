/**
 *	@file	unstoppable_token.hpp
 *
 *	@brief	unstoppable_token の定義
 */

#ifndef HAMON_STOP_TOKEN_UNSTOPPABLE_TOKEN_HPP
#define HAMON_STOP_TOKEN_UNSTOPPABLE_TOKEN_HPP

#include <hamon/stop_token/stoppable_token.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 32.3.3 Stop token concepts[stoptoken.concepts]

// [stoptoken.concepts]/4

// 規格通りに記述すると、
// requires (const Token tok) {
// 	requires bool_constant<(!tok.stop_possible())>::value;
// };
// の部分がgccとclangでエラーになる(tokが定数式内で使えない)。
// 回避策としてヘルパー関数を通すようにしたが、それによって
// constexprにデフォルトコンストラクト可能であるという要求が追加されてしまった。

template <typename Token>
constexpr bool unstoppable_token_helper(Token const& tok)
{
	return tok.stop_possible();
}

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Token>
HAMON_CONCEPT_OR_BOOL unstoppable_token =
	hamon::stoppable_token<Token> &&
	requires
	{
		requires hamon::bool_constant<(!unstoppable_token_helper(Token()))>::value;
	};

#else

template <typename Token>
struct unstoppable_token_impl
{
private:
	template <typename Token2,
		typename = hamon::enable_if_t<hamon::stoppable_token<Token2>>,
		typename = hamon::enable_if_t<hamon::bool_constant<!unstoppable_token_helper(Token2())>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename Token2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Token>(0));
};

template <typename Token>
HAMON_CONCEPT_OR_BOOL unstoppable_token =
	unstoppable_token_impl<Token>::type::value;

#endif

}	// namespace hamon

#endif // HAMON_STOP_TOKEN_UNSTOPPABLE_TOKEN_HPP
