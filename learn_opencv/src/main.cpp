#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#define CVUI_IMPLEMENTATION
#include "../ref/cvui.h"

#define LOG(x) std::cout<< x << '\n'

int main()
{
	cv::Mat image = cv::imread("./image/threshold.jpg");

	if (image.empty())
	{
		LOG("load image error!");

		return -1;
	}

	cv::imshow("src image", image);

	cv::namedWindow("image thresh");
	cvui::init("image thresh");

	cv::Mat thresh_image;

	double thresh_value{ 0 };
	double max_value{ 255 };

	bool open_inv{ false };
	bool open_truncation{ false };
	bool open_tozero{ false };
	bool open_tozero_inv{ false };

	while (cv::waitKey(30) != 'q')
	{
		thresh_image = image.clone();

		if (open_inv)
			cv::threshold(image, thresh_image, thresh_value, max_value, cv::THRESH_BINARY_INV);
		else
			if (open_truncation)
				cv::threshold(image, thresh_image, thresh_value, max_value, cv::THRESH_TRUNC);
			else if(open_tozero)
				cv::threshold(image, thresh_image, thresh_value, max_value, cv::THRESH_TOZERO);
			else if(open_tozero_inv)
				cv::threshold(image, thresh_image, thresh_value, max_value, cv::THRESH_TOZERO_INV);
			else
				cv::threshold(image, thresh_image, thresh_value, max_value, cv::THRESH_BINARY);

		cvui::window(thresh_image, 10, 10, 200, 245, "thresh setting");
		cvui::text(thresh_image, 15, 35, "thresh_value:");
		cvui::trackbar(thresh_image, 20, 50, 170, &thresh_value, (double)0.0, (double)255.0, 1, "%.0Lf");
		cvui::text(thresh_image, 15, 105, "max_value:");
		cvui::trackbar(thresh_image, 20, 120, 170, &max_value, (double)0.0, (double)255.0, 1, "%.0Lf");
		cvui::checkbox(thresh_image, 15, 165, "open_thresh_inv", &open_inv);
		cvui::checkbox(thresh_image, 15, 185, "open_truncation", &open_truncation);
		cvui::checkbox(thresh_image, 15, 205, "open_tozero", &open_tozero);
		cvui::checkbox(thresh_image, 15, 225, "open_tozero_inv", &open_tozero_inv);

		cv::imshow("image thresh", thresh_image);

		cvui::update();
	}

	cv::destroyAllWindows();
	return 0;
}