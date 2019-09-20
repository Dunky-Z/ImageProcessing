#include "Color2Gray.h"
#include "utils.h"

void color2Gray(const String & filename, /*int max_iter,*/ double alpha, double theta)
{
	Mat source, target;
	string outFile = "target1.png";
	int rows, cols, N;
	source = imread(filename);
	cvtColor(source, source, cv::ColorConversionCodes::COLOR_RGB2Lab);
	rows = source.rows;
	cols = source.cols;

	N = rows * cols;
	VectorXd delta(N), g(N);
	MatrixXd A(N, N);

	delta = getMatrixb(source, rows, cols, alpha, theta);
	g = initG(source, rows, cols);
	A = getMatrixA(rows, cols);
	cout << "解方程" << endl;
	g = A.ldlt().solve(delta);

	cout << "写文件" << endl;
	target = Mat(rows, cols, CV_8U);
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			int _g = g(row * cols + col);
			if (_g < 0) _g = 0;
			if (_g > 255) _g = 255;
			target.at<uchar>(row, col) = static_cast<uchar>(_g);
		}
	}
	imwrite(outFile, target);
}
