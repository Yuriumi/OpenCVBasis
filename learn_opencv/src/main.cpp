#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#define CVUI_IMPLEMENTATION
#include "../ref/cvui.h"

#define LOG(x) std::cout<< x << '\n'

int main()
{
	cv::Mat image = cv::imread("./image/input-image-of-wood.jpg");

	if (image.empty())
	{
		LOG("Load image error!");

		return -1;
	}

	cv::imshow("origin image", image);

	// none
	cv::Mat kernel_none = (cv::Mat_<double>(3, 3) << 0, 0, 0, 0, 1, 0, 0, 0, 0);
	cv::Mat filter_image;
	bool none_filer{ true };
	// blur
	cv::Mat kernel_02 = cv::Mat::ones(5, 5, CV_64F);
	cv::Mat kernel_blur = kernel_02 / 25;
	bool blur_filter{ false };
	// gaussian
	bool gaussian_filter{ false };
	// median blur
	bool median_blur_filter{ false };
	// sharp
	cv::Mat kernel_sharp = (cv::Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	bool sharp_filter{ false };
	// bilateral
	bool bilateral_filter{ false };

	cv::namedWindow("Filter image");
	cvui::init("Filter image");

	while (cv::waitKey(15) != 'q')
	{
		filter_image = image.clone();

		if (none_filer)
			cv::filter2D(image, filter_image, -1, kernel_none, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
		else if (blur_filter)
			cv::filter2D(image, filter_image, -1, kernel_blur, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
		// cv::blur(filter_image, filter_image, cv::Size(5, 5));
		else if (gaussian_filter)
			cv::GaussianBlur(image, filter_image, cv::Size(5, 5), 0, 0);
		else if (median_blur_filter)
			cv::medianBlur(image, filter_image, (5, 5));
		else if (sharp_filter)
			cv::filter2D(image, filter_image, -1, kernel_sharp, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);
		else if (bilateral_filter)
			cv::bilateralFilter(image, filter_image, 9, 75, 75);

		cvui::window(filter_image, 10, 10, 185, 185, "filter setting");
		cvui::checkbox(filter_image, 25, 35, "none_filter", &none_filer);
		cvui::text(filter_image, 15, 55, "image_blur");
		cvui::checkbox(filter_image, 25, 75, "blur_filter", &blur_filter);
		cvui::checkbox(filter_image, 25, 95, "gaussian_filter", &gaussian_filter);
		cvui::checkbox(filter_image, 25, 115, "median_blur_filter", &median_blur_filter);
		cvui::text(filter_image, 15, 135, "image_sharp");
		cvui::checkbox(filter_image, 25, 155, "sharp_filter", &sharp_filter);
		cvui::checkbox(filter_image, 25, 175, "bilateral_filter", &bilateral_filter);

		cv::imshow("Filter image", filter_image);

		cvui::update();
	}

	cv::destroyAllWindows();
	return 0;
}