#include <iostream>

#include <opencv2/opencv.hpp>

#define LOG(x) std::cout<< x << '\n'

int main()
{
	cv::Mat image = cv::imread("./image/test.jpg");

	if (image.empty())
	{
		LOG("Failed to load image");

		return -1;
	}

	cv::imwrite("./save/test_save.jpg", image);

	cv::imshow("window", image);

	cv::waitKey(0);

	cv::destroyAllWindows();
	return 0;
}