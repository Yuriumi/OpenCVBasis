# 读取与写入视频

视频与图像的操作十分类似;视频只不过是一系列图像(帧)的集合,因此我们要做的就是循环遍历所有的帧,然后对每一帧进行处理.

使用的[视频](video/Cars.mp4)

## C++代码

``` cpp {.line-numbers}
#include <iostream>

#include <opencv2/opencv.hpp>

#define LOG(x) std::cout<< x << '\n'

int main()
{
    cv::VideoCapture video_capture("./video/Cars.mp4");

    int time_lag;

    if (!video_capture.isOpened())
        LOG("Video read failed!");
    else
    {
        int fps = video_capture.get(cv::CAP_PROP_FPS);
        LOG("Fps: " << fps);

        int frame_count = video_capture.get(cv::CAP_PROP_FRAME_COUNT);
        LOG("Frame count: " << frame_count);

        // 计算帧的时间间隔
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

    cv::destroyAllWindows();
    return 0;
}
```

## 视频读取

`cv::VideoCapture`是OpenCV中的用于存储视频文件,摄像头或者其他视频源中捕获的图像帧.

`cv::VideoCapture::isOpened`用于确认视频文件是否打开.

`cv::VideoCapture::get`
    `double cv::VideoCapture::get(int propId) const`
    用于获取视频的各种属性值;常见的参数有

- `cv::CAP_PROP_POS_MSEC`: 当前位置的视频时间戳
- `cv::CAP_PROP_FRAME_WIDTH`: 帧宽度
- `cv::CAP_PROP_FRAME_HEIGHT`: 帧高度
- `cv::CAP_PROP_FPS`: 帧率
- `cv::CAP_PROP_FRAME_COUNT`: 视频总帧数

`cv::VideoCapture::read`
    `bool cv::VideoCapture::read(cv::OutputArray image)`用于读取视频中的一帧图像

`cv::VideoCapture::release`释放视频资源.

## 从摄像头读取视频

``` cpp {.line-numbers}
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

    // 释放资源
    output.release();
    video_capture.release();
}
```

从摄像头读取视频很简单,我们只需要将视频路径改为0即可.

`cv::VideoCapture video_capture(0);`

`cv::VideoWriter output(filename, fourcc, fps, frame_size);`

- `filename` 文件存放路径
- `fourcc` 编码解码器;下为常见的编码解码器
  - `'M', 'J', 'P', 'G'` : Motion-JPEG
  - `'A', 'V', 'C', '1'` : H.264
- `fps` 帧率
- `frame_size` 分辨率

## 视频读取错误

!!!warning
    OpenCV默认读取的视频格式为.AVI,如果想读取.MP4格式的文件我们需要将`opencv\build\bin`中的`opencv_videoio_ffmpeg470_64.dll`文件放入项目中即可.
