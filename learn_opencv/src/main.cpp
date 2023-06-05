#include <iostream>

#include <opencv2/opencv.hpp>

#define LOG(x) std::cout<< x << '\n'

void video_capture()
{
	cv::VideoCapture video_capture("./video/Cars.mp4");

	int time_lag{ 0 };

	if (!video_capture.isOpened())
		LOG("Video read failed!");
	else
	{
		int fps = video_capture.get(cv::CAP_PROP_FPS);
		LOG("Fps: " << fps);

		int frame_count = video_capture.get(cv::CAP_PROP_FRAME_COUNT);
		LOG("Frame count: " << frame_count);

		time_lag = ((int)(1000 * (1 / (float)fps)));
	}

	while (video_capture.isOpened())
	{
		cv::Mat frame;

		bool isSuccess = video_capture.read(frame);

		if (isSuccess)
			cv::imshow("Video_Frame", frame);

		if (isSuccess == false)
		{
			LOG("Frame read failed or video camera is disconnected!");
			break;
		}

		int key = cv::waitKey(time_lag);
		if (key == 'q')
		{
			LOG("Stopping the video");
			break;
		}
	}

	video_capture.release();
}

void camera_capture()
{
	cv::VideoCapture video_capture(0);

	int frame_width = static_cast<int>(video_capture.get(cv::CAP_PROP_FRAME_WIDTH));
	int frame_height = static_cast<int>(video_capture.get(cv::CAP_PROP_FRAME_HEIGHT));

	cv::Size frame_size(frame_width, frame_height);

	int fps = 30;

	cv::VideoWriter output("./save/output_video.mp4", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, frame_size);

	while (video_capture.isOpened())
	{
		cv::Mat frame;

		bool isSuccess = video_capture.read(frame);

		if (isSuccess)
		{
			output.write(frame);
			cv::imshow("Video_Frame", frame);
		}

		if (isSuccess == false)
		{
			LOG("Frame read failed or video camera is disconnected!");
			break;
		}

		int key = cv::waitKey(30);
		if (key == 'q')
		{
			LOG("Stopping the video");
			break;
		}
	}

	output.release();
	video_capture.release();
}

int main()
{
	camera_capture();

	cv::destroyAllWindows();
	return 0;
}