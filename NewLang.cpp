#include <map>
#include <string>

template <typename Element>
class Optional
{
	public:
	Optional (Element element)
	: _element {element}
	{
	}

	bool doesExist()
	{
		return _element != nullptr;
	}

	Element element()
	{
		return _element;
	}

	private:
	Element _element;
}

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
	Optional <Value>* value (Key key)
	{
		if (_map.count (key) != 0) {
			return new Optional <Value> (_map.at (key));
		}
		else {
			return new Optional <Value> (nullptr);
		}
	}

	template <typename OtherKey>
	Optional <Value>* value (OtherKey key)
	{
                Array <Key>* mapKeys = keys();
                for (Key mapKey : mapKeys) {
                        if (key == mapKey) {
                                return new Optional <Value> (value (mapKey));
                        }
                }
                return new Optional <Value> (nullptr);
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

	Array <Key*>* keys()
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
			_tokens->pushBack (new Token (tokenType, tokenValue));
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

template <typename CollectionWithOrder>
class ASTDefinition
{
        using Definition = CollectionWithOrder <std::string*>;
        using Types = CollectionWithOrder <std::string*>;

        public:
        Definition* definition()
        {
                return _definition;
        }

        bool isEqual (CollectionWithOrder <AST*>* aSTs)
        {
                Types aSTTypes = types (aSTs);
                Iterator* typesIterator = aSTTypes->iterator();
                Iterator* definitionIterator = definition->iterator();
                for (typesIterator->first(), definitionIterator->first(); !typesIterator->isDone() && !definitionIterator->isDone(); typesIterator->next()) {
                        if (definitionIterator->current() != typesIterator->current()) {
                                return false;
                        }
                }
		return typesIterator->isDone() && definitionIterator->isDone();
        }

        private:
        Definition* _definition;

        Types* types (CollectionWithOrder <AST*>* aSTs)
        {
                Types* typesToReturn = new Types;
                for (AST* aST : aSTs) {
                        typesToReturn->pushBack (aST->type());
                }
                return typesToReturn;
        }
};

template <typename CollectionWithOrder>
bool operator== (ASTDefinition* aSTDefinition, CollectionWithOrder* type)
{
        return aSTDefinition->isEqual (type);
}

template <typename CollectionWithOrder>
class Parser
{
	public:
	AST* ast()
	{
		for (long segmentSize = 0; segmentSize < _ASTs->size(); ++segmentSize) {
			for (long leftIndex = 0; leftIndex < _ASTs->size(); ++leftIndex) {
				long rightIndex = leftIndex + segmentSize;
				CollectionWithOrder <AST*>* subASTs = new CollectionWithOrder <AST*> (_ASTs, leftIndex, rightIndex);
				Optional <std::string*>* aSTType = _ASTDefinitions->value (subASTs);
				if (aSTType->doesExist()) {
					AST* aSTComposedFromOthers = new AST (aSTType->value(), subASTs);
					replace (leftIndex, rightIndex, aSTComposedFromOthers);
				}
			}
		}
                AST* compositeAST = _ASTs.front();
                return compositeAST;
	}

	private:
	CollectionWithOrder <AST*>* _ASTs;
	Map <ASTDefinition*, std::string*>* _ASTDefinitions;

	void replace(long leftIndex, long rightIndex, AST* insertElement)
	{
		_ASTs.remove (leftIndex, rightIndex);
		_ASTs.addElement (leftIndex, insertElement);
	}
};