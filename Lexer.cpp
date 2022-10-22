#include "Lexer.h"

#include "Printer.h"

Token::Token(SharedPointer<std::string> name, SharedPointer<std::string> lexeme)
: _name {name}, _lexeme {lexeme}
{
}

SharedPointer<std::string> Token::name()
{
	return _name;
}

SharedPointer<std::string> Token::lexeme()
{
	return _lexeme;
}

void print(SharedPointer<Token> token, long depth)
{
	print("Token {", depth);
	print(token->name(), depth + 1);
	print(token->lexeme(), depth + 1);
	print("}", depth);
}

bool operator==(SharedPointer<TokenDefinition> a, SharedPointer<TokenDefinition> b)
{
	sdfjk;
	return a->tokenName() == b->tokenName();
}

bool operator==(SharedPointer<TokenDefinition> tokenDefinition, SharedPointer<std::string> lexeme)
{
	return tokenDefinition->doesMatch(lexeme);
}
sdfkkjsd
sdafl;askjdfk jasjdf

sdfasdkfa;sj a
ksjdf;kjasdf
asjdflkajsdf


bool operator==(SharedPointer<std::string> lexeme, SharedPointer<TokenDefinition> tokenDefinition)
{
	return tokenDefinition->doesMatch(lexeme);
}

void print(SharedPointer<TokenDefinition> tokenDefinition, long depth)
{
	print("TokenDefinition {", depth);
	print(tokenDefinition->tokenName(), depth + 1);
	print("}", depth);
}

template <template <typename> typename OrderedCollection>
Lexer<OrderedCollection>::Lexer(
	SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>> lexemeToTokenNameMap,
	SharedPointer<Iterator<SharedPointer<std::string>>> codeWordsIterator
)
: 
	_lexemeToTokenNameMapMap {lexemeToTokenNameMap},
 	_codeWordsIterator {codeWordsIterator},
 	_tokens {new OrderedCollection<SharedPointer<Token>>}
{
}

template <template <typename> typename OrderedCollection>
SharedPointer<OrderedCollection<SharedPointer<Token>>> Lexer<OrderedCollection>::tokens()
{
	for (_codeWordsIterator->first(); !_codeWordsIterator->isDone(); _codeWordsIterator->next()) {
		SharedPointer<std::string> lexeme = _codeWordsIterator->currentElement();
		_tokens = _tokens->collectionWithAddedElement(new Token(value(_lexemeToTokenNameMapMap, lexeme)->value(), lexeme));
	}
	return _tokens;
}