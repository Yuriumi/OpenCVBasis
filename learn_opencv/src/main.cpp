#include <iostream>

#include <opencv2/opencv.hpp>

int main()
{
	cv::Mat image = cv::imread("./image/test.jpg");

	cv::imshow("window", image);

	cv::waitKey(0);

	return 0;
}