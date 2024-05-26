#pragma once

class TListElement {

	public:

        /** Constructor **/
		TListElement( void ) {
			myNext = 0L;
			myPrev = 0L;
		}

        /** Deconstructor **/
		~TListElement( void ) {}

		/** Modification **/
		void setNext( TListElement * element ) { myNext = element; }
		void setPrev( TListElement * element ) { myPrev = element; }
		void setValue( void * value ) { myValue = value; }

        /** Utils **/
		void * getValue( void ) { return myValue; }
		TListElement * getNext( void ) { return myNext; }
		TListElement * getPrev( void ) { return myPrev; }

	private:

		void * myValue;

		TListElement * myNext;
		TListElement * myPrev;

}; 

class TList {

	public:

        /** Constructors **/
		TList( void );
        TList( const TList & list );

        /** Deconstructor **/
		~TList( void );

        /** Modification **/
		void clear( void );
		void append( void * element );
		void update( int position, void * element );
		void remove( int position );

        /** Utils **/
		int count( void ) const { return myLength; }
		void * getValue( int position ) const;

        /** Operators **/
        TList & operator=( const TList & other );
	
	private:

		TListElement * getLast( void );
		TListElement * getElement( int position );

		TListElement * myFirstElement;
		int myLength;
};
