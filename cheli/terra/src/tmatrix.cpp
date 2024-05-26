#include <tmatrix.hpp>

TMatrix::TMatrix() {
    myNumRows = 0;
    myNumCols = 0;
    myNumFields = 0;
}

TMatrix::TMatrix( float p_layout[], int p_rows, int p_cols ) {

    // Set attributes
    myNumRows = p_rows;
    myNumCols = p_cols;
    myNumFields = myNumRows * myNumCols;

    myFields = new float[myNumFields];

    // Set Layout of Matrix
    for ( int i = 0; i < myNumFields; i++ ) {
        myFields[i] = p_layout[i];
    }
}

TMatrix::TMatrix( int p_rows, int p_cols ) {
    myNumRows = p_rows;
    myNumCols = p_cols;
    myNumFields = myNumRows * myNumCols;

    myFields = new float[myNumFields];
}

TMatrix::~TMatrix() {
    delete[] myFields;
}

void TMatrix::mult( float p_scalar ) {
    for ( int i = 0; i < myNumFields; i++ ) {
        myFields[i] *= p_scalar;
    }
}

TMatrix TMatrix::mult( TMatrix * p_matrix ) {
    float * new_layout = new float[myNumRows * p_matrix->countCols()];

    // Perform Matrix multiplication
    for (int i = 0; i < myNumRows; i++) {
        for (int j = 0; j < p_matrix->countCols(); j++) {
            float new_field = 0;

            for (int k = 0; k < p_matrix->countRows(); k++) {
                new_field += this->getValue( k, i ) * p_matrix->getValue( j, k );
            }

            new_layout[j + i * p_matrix->countCols()] = new_field;
        }
    }
    // Create new Matrix
    TMatrix new_matrix( new_layout, myNumRows, p_matrix->countCols() );

    delete[] new_layout;
    return new_matrix;
}

float TMatrix::getValue( int p_position ) {
    return myFields[p_position];
}

float TMatrix::getValue( int p_x, int p_y ) {
    return myFields[p_x + p_y * myNumCols];
}

int TMatrix::countRows() {
    return myNumRows;
}

int TMatrix::countCols() {
    return myNumCols;
}

int TMatrix::countFields() {
    return myNumFields;
}

