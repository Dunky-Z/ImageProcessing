#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2\imgproc\types_c.h>
#include <Eigen\Dense>


using namespace Eigen;
using namespace cv;
using namespace std;

double crunch(double x, double alpha);

double calDelta(double alpha, double theta, const Vec3b& color_i, const Vec3b& color_j);
VectorXd getMatrixb(const Mat& source, const int rows, const int cols, const double alpha, const double theta);
MatrixXd getMatrixA(const int rows, const int cols);
VectorXd initG(const Mat & source, const int rows, const int cols);