#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <random>

//#include <pfd/portable-file-dialogs.h>
//
//#define CVUI_IMPLEMENTATION
//#include "../ref/cvui.h"

#define LOG(x) std::cout<< x << '\n'

int computeMedian(std::vector<int> elements)
{
	std::nth_element(elements.begin(), elements.begin() + elements.size() / 2, elements.end());

	// std::sort(elements.begin(),elements.end());
	return elements[elements.size() / 2];
}

cv::Mat compute_median(std::vector<cv::Mat> vec)
{
	cv::Mat medianImg(vec[0].rows, vec[0].cols, CV_8UC3, cv::Scalar(0, 0, 0));

	for (int row = 0; row < vec[0].rows; row++)
	{
		for (int col = 0; col < vec[0].cols; col++)
		{
			std::vector<int> elements_B;
			std::vector<int> elements_G;
			std::vector<int> elements_R;

			for (int imgNumber = 0; imgNumber < vec.size(); imgNumber++)
			{
				int B = vec[imgNumber].at<cv::Vec3b>(row, col)[0];
				int G = vec[imgNumber].at<cv::Vec3b>(row, col)[1];
				int R = vec[imgNumber].at<cv::Vec3b>(row, col)[2];

				elements_B.push_back(B);
				elements_G.push_back(G);
				elements_R.push_back(R);
			}

			medianImg.at<cv::Vec3b>(row, col)[0] = computeMedian(elements_B);
			medianImg.at<cv::Vec3b>(row, col)[1] = computeMedian(elements_G);
			medianImg.at<cv::Vec3b>(row, col)[2] = computeMedian(elements_R);
		}
	}
	return medianImg;
}

int main()
{
	cv::VideoCapture cap("./video/video.mp4");

	if (!cap.isOpened())
	{
		LOG("open video error!");

		return -1;
	}

	// 随机取25帧取中值.
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, cap.get(cv::CAP_PROP_FRAME_COUNT));

	std::vector<cv::Mat> frames;

	for (int i = 0; i < 25; i++)
	{
		int fid = distribution(generator);
		cap.set(cv::CAP_PROP_POS_FRAMES, fid);

		cv::Mat pre_frame;

		cap >> pre_frame;
		if (pre_frame.empty())
			continue;
		frames.push_back(pre_frame);
	}

	cv::Mat median_frame = compute_median(frames);

	cv::imshow("frame", median_frame);

	cap.set(cv::CAP_PROP_POS_FRAMES, 0);

	cv::Mat gray_median_frame;
	cv::cvtColor(median_frame, gray_median_frame, cv::COLOR_BGR2GRAY);

	cv::Mat frame;

	while (cv::waitKey(20) != 'q')
	{
		cap >> frame;

		if (frame.empty())
			break;

		cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);

		cv::Mat dframe;
		cv::absdiff(frame, gray_median_frame, dframe);

		cv::threshold(dframe, dframe, 30, 255, cv::THRESH_BINARY);

		cv::imshow("video", dframe);
	}

	cv::waitKey(0);

	return 0;
}