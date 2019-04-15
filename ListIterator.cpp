#include "ListIterator.h"
#include <exception>
ListIterator::ListIterator(const IteratedList& list) : c(list)
{
	this->position = c.head;
}

// sets the iterator to the first element of the container

void ListIterator::first()
{
	this->position = c.head;
}



//moves the iterator to the next element

//throws exception if the iterator is not valid

void ListIterator::next()
{
	if (valid() == true)
	{
		this->position=this->c.getNextElem(*this);
	}
	else
		throw std::exception("Invalid");
}



//checks if the iterator is valid

bool ListIterator::valid() const
{
	return this->position != -1;
}



//returns the value of the current element from the iterator

// throws exception if the iterator is not valid

TElem ListIterator::getCurrent() const
{
	if (valid() == true)
	{
		return this->c.getElement(*this);
	}
	else
		throw std::exception("Invalid");

}