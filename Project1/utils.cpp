#include "utils.h"

double crunch(double x, double alpha)
{
	return alpha > 0 ? alpha * tanh(x / alpha) : 0;
}

double calDelta(double alpha, double theta, const Vec3b & color_i, const Vec3b & color_j)
{
	double Lij = color_i[0] - color_j[0];
	double Cij_a = color_i[1] - color_j[1];
	double Cij_b = color_i[2] - color_j[2];
	double color_dis = sqrt(Cij_a * Cij_a + Cij_b * Cij_b);
	double crunch_res = crunch(color_dis, alpha);
	if (abs(Lij) > crunch_res)
		return Lij;
	else if (Cij_a * cos(theta) + Cij_b * sin(theta) >= 0)
		return crunch_res;
	else
		return -crunch_res;
}

VectorXd getMatrixb(const Mat & source, const int rows, const int cols, const double alpha, const double theta)
{
	cout << "getb" << endl;
	VectorXd deltas(rows*cols);
	deltas.setZero();
	for (int row = 0; row < rows; ++row)
	{
		cout << "B";
		for (int col = 0; col < cols; ++col)
		{
			for (int r = 0; r < rows; ++r)
			{
				for (int c = 0; c < cols; ++c)
				{	
					if (r == row && c == col) continue;
					deltas(row * cols + col) += calDelta(alpha, theta, source.at<Vec3b>(row, col), source.at<Vec3b>(r, c));
				}
			}
		}
	}
	return deltas;
}

VectorXd initG(const Mat & source, const int rows, const int cols)
{
	cout << "initG" << endl;
	VectorXd g(rows*cols);
	g.setZero();
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			g(row * cols + col) = source.at<Vec3b>(row, col)[0];
		}
	}
	return g;
}

MatrixXd getMatrixA(const int rows, const int cols)
{
	cout << "getA" << endl;
	int N = rows * cols;
	MatrixXd A;
	try
	{
		A.resize(N, N);
	}
	catch (std::exception &e) // catch all exceptions, no type declaration required
	{
	}
	//for (int i = 0; i < N; ++i)
	//	for (int j = 0; j < N; ++j)
	//		A(i, j) = -1;
	A.fill(-1);
	for (int i = 0; i < N; ++i)
		A(i, i) = N - 1;
	return A;
}
