#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#define CVUI_IMPLEMENTATION
#include "../ref/cvui.h"

#define LOG(x) std::cout<< x << '\n'

int main()
{
	cv::Mat image = cv::imread("./image/image_rt.jpg");
	cv::imshow("image", image);

	cv::Point2f center((image.cols - 1) / 2.0, (image.rows - 1) / 2.0);

	cv::Mat rotate_image;

	double angular{ 45.4 };
	
	cv::namedWindow("rotated image");
	cvui::init("rotated image");
	while (cv::waitKey(7) != 27)
	{
		double angle = angular * CV_PI / 180.0;

		cv::Mat trans_origin_mat = (cv::Mat_<double>(2, 3) << 1, 0, -center.x,
			0, 1, -center.y);

		cv::Mat rorate_origin_mat = (cv::Mat_<double>(2, 3) << std::cos(angle), -std::sin(angle), 0,
			std::sin(angle), std::cos(angle), 0);

		cv::Mat trans_mat = (cv::Mat_<double>(2, 3) << 1, 0, center.x,
			0, 1, center.y);

		cv::Mat rotation_matrix = cv::getRotationMatrix2D(center, angle, 1.0);

		cv::warpAffine(image, rotate_image, trans_origin_mat, image.size());
		// cv::warpAffine(rotate_image, rotate_image, rorate_origin_mat, image.size());
		// cv::warpAffine(rotate_image, rotate_image, trans_mat, image.size());

		// cvui::window(rotate_image, 10, 10, 300, 90, "Basic Transform");
		// cvui::trackbar(rotate_image, 35, 35, 250, &angular, (double)-180.0, (double)180.0, 1.);

		cvui::update();
		cv::imshow("rotated image", rotate_image);
	}

	cv::destroyAllWindows();
	return 0;
}