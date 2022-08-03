#include "SyntaxTreeDefinitions.h"

DefaultSyntaxTree::DefaultSyntaxTree(SharedPointer<std::string> name, SharedPointer<Array<SharedPointer<SyntaxTree>>> syntaxTreeBuildingParts)
: _name {name}, _syntaxTreeBuildingParts {syntaxTreeBuildingParts}
{
}

SharedPointer<std::string> DefaultSyntaxTree::name()
{
	return _name;
}

SharedPointer<Optional<SharedPointer<Map<SharedPointer<std::string>, SharedPointer<SyntaxTree>>>>> DefaultSyntaxTree::children()
{
	SharedPointer<Map<SharedPointer<std::string>, SharedPointer<SyntaxTree>>> outputChildren =
		new OrderedByValueMap<SharedPointer<std::string>, SharedPointer<SyntaxTree>>();
	SharedPointer<Iterator<SharedPointer<SyntaxTree>>> syntaxTreeBuildingPartsIterator = _syntaxTreeBuildingParts->iterator();
	for (syntaxTreeBuildingPartsIterator->first(); !syntaxTreeBuildingPartsIterator->isDone(); syntaxTreeBuildingPartsIterator->next()) {
		outputChildren = outputChildren->collectionWithAddedElement(new DefaultPair<SharedPointer<std::string>, SharedPointer<SyntaxTree>>(
			syntaxTreeBuildingPartsIterator->currentElement()->name(), syntaxTreeBuildingPartsIterator->currentElement() 
		));
	}
	return new Optional<SharedPointer<Map<SharedPointer<std::string>, SharedPointer<SyntaxTree>>>>(outputChildren);
}

DefaultSyntaxTreeBuilder::DefaultSyntaxTreeBuilder(SharedPointer<std::string> name)
: _name {name}
{
}

SharedPointer<SyntaxTree> DefaultSyntaxTreeBuilder::buildedSyntaxTree(SharedPointer<Array<SharedPointer<SyntaxTree>>> syntaxTreeBuildingParts)
{
	return new DefaultSyntaxTree(_name, syntaxTreeBuildingParts);
}

SyntaxTreeDefinitions::SyntaxTreeDefinitions()
{
	SharedPointer<SyntaxTreeDefinition> defineOperatorDefinition = new TokenSyntaxTreeDefinition(new std::string("define-operator"));
	SharedPointer<SyntaxTreeDefinition> lambdaAbstractionOperatorDefinition = new TokenSyntaxTreeDefinition(new std::string("lambda-abstraction-operator"));
	SharedPointer<SyntaxTreeDefinition> endDefinitionOperatorDefinition = new TokenSyntaxTreeDefinition(new std::string("end-definition-operator"));
	SharedPointer<SyntaxTreeDefinition> openingCourseBracketDefinition = new TokenSyntaxTreeDefinition(new std::string("opening-course-bracket"));
	SharedPointer<SyntaxTreeDefinition> closingCourseBracketDefinition = new TokenSyntaxTreeDefinition(new std::string("closing-course-bracket"));
	SharedPointer<SyntaxTreeDefinition> beginCompilerBlockBracketDefinition = new TokenSyntaxTreeDefinition(new std::string("begin-compiler-block-operator"));
	SharedPointer<SyntaxTreeDefinition> endCompilerBlockBracketDefinition = new TokenSyntaxTreeDefinition(new std::string("end-compiler-block-operator"));
	SharedPointer<SyntaxTreeDefinition> variableDefinition = new TokenSyntaxTreeDefinition(new std::string("variable"));
	SharedPointer<SyntaxTreeDefinition> compilerBlockDefinition = new CompilerBlockSyntaxTreeDefinition;
	SharedPointer<SyntaxTreeDefinition> valueDefinition;
	SharedPointer<SyntaxTreeDefinition> lambdaDefinition;
	SharedPointer<SyntaxTreeDefinition> applicationDefinition;
	SharedPointer<SyntaxTreeDefinition> definitionDefinition = new DefaultSyntaxTreeDefinition(
		new std::string("definition"),
		new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {variableDefinition, defineOperatorDefinition, valueDefinition, endDefinitionOperatorDefinition}
	);
	SharedPointer<std::string> valueSyntaxTreeName = new std::string("value");
	valueDefinition = new OrSyntaxTreeDefinition(
		valueSyntaxTreeName,
		new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {
			new CaseSyntaxTreeDefinition(valueSyntaxTreeName, new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {variableDefinition}),
			new CaseSyntaxTreeDefinition(valueSyntaxTreeName, new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {lambdaDefinition}),
			new CaseSyntaxTreeDefinition(valueSyntaxTreeName, new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {applicationDefinition}),
			new CaseSyntaxTreeDefinition(valueSyntaxTreeName, new DefaultArray<SharedPointer<SyntaxTreeDefinition>> {
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
		compilerBlockDefinition,
		definitionDefinition,
		valueDefinition,
		lambdaDefinition,
		applicationDefinition
	};
	_syntaxTreeBuildingPartsToSyntaxTreeBuilderMap = new OrderedByValueMap<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTreeBuilder>>;
	SharedPointer<Iterator<SharedPointer<SyntaxTreeDefinition>>> syntaxTreeDefinitionsCollectionIterator = _syntaxTreeDefinitionsCollection->iterator();
	for (syntaxTreeDefinitionsCollectionIterator->first(); !syntaxTreeDefinitionsCollectionIterator->isDone(); syntaxTreeDefinitionsCollectionIterator->next()) {
		_syntaxTreeBuildingPartsToSyntaxTreeBuilderMap = _syntaxTreeBuildingPartsToSyntaxTreeBuilderMap->collectionWithAddedElement(
			new DefaultPair<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTreeBuilder>>(
				syntaxTreeDefinitionsCollectionIterator->currentElement(),
				syntaxTreeDefinitionsCollectionIterator->currentElement()->syntaxTreeBuilder()
			)
		);
	}
}

SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTreeBuilder>>> SyntaxTreeDefinitions::syntaxTreeBuildingPartsToSyntaxTreeBuilderMap()
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

bool TokenSyntaxTreeDefinition::doesMatch(SharedPointer<SyntaxTree> syntaxTree)
{
	return syntaxTree->name() == _tokenName;
}

SharedPointer<SyntaxTreeBuilder> CompilerBlockSyntaxTreeDefinition::syntaxTreeBuilder()
{
	return new DefaultSyntaxTreeBuilder(new std::string("compiler-block"));
}

bool CompilerBlockSyntaxTreeDefinition::doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>> syntaxTreeBuildingParts)
{
	return
		syntaxTreeBuildingParts->element(new Index(0))->name() == std::string("begin-comiler-block-bracket") &&
		syntaxTreeBuildingParts->element(new Index(*syntaxTreeBuildingParts->size() - 1))->name() == "end-comiler-block-bracket"
	;
}

bool CompilerBlockSyntaxTreeDefinition::doesMatch(SharedPointer<SyntaxTree> syntaxTree)
{
	return syntaxTree->name() == "compiler-block";
}

SharedPointer<SyntaxTreeBuilder> AnythingSyntaxTreeDefinition::syntaxTreeBuilder()
{
	return new DefaultSyntaxTreeBuilder(new std::string("anything"));
}

bool AnythingSyntaxTreeDefinition::doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>)
{
	return true;
}

bool AnythingSyntaxTreeDefinition::doesMatch(SharedPointer<SyntaxTree> syntaxTree)
{
	return syntaxTree->name() == new std::string("anything");
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

bool DefaultSyntaxTreeDefinition::doesMatch(SharedPointer<SyntaxTree> syntaxTree)
{
	return syntaxTree->name() == _syntaxTreeName;
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

bool OrSyntaxTreeDefinition::doesMatch(SharedPointer<SyntaxTree> syntaxTree)
{
	return syntaxTree->name() == _syntaxTreeName;
}

CaseSyntaxTreeDefinition::CaseSyntaxTreeDefinition(
	SharedPointer<std::string> syntaxTreeName,
	SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> definitionParts
)
: _basicSyntaxTreeDefinition {new DefaultSyntaxTreeDefinition(syntaxTreeName, definitionParts)}
{
}

SharedPointer<SyntaxTreeBuilder> CaseSyntaxTreeDefinition::syntaxTreeBuilder()
{
	return _basicSyntaxTreeDefinition->syntaxTreeBuilder();
}

bool CaseSyntaxTreeDefinition::doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>> syntaxTreeBuildingParts)
{
	return _basicSyntaxTreeDefinition->doesMatch(syntaxTreeBuildingParts);
}

bool CaseSyntaxTreeDefinition::doesMatch(SharedPointer<SyntaxTree> syntaxTree)
{
	return _basicSyntaxTreeDefinition->doesMatch(syntaxTree);
}