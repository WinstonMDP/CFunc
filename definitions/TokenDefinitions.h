#ifndef TOKEN_DEFINITIONS
#define TOKEN_DEFINITIONS

#include <string>

#include "../Lexer.h"

#include "../MDPLibrary/SharedPointer.h"
#include "../MDPLibrary/Structures.h"

class TokenDefinitions
{
	public:
	TokenDefinitions();
	SharedPointer<Collection<SharedPointer<TokenDefinition>>> tokenDefinitionsCollection();

	private:
	SharedPointer<Collection<SharedPointer<TokenDefinition>>> _tokenDefinitionsCollection;
};

class DefaultTokenDefinition : public TokenDefinition
{
	public:
	DefaultTokenDefinition(SharedPointer<std::string> tokenName, SharedPointer<std::string> viewInCode);
	SharedPointer<std::string> tokenName() const override;
	bool isEqual(SharedPointer<std::string> viewInCode) override;

	private:
	SharedPointer<std::string> _tokenName;
	SharedPointer<std::string> _viewInCode;
};

class OtherTokenDefinition : public TokenDefinition
{
	public:
	OtherTokenDefinition(SharedPointer<std::string> tokenName);
	SharedPointer<std::string> tokenName() const override;
	bool isEqual(SharedPointer<std::string> viewInCode) override;

	private:
	SharedPointer<std::string> _tokenName;
};

bool operator<(const TokenDefinition& a, const TokenDefinition& b);
template <typename Value>
bool operator<(const SharedPointer<Value>& a, const SharedPointer<Value>& b);

#include "TokenDefinitions.cpp"

#endif