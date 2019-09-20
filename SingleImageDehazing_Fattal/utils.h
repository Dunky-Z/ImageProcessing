#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2\imgproc\types_c.h>

using namespace std;
using namespace cv;

double sqr(const double x);
double norm(const vector<double> &Alight);
double avg(const double *srcData, const int n);
double conv(double *f, double *g, const int n);
Mat calculateIA(const Mat &src, const int rows, const int cols, const vector<double> &Alight, const double &normA);
Mat calculateIR(const Mat &src, const int rows, const int cols, const Mat &IA);
Mat calculateH(const Mat &src, const int rows, const int cols, const Mat &IA, const Mat &IR, const double &normA);
double calculatEta(const Mat &src, const int rows, const int cols, const Mat &IA, const Mat &IR, const Mat &h);
Mat calculateTransmisson(const int rows, const int cols, const Mat &Ia, const Mat &IR, const double eta,const double normA);