#include <iostream>

#include "Color2Gray.h"

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	int max_iter = 30;
	double alpha = 25, theta = M_PI_4 * 2;
	color2Gray(argv[1], /*max_iter,*/ alpha, theta);
	return 0;

	//Mat src = imread("dots.png");
	//imshow("src", src);
	//imwrite("dots1.png", src);
	//waitKey(0);
	//return 0;
}