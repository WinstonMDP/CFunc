#include <iostream>
#include <vector>

class Term
{

};

class Body
{
	public:
	Body (std::vector <Term> p_body) : body (p_body)
	{
	}

	private:
	std::vector <Term> body;
};

class Primitive : public Term
{
	public:
	Primitive (std::string p_name) : name (p_name)
	{
	}

	private:
	std::string name;
};

class Abstraction : public Term
{
	public:
	Abstraction (Primitive p_parameter, Body p_body) : parameter (p_parameter), body (p_body)
	{
	}

	

	private:
	Primitive parameter;
	Body body;
};

int main ()
{

	Primitive x ("x");
	Abstraction xAbstraction (x, Body {std::vector <Term> {x}}); // Bad vector, i want to remove it
	Primitive y ("y");
	Primitive z ("z");
	Body body (std::vector <Term> {xAbstraction, y, z});

	return 0;
}

