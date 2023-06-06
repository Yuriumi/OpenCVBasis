#include <iostream>

#include <opencv2/opencv.hpp>

#define LOG(x) std::cout<< x << '\n'

int main()
{
	cv::Mat image = cv::imread("./image/test.jpg");

	if (image.empty())
	{
		LOG("Load image error!");

		return -1;
	}

	LOG("Image width: " << image.size().width);
	LOG("Image height: " << image.size().height);
	LOG("Image Channels: " << image.channels());

	cv::Mat img = image(cv::Range(80, 280), cv::Range(150, 330));

	cv::imwrite("./save/crop_img.jpg", img);

	cv::imshow("Origin image", image);
	cv::imshow("Cropped image", img);

	cv::waitKey();

	cv::destroyAllWindows();
	return 0;
}