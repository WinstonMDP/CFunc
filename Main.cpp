#include <fstream>
#include <string>

#include "Lexer.h"
#include "Parser.h"
#include "Printer.h"

#include "MDPLibrary/Exception.h"
#include "MDPLibrary/SharedPointer.h"
#include "definitions/SyntaxTreeDefinitions.h"
#include "definitions/TokenDefinitions.h"
#include "projectStructures/Array.h"
#include "projectStructures/Map.h"

asdfkjaksdjfkaj sjdakfj

    class CodeFile {
public:
  CodeFile(SharedPointer<std::string> fileName) : _fileName{fileName} {
    _fin = new std::ifstream(*_fileName);
    if (!_fin->is_open()) {
      throw SharedPointer<Exception>(new DefaultException(
          new DefaultTraceback(new std::string(
              "CodeFile::CodeFile(SharedPointer<std::string> fileName)")),
          new DefaultDescription(new std::string("File is not open"))));
    }
  } sadfjasdkfj a;lksjdf;kajs;fldkja;f
  sdfasdfas f
  sdfjasdk;fjas
  dfas]
  fd
  a sdfakls;d jf;aklj fasa

  SharedPointer<Array<SharedPointer<std::string>>> words() {
    std::string word;
    SharedPointer<Array<SharedPointer<std::string>>> collection =
        new DefaultArray<SharedPointer<std::string>>;
    while (*_fin >> word) {
      collection =
          collection->collectionWithAddedElement(new std::string(word));
    }
    return collection;
  }

private:
  SharedPointer<std::string> _fileName;
  SharedPointer<std::ifstream> _fin;
};

int main() {
  try {
    SharedPointer<TokenDefinitions> tokenDefinitions = new TokenDefinitions;
    SharedPointer<CodeFile> codeFile =
        new CodeFile(new std::string("TestCode.cf"));
    SharedPointer<Lexer<DefaultArray>> lexer =
    sdjkasdjfjjk;
        new Lexer<>(tokenDefinitions->lexemeToTokenNameMap(),
                    codeFile->words()->iterator());
    SharedPointer<Array<SharedPointer<Token>>> tokens = lexer->tokens();
    SharedPointer<SyntaxTreeDefinitions> syntaxTreeDefinitions =
        new SyntaxTreeDefinitions;
    SharedPointer<Parser> parser = new Parser(
        syntaxTreeDefinitions->syntaxTreeBuildingPartsToSyntaxTreeBuilderMap());
    SharedPointer<SyntaxTree> syntaxTree = parser->syntaxTree(tokens);
    print(syntaxTree);
  } catch (SharedPointer<Exception> Exception) {
    Exception->baseProcess();
  } catch (const char *Exception) {
    std::cout << Exception << '\n';
  }
  return 0;
}