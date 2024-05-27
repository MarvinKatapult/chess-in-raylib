#include <tlist.hpp>
#include <stdio.h>

TList::TList() {
	myLength = 0;
    myFirstElement = 0L;
}

TList::TList( const TList & p_list ) {
    myLength = 0;
    myFirstElement = 0L;
    
    for ( int i = 0; i < p_list.count(); i++ ) {
        append( p_list.getValue( i ) );
    }
}

TList::~TList() {
	clear();
}

void TList::clear() {
	TListElement * current = myFirstElement;
	myFirstElement = 0L;

	// Go through Elements and delete
	while ( current != 0L ) {
		TListElement * temp = current;
		current = current->getNext();
		delete( temp );
	}
	myLength = 0;
}

void TList::append( void * p_element ) {
	// Create new Element
	TListElement * new_element = new TListElement();
	new_element->setValue( p_element );	

	// If element is not first element
	if ( myLength != 0 ) {
		TListElement * last_element = getLast();
		// Chain Elements
		last_element->setNext( new_element );
		new_element->setPrev( last_element );

	// If Element is first Element
	} else myFirstElement = new_element;
	myLength++;
}

void * TList::getValue( int p_position ) const {
	TListElement * current = myFirstElement;
	while( p_position != 0 ) {
		if ( current->getNext() == 0L ) return 0L;
		current = current->getNext();
		p_position--;
	}
	
	return current->getValue();
}

void TList::update( int p_position, void * p_value ) {
    TListElement * element = getElement( p_position );
    if ( element != 0L ) element->setValue( p_value );
}

void TList::remove( int p_position ) {
	TListElement * current = getElement( p_position );
    if ( current == 0L ) return;

    TListElement * next = current->getNext();
    TListElement * prev = current->getPrev();
    if ( next != 0L ) {
        next->setPrev( prev );
    }
    if ( prev != 0L ) {
        prev->setNext( next );
    }
    if ( current == myFirstElement ) myFirstElement = next;

	myLength--;
	delete( current );
}

TListElement * TList::getLast() {
	TListElement * current = myFirstElement;
    if ( current == 0L ) return 0L;
	while ( current->getNext() != 0L ) {
		current = current->getNext();
	}

	return current;
}

TListElement * TList::getElement( int p_position ) {
    if ( p_position == 0 ) return myFirstElement;

	TListElement * current = myFirstElement;
	while ( p_position != 0 ) {
        if ( current == 0L ) return 0L;
		current = current->getNext();
		p_position--;
	}

	return current;
}

TList & TList::operator=( const TList & p_other ) {
    myLength = 0;
    
    for ( int i = 0; i < p_other.count(); i++ ) {
        append( p_other.getValue( i ) );
    }

    return *this;
}
