#include "Parser.h"

#include "MDPLibrary/Exeption.h"
#include "projectStructures/CollectionOperations.h"
#include "projectStructures/Map.h"

Parser::Parser(SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTree>>> syntaxTreeBuildingPartsToSyntaxTreeBuilderMap)
: _syntaxTreeBuildingPartsToSyntaxTreeBuilderMap {syntaxTreeBuildingPartsToSyntaxTreeBuilderMap}
{
}

SharedPointer<SyntaxTree> Parser::syntaxTree(SharedPointer<Array<SharedPointer<Token>>> tokens)
{
	SharedPointer<Iterator<SharedPointer<Token>>> tokensIterator = tokens->iterator();
	for (tokensIterator->first(); !tokensIterator->isDone(); tokensIterator->next()) {
		_syntaxTreeBuildingParts = _syntaxTreeBuildingParts->collectionWithAddedElement(
			new TokenSyntaxTree(tokenIterator->currentElement())
		);
	}
	SharedPointer<Iterator<SharedPointer<SyntaxTree>>> syntaxTreeBuildingPartsIterator;
	bool wasSyntaxTreeBuilt;
	do {
		wasSyntaxTreeBuilt = false;
		for (
			SharedPointer<Size> syntaxTreeBuildingPartsSubsegmentSize = new Size(1);
			*syntaxTreeBuildingPartsSubsegmentSize < *_syntaxTreeBuildingParts->size() && !wasSyntaxTreeBuilt;
			++(*syntaxTreeBuildingPartsSubsegmentSize)
		) {
			syntaxTreeBuildingPartsIterator = _syntaxTreeBuildingParts->iterator();
			SharedPointer<Index> currentElementIndex = new Index(0);
			for (
				syntaxTreeBuildingPartsIterator->first();
				!syntaxTreeBuildingPartsIterator->isDone() && !wasSyntaxTreeBuilt;
				syntaxTreeBuildingPartsIterator->next()
			) {
				SharedPointer<Array<SharedPointer<SyntaxTree>>> syntaxTreeBuildingPartsSubsegment =
					subsegment<Array>(syntaxTreeBuildingPartsIterator, syntaxTreeBuildingPartsSubsegmentSize);
				SharedPointer<Optional<SharedPointer<SyntaxTree>>> syntaxTreeFromSyntaxTreeBuildingPartsSubsegment = 
					_syntaxTreeBuildingPartsToSyntaxTreeBuilderMap->value(syntaxTreeBuildingPartsSubsegment);
				wasSyntaxTreeBuilt = syntaxTreeFromSyntaxTreeBuildingPartsSubsegment->doesValueExist();
				if (wasSyntaxTreeBuilt) {
					_syntaxTreeBuildingParts = replacedCollection<SharedPointer<SyntaxTree>>(
						_syntaxTreeBuildingParts,
						currentElementIndex,
						syntaxTreeBuildingPartsSubsegmentSize,
						syntaxTreeFromSyntaxTreeBuildingPartsSubsegment->value()
					);
				}
			}
		}
	} while (wasSyntaxTreeBuilt);
	if (*_syntaxTreeBuildingParts->size() != 1) {
		throw SharedPointer<Exeption>(new DefaultExeption(
			new DefaultTraceback(new std::string("SharedPointer<SyntaxTree> Parser::syntaxTree(SharedPointer<Array<SharedPointer<Token>>> tokens)")),
			new DefaultDescription(new std::string("_syntaxTreeBuildingParts doesn`t have one element: it have more or less."))
		));
	}
	return _syntaxTreeBuildingParts;
}