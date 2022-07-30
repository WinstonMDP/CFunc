#include "Parser.h"

#include "Printer.h"

#include "MDPLibrary/Exeption.h"
#include "projectStructures/CollectionOperations.h"
#include "projectStructures/Map.h"

void print(SharedPointer<SyntaxTree> syntaxTree, long depth)
{
	
	SharedPointer<Optional<SharedPointer<Map<SharedPointer<std::string>, SharedPointer<SyntaxTree>>>>> syntaxTreeChildren = syntaxTree->children();
	if (syntaxTreeChildren->doesValueExist()) {
		std::string a = *syntaxTree->name();
		a += " {";
		print(a, depth);
		SharedPointer<Iterator<SharedPointer<Pair<SharedPointer<std::string>, SharedPointer<SyntaxTree>>>>> syntaxTreeChildrenIterator =
			syntaxTreeChildren->value()->iterator();
		for (syntaxTreeChildrenIterator->first(); !syntaxTreeChildrenIterator->isDone(); syntaxTreeChildrenIterator->next()) {
			print(syntaxTreeChildrenIterator->currentElement()->rightElement(), depth + 1);
		}
		print("}", depth);
	}
	else {
		print(*syntaxTree->name(), depth);
	}
}

TokenSyntaxTree::TokenSyntaxTree(SharedPointer<Token> token)
: _token {token}
{
}

SharedPointer<std::string> TokenSyntaxTree::name()
{
	return _token->name();
}

SharedPointer<Optional<SharedPointer<Map<SharedPointer<std::string>, SharedPointer<SyntaxTree>>>>> TokenSyntaxTree::children()
{
	return new Optional<SharedPointer<Map<SharedPointer<std::string>, SharedPointer<SyntaxTree>>>>();
}

bool operator==(SharedPointer<SyntaxTreeDefinition> syntaxTreeDefinition, SharedPointer<Array<SharedPointer<SyntaxTree>>> syntaxTreeBuildingParts)
{
	return syntaxTreeDefinition->doesMatch(syntaxTreeBuildingParts);
}

bool operator==(SharedPointer<SyntaxTreeDefinition> syntaxTreeDefinition, SharedPointer<SyntaxTree> syntaxTree)
{
	return syntaxTreeDefinition->doesMatch(syntaxTree);
}

Parser::Parser(SharedPointer<Map<SharedPointer<SyntaxTreeDefinition>, SharedPointer<SyntaxTreeBuilder>>> syntaxTreeBuildingPartsToSyntaxTreeBuilderMap)
: _syntaxTreeBuildingPartsToSyntaxTreeBuilderMap {syntaxTreeBuildingPartsToSyntaxTreeBuilderMap}
{
}

SharedPointer<SyntaxTree> Parser::syntaxTree(SharedPointer<Array<SharedPointer<Token>>> tokens)
{
	SharedPointer<Iterator<SharedPointer<Token>>> tokensIterator = tokens->iterator();
	for (tokensIterator->first(); !tokensIterator->isDone(); tokensIterator->next()) {
		_syntaxTreeBuildingParts = _syntaxTreeBuildingParts->collectionWithAddedElement(
			new TokenSyntaxTree(tokensIterator->currentElement())
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
					subsegment<DefaultArray, Iterator, SharedPointer<SyntaxTree>>(syntaxTreeBuildingPartsIterator, syntaxTreeBuildingPartsSubsegmentSize);
				SharedPointer<Optional<SharedPointer<SyntaxTreeBuilder>>> syntaxTreeBuilderFromSyntaxTreeBuildingPartsSubsegment = 
					value(_syntaxTreeBuildingPartsToSyntaxTreeBuilderMap, syntaxTreeBuildingPartsSubsegment);
				wasSyntaxTreeBuilt = syntaxTreeBuilderFromSyntaxTreeBuildingPartsSubsegment->doesValueExist();
				if (wasSyntaxTreeBuilt) {
					_syntaxTreeBuildingParts = replacedArray(
						_syntaxTreeBuildingParts,
						currentElementIndex,
						syntaxTreeBuildingPartsSubsegmentSize,
						syntaxTreeBuilderFromSyntaxTreeBuildingPartsSubsegment->value()->buildedSyntaxTree(syntaxTreeBuildingPartsSubsegment)
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
	return _syntaxTreeBuildingParts->element(new Index(0));
}