#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Collections.h"

class DefaultTokenDefinition : public TokenDefinition
{
	public:
	DefaultTokenDefinition(SharedPointer<std::string> tokenName, SharedPointer<std::string> viewInCode)
	: _tokenName {tokenName}, _viewInCode {viewInCode}
	{
	}

	SharedPointer<std::string> tokenName() const override
	{
		return _tokenName;
	}

	bool isEqual(SharedPointer<std::string> viewInCode) override
	{
		return *_viewInCode == *viewInCode;
	}

	private:
	SharedPointer<std::string> _tokenName;
	SharedPointer<std::string> _viewInCode;
};

class OtherTokenDefinition : public TokenDefinition
{
	public:
	OtherTokenDefinition(SharedPointer<std::string> tokenName)
	: _tokenName {tokenName}
	{
	}

	SharedPointer<std::string> tokenName() const override
	{
		return _tokenName;
	}

	bool isEqual(SharedPointer<std::string> viewInCode) override
	{
		return true;
	}

	private:
	SharedPointer<std::string> _tokenName;
};


template <template <typename> typename Collection = Array>
class CodeFile
{
	public:
	CodeFile(SharedPointer<std::string> fileName)
	: _fileName {fileName}
	{
		_fin = new std::ifstream(*_fileName);
		if(!_fin->is_open()) {
			throw "CodeFile(SharedPointer<std::string> fileName): \n\
			File is not open.";
		}
	}

	SharedPointer<Collection<SharedPointer<std::string>>> words()
	{
		std::string word;
		SharedPointer<Collection<SharedPointer<std::string>>> collection = new Collection<SharedPointer<std::string>>;
		while (*_fin >> word) {
			collection->add(new std::string(word));
		}
		return collection;
	}

	private:
	SharedPointer<std::string> _fileName;
	SharedPointer<std::ifstream> _fin;
};

template <typename Key, typename Value, template <typename> typename CollectionWithOrder = Array>
class MapWithPriority : public Map<Key, Value>
{
	public:
	MapWithPriority()
	: _collectionWithOrder {new CollectionWithOrder<SharedPointer<Pair<Key, Value>>>}
	{
	}

	SharedPointer<Optional<Value>> value(Key key) override
	{
		SharedPointer<Iterator<SharedPointer<Pair<Key, Value>>>> collectionWithOrderIterator = _collectionWithOrder->iterator();
		for (collectionWithOrderIterator->first(); !collectionWithOrderIterator->isDone(); collectionWithOrderIterator->next()) {
			if (collectionWithOrderIterator->current()->left() == key) {
				return new Optional<Value>(collectionWithOrderIterator->current()->right());
			}
		}
		return new Optional<Value>;
	}

	void add(Key key, Value value) override
	{
		_collectionWithOrder->add(new Pair<Key, Value>(key, value));
	}

	SharedPointer<Array<Key>> keys() override
	{
		SharedPointer<Array<Key>> keysArray= new Array<Key>;
		SharedPointer<Iterator<SharedPointer<Pair<Key, Value>>>> collectionWithOrderIterator = _collectionWithOrder->iterator();
		for (collectionWithOrderIterator->first(); !collectionWithOrderIterator->isDone(); collectionWithOrderIterator->next()) {
			keysArray->add(collectionWithOrderIterator->current()->left());
		}
		return keysArray;
	}

	private:
	SharedPointer<CollectionWithOrder<SharedPointer<Pair<Key, Value>>>> _collectionWithOrder;
};

bool operator<(const TokenDefinition& a, const TokenDefinition& b);
template <typename Value>
bool operator<(const SharedPointer<Value>& a, const SharedPointer<Value>& b);

void retreat(long depth)
{
	for (long i = 0; i < depth; ++i) {
		std::cout << " ";
	}
}

void print(SharedPointer<long>, long = 0);
void print(SharedPointer<std::string>, long = 0);
template <typename Element>
void print(SharedPointer<Array<Element>>, long = 0);
template <typename Key, typename Value>
void print(SharedPointer<Map<Key, Value>> map, long = 0);
void print(SharedPointer<Token> token, long = 0);
void print(SharedPointer<TokenDefinition>, long = 0);

int main()
{
	try {
		SharedPointer<Array<SharedPointer<TokenDefinition>>> tokenDefinitions = new Array<SharedPointer<TokenDefinition>> {
			new DefaultTokenDefinition(new std::string("define"), new std::string("=")),
			new DefaultTokenDefinition(new std::string("lambda-abstraction-operator"), new std::string(".")),
			new DefaultTokenDefinition(new std::string("end-definition-operator"), new std::string(";")),
			new DefaultTokenDefinition(new std::string("opening-course-bracket"), new std::string("(")),
			new DefaultTokenDefinition(new std::string("closing-course-bracket"), new std::string(")")),
			new DefaultTokenDefinition(new std::string("compiler-validation-bracket"), new std::string("\"")),
			new OtherTokenDefinition(new std::string("variable"))
		};
		SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>> tokenViewInCodeToNameMap =
			new MapWithPriority<SharedPointer<TokenDefinition>, SharedPointer<std::string>>;
		SharedPointer<Iterator<SharedPointer<TokenDefinition>>> tokenDefinitionsIterator = tokenDefinitions->iterator();
		for (tokenDefinitionsIterator->first(); !tokenDefinitionsIterator->isDone(); tokenDefinitionsIterator->next()) {
			tokenViewInCodeToNameMap->add(tokenDefinitionsIterator->current(), tokenDefinitionsIterator->current()->tokenName());
		}
		SharedPointer<std::string> codeFileName = new std::string("TestCode.cf");
		SharedPointer<CodeFile<>> codeFile = new CodeFile<>(codeFileName);
		SharedPointer<Array<SharedPointer<std::string>>> codeWords = codeFile->words();
		SharedPointer<Iterator<SharedPointer<std::string>>> codeWordsIterator = codeWords->iterator();
		SharedPointer<Lexer<>> lexer = new Lexer<>(tokenViewInCodeToNameMap, codeWordsIterator);
		SharedPointer<Array<SharedPointer<Token>>> tokens = lexer->tokens();
		print(tokens);
	}
	catch (const char* message) {
		std::cout << message << '\n';
	}
	return 0;
}

bool operator<(const TokenDefinition& a, const TokenDefinition& b)
{
	return a.tokenName() < b.tokenName();
} 

template <typename Value>
bool operator<(const SharedPointer<Value>& a, const SharedPointer<Value>& b)
{
	return *a < *b;
}

void print(SharedPointer<TokenDefinition> tokenDefinition, long depth)
{
	retreat(depth);
	std::cout << "TokenDefinition {" << '\n';
	print(tokenDefinition->tokenName(), depth + 1);
	retreat(depth);
	std::cout << '}' << '\n';
}

template <typename Element>
void print(SharedPointer<Array<Element>> array, long depth)
{
	retreat(depth);
	std::cout << "Array<Element> {" << '\n';
	SharedPointer<Iterator<Element>> arrayIterator = array->iterator();
	for (arrayIterator->first(); !arrayIterator->isDone(); arrayIterator->next()) {
		print(arrayIterator->current(), depth + 1);
	}
	std::cout << '}' << '\n';
	retreat(depth);
}

template <typename Key, typename Value>
void print(SharedPointer<Map<Key, Value>> map, long depth)
{
	SharedPointer<Iterator<Key>> mapKeysIterator = map->keys()->iterator();
	retreat(depth);
	std::cout << "Map<Key, Value> {" << '\n';
	for (mapKeysIterator->first(); !mapKeysIterator->isDone(); mapKeysIterator->next()) {
		print(mapKeysIterator->current(), depth + 1);
		print(map->value(mapKeysIterator->current())->value(), depth + 1);
	}
	std::cout << '}' << '\n';
	retreat(depth);
}

void print(SharedPointer<long> number, long depth)
{
	retreat(depth);
	std::cout << *number << '\n';
}

void print(SharedPointer<std::string> string, long depth)
{
	retreat(depth);
	std::cout << *string << '\n';
}

void print(SharedPointer<Token> token, long depth)
{
	retreat(depth);
	std::cout << "Token {" << '\n';
	print(token->name(), depth + 1);
	print(token->viewInCode(), depth + 1);
	retreat(depth);
	std::cout << '}' << '\n';
}