#ifndef LEXER
#define LEXER

#include <string>

#include "projectStructures/Array.h"
#include "projectStructures/Map.h"

#include "MDPLibrary/SharedPointer.h"

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

void print(SharedPointer<Token>, long depth = 0);

class TokenDefinition
{
	public:
	virtual SharedPointer<std::string> tokenName() const = 0;
	virtual bool isEqual(SharedPointer<std::string> viewInCode) = 0;
};

bool operator==(SharedPointer<TokenDefinition>, SharedPointer<std::string>);
bool operator==(SharedPointer<std::string>, SharedPointer<TokenDefinition>);

void print(SharedPointer<TokenDefinition>, long depth = 0);

template <template <typename> typename OrderedCollection = DefaultArray>
class Lexer
{
	public:
	Lexer(
		SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>> tokenViewInCodeToNameMap,
		SharedPointer<Iterator<SharedPointer<std::string>>> codeWordsIterator
	);
	SharedPointer<OrderedCollection<SharedPointer<Token>>> tokens();

	private:
	SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>> _tokenViewInCodeToNameMap;
	SharedPointer<Iterator<SharedPointer<std::string>>> _codeWordsIterator;
	SharedPointer<OrderedCollection<SharedPointer<Token>>> _tokens;
};

#include "Lexer.cpp"

#endif