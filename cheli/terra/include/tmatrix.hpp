#pragma once

class TMatrix {

	public:

        /** Constructors **/
		TMatrix( void );
		TMatrix( float layout[], int rows, int cols );
		TMatrix( int rows, int cols );

        /** Deconstructor **/
		~TMatrix( void );

        /** Modification **/
		void mult( float scalar );
		TMatrix mult( TMatrix * matrix );

        /** Utils **/
		float getValue( int position );
		float getValue( int x, int y );
		int countRows( void );
		int countCols( void );
		int countFields( void );

	private:

		float * myFields;

		int myNumFields;
		int myNumRows;
		int myNumCols;
};
