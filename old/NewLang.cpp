#include <iostream>
#include <fstream>
#include "MDPLibrary/SharedPointer.h"
#include "MDPLibrary/Optional.h"
#include "Collections.h"
#include <string>
#include "Lexer.h"

template <template <typename> typename CollectionWithOrder = Array>
class InputCodeFile
{
	public:
	InputCodeFile (std::string* fileName)
	: _fileName {fileName}
	{
	}

	CollectionWithOrder <std::string*>* words()
	{
		fin = new std::ifstream (_fileName);
		while (!fin->eof()) {
			std::string word;
			fin >> word;
			_words->pushBack (word);
		}
		return _words;
	}

	~InputCodeFile()
	{
		delete _fin;
	}

	private:
	std::ifstream* _fin;
	std::string* _fileName;
	CollectionWithOrder <std::string*>* _words;
};


class TokensDefinitionsFile
{
	public:
	TokensDefinitionsFile (std::string* fileName)
	: _fileName {fileName}
	{
	}

	TokenTypesMap* tokensTypesMap()
	{
		fin->open (*_fileName);
		while (!fin->eof()) {
			std::string* type = typeFromFile();
			std::string* definition = definitionFromFile();
			_tokensTypesMap->addElement (type, definition);
		}
		return _tokensTypesMap;
	}

	private:
	TokenTypesMap* _tokensTypesMap;
	std::string* _fileName;
	std::ifstream* fin;

	std::string* typeFromFile()
	{
		std::string* type = new std::string;
		*fin >> *type;
		if (type->find (";") == std::string::npos) {
			throw "TokensDefinitionsFile::typeFromFile has found ';'.";
		}
		return type;
	}

	std::string* definitionFromFile()
	{
		std::string* definition = new std::string;
		while (definition->back() != ';') {
			if (fin->eof()) {
				throw "TokensDefinitionFile::definitionFromFile can`t find ';' befor EOF.";
			}
			std::string string;
			*fin >> string;
			*definition += string;
		}
		if (definition->back() != ';' || definition->at (definition->size() - 2) != '"') {
			throw "TokenDefinitinoFile::definitionFromFile must have ';' at the end of definition.";
		}
		definition->erase (definition->end() - 2, definition->end());
		return definition;
	}
};

int main()
{
	std::string* inputCodeFileName = new std::string ("TestCode.cf");
	InputCodeFile <Array>* inputCodeFile = new InputCodeFile <Array> (inputCodeFileName);
	Array <std::string*>* words = inputCodeFile->words();
	std::string* tokensDefinitionsFileName = new std::string ("TokensDefinitions.txt");
	TokensDefinitionsFile* tokensDefinitionsFile = new TokensDefinitionsFile (tokensDefinitionsFileName);
	Lexer <Array>* lexer = new Lexer <Array> (words->iterator(), tokensDefinitionsFile->tokensTypesMap());
	return 0;
}