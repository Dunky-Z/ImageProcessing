#include "utils.h"

using namespace std;
using namespace cv;

void main(int argc, char** argv)
{
	Mat src = imread(argv[1]);
	imshow("src", src);

	//���ô�����Ĭ��ֵ
	double Airlight[3] = { 0.7, 0.8, 0.9 };

	waitKey(0);
}