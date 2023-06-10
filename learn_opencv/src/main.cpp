#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>
#include <pfd/portable-file-dialogs.h>

#define CVUI_IMPLEMENTATION
#include "../ref/cvui.h"

#define LOG(x) std::cout<< x << '\n'

int main()
{
	cv::Mat image = cv::imread("./image/input_image-1.jpg",0);

	if (image.empty())
	{
		LOG("load image error!");

		cv::destroyAllWindows();
		return -1;
	}

	cv::imshow("origin", image);

	cv::namedWindow("edge setting");
	cvui::init("edge setting");

	cv::Mat edge_image;
	cv::Mat ui_window(250,250,CV_8UC3);

	bool open_sobel{ false };
	bool open_x{ false };
	bool open_y{ false };
	bool open_xy{ false };
	bool open_canny{ false };

	while (cv::waitKey(15) != 'q')
	{
		edge_image = image.clone();
		ui_window = cv::Scalar(93, 62, 42);
		cv::Mat blur_image;

		cv::GaussianBlur(image, blur_image, cv::Size(3, 3), 0, 0);

		if (open_sobel)
		{
			if (open_x)
				cv::Sobel(blur_image, edge_image, CV_64F, 1, 0, 3);
			else if (open_y)
				cv::Sobel(blur_image, edge_image, CV_64F, 0, 1, 3);
			else if (open_xy)
				cv::Sobel(blur_image, edge_image, CV_64F, 1, 1, 3);
			else
				edge_image = blur_image.clone();
		}
		else if (open_canny)
		{
			cv::Canny(blur_image, edge_image, 100, 200, 3, false);
		}
		cv::imshow("edge detection", edge_image);

		cvui::window(ui_window, 10, 10, 200, 220, "edge setting");
		cvui::checkbox(ui_window, 15, 40, "open sobel decetion", &open_sobel);
		cvui::checkbox(ui_window, 25, 60, "open sobel x", &open_x);
		cvui::checkbox(ui_window, 25, 80, "open sobel y", &open_y);
		cvui::checkbox(ui_window, 25, 100, "open sobel xy", &open_xy);
		cvui::checkbox(ui_window, 15, 120, "open canny", &open_canny);
		cvui::update();

		cv::imshow("edge setting", ui_window);
	}

	cv::destroyAllWindows();
	return 0;
}