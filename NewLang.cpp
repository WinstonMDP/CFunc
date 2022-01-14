#include <map>
#include <string>

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
