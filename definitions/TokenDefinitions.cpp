#include "TokenDefinitions.h"

TokenDefinitions::TokenDefinitions()
{
	_tokenDefinitionsCollection = new DefaultArray<SharedPointer<TokenDefinition>> {
		new DefaultTokenDefinition(new std::string("define"), new std::string("=")),
		new DefaultTokenDefinition(new std::string("lambda-abstraction-operator"), new std::string(".")),
		new DefaultTokenDefinition(new std::string("end-definition-operator"), new std::string(";")),
		new DefaultTokenDefinition(new std::string("opening-course-bracket"), new std::string("(")),
		new DefaultTokenDefinition(new std::string("closing-course-bracket"), new std::string(")")),
		new DefaultTokenDefinition(new std::string("compiler-validation-bracket"), new std::string("\"")),
		new OtherTokenDefinition(new std::string("variable"))
	};
	_tokenViewInCodeToNameMap = new OrderedByValueMap<SharedPointer<TokenDefinition>, SharedPointer<std::string>>;
	SharedPointer<Iterator<SharedPointer<TokenDefinition>>> tokenDefinitionsIterator = _tokenDefinitionsCollection->iterator();
	for (tokenDefinitionsIterator->first(); !tokenDefinitionsIterator->isDone(); tokenDefinitionsIterator->next()) {
		_tokenViewInCodeToNameMap = _tokenViewInCodeToNameMap->collectionWithAddedElement(
			new DefaultPair<SharedPointer<TokenDefinition>, SharedPointer<std::string>>(
				tokenDefinitionsIterator->currentElement(),
				tokenDefinitionsIterator->currentElement()->tokenName()
			)
		);
	}
}

Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>* TokenDefinitions::lexemeToTokenNameMap()
{
	return _tokenViewInCodeToNameMap.primitivePointer();
}

DefaultTokenDefinition::DefaultTokenDefinition(SharedPointer<std::string> tokenName, SharedPointer<std::string> lexeme)
: _tokenName {tokenName}, _lexeme {lexeme}
{
}

SharedPointer<std::string> DefaultTokenDefinition::tokenName() const
{
	return _tokenName;
}

bool DefaultTokenDefinition::isEqual(SharedPointer<std::string> lexeme)
{
	return *_lexeme == *lexeme;
}

OtherTokenDefinition::OtherTokenDefinition(SharedPointer<std::string> tokenName)
: _tokenName {tokenName}
{
}

SharedPointer<std::string> OtherTokenDefinition::tokenName() const
{
	return _tokenName;
}

bool OtherTokenDefinition::isEqual(SharedPointer<std::string> lexeme)
{
	return true;
}

bool operator<(const TokenDefinition& a, const TokenDefinition& b)
{
	return a.tokenName() < b.tokenName();
} 