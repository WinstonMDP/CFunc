#include <map>
#include <string>

template <typename Element>
class Iterator
{
	virtual void first() = 0;
	virtual bool isDone() = 0;
	virtual void next() = 0;
	virtual Element current() = 0;
};

template <typename Element>
class Collection
{
	public:
	virtual Iterator <Element>* iterator() = 0;
	virtual Collection <Element>* collectionWithNewElement (Element) = 0;
	virtual void push (Element) = 0;
};

template <typename Element>
class Array
{
};

template <typename Key, typename Value>
class Map
{
	public:
	Value value (Key key)
	{
		return _map.at (key);
	}

	Map <Key, Value>* mapWithNewElement (Key key, Value value)
	{
		std::map <Key, Value>* newMap = new std::map <Key, Value> (_map);
		newMap.at (key) = value;
		return newMap;
	}

	Array <Key>* keys()
	{
		return _keys;
	}

	private:
	std::map <Key, Value>* _map;
	Array <Key>* _keys;
};

class Token
{
	public:
	Token (std::string* type, std::string* value)
	: _type {type}, _value {value}
	{
	}

	std::string* type()
	{
		return _type;
	}

	std::string* value()
	{
		return _value;
	}

	private:
	std::string* _type;
	std::string* _value;
};

class Lexer
{
	public:
	Collection <Token*>* tokens()
	{
		for (_wordsIterator->first(); !_wordsIterator->isDone(); _wordsIterator->next())
		{
			std::string* tokenValue = _wordsIterator->current();
			std::string* tokenType = _typesMap->value (tokenValue);
			_tokens->push (new Token (tokenType, tokenValue));
		}
		return _tokens;
	}

	private:
	Iterator <std::string*>* _wordsIterator;
	Map <std::string*, std::string*>* _typesMap;
	Collection <Token*>* _tokens;
};

class AST //composite
{
	public:
	std::string* type()
	{
		return _type;
	}

	Map <std::string*, AST*>* children()
	{
		return _children;
	}

	Map <std::string*, AST*>* ASTWithNewChild (std::string* key, AST* newChild)
	{
		return _children->mapWithNewElement (key, newChild);
	}
	
	private:
	std::string* _type;
	Map <std::string*, AST*>* _children;
};
