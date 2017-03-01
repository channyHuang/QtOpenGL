/*
A simple matrix class

With this class you can:
- create a 2D matrix with custom size
- get/set the cell values
- use operators +, -, *, /
- use functions Ones(), Zeros(), Diag(), Det(), Inv(), Size()
- print the content of the matrix

Usage:
you can create a matrix by:
Matrix A;
Matrix A = Matrix(rows, cols);
Matrix A = B;

you can get and set matrix elements by:
A(2,3) = 5.6;    // set an element of Matix A
value = A(3,1);   // get an element of Matrix A
value = A.get(3,1); // get an element of a constant Matrix A
A = B;        // copy content of Matrix B to Matrix A

you can apply operations with matrices and doubles:
A = B + C;
A = B - C;
A = -B;
A = B * C;
A = B / C;

the following functions are available:
A = Ones(rows, cols);
A = Zeros(rows, cols);
A = Diag(n);
A = Diag(B);
d = Det(A);
A = Inv(B);
cols = A.GetCols();
rows = A.GetRows();
cols = Size(A, 1);
rows = Size(A, 2);

you can quick-print the content of a matrix in the console with:
A.Print();
*/

#include <cstdlib>
#include <cstdio>
#include <math.h>

#define PAUSE {printf("Press \"Enter\" to continue\n"); fflush(stdin); getchar(); fflush(stdin);}

// Declarations
class Matrix;
double Det(const Matrix& a);
Matrix Diag(const int n);
Matrix Diag(const Matrix& v);
Matrix Inv(const Matrix& a);
Matrix Ones(const int rows, const int cols);
int Size(const Matrix& a, const int i);
Matrix Zeros(const int rows, const int cols);
Matrix Rev(const Matrix& a);


/*
* a simple Exceptions class
* you can create an exeption by entering
*   throw Exceptions("...Error description...");
* and get the error message from the data msg for displaying:
*   err.msg
*/


class Exceptions
{
public:
	const char* msg;
	Exceptions(const char* arg)
		: msg(arg)
	{
	}
};


class Matrix
{
public:
	// constructor
	Matrix()
	{
		//printf("Executing constructor Matrix() ...\n");
		// create a Matrix object without content
		p = NULL;
		rows = 0;
		cols = 0;
	}

	// constructor
	Matrix(const int row_count, const int column_count)
	{
		// create a Matrix object with given number of rows and columns
		p = NULL;

		if (row_count > 0 && column_count > 0)
		{
			rows = row_count;
			cols = column_count;

			p = new double*[rows];
			for (int r = 0; r < rows; r++)
			{
				p[r] = new double[cols];

				// initially fill in zeros for all values in the matrix;
				for (int c = 0; c < cols; c++)
				{
					p[r][c] = 0;
				}
			}
		}
	}

	// assignment operator
	Matrix(const Matrix& a)
	{
		rows = a.rows;
		cols = a.cols;
		p = new double*[a.rows];
		for (int r = 0; r < a.rows; r++)
		{
			p[r] = new double[a.cols];

			// copy the values from the matrix a
			for (int c = 0; c < a.cols; c++)
			{
				p[r][c] = a.p[r][c];
			}
		}
	}

	// index operator. You can use this class like myMatrix(col, row)
	// the indexes are one-based, not zero based.
	double& operator()(const int r, const int c)
	{
		if (p != NULL && r >= 0 && r < rows && c >= 0 && c < cols)
		{
			return p[r][c];
		}
		else
		{
			throw Exceptions("Subscript out of range");
		}
	}

	// index operator. You can use this class like myMatrix.get(col, row)
	// the indexes are one-based, not zero based.
	// use this function get if you want to read from a const Matrix
	double get(const int r, const int c) const
	{
		if (p != NULL && r >= 0 && r < rows && c >= 0 && c < cols)
		{
			return p[r][c];
		}
		else
		{
			throw Exceptions("Subscript out of range");
		}
	}

	// assignment operator
	Matrix& operator= (const Matrix& a)
	{
		rows = a.rows;
		cols = a.cols;
		p = new double*[a.rows];
		for (int r = 0; r < a.rows; r++)
		{
			p[r] = new double[a.cols];

			// copy the values from the matrix a
			for (int c = 0; c < a.cols; c++)
			{
				p[r][c] = a.p[r][c];
			}
		}
		return *this;
	}

	// add a double value (elements wise)
	Matrix& Add(const double v)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				p[r][c] += v;
			}
		}
		return *this;
	}

	// subtract a double value (elements wise)
	Matrix& Subtract(const double v)
	{
		return Add(-v);
	}

	// multiply a double value (elements wise)
	Matrix& Multiply(const double v)
	{
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				p[r][c] *= v;
			}
		}
		return *this;
	}

	// divide a double value (elements wise)
	Matrix& Divide(const double v)
	{
		return Multiply(1 / v);
	}

	// addition of Matrix with Matrix
	friend Matrix operator+(const Matrix& a, const Matrix& b)
	{
		// check if the dimensions match
		if (a.rows == b.rows && a.cols == b.cols)
		{
			Matrix res(a.rows, a.cols);

			for (int r = 0; r < a.rows; r++)
			{
				for (int c = 0; c < a.cols; c++)
				{
					res.p[r][c] = a.p[r][c] + b.p[r][c];
				}
			}
			return res;
		}
		else
		{
			// give an error
			throw Exceptions("Dimensions does not match");
		}

		// return an empty matrix (this never happens but just for safety)
		return Matrix();
	}

	// addition of Matrix with double
	friend Matrix operator+ (const Matrix& a, const double b)
	{
		Matrix res = a;
		res.Add(b);
		return res;
	}
	// addition of double with Matrix
	friend Matrix operator+ (const double b, const Matrix& a)
	{
		Matrix res = a;
		res.Add(b);
		return res;
	}

	// subtraction of Matrix with Matrix
	friend Matrix operator- (const Matrix& a, const Matrix& b)
	{
		// check if the dimensions match
		if (a.rows == b.rows && a.cols == b.cols)
		{
			Matrix res(a.rows, a.cols);

			for (int r = 0; r < a.rows; r++)
			{
				for (int c = 0; c < a.cols; c++)
				{
					res.p[r][c] = a.p[r][c] - b.p[r][c];
				}
			}
			return res;
		}
		else
		{
			// give an error
			throw Exceptions("Dimensions does not match");
		}

		// return an empty matrix (this never happens but just for safety)
		return Matrix();
	}

	// subtraction of Matrix with double
	friend Matrix operator- (const Matrix& a, const double b)
	{
		Matrix res = a;
		res.Subtract(b);
		return res;
	}
	// subtraction of double with Matrix
	friend Matrix operator- (const double b, const Matrix& a)
	{
		Matrix res = -a;
		res.Add(b);
		return res;
	}

	// operator unary minus
	friend Matrix operator- (const Matrix& a)
	{
		Matrix res(a.rows, a.cols);

		for (int r = 0; r < a.rows; r++)
		{
			for (int c = 0; c < a.cols; c++)
			{
				res.p[r][c] = -a.p[r][c];
			}
		}

		return res;
	}

	// operator multiplication
	friend Matrix operator* (const Matrix& a, const Matrix& b)
	{
		// check if the dimensions match
		if (a.cols == b.rows)
		{
			Matrix res(a.rows, b.cols);

			for (int r = 0; r < a.rows; r++)
			{
				for (int c_res = 0; c_res < b.cols; c_res++)
				{
					for (int c = 0; c < a.cols; c++)
					{
						res.p[r][c_res] += a.p[r][c] * b.p[c][c_res];
					}
				}
			}
			return res;
		}
		else
		{
			// give an error
			throw Exceptions("Dimensions does not match");
		}

		// return an empty matrix (this never happens but just for safety)
		return Matrix();
	}

	// multiplication of Matrix with double
	friend Matrix operator* (const Matrix& a, const double b)
	{
		Matrix res = a;
		res.Multiply(b);
		return res;
	}
	// multiplication of double with Matrix
	friend Matrix operator* (const double b, const Matrix& a)
	{
		Matrix res = a;
		res.Multiply(b);
		return res;
	}

	// division of Matrix with Matrix
	friend Matrix operator/ (const Matrix& a, const Matrix& b)
	{
		// check if the dimensions match: must be square and equal sizes
		if (a.rows == a.cols && a.rows == a.cols && b.rows == b.cols)
		{
			Matrix res(a.rows, a.cols);

			res = a * Inv(b);

			return res;
		}
		else
		{
			// give an error
			throw Exceptions("Dimensions does not match");
		}

		// return an empty matrix (this never happens but just for safety)
		return Matrix();
	}

	// division of Matrix with double
	friend Matrix operator/ (const Matrix& a, const double b)
	{
		Matrix res = a;
		res.Divide(b);
		return res;
	}

	// division of double with Matrix
	friend Matrix operator/ (const double b, const Matrix& a)
	{
		Matrix b_matrix(1, 1);
		b_matrix(0, 0) = b;

		Matrix res = b_matrix / a;
		return res;
	}

	/**
	* returns the minor from the given matrix where
	* the selected row and column are removed
	*/
	Matrix Minor(const int row, const int col) const
	{
		Matrix res;
		if (row > 0 && row <= rows && col > 0 && col <= cols)
		{
			res = Matrix(rows - 1, cols - 1);

			// copy the content of the matrix to the minor, except the selected
			for (int r = 0; r < (rows - (row >= rows)); r++)
			{
				for (int c = 0; c < (cols - (col >= cols)); c++)
				{
					res(r - (r > row), c - (c > col)) = p[r][c];
				}
			}
		}
		else
		{
			throw Exceptions("Index for minor out of range");
		}

		return res;
	}

	/*
	* returns the size of the i-th dimension of the matrix.
	* i.e. for i=1 the function returns the number of rows,
	* and for i=2 the function returns the number of columns
	* else the function returns 0
	*/
	int Size(const int i) const
	{
		if (i == 1)
		{
			return rows;
		}
		else if (i == 2)
		{
			return cols;
		}
		return 0;
	}

	// returns the number of rows
	int GetRows() const
	{
		return rows;
	}

	// returns the number of columns
	int GetCols() const
	{
		return cols;
	}

	// print the contents of the matrix
	void Print() const
	{
		if (p != NULL)
		{
			printf("[");
			for (int r = 0; r < rows; r++)
			{
				if (r > 0)
				{
					printf(" ");
				}
				for (int c = 0; c < cols - 1; c++)
				{
					printf("%.2f, ", p[r][c]);
				}
				if (r < rows - 1)
				{
					printf("%.2f;\n", p[r][cols - 1]);
				}
				else
				{
					printf("%.2f]\n", p[r][cols - 1]);
				}
			}
		}
		else
		{
			// matrix is empty
			printf("[ ]\n");
		}
	}

public:
	// destructor
	~Matrix()
	{
		// clean up allocated memory
		for (int r = 0; r < rows; r++)
		{
			delete p[r];
		}
		delete p;
		p = NULL;
	}

private:
	int rows;
	int cols;
	double** p;     // pointer to a matrix with doubles
};
