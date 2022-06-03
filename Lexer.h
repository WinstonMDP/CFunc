#ifndef LEXER
#define LEXER

#include "MDPLibrary/SharedPointer.h"
#include "Collections.h"
#include <string>

class Token
{
	public:
	Token(SharedPointer<std::string> name, SharedPointer<std::string> viewInCode);
	SharedPointer<std::string> name();
	SharedPointer<std::string> viewInCode();

	private:
	SharedPointer<std::string> _name;
	SharedPointer<std::string> _viewInCode;
};

class TokenDefinition
{
	public:
	virtual SharedPointer<std::string> tokenName() const = 0;
	virtual bool isEqual(SharedPointer<std::string> viewInCode) = 0;
};

bool operator==(SharedPointer<TokenDefinition>, SharedPointer<std::string>);
bool operator==(SharedPointer<std::string>, SharedPointer<TokenDefinition>);

template <template <typename> typename CollectionWithOrder = Array>
class Lexer
{
	public:
	Lexer(
		SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>> tokenViewInCodeToNameMap,
		SharedPointer<Iterator<SharedPointer<std::string>>> codeWordsIterator
	);
	SharedPointer<CollectionWithOrder<SharedPointer<Token>>> tokens();

	private:
	SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>> _tokenViewInCodeToNameMap;
	SharedPointer<Iterator<SharedPointer<std::string>>> _codeWordsIterator;
	SharedPointer<CollectionWithOrder<SharedPointer<Token>>> _tokens;
};

#include "Lexer.cpp"

#endif