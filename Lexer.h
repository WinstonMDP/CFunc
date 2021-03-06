#ifndef LEXER
#define LEXER

#include <string>

#include "MDPLibrary/SharedPointer.h"
#include "projectStructures/Array.h"
#include "projectStructures/Map.h"

class Token
{
	public:
	Token(SharedPointer<std::string> name, SharedPointer<std::string> lexeme);
	SharedPointer<std::string> name();
	SharedPointer<std::string> lexeme();

	private:
	SharedPointer<std::string> _name;
	SharedPointer<std::string> _lexeme;
};

void print(SharedPointer<Token>, long depth = 0);

class TokenDefinition
{
	public:
	virtual SharedPointer<std::string> tokenName() const = 0;
	virtual bool doesMatch(SharedPointer<std::string> lexeme) = 0;
	virtual ~TokenDefinition() = default;
};

bool operator==(SharedPointer<TokenDefinition>, SharedPointer<TokenDefinition>);
bool operator==(SharedPointer<TokenDefinition>, SharedPointer<std::string>);
bool operator==(SharedPointer<std::string>, SharedPointer<TokenDefinition>);

void print(SharedPointer<TokenDefinition>, long depth = 0);

template <template <typename> typename OrderedCollection = DefaultArray>
class Lexer
{
	public:
	Lexer(
		SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>> lexemeToTokenNameMap,
		SharedPointer<Iterator<SharedPointer<std::string>>> codeWordsIterator
	);
	SharedPointer<OrderedCollection<SharedPointer<Token>>> tokens();

	private:
	SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>> _lexemeToTokenNameMapMap;
	SharedPointer<Iterator<SharedPointer<std::string>>> _codeWordsIterator;
	SharedPointer<OrderedCollection<SharedPointer<Token>>> _tokens;
};

#include "Lexer.cpp"

#endif