#include "Lexer.h"

#include "Printer.h"

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

void print(SharedPointer<Token> token, long depth)
{
	print("Token {", depth);
	print(token->name(), depth + 1);
	print(token->viewInCode(), depth + 1);
	print("}", depth);
}

bool operator==(SharedPointer<TokenDefinition> a, SharedPointer<TokenDefinition> b)
{
	return a->tokenName() == b->tokenName();
}

bool operator==(SharedPointer<TokenDefinition> tokenDefinition, SharedPointer<std::string> viewInCode)
{
	return tokenDefinition->isEqual(viewInCode);
}

bool operator==(SharedPointer<std::string> viewInCode, SharedPointer<TokenDefinition> tokenDefinition)
{
	return tokenDefinition->isEqual(viewInCode);
}

void print(SharedPointer<TokenDefinition> tokenDefinition, long depth)
{
	print("TokenDefinition {", depth);
	print(tokenDefinition->tokenName(), depth + 1);
	print("}", depth);
}

template <template <typename> typename OrderedCollection>
Lexer<OrderedCollection>::Lexer(
	SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>> tokenViewInCodeToNameMap,
	SharedPointer<Iterator<SharedPointer<std::string>>> codeWordsIterator
)
: 
	_tokenViewInCodeToNameMap {tokenViewInCodeToNameMap},
 	_codeWordsIterator {codeWordsIterator},
 	_tokens {new OrderedCollection<SharedPointer<Token>>}
{
}

template <template <typename> typename OrderedCollection>
SharedPointer<OrderedCollection<SharedPointer<Token>>> Lexer<OrderedCollection>::tokens()
{
	for (_codeWordsIterator->first(); !_codeWordsIterator->isDone(); _codeWordsIterator->next()) {
		SharedPointer<std::string> tokenViewInCode = _codeWordsIterator->current();
		_tokens = _tokens->collectionWithAddedElement(new Token(value(_tokenViewInCodeToNameMap, tokenViewInCode)->value(), tokenViewInCode));
	}
	return _tokens;
}