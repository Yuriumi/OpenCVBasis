#include <iostream>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>
#include <pfd/portable-file-dialogs.h>

#define CVUI_IMPLEMENTATION
#include "../ref/cvui.h"

#define LOG(x) std::cout<< x << '\n'

int main()
{
	cv::Mat image = cv::imread("./image/image_1.jpg");

	if (image.empty())
	{
		LOG("load image error!");

		cv::destroyAllWindows();
		return -1;
	}

	cv::Mat image_gray;
	cv::cvtColor(image, image_gray, cv::COLOR_BGR2GRAY);

	cv::Mat image_thresh;
	cv::threshold(image_gray, image_thresh, 150, 255, cv::THRESH_BINARY);

	cv::imshow("thresh binary", image_thresh);

	// CHAIN_APPROX_NONE
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::findContours(image_thresh, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	// Draw contours
	cv::Mat origin_image_copy = image.clone();
	cv::drawContours(origin_image_copy, contours, -1, cv::Scalar(0, 255, 0), 2);
	cv::imshow("image contours", origin_image_copy);

	cv::waitKey(0);
	cv::destroyAllWindows();

	/*cv::Mat simple_image = image.clone();

	for (int i = 0; i < contours.size(); i++)
		for (int j = 0; j < contours[i].size(); j++)
			cv::circle(simple_image, (contours[i], contours[i][j]), 2, cv::Scalar(0, 255, 0), 2);

	cv::imshow("simple image", simple_image);

	cv::waitKey();*/

	cv::destroyAllWindows();
	return 0;
}