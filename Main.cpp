#include <fstream>
#include <string>

#include "Lexer.h"
#include "Printer.h"

#include "definitions/TokenDefinitions.h"
#include "MDPLibrary/Exeption.h"
#include "MDPLibrary/SharedPointer.h"
#include "projectStructures/Array.h"
#include "projectStructures/Map.h"

class CodeFile
{
	public:
	CodeFile(SharedPointer<std::string> fileName)
	: _fileName {fileName}
	{
		_fin = new std::ifstream(*_fileName);
		if(!_fin->is_open()) {
			throw SharedPointer<Exeption>(new DefaultExeption(
				new DefaultTraceback(new std::string("CodeFile::CodeFile(SharedPointer<std::string> fileName)")),
				new DefaultDescription(new std::string("File is not open."))
			));
		}
	}

	SharedPointer<Array<SharedPointer<std::string>>> words()
	{
		std::string word;
		SharedPointer<Array<SharedPointer<std::string>>> collection = new DefaultArray<SharedPointer<std::string>>;
		while (*_fin >> word) {
			collection = collection->collectionWithAddedElement(new std::string(word));
		}
		return collection;
	}

	private:
	SharedPointer<std::string> _fileName;
	SharedPointer<std::ifstream> _fin;
};

int main()
{
	try {
		SharedPointer<TokenDefinitions> tokenDefinitions = new TokenDefinitions;
		SharedPointer<CodeFile> codeFile = new CodeFile(new std::string("TestCode.cf"));
		SharedPointer<Array<SharedPointer<std::string>>> codeWords = codeFile->words();
		print(codeWords);
		SharedPointer<Iterator<SharedPointer<std::string>>> codeWordsIterator = codeWords->iterator();
		print(SharedPointer<Map<SharedPointer<TokenDefinition>, SharedPointer<std::string>>>(tokenDefinitions->tokenViewInCodeToNameMap()));
		SharedPointer<Lexer<DefaultArray>> lexer = new Lexer<DefaultArray>(tokenDefinitions->tokenViewInCodeToNameMap(), codeWordsIterator);
		SharedPointer<Array<SharedPointer<Token>>> tokens = lexer->tokens();
		print(tokens);
	}
	catch (SharedPointer<Exeption> exeption) {
		exeption->baseProcess();
	}
	catch (const char* exeption) {
		std::cout << exeption << '\n';
	}
	return 0;
}