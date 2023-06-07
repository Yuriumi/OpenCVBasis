#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#define CVUI_IMPLEMENTATION
#include "../ref/cvui.h"

#define LOG(x) std::cout<< x << '\n'

int main()
{
	cv::Mat image = cv::imread("./image/sample.jpg");

	if (image.empty())
	{
		LOG("load image error!");

		return -1;
	}

	cv::imshow("Origin image", image);

	cv::Mat draw_annotation_img;
	
	// line
	cv::Point start_point(200, 80);
	cv::Point end_point(450, 80);
	// circle
	cv::Point circle_center(415, 190);
	int circle_radius = 100;
	// ellipse
	cv::Point axis1(100, 50);
	cv::Point axis2(125, 50);
	// rectangle
	cv::Point rect_start_point(300, 115);
	cv::Point rect_end_point(475, 225);
	// text
	cv::Point text_position(50, 350);

	cv::namedWindow("draw Window");
	cvui::init("draw Window");

	bool draw_line{ false };
	bool draw_circle{ false };
	bool draw_ellipse{ false };
	bool draw_rectangle{ false };
	bool draw_text{ false };

	while (cv::waitKey(30) != 'q')
	{
		draw_annotation_img = image.clone();

		cvui::window(draw_annotation_img, 15, 15, 200, 150, "Setting");
		cvui::checkbox(draw_annotation_img, 35, 45, "Draw line", &draw_line);
		cvui::checkbox(draw_annotation_img, 35, 65, "Draw circle", &draw_circle);
		cvui::checkbox(draw_annotation_img, 35, 85, "Draw ellipse", &draw_ellipse);
		cvui::checkbox(draw_annotation_img, 35, 105, "Draw rectangle", &draw_rectangle);
		cvui::checkbox(draw_annotation_img, 35, 125, "Draw text", &draw_text);

		if (draw_line)
			cv::line(draw_annotation_img, start_point, end_point, cv::Scalar(0, 255, 0), 2, cv::LINE_8);
		if (draw_circle)
			cv::circle(draw_annotation_img, circle_center, circle_radius, cv::Scalar(255, 0, 0), 2);
		if (draw_ellipse)
		{
			cv::ellipse(draw_annotation_img, circle_center, axis1, 0, 0, 360, cv::Scalar(0, 0, 255), 3);
			cv::ellipse(draw_annotation_img, circle_center, axis2, 90, 0, 360, cv::Scalar(255, 0, 0), 3);
		}
		if (draw_rectangle)
			cv::rectangle(draw_annotation_img, rect_start_point, rect_end_point, cv::Scalar(0, 0, 255), 2);
		if (draw_text)
			cv::putText(draw_annotation_img, "I am a Happy dog!", text_position, cv::FONT_HERSHEY_COMPLEX, 1.5, cv::Scalar(250, 225, 100),2);

		cv::imshow("draw Window", draw_annotation_img);

		cvui::update();
	}

	cv::destroyAllWindows();
	return 0;
}