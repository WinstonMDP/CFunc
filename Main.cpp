#include <iostream>
#include <fstream>
#include "Lexer.h"

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
		return _viewInCode == viewInCode;
	}

	private:
	SharedPointer<std::string> _tokenName;
	SharedPointer<std::string> _viewInCode;
};


template <template <typename> typename Collection = Array>
class CodeFile
{
	public:
	CodeFile(SharedPointer<std::string> fileName)
	: _fileName {fileName}
	{
		_fin = new std::ifstream(*_fileName);
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

bool operator<(const TokenDefinition& a, const TokenDefinition& b);
template <typename Value>
bool operator<(const SharedPointer<Value>& a, const SharedPointer<Value>& b);

int main()
{
	SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>> tokenViewInCodeToNameMap;
	SharedPointer<std::string> codeFileName = new std::string("TestCode.cpp");
	SharedPointer<CodeFile<>> codeFile = new CodeFile<>(codeFileName);
	SharedPointer<Array<SharedPointer<std::string>>> codeWords = codeFile->words();
	SharedPointer<Iterator<SharedPointer<std::string>>> codeWordsIterator = codeWords->iterator();
	SharedPointer<Lexer<>> lexer = new Lexer<>(tokenViewInCodeToNameMap, codeWordsIterator);
	SharedPointer<Array<SharedPointer<Token>>> tokens = lexer->tokens();
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