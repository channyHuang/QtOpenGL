#include "matrixClass.h"


/*
* i.e. for i=1 the function returns the number of rows,
* and for i=2 the function returns the number of columns
* else the function returns 0
*/
int Size(const Matrix& a, const int i)
{
	return a.Size(i);
}


/**
* returns a matrix with size cols x rows with ones as values
*/
Matrix Ones(const int rows, const int cols)
{
	Matrix res = Matrix(rows, cols);

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			res(r, c) = 1;
		}
	}
	return res;
}

/**
* returns a matrix with size cols x rows with zeros as values
*/
Matrix Zeros(const int rows, const int cols)
{
	return Matrix(rows, cols);
}


/**
* returns a diagonal matrix with size n x n with ones at the diagonal
* @param  v a vector
* @return a diagonal matrix with ones on the diagonal
*/
Matrix Diag(const int n)
{
	Matrix res = Matrix(n, n);
	for (int i = 0; i < n; i++)
	{
		res(i, i) = 1;
	}
	return res;
}

/**
* returns a diagonal matrix
* @param  v a vector
* @return a diagonal matrix with the given vector v on the diagonal
*/
Matrix Diag(const Matrix& v)
{
	Matrix res;
	if (v.GetCols() == 1)
	{
		// the given matrix is a vector n x 1
		int rows = v.GetRows();
		res = Matrix(rows, rows);

		// copy the values of the vector to the matrix
		for (int r = 0; r < rows; r++)
		{
			res(r, r) = v.get(r, 0);
		}
	}
	else if (v.GetRows() == 1)
	{
		// the given matrix is a vector 1 x n
		int cols = v.GetCols();
		res = Matrix(cols, cols);

		// copy the values of the vector to the matrix
		for (int c = 0; c < cols; c++)
		{
			res(c, c) = v.get(0, c);
		}
	}
	else
	{
		throw Exceptions("Parameter for diag must be a vector");
	}
	return res;
}

/*
* returns the determinant of Matrix a
*/
double Det(const Matrix& a)
{
	double d = 0;    // value of the determinant
	int rows = a.GetRows();
	int cols = a.GetRows();

	if (rows == cols)
	{
		// this is a square matrix
		if (rows == 1)
		{
			// this is a 1 x 1 matrix
			d = a.get(0, 0);
		}
		else if (rows == 2)
		{
			// this is a 2 x 2 matrix
			// the determinant of [a11,a12;a21,a22] is det = a11*a22-a21*a12
			d = a.get(1, 1) * a.get(0, 0) - a.get(0, 1) * a.get(1, 0);
		}
		else
		{
			// this is a matrix of 3 x 3 or larger
			for (int c = 0; c < cols; c++)
			{
				Matrix M = a.Minor(0, c);
				//d += pow(-1, 1+c) * a(1, c) * Det(M);
				d += (c % 2 + c % 2 - 1) * a.get(0, c) * Det(M); // faster than with pow()
			}
		}
	}
	else
	{
		throw Exceptions("Matrix must be square");
	}
	return d;
}

// swap two values
void Swap(double& a, double& b)
{
	double temp = a;
	a = b;
	b = temp;
}

/*
* returns the inverse of Matrix a
*/
Matrix Inv(const Matrix& a)
{
	Matrix res;
	double d = 0;    // value of the determinant
	int rows = a.GetRows();
	int cols = a.GetRows();

	d = Det(a);
	if (rows == cols && d != 0)
	{
		// this is a square matrix
		if (rows == 1)
		{
			// this is a 1 x 1 matrix
			res = Matrix(rows, cols);
			res(0, 0) = 1 / a.get(0, 0);
		}
		else if (rows == 2)
		{
			// this is a 2 x 2 matrix
			res = Matrix(rows, cols);
			res(0, 0) = a.get(1, 1);
			res(0, 1) = -a.get(0, 1);
			res(1, 0) = -a.get(1, 0);
			res(1, 1) = a.get(0, 0);
			res = (1 / d) * res;
		}
		else
		{
			// this is a matrix of 3 x 3 or larger
			// calculate inverse using gauss-jordan elimination
			res = Diag(rows);   // a diagonal matrix with ones at the diagonal
			Matrix ai = a;    // make a copy of Matrix a

			for (int c = 0; c < cols; c++)
			{
				// element (c, c) should be non zero. if not, swap content
				// of lower rows
				int r;
				for (r = c; r < rows && ai(r, c) == 0; r++)
				{
				}
				if (r != c)
				{
					// swap rows
					for (int s = 0; s < cols; s++)
					{
						Swap(ai(c, s), ai(r, s));
						Swap(res(c, s), res(r, s));
					}
				}

				// eliminate non-zero values on the other rows at column c
				for (int r = 0; r < rows; r++)
				{
					if (r != c)
					{
						// eleminate value at column c and row r
						if (ai(r, c) != 0)
						{
							double f = -ai(r, c) / ai(c, c);

							// add (f * row c) to row r to eleminate the value
							// at column c
							for (int s = 0; s < cols; s++)
							{
								ai(r, s) += f * ai(c, s);
								res(r, s) += f * res(c, s);
							}
						}
					}
					else
					{
						// make value at (c, c) one,
						// divide each value on row r with the value at ai(c,c)
						double f = ai(c, c);
						for (int s = 0; s < cols; s++)
						{
							ai(r, s) /= f;
							res(r, s) /= f;
						}
					}
				}
			}
		}
	}
	else
	{
		if (rows != cols)
		{
			throw Exceptions("Matrix must be square");
		}
		else
		{
			throw Exceptions("Determinant of matrix is zero");
		}
	}
	return res;
}

Matrix Rev(const Matrix& a)
{
	Matrix res(a.Size(2), a.Size(1));
	for (int i = 0; i < res.Size(1); i++) {
		for (int j = 0; j < res.Size(2); j++) {
			res(j, i) = a.get(i, j);
		}
	}
	return res;
}
