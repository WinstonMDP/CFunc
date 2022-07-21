#ifndef SYNTAX_TREE_DEFINITIONS
#define SYNTAX_TREE_DEFINITIONS

#include "../Parser.h"

class DefaultSyntaxTree : public SyntaxTree
{
	public:
	SharedPointer<std::string> name() override;

	private:
	SharedPointer<std::string> _name;
};

class DefaultSyntaxTreeBuilder : public SyntaxTreeBuilder
{
	public:
	DefaultSyntaxTreeBuilder() = default;
	DefaultSyntaxTreeBuilder(SharedPointer<std::string> name);
	SharedPointer<SyntaxTree> buildedSyntaxTree(SharedPointer<Array<SharedPointer<SyntaxTree>>>) override;

	private:
	SharedPointer<std::string> _name;
};

class SyntaxTreeDefinitions
{
	public:
	SyntaxTreeDefinitions();
	SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTree>>> syntaxTreeBuildingPartsToSyntaxTreeBuilderMap();

	private:
	SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> _syntaxTreeDefinitionsCollection;
	SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTree>>> _syntaxTreeBuildingPartsToSyntaxTreeBuilderMap;
};

class TokenSyntaxTreeDefinition : public SyntaxTreeDefinition
{
	public:
	TokenSyntaxTreeDefinition(SharedPointer<std::string> tokenName);
	SharedPointer<SyntaxTreeBuilder> syntaxTreeBuilder() override;
	bool doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>) override;

	private:
	SharedPointer<std::string> _tokenName;
};

class AnythingSyntaxTreeDefinition : public SyntaxTreeDefinition
{
	public:
	AnythingSyntaxTreeDefinition() = default;
	SharedPointer<SyntaxTreeBuilder> syntaxTreeBuilder() override;
	bool doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>) override;
};

class DefaultSyntaxTreeDefinition : public SyntaxTreeDefinition
{
	public:
	DefaultSyntaxTreeDefinition(SharedPointer<std::string> syntaxTreeName, SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> definitionParts);
	SharedPointer<SyntaxTreeBuilder> syntaxTreeBuilder() override;
	bool doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>) override;

	private:
	SharedPointer<std::string> _syntaxTreeName;
	SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> _definitionParts;
};

class OrSyntaxTreeDefinition : public SyntaxTreeDefinition
{
	public:
	OrSyntaxTreeDefinition(SharedPointer<std::string> syntaxTreeName, SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> definitionCases);
	SharedPointer<SyntaxTreeBuilder> syntaxTreeBuilder() override;
	bool doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>) override;

	private:
	SharedPointer<std::string> _syntaxTreeName;
	SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> _definitionCases;
};

class CaseSyntaxTreeDefinition : public SyntaxTreeDefinition
{
	public:
	CaseSyntaxTreeDefinition(SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>>);
	SharedPointer<SyntaxTreeBuilder> syntaxTreeBuilder() override;
	bool doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>) override;

	private:
	SharedPointer<SyntaxTreeDefinition> _basicSyntaxTreeDefinition;
};

#include "SyntaxTreeDefinitions.cpp"

#endif