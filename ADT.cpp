#include "ADT.h"


IteratedList::IteratedList()
{
	this->capacity = 105;
	this->head = -1;
	this->tail = -1;
	this->first_empty = 0;
	this->nodes = new DLLANode[this->capacity];
	for (int index = 0; index < this->capacity; index++)
	{

		nodes[index].next = index + 1;
		nodes[index].prev = index - 1;
		nodes[index].info = 0;
	}
	nodes[this->capacity-1].next = -1;
}

int IteratedList::size() const
{
	return this->number_of_elements;
}

bool IteratedList::isEmpty() const
{
	return this->number_of_elements == 0;
}


// returns the first position from the list

ListIterator IteratedList::first() const
{
	ListIterator it = ListIterator(*this);
	return it;
}



// returns the element from the given position

//throws an exception if the position is not valid

TElem IteratedList::getElement(ListIterator pos) const
{
	if (pos.position == -1 || pos.position > capacity)
		throw std::exception("Invalid");
	return this->nodes[pos.position].info;
}

//get next value
int IteratedList::getNextElem(ListIterator pos)const
{
	if (pos.position == -1 || pos.position > capacity)
		throw std::exception("Invalid");
	return this->nodes[pos.position].next;
}

// changes the element from the current position to the given one.

//returns the old value from the position

//throws exception if the position is not valid

TElem IteratedList::setElement(ListIterator pos, TElem e)
{
	if (pos.position == -1 || pos.position > capacity)
		throw std::exception("Invalid");
	TElem old=this->nodes[pos.position].info;
	this->nodes[pos.position].info = e;
	return old;
}



// adds a new element to the end of the list

void IteratedList::addToEnd(TElem e)
{
	number_of_elements += 1;
	if (first_empty == -1)
	{
		Resize();
	}
	{
		int empty_after;
		empty_after = nodes[first_empty].next;
		if (head == -1)
		{
			//add the first time
			head = first_empty;
			tail = first_empty;
			nodes[first_empty].info = e;
			nodes[first_empty].next = -1;
			nodes[first_empty].prev = -1;
			if (empty_after != -1)
				nodes[empty_after].prev = -1;
		}
		else
		{
			nodes[tail].next = first_empty;
			//add to the list
			nodes[first_empty].info = e;
			nodes[first_empty].prev = tail;
			nodes[first_empty].next = -1;
			if (empty_after != -1)
				nodes[empty_after].prev = -1;
			tail = first_empty;
		}
		first_empty = empty_after;
	}
	
}

void IteratedList::Resize()
{
	
	DLLANode* copy_store = new DLLANode[this->capacity*2];
	for (int index = 0; index < this->capacity; index++)
		copy_store[index] = this->nodes[index];
	this->first_empty = this->capacity;
	this->capacity = this->capacity * 2;
	for (int index = this->first_empty; index < this->capacity; index++)
	{
		copy_store[index].info = 0;
		copy_store[index].next = index+1;
		copy_store[index].prev = index-1;
	}
	copy_store[this->first_empty].prev = -1;
	copy_store[this->capacity - 1].next = -1;
	this->nodes = copy_store;
}


//adds a new element to a given position

//after addition, pos points to the newly added element

//throws an exception if pos is not valid

void IteratedList::addToPosition(ListIterator& pos, TElem e)
{
	number_of_elements += 1;
	if (first_empty == -1)
	{
		Resize();
	}
	{
		int empty_after;
		empty_after = nodes[first_empty].next;
		if ((pos.position == -1 &&  pos.position!=head) || pos.position > capacity)
		{
			throw std::exception("invalid");
		}
		else
			if(pos.position == head)
			{
				if (head == -1)
				{
					//add the first time
					head = first_empty;
					tail = first_empty;
					nodes[first_empty].info = e;
					nodes[first_empty].next = -1;
					nodes[first_empty].prev = -1;
					if (empty_after != -1)
						nodes[empty_after].prev = -1;
				}
				else
				{
					empty_after = nodes[first_empty].next;
					nodes[first_empty].info = e;
					nodes[first_empty].next = head;
					nodes[first_empty].prev = -1;
					nodes[head].prev = empty_after;
					if (empty_after != -1)
						nodes[empty_after].prev = -1;
					head = first_empty;
				}
				
			}
			else if (pos.position == tail)
			{
				nodes[tail].next = first_empty;
				//add to the list
				nodes[first_empty].info = e;
				nodes[first_empty].prev = tail;
				nodes[first_empty].next = -1;
				if (empty_after != -1)
					nodes[empty_after].prev = -1;
				tail = first_empty;
			}
			else
			{
				//int prev_change, next_change;
				nodes[first_empty].info = nodes[pos.position].info;
				//prev_change = nodes[pos.position].prev;
				//next_change = nodes[pos.position].next;
				nodes[first_empty].next = pos.position;
				nodes[first_empty].prev = nodes[pos.position].prev;
				nodes[pos.position].info = e;
				nodes[pos.position].prev = first_empty;
				if (empty_after != -1)
					nodes[empty_after].prev = -1;
			}
		//pos.position = first_empty;
		first_empty = empty_after;
	}
	
}



//removes the element from position pos

//returns the removed element

//after removal pos is positioned on the next element (the one after the removed one) or it is invalid if the last element was removed

//arunca exceptie daca poz nu e valid

TElem IteratedList::remove(ListIterator& pos)
{
	if ((pos.position == -1 && pos.position != head) || pos.position > capacity)
	{
		throw std::exception("invalid");
	}
	TElem value = nodes[pos.position].info;
	nodes[pos.position].info = 0;
	nodes[nodes[pos.position].prev].next = nodes[pos.position].next;
	nodes[nodes[pos.position].next].prev = nodes[pos.position].prev;
	int new_position = nodes[pos.position].next;
	nodes[first_empty].prev = pos.position;
	nodes[pos.position].next = first_empty;
	nodes[pos.position].prev = -1;
	first_empty = pos.position;
	pos.position = new_position;
	number_of_elements -= 1;
	return value;
}



// searches for the first occurrance of an element 

//returns an iterator that points to the element, if it appears in the list, or an invalid iterator if the element is not in the list

ListIterator IteratedList::search(TElem e) const
{
	int position = head;
	while (nodes[position].info != e && nodes[position].next != -1)
		position = nodes[position].next;
	ListIterator it = ListIterator(*this);
	if (nodes[position].info == e)
	{
		it.position = position;
	}
	else
	{
		it.position = -1;
	}
	return it;
}



//destructor



IteratedList::~IteratedList()
{
	//delete[] this->nodes;
}
