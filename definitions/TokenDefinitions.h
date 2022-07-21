#ifndef TOKEN_DEFINITIONS
#define TOKEN_DEFINITIONS

#include <string>

#include "../Lexer.h"

#include "../MDPLibrary/SharedPointer.h"
#include "../MDPLibrary/Structures.h"
#include "../projectStructures/Map.h"

class TokenDefinitions
{
	public:
	TokenDefinitions();
	Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>* lexemeToTokenNameMap();

	private:
	SharedPointer<Collection<SharedPointer<TokenDefinition>>> _tokenDefinitionsCollection;
	SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>> _lexemeToTokenNameMapMap;
};

class DefaultTokenDefinition : public TokenDefinition
{
	public:
	DefaultTokenDefinition(SharedPointer<std::string> tokenName, SharedPointer<std::string> lexeme);
	SharedPointer<std::string> tokenName() const override;
	bool doesMatch(SharedPointer<std::string> lexeme) override;

	private:
	SharedPointer<std::string> _tokenName;
	SharedPointer<std::string> _lexeme;
};

class OtherTokenDefinition : public TokenDefinition
{
	public:
	OtherTokenDefinition(SharedPointer<std::string> tokenName);
	SharedPointer<std::string> tokenName() const override;
	bool doesMatch(SharedPointer<std::string> lexeme) override;

	private:
	SharedPointer<std::string> _tokenName;
};

bool operator<(const TokenDefinition& a, const TokenDefinition& b);

#include "TokenDefinitions.cpp"

#endif