#include "Lexer.h"

Token::Token(SharedPointer<std::string> name, SharedPointer<std::string> viewInCode)
: _name {name}, _viewInCode {viewInCode}
{
}

SharedPointer<std::string> Token::name()
{
	return _name;
}

SharedPointer<std::string> Token::viewInCode()
{
	return _viewInCode;
}

bool operator==(SharedPointer<TokenDefinition> tokenDefinition, SharedPointer<std::string> viewInCode)
{
	return tokenDefinition->isEqual(viewInCode);
}

bool operator==(SharedPointer<std::string> viewInCode, SharedPointer<TokenDefinition> tokenDefinition)
{
	return tokenDefinition->isEqual(viewInCode);
}

template <template <typename> typename CollectionWithOrder>
Lexer<CollectionWithOrder>::Lexer(
	SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>> tokenViewInCodeToNameMap,
	SharedPointer<Iterator<SharedPointer<std::string>>> codeWordsIterator
)
: 
	_tokenViewInCodeToNameMap {tokenViewInCodeToNameMap},
 	_codeWordsIterator {codeWordsIterator},
 	_tokens {new CollectionWithOrder<SharedPointer<Token>>()}
{
}

template <template <typename> typename CollectionWithOrder>
SharedPointer<CollectionWithOrder<SharedPointer<Token>>> Lexer<CollectionWithOrder>::tokens()
{
	for (_codeWordsIterator->first(); !_codeWordsIterator->isDone(); _codeWordsIterator->next()) {
		SharedPointer<std::string> tokenViewInCode = _codeWordsIterator->current();
		_tokens->add(new Token(value(_tokenViewInCodeToNameMap, tokenViewInCode)->value(), tokenViewInCode));
	}
	return _tokens;
}