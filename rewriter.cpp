#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <cstring>
#include <algorithm>

std::vector <std::string> writeIn (std::string fileName)
{
    std::ifstream fin (fileName);

    std::vector <std::string> primalLambdaCode;
    std::string string;
    while (!fin.eof()) {
        fin >> string;
        primalLambdaCode.push_back (string);
    }
    
    return primalLambdaCode;
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
I closingBracket (I beginBracket)
{
    if (*beginBracket == "(") {
        ++beginBracket;
    }
    long nOpenBrackets = 1;

    I iter;
    for (iter = beginBracket; nOpenBrackets != 0; ++iter) {
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
I openingBracket (I iter)
{
    for ( ; *iter != "("; --iter)
    ;
    return iter;
}

std::vector <std::string> :: iterator findApplication (std::vector <std::string>& lambdaCode)
{
    std::vector <std::string> :: iterator iter;
    for (iter = lambdaCode.begin(); iter != lambdaCode.end(); ++iter) {
    std::vector <std::string> :: iterator argumentIter = closingBracket (iter) + 1;

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

std::vector <std::string> getArgument (std::vector <std::string>& lambdaCode, std::vector <std::string> :: iterator parameterIter)
{
    std::vector <std::string> :: iterator iter = closingBracket (parameterIter);
    std::vector <std::string> argument;

    ++iter;

    static long nFunctionCalls = 0;
    ++nFunctionCalls;
    std::string prefixNumber = std::to_string (nFunctionCalls);

    if (*iter == "(") {
        std::vector <std::string> :: iterator beginIter = iter;
        std::vector <std::string> :: iterator endIter = closingBracket (iter);

        argument.push_back (*beginIter);
        ++iter;

        
        for ( ; iter != endIter; ++iter) {
            if (*iter != "(" && *iter != ")") {
                argument.push_back (append (prefixNumber, append (std::string {"-"}, *iter)));
            }
            else {
                argument.push_back (*iter);
            }
        }

        argument.push_back (*endIter);

        lambdaCode.erase (beginIter, endIter + 1);
    }
    else {
        argument.push_back (append (prefixNumber, append (std::string {"-"}, *iter)));
        lambdaCode.erase (iter);
    }
    return argument;
}

void deleteParameterBrackets (std::vector <std::string>& lambdaCode, std::vector <std::string> :: iterator& parameterIter)
{
    if ((*(parameterIter + 1)).back() != '.') {
        lambdaCode.erase (openingBracket (parameterIter));
        --parameterIter;
        lambdaCode.erase (closingBracket (parameterIter));
    } 
    lambdaCode.erase (parameterIter);
}

void applicate (std::vector <std::string>& lambdaCode, std::vector <std::string> :: iterator parameterIter)
{
    std::string parameter = pop_back (*parameterIter);
    std::string dotParameter = *parameterIter;
    std::vector <std::string> argument = getArgument (lambdaCode, parameterIter);

    deleteParameterBrackets (lambdaCode, parameterIter);

    for (std::vector <std::string> :: iterator iter = parameterIter; iter != lambdaCode.end(); ++iter) {
        if (*iter == parameter) {
            lambdaCode.erase (iter);
            iter = lambdaCode.insert (iter, argument.begin(), argument.end());
        }
        else if (*iter == dotParameter) {
            iter = closingBracket (iter);
        }
    }
}

std::vector <std::string> startRewritingLoop (std::vector <std::string> primalLambdaCode)
{
    for (std::vector <std::string> :: iterator parameterIter = findApplication (primalLambdaCode); parameterIter != primalLambdaCode.end();
         parameterIter = findApplication (primalLambdaCode)) {
        applicate (primalLambdaCode, parameterIter);
        print ("output.ncfunc", primalLambdaCode, " ");
    }

    return primalLambdaCode;
}

int main ()
{
    std::vector <std::string> primalLambdaCode = writeIn ("test.cfunc");
    std::vector <std::string> incompleteLambdaCode = startRewritingLoop (primalLambdaCode);
    print ("output.ncfunc", incompleteLambdaCode, " ");
    return 0;
}