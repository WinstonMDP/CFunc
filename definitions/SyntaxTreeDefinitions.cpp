#include "SyntaxTreeDefinitions.h"

SyntaxTreeDefinitions::SyntaxTreeDefinitions()
{
	SharedPointer<SyntaxTreeDefinition> defineOperatorDefinition = new TokenSyntaxTreeDefinition(new std::string("define-token-operator"));
	SharedPointer<SyntaxTreeDefinition> lambdaAbstractionOperatorDefinition = new TokenSyntaxTreeDefinition(new std::string("lambda-abstraction-operator"));
	SharedPointer<SyntaxTreeDefinition> endDefinitionOperatorDefinition = new TokenSyntaxTreeDefinition(new std::string("end-definition-operator"));
	SharedPointer<SyntaxTreeDefinition> openingCourseBracketDefinition = new TokenSyntaxTreeDefinition(new std::string("opening-course-bracket"));
	SharedPointer<SyntaxTreeDefinition> closingCourseBracketDefinition = new TokenSyntaxTreeDefinition(new std::string("closing-course-bracket"));
	SharedPointer<SyntaxTreeDefinition> beginCompilerBlockBracketDefinition = new TokenSyntaxTreeDefinition(new std::string("begin-compiler-block-operator"));
	SharedPointer<SyntaxTreeDefinition> endCompilerBlockBracketDefinition = new TokenSyntaxTreeDefinition(new std::string("end-compiler-block-operator"));
	SharedPointer<SyntaxTreeDefinition> variableDefinition = new TokenSyntaxTreeDefinition(new std::string("variable"));
	SharedPointer<SyntaxTreeDefinition> anythingDefinition = new AnythingSyntaxTreeDefinition;
	SharedPointer<SyntaxTreeDefinition> compilerBlockDefinition = new DefaultSyntaxTreeDefinition(
		new std::string("compiler-block"),
		new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {beginCompilerBlockBracketDefinition, anythingDefinition, endCompilerBlockBracketDefinition}
	);
	SharedPointer<SyntaxTreeDefinition> valueDefinition;
	SharedPointer<SyntaxTreeDefinition> lambdaDefinition;
	SharedPointer<SyntaxTreeDefinition> applicationDefinition;
	SharedPointer<SyntaxTreeDefinition> definitionDefinition = new DefaultSyntaxTreeDefinition(
		new std::string("definition"),
		new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {variableDefinition, defineOperatorDefinition, valueDefinition, endDefinitionOperatorDefinition}
	);
	valueDefinition = new OrSyntaxTreeDefinition(
		new std::string("value"),
		new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {
			new CaseSyntaxTreeDefinition(new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {variableDefinition}),
			new CaseSyntaxTreeDefinition(new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {lambdaDefinition}),
			new CaseSyntaxTreeDefinition(new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {applicationDefinition}),
			new CaseSyntaxTreeDefinition(new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {
				openingCourseBracketDefinition, valueDefinition, closingCourseBracketDefinition
			})
		}
	);
	lambdaDefinition = new DefaultSyntaxTreeDefinition(
		new std::string("lambda"),
		new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {variableDefinition, defineOperatorDefinition, valueDefinition, endDefinitionOperatorDefinition}
	);
	applicationDefinition = new DefaultSyntaxTreeDefinition(
		new std::string("application"),
		new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {valueDefinition, valueDefinition}
	);
	_syntaxTreeDefinitionsCollection = new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {
		defineOperatorDefinition,
		lambdaAbstractionOperatorDefinition,
		endDefinitionOperatorDefinition,
		openingCourseBracketDefinition,
		closingCourseBracketDefinition,
		beginCompilerBlockBracketDefinition,
		endCompilerBlockBracketDefinition,
		variableDefinition,
		anythingDefinition,
		compilerBlockDefinition,
		definitionDefinition,
		valueDefinition,
		lambdaDefinition,
		applicationDefinition
	};
	_syntaxTreeBuildingPartsToSyntaxTreeBuilderMap = new OrderedByValueMap<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTree>>;
	SharedPointer<Iterator<SharedPointer<SyntaxTreeDefinition>>> syntaxTreeDefinitionsCollectionIterator = _syntaxTreeDefinitionsCollection->iterator();
	for (syntaxTreeDefinitionsCollectionIterator->first(); !syntaxTreeDefinitionsCollectionIterator->isDone(); syntaxTreeDefinitionsCollectionIterator->next()) {
		_syntaxTreeBuildingPartsToSyntaxTreeBuilderMap = _syntaxTreeBuildingPartsToSyntaxTreeBuilderMap->collectionWithAddedElement(
			new DefaultPair<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTree>>(
				syntaxTreeDefinitionsCollectionIterator->currentElement(),
				syntaxTreeDefinitionsCollectionIterator->currentElement()->syntaxTreeBuilder()
			)
		);
	}
}

SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTree>>> SyntaxTreeDefinitions::syntaxTreeBuildingPartsToSyntaxTreeBuilderMap()
{
	return _syntaxTreeBuildingPartsToSyntaxTreeBuilderMap;
}

TokenSyntaxTreeDefinition::TokenSyntaxTreeDefinition(SharedPointer<std::string> tokenName)
: _tokenName {tokenName}
{
}

SharedPointer<SyntaxTreeBuilder> TokenSyntaxTreeDefinition::syntaxTreeBuilder()
{
	return new DefaultSyntaxTreeBuilder(_tokenName);
}

bool TokenSyntaxTreeDefinition::doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>> syntaxTreeBuildingParts)
{
	return *syntaxTreeBuildingParts->size() == 0 && syntaxTreeBuildingParts->element(new Index(0))->name() == _tokenName;
}

SharedPointer<SyntaxTreeBuilder> AnythingSyntaxTreeDefinition::syntaxTreeBuilder()
{
	return new DefaultSyntaxTreeBuilder(new std::string("anything"));
}

bool AnythingSyntaxTreeDefinition::doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>)
{
	return true;
}

DefaultSyntaxTreeDefinition::DefaultSyntaxTreeDefinition(
	SharedPointer<std::string> syntaxTreeName,
	SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> definitionParts
)
: _syntaxTreeName {syntaxTreeName}, _definitionParts {definitionParts} 
{
}

SharedPointer<SyntaxTreeBuilder> DefaultSyntaxTreeDefinition::syntaxTreeBuilder()
{
	return new DefaultSyntaxTreeBuilder(_syntaxTreeName);
}

bool DefaultSyntaxTreeDefinition::doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>> syntaxTreeBuildingParts)
{
	return _definitionParts == syntaxTreeBuildingParts;
}

OrSyntaxTreeDefinition::OrSyntaxTreeDefinition(
	SharedPointer<std::string> syntaxTreeName,
	SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> definitionCases
)
: _syntaxTreeName {syntaxTreeName}, _definitionCases {definitionCases}
{
}

SharedPointer<SyntaxTreeBuilder> OrSyntaxTreeDefinition::syntaxTreeBuilder()
{
	return new DefaultSyntaxTreeBuilder(_syntaxTreeName);
}

bool OrSyntaxTreeDefinition::doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>> syntaxTreeBuildingParts)
{
	SharedPointer<Iterator<SharedPointer<SyntaxTreeDefinition>>> definitionCasesIterator = _definitionCases->iterator();
	bool doesMatchOutput = false;
	for (
		definitionCasesIterator->first();
		!definitionCasesIterator->isDone() && !doesMatchOutput;
		definitionCasesIterator->next()
	) {
		doesMatchOutput = definitionCasesIterator->currentElement()->doesMatch(syntaxTreeBuildingParts);
	}
	return doesMatchOutput;
}

CaseSyntaxTreeDefinition(SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> definitionParts)
: _basicSyntaxTreeDefinition {new DefaultSyntaxTreeDefinition(new std::string(""), definitionPatrts)}
{
}

SharedPointer<SyntaxTreeBuilder> CaseSyntaxTreeDefinition::syntaxTreeBuilder()
{
	return _basicSyntaxTreeDefinition->syntaxTreeBuilder();
}

bool CaseSyntaxTreeDefinition::doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>> syntaxTreeBuildingParts)
{
	return _basicSyntaxTreeDefinition->doesMatch(syntaxtreeBuildingParts);
}