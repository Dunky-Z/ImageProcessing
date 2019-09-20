#include "utils.h"

double sqr(const double x)
{
	return x * x;
}

double norm(const vector<double>& Alight)
{
	return sqrt(sqr(Alight[0]) + sqr(Alight[1]) + sqr(Alight[2]));
}

double avg(const double * srcData, const int n)
{
	double sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += srcData[i];
	}
	return sum / n;
}

double conv(double * f, double * g, const int n)
{
	double Ef = avg(f, n);
	double Eg = avg(g, n);
}

Mat calculateIA(const Mat &src, const int rows, const int cols, const vector<double> &Alight, const double &normA)
{
	Mat IA(rows, cols, CV_32FC1);
	for (int i = 0; i < rows; ++i)
	{
		const double* srcPtr = src.ptr<double>(i);
		double* dstPtr = IA.ptr<double>(i);
		for (int j = 0; j < cols; ++j)
		{
			double res = 0;
			for (int channel = 0; channel < 3; ++channel)
				res += (*srcPtr++) * Alight[k];
			*dstPtr++ = res / normA;
		}
	}
	return IA;
}

Mat calculateIR(const Mat & src, const int rows, const int cols, const Mat & IA)
{
	Mat IR(rows, cols, CV_32FC1);
	for (int i = 0; i < rows; ++i)
	{
		const double* srcPtr = src.ptr<double>(i);
		double* IRPtr = IR.ptr<double>(i);
		double* IAPtr = IA.ptr<double>(i);
		for (int j = 0; j < cols; ++j)
		{
			double srcNorm = norm(srcPtr[j]);
			*IRPtr = sqrt(sqr(srcNorm) - sqr(*IAPtr));
			IAPtr++;
			IRPtr++;
		}
	}
	return IA;
}

Mat calculateH(const Mat & src, const int rows, const int cols, const Mat & IA, const Mat & IR, const double &normA)
{
	Mat h(rows, cols, CV_32FC1);
	for (int i = 0; i < rows; ++i)
	{
		double* IAPtr = IA.ptr<double>(i);
		double* IRPtr = IR.ptr<double>(i);
		double* hPtr = h.ptr<double>(i);
		for (int j = 0; j < cols; ++j)
		{
			*hPtr = (normA - *IAPtr) / *IRPtr;
			hPtr++;
			IAPtr++;
			IRPtr++;
		}
	}
}

double calculatEta(const Mat & src, const int rows, const int cols, const Mat & IA, const Mat & IR, const Mat & h)
{
	int len = rows * cols;
	double* IAarr = new double[len];
	double* IRarr = new double[len];
	double* harr = new double[len];
	for (int i = 0; i < rows; ++i)
	{
		const double* IAdata = IA.ptr<double>(i);
		const double* IRdata = IR.ptr<double>(i);
		const double* hdata = h.ptr<double>(i);
		for (int j = 0; j < cols; ++j)
		{
			IAarr[i*cols + j] = *IAdata++;
			IRarr[i*cols + j] = *IRdata++;
			harr[i*cols + j] = *hdata++;
		}
	}
	return (conv(IAarr, harr, len) / conv(IRarr, harr, len));
}

Mat calculateTransmisson(const int rows, const int cols, const Mat & IA, const Mat & IR, const double eta, const double normA)
{
	Mat t(rows, cols, CV_32FC1);
	for (int i = 0; i < rows; ++i)
	{
		double* IAPtr = IA.ptr<double>(i);
		double* IRPtr = IR.ptr<double>(i);
		double* tPtr = t.ptr<double>(i);
		for (int j = 0; j < cols; ++j)
		{
			*tPtr = 1 - (*IAPtr - eta * (*IRPtr)) / normA;
			tPtr++; IAPtr++; IRPtr++;
		}
	}

}
