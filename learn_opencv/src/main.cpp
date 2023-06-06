#include <iostream>

#include <opencv2/opencv.hpp>

#define LOG(x) std::cout<< x << '\n'

int main()
{
	cv::Mat image = cv::imread("./image/car_image.jpg");
	cv::imshow("Origin Image", image);

	int down_width = 300;
	int down_height = 200;
	cv::Mat resized_down_image;

	cv::resize(image, resized_down_image, cv::Size(down_width, down_height), cv::INTER_LINEAR);

	int up_width = 600;
	int up_height = 400;
	cv::Mat resized_up_image;

	cv::resize(image, resized_up_image, cv::Size(up_width, up_height), cv::INTER_LINEAR);

	cv::imshow("resize down image", resized_down_image);
	cv::imshow("resize up image", resized_up_image);

	double scale_up_x = 1.2;
	double scale_up_y{ scale_up_x };

	double scale_down = 0.6;

	cv::Mat scaled_up_image, scaled_down_image;

	cv::resize(image, scaled_up_image, cv::Size(), scale_up_x, scale_up_y, cv::INTER_LINEAR);
	cv::resize(image, scaled_down_image, cv::Size(), scale_down, scale_down, cv::INTER_LINEAR);

	cv::imshow("scale down image", scaled_down_image);
	cv::imshow("scale up image", scaled_up_image);

	cv::waitKey();

	cv::destroyAllWindows();
	return 0;
}