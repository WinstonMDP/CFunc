#include <iostream>
#include <vector>

class Term
{
        public:
        virtual Body reductionResult();
	virtual Body applicationResult();
};

class Body
{
	public:
	Body (std::vector <Term> p_body) : body (p_body)
	{
	}

	Body reductionResult ()
	{
                return this->elementsReductionResult().elementsApplicationResult();
        }

	private:
	std::vector <Term> body;

        Body elementsReductionResult () 
        {
		long firstIterationElementIndex;
		return recuElementsReductionResult (body, firstIterationElementIndex, [body] (long i) {return body.size() - i;} );
        }

	template <class F>
        Body recuElementsReductionResult (Body iterBody, long i, F nextElementIndex)
        {
                return this->recuElementsReductionResult(append (withoutLastElement(iterBody), body.at (nextElementIndex (i)).reductionResult()), i + 1);
        }

	Body elementsApplicationResult ()
	{
		return recuElementsApplicationResult ();
	}

	Body recuElementsApplicationResult ()
	{
	}
};

class Primitive : public Term
{
	public:
	Primitive (std::string p_name) : name (p_name)
	{
	}

        Body reductionResult ()
        {
                return *this;
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

        virtual Body reductionResult ()
        {
                return body.reductionResult();
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
	body.reductionResult();
	return 0;
}

