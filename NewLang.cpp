#include <map>
#include <string>

template <typename Element>
class Iterator //iterator
{
	virtual void first() = 0;
	virtual bool isDone() = 0;
	virtual void next() = 0;
	virtual Element current() = 0;
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

	template <typename OtherKey>
	Value value (OtherKey key)
	{
	}

	Map <Key, Value>* mapWithNewElement (Key key, Value value)
	{
		std::map <Key, Value>* newMap = new std::map <Key, Value> (_map);
		newMap.at (key) = value;
		return newMap;
	}

	void addElement (Key key, Value value)
	{
		_map.at (key) = value;
	}

	Map <Key, Value>* mapWithoutElement (Key key)
	{
		std::map <Key, Value>* newMap = new std::map <Key, Value> (_map);
		newMap->erase (key);
		return newMap;
	}

	void removeElement (Key key)
	{
		_map.erase (key);
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

template <typename Collection>
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
	using Children = Map <std::string*, AST*>;

	public:
	std::string* type()
	{
		return _type;
	}

	Children* children()
	{
		return _children;
	}

	Children* ASTWithNewChild (AST* newChild)
	{
		return _children->mapWithNewElement (newChild->type(), newChild);
	}

	void addChild (AST* child)
	{
		_children->addElement (child->type(), child);
	}

	Children* ASTWithoutChild (AST* child)
	{
		return _children->mapWithoutElement (child->type());
	}

	void removeChild (AST* child)
	{
		_children->removeElement (child->type());
	}
	
	private:
	std::string* _type;
	Children* _children;
};

class ASTDefinition
{
};

template <typename Collection>
class Parser
{
	public:
	AST* ast()
	{
		for (long segmentSize = 0; _uncompositeASTs->size() != 0; ++segmentSize) {
			for (long leftIndex = 0; leftIndex < _unprocessedAST->size(); ++leftIndex) {
				long rightIndex = leftIndex + segmentSize;
				Array <AST*>* subunprocessedASTs = new Array <AST*> (_uncompositeASTs, leftIndex, rightIndex);
				if (isInclude (_ASTDefinitions, subuncompositeASTs)) {
					_uncompositeASTs.remove (leftIndex, rightIndex);
					AST* newASTToComposeWithOther = new AST (_ASTDefinitions->value (subuncompositeASTs), subuncompositeASTs);
					_uncompositeASTs.addElement (leftIndex, newASTToComposeWithOther);
				}
			}
		}
	}

	private:
	Array <AST*>* _uncompositeASTs;
	Map <ASTDefinition*, std::string*>* _ASTDefinitions;
};