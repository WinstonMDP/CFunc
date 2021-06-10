#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstring>
#include <algorithm>

std::vector <std::string> writeIn (std::string fileName)
{
    std::ifstream fin (fileName);

    std::vector <std::string> LambdaCode;
    std::string string;
    while (!fin.eof()) {
        fin >> string;
        LambdaCode.push_back (string);
    }
    
    return LambdaCode;
}

template <class C>
void print (std::string filename, C collection, std::string separator = " ")
{
    std::ofstream fout (filename);
    for (typename C :: value_type v : collection) {
        fout << v << separator;
    }
}

template <class I>
I closingBracket (I openingBracketIter)
{
    if (*openingBracketIter == "(") {
        ++openingBracketIter;
    }

    long nOpenBrackets = 1;
    I iter;
    for (iter = openingBracketIter; nOpenBrackets != 0; ++iter) {
        if (*iter == "(") {
            ++nOpenBrackets;
        }
        else if (*iter == ")") {
            --nOpenBrackets;
        }
    }
    --iter;

    return iter;
}

template <class I>
I openingBracketNear (I iter)
{
    for ( ; *iter != "("; --iter)
    ;
    return iter;
}

template <class C>
typename C :: iterator findApplication (C& lambdaCode)
{
    typename C :: iterator iter;
    for (iter = lambdaCode.begin(); iter != lambdaCode.end(); ++iter) {
        typename C :: iterator argumentIter = closingBracket (iter) + 1;
        if ((*iter).back() == '.' && argumentIter != lambdaCode.end() && *argumentIter != ")") {
            return iter;
        }
    }
    return iter; // lambdaCode.end()
}

template <class C>
C pop_back (C colletion)
{
    colletion.pop_back();
    return colletion;
}

template <class C>
C append ( const C& A, const C& B )
{
	C AB;
	AB.reserve( A.size() + B.size() );
	AB.insert( AB.end(), A.begin(), A.end() );
	AB.insert( AB.end(), B.begin(), B.end() );
	return AB;
}

template <class C, class I>
C getArgument (C& lambdaCode, I parameterIter)
{
    C argument;

    I iter = closingBracket (parameterIter);
    ++iter;

    static long nFunctionCalls = 0;
    ++nFunctionCalls;
    std::string prefixNumber = std::to_string (nFunctionCalls);
    std::string prefix = append (prefixNumber, std::string {"-"});

    if (*iter == "(") {
        I beginIter = iter;
        I endIter = closingBracket (iter);

        argument.push_back (*beginIter);
        ++iter;
        for ( ; iter != endIter; ++iter) {
            if (*iter != "(" && *iter != ")") {
                argument.push_back (append (prefix, *iter));
            }
            else {
                argument.push_back (*iter);
            }
        }
        argument.push_back (*endIter);

        lambdaCode.erase (beginIter, endIter + 1);
    }
    else {
        argument.push_back (append (prefix, *iter));
        lambdaCode.erase (iter);
    }
    return argument;
}

template <class C, class I>
void deleteParameterBrackets (C& lambdaCode, I& parameterIter)
{
    if ((*(parameterIter + 1)).back() != '.') {
        lambdaCode.erase (openingBracketNear (parameterIter));
        --parameterIter;
        lambdaCode.erase (closingBracket (parameterIter));
    } 
    lambdaCode.erase (parameterIter);
}

template <class C, class I>
void applicate (C& lambdaCode, I parameterIter)
{
    std::string parameter = pop_back (*parameterIter);
    std::string dotParameter = *parameterIter;
    C argument = getArgument (lambdaCode, parameterIter);

    deleteParameterBrackets (lambdaCode, parameterIter);

    for (I iter = parameterIter; iter != lambdaCode.end(); ++iter) {
        if (*iter == parameter) {
            lambdaCode.erase (iter);
            iter = lambdaCode.insert (iter, argument.begin(), argument.end());
        }
        else if (*iter == dotParameter) {
            iter = closingBracket (iter);
        }
    }
}

template <class C>
C startRewritingLoop (C inputCode)
{
    for (typename C :: iterator parameterIter = findApplication (inputCode); parameterIter != inputCode.end();
         parameterIter = findApplication (inputCode)) {
        applicate (inputCode, parameterIter);
        // print ("output.ncfunc", primalLambdaCode, " ");
    }

    return inputCode;
}

std::vector <std::string> compositeParser (std::string compositeCode)
{
    std::vector <std::string> outputCode;
    bool shouldSplit = false;
    for (char ch : compositeCode) {
        if (ch == '(' || ch == ')') {
            outputCode.push_back (std::string {ch});
            shouldSplit = true;
        }
        else if (ch == '.') {
            outputCode.back().push_back ('.');
            shouldSplit = true;
        }
        else {
            if (outputCode.size () == 0 || shouldSplit) {
                outputCode.push_back (std::string {ch});
                shouldSplit = false;
            }
            else {
                outputCode.back().push_back (ch);
            }
        }
    }
    return outputCode;
}

template <class C>
C parser (C inputCode)
{
    C outputCode;
    for (std::string el : inputCode) {
        if (el == "(" || el == ")") {
            outputCode.push_back (el);
        }
        else if (el == ".") {
            outputCode.back().append(el);
        }
        else if (el.find ("(") != std::string::npos || el.find(")") != std::string::npos || el.find (".") != std::string::npos) {
            C compositeCode = compositeParser (el);
            outputCode.insert (outputCode.end(), compositeCode.begin(), compositeCode.end());
        } 
        else {
            outputCode.push_back (el);
        }
    }
    return outputCode;
}

int main ()
{
    std::vector <std::string> primalLambdaCode = parser (writeIn ("test.cfunc"));
    std::vector <std::string> incompleteLambdaCode = startRewritingLoop (primalLambdaCode);
    print ("output.ncfunc", incompleteLambdaCode, " ");
    return 0;
}