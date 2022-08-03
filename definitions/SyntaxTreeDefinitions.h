#ifndef SYNTAX_TREE_DEFINITIONS
#define SYNTAX_TREE_DEFINITIONS

#include "../Parser.h"

class DefaultSyntaxTree : public SyntaxTree
{
	public:
	DefaultSyntaxTree(SharedPointer<std::string> name, SharedPointer<Array<SharedPointer<SyntaxTree>>> syntaxTreeBuildingParts);
	SharedPointer<std::string> name() override;
	SharedPointer<Optional<SharedPointer<Map<SharedPointer<std::string>, SharedPointer<SyntaxTree>>>>> children() override;

	private:
	SharedPointer<std::string> _name;
	SharedPointer<Array<SharedPointer<SyntaxTree>>> _syntaxTreeBuildingParts;
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
	SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTreeBuilder>>> syntaxTreeBuildingPartsToSyntaxTreeBuilderMap();

	private:
	SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> _syntaxTreeDefinitionsCollection;
	SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTreeBuilder>>> _syntaxTreeBuildingPartsToSyntaxTreeBuilderMap;
};

class TokenSyntaxTreeDefinition : public SyntaxTreeDefinition
{
	public:
	TokenSyntaxTreeDefinition(SharedPointer<std::string> tokenName);
	SharedPointer<SyntaxTreeBuilder> syntaxTreeBuilder() override;
	bool doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>) override;
	bool doesMatch(SharedPointer<SyntaxTree>) override;

	private:
	SharedPointer<std::string> _tokenName;
};

class CompilerBlockSyntaxTreeDefinition : public SyntaxTreeDefinition
{
	public:
	SharedPointer<SyntaxTreeBuilder> syntaxTreeBuilder() override;
	bool doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>) override;
	bool doesMatch(SharedPointer<SyntaxTree>) override;
};

class AnythingSyntaxTreeDefinition : public SyntaxTreeDefinition
{
	public:
	AnythingSyntaxTreeDefinition() = default;
	SharedPointer<SyntaxTreeBuilder> syntaxTreeBuilder() override;
	bool doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>) override;
	bool doesMatch(SharedPointer<SyntaxTree>) override;
};

class DefaultSyntaxTreeDefinition : public SyntaxTreeDefinition
{
	public:
	DefaultSyntaxTreeDefinition(SharedPointer<std::string> syntaxTreeName, SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> definitionParts);
	SharedPointer<SyntaxTreeBuilder> syntaxTreeBuilder() override;
	bool doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>) override;
	bool doesMatch(SharedPointer<SyntaxTree>) override;

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
	bool doesMatch(SharedPointer<SyntaxTree>) override;

	private:
	SharedPointer<std::string> _syntaxTreeName;
	SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> _definitionCases;
};

class CaseSyntaxTreeDefinition : public SyntaxTreeDefinition
{
	public:
	CaseSyntaxTreeDefinition(SharedPointer<std::string> syntaxTreeName, SharedPointer<Array<SharedPointer<SyntaxTreeDefinition>>> definitionParts);
	SharedPointer<SyntaxTreeBuilder> syntaxTreeBuilder() override;
	bool doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>) override;
	bool doesMatch(SharedPointer<SyntaxTree>) override;

	private:
	SharedPointer<SyntaxTreeDefinition> _basicSyntaxTreeDefinition;
};

#include "SyntaxTreeDefinitions.cpp"

#endif