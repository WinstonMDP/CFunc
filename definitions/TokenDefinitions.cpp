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
				tokenDefinitionsIterator->current(),
				tokenDefinitionsIterator->current()->tokenName()
			)
		);
	}
}

Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>* TokenDefinitions::tokenViewInCodeToNameMap()
{
	return _tokenViewInCodeToNameMap.primitivePointer();
}

DefaultTokenDefinition::DefaultTokenDefinition(SharedPointer<std::string> tokenName, SharedPointer<std::string> viewInCode)
: _tokenName {tokenName}, _viewInCode {viewInCode}
{
}

SharedPointer<std::string> DefaultTokenDefinition::tokenName() const
{
	return _tokenName;
}

bool DefaultTokenDefinition::isEqual(SharedPointer<std::string> viewInCode)
{
	return *_viewInCode == *viewInCode;
}

OtherTokenDefinition::OtherTokenDefinition(SharedPointer<std::string> tokenName)
: _tokenName {tokenName}
{
}

SharedPointer<std::string> OtherTokenDefinition::tokenName() const
{
	return _tokenName;
}

bool OtherTokenDefinition::isEqual(SharedPointer<std::string> viewInCode)
{
	return true;
}

bool operator<(const TokenDefinition& a, const TokenDefinition& b)
{
	return a.tokenName() < b.tokenName();
} 

template <typename Value>
bool operator<(const SharedPointer<Value>& a, const SharedPointer<Value>& b)
{
	return *a < *b;
}