#ifndef PARSER
#define PARSER

#include <string>

#include "Lexer.h"

#include "MDPLibrary/SharedPointer.h"
#include "projectStructures/Array.h"
#include "projectStructures/Map.h"

class SyntaxTree
{
	public:
	virtual SharedPointer<std::string> name() = 0;
	virtual SharedPointer<Optional<SharedPointer<Map<SharedPointer<std::string>, SharedPointer<SyntaxTree>>>>> children() = 0;
	virtual ~SyntaxTree() = default; 
};

void print(SharedPointer<SyntaxTree>, long depht = 0);

class TokenSyntaxTree : public SyntaxTree
{
	public:
	TokenSyntaxTree(SharedPointer<Token>);
	SharedPointer<std::string> name() override;
	SharedPointer<Optional<SharedPointer<Map<SharedPointer<std::string>, SharedPointer<SyntaxTree>>>>> children() override;

	private:
	SharedPointer<Token> _token;
};

class SyntaxTreeBuilder
{
	public:
	virtual SharedPointer<SyntaxTree> buildedSyntaxTree(SharedPointer<Array<SharedPointer<SyntaxTree>>>) = 0;
	virtual ~SyntaxTreeBuilder() = default;
};

class SyntaxTreeDefinition
{
	public:
	virtual SharedPointer<SyntaxTreeBuilder> syntaxTreeBuilder() = 0;
	virtual bool doesMatch(SharedPointer<SyntaxTree>) = 0;
	virtual bool doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>) = 0;
	virtual ~SyntaxTreeDefinition() = default;
};

bool operator==(SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTreeDefinition>);
bool operator==(SharedPointer<SyntaxTreeDefinition>, SharedPointer<Array<SharedPointer<SyntaxTree>>> syntaxTreeBuildingParts);
bool operator==(SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTree>);

class Parser
{
	public:
	Parser(SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTreeBuilder>>>);
	SharedPointer<SyntaxTree> syntaxTree(SharedPointer<Array<SharedPointer<Token>>>);

	private:
	SharedPointer<Array<SharedPointer<SyntaxTree>>> _syntaxTreeBuildingParts;
	SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTreeBuilder>>> _syntaxTreeBuildingPartsToSyntaxTreeBuilderMap;

	Parser(SharedPointer<Array<SharedPointer<SyntaxTree>>>, SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTreeBuilder>>>);
};

#include "Parser.cpp"

#endif