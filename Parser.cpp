#include "Parser.h"

LeafAsT::LeafAsT(SharedPointer<std::string> type)
: _type{type}
{
}

LeafAsT::LeafAsT(SharedPointer<Token> token)
: LeafAsT(token->name())
{
}

SharedPointer<std::string> LeafAsT::type() override
{
	return _type;
}

SharedPointer<Children> LeafAsT::children() override
{
	throw "SharedPointer<Children> LeafAsT::children() override: \
			LeafAsT cannot have children.";
}

void LeafAsT::addChild(SharedPointer<Ast> child) override
{
	throw "void LeafAsT::addChild(SharedPointer<Ast> child) override: \
			LeafAsT cannot have children.";
}

void LeafAsT::removeChild(SharedPointer<Ast> child) override
{
	throw "void removeChild(SharedPointer<Ast> child) override: \
			LeafAsT cannot have children.";
}


CompositeAst::CompositeAst(SharedPointer<std::string> type, SharedPointer<Children> children)
: _type{type}, _children{children}
{
}

SharedPointer<std::string> CompositeAst::type() override
{
	return _type;
}

SharedPointer<Children> CompositeAst::children() override
{
	return _children;
}

void CompositeAst::addChild(SharedPointer<Ast> child) override
{
	_children->addElement(child);
}

void CompositeAst::removeChild(SharedPointer<Ast> child) override
{
	_children->removeElement(child);
}


template <template <typename> typename CollectionWithOrder>
bool operator==(SharedPointer<AstDefinition<CollectionWithOrder>> astDefinition, SharedPointer<CollectionWithOrder<Ast>> astChildren)
{
	return aSTDefinition->isEqual(aSTChildren);
}



template <template <typename> typename CollectionWithOrder>
Parser<CollectionWithOrder>::Parser(
	Map<SharedPointer<AstDefinition<CollectionWithOrder>>, SharedPointer<std::string>> astsToCompositeAstType,
	SharedPointer<CollectionWithOrder<SharedPointer<Ast>>> asts
)
: _astsToCompositeAstType {astsToCompositeAstType}, _asts {asts}
{
}

template <template <typename> typename CollectionWithOrder>
SharedPointer<Ast> Parser<CollectionWithOrder>::ast()
{
	for (long segmentSize = 0; segmentSize < _asts->size(); ++segmentSize) {
		for (long leftIndex = 0; leftIndex < _asts->size(); ++leftIndex) {
			long rightIndex = leftIndex + segmentSize;
			SharedPointer<CollectionWithOrder<SharedPointer<Ast>>> astsOnTheSegment = new CollectionWithOrder<SharedPointer<Ast>>(_asts, leftIndex, rightIndex);
			Optional<SharedPointer<std::string>> astType = _astsToCompositeAstType->value(astsOnTheSegment);
			if (astType->doesExist()) {
				SharedPointer<Ast> compositeAst = new CompositeAst(astType->value(), astsOnTheSegment);
				_replaceInAsts(leftIndex, rightIndex, compositeAsT);
			}
		}
	}
	SharedPointer<Ast> ast = _asts.front();
	return ast;
}

template <template <typename> typename CollectionWithOrder>
void Parser<CollectionWithOrder>::_replaceInAsts(long leftIndex, long rightIndex, SharedPointer<Ast> insertElement)
{
	_AsTs.remove(leftIndex, rightIndex);
	_AsTs.addElement(leftIndex, insertElement);
}