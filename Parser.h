#ifndef PARSER
#define PARSER

#include "MDPLibrary/SharedPointer.h"
#include "Lexer.h"
#include <string>

class Ast //composite
{
	public:
	using Children = Set<SharedPointer<Ast>>;

	virtual SharedPointer<std::string> type() = 0;
	virtual SharedPointer<Children> children() = 0;
	virtual void addChild(SharedPointer<Ast> child) = 0;
	virtual void removeChild(SharedPointer<Ast> child) = 0;
};

class LeafAsT : public Ast
{
	public:
	LeafAsT(SharedPointer<std::string> type);
	LeafAsT(SharedPointer<Token>);
	SharedPointer<std::string> type() override;
	SharedPointer<Children> children() override;
	void addChild(SharedPointer<Ast> child) override;
	void removeChild(SharedPointer<Ast> child) override;

	private:
	SharedPointer<std::string> _type;
};

class CompositeAst : public Ast
{
	public:
	CompositeAst(SharedPointer<std::string> type, SharedPointer<Children>);
	SharedPointer<std::string> type() override;
	SharedPointer<Children> children() override;
	void addChild(SharedPointer<Ast> child) override;
	void removeChild(SharedPointer<Ast> child) override;

	private:
	SharedPointer<std::string> _type;
	SharedPointer<Children> _children;
};

template <template <typename> typename CollectionWithOrder>
class AstDefinition
{
	public:
	virtual SharedPointer<std::string> astType() = 0;
	virtual bool isEqual(SharedPointer<CollectionWithOrder<Ast>>) = 0;
};

template <template <typename> typename CollectionWithOrder>
bool operator==(SharedPointer<AstDefinition<CollectionWithOrder>> astDefinition, SharedPointer<CollectionWithOrder<Ast>> astChildren);

template <template <typename> typename CollectionWithOrder>
class Parser
{
	public:
	Parser(
		Map<SharedPointer<AstDefinition<CollectionWithOrder>>, SharedPointer<std::string>> astsToCompositeAstType,
		SharedPointer<CollectionWithOrder<SharedPointer<Ast>>> asts
	);
	SharedPointer<Ast> ast();

	private:
	SharedPointer<CollectionWithOrder<SharedPointer<Ast>>> _asts;
	Map<SharedPointer<AstDefinition<CollectionWithOrder>>, SharedPointer<std::string>> _astsToCompositeAstType;

	void _replaceInAsts(long leftIndex, long rightIndex, SharedPointer<Ast> insertElement);
};

#include "Parser.cpp"

#endif