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
	virtual ~SyntaxTree() = default; 
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
	virtual bool doesMatch(SharedPointer<Array<SharedPointer<SyntaxTree>>>) = 0;
	virtual ~SyntaxTreeDefinition() = default;
};

class Parser
{
	public:
	Parser(SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTree>>>);
	SharedPointer<SyntaxTree> syntaxTree(SharedPointer<Array<SharedPointer<Token>>>);

	private:
	SharedPointer<Array<SharedPointer<SyntaxTree>>> _syntaxTreeBuildingParts;
	SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTree>>> _syntaxTreeBuildingPartsToSyntaxTreeBuilderMap;
};

#include "Parser.cpp"

#endif