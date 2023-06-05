# 使用OpenCV读取,显示和写入图像

读取图像是所有操作(裁剪,缩放,旋转)的基础,因此这个基本操作很重要;我们将使用以下函数来完成这些操作.

1. `cv::imread()` 读取图像
2. `cv::imshow()` 窗口中显示图像
3. `cv::imwrite()` 将图像写入硬盘

下面是将会使用的[测试图像](image/test.jpg)

![test_image](image/test.jpg)

## C++代码

``` cpp {.line-numbers}
#include <iostream>

#include <opencv2/opencv.hpp>

// 方便打印提示信息
#define LOG(x) std::cout<< x << '\n'

int main()
{
    cv::Mat image = cv::imread("./image/test.jpg");

    // 检测图像是否写入成功
    if (image.empty())
    {
        LOG("Failed to load image");

        return -1;
    }

    cv::imshow("window", image);

    cv::waitKey(0);

    // 销毁所有显示的窗口
    cv::destroyAllWindows();
    return 0;
}
```

## 读取图像

`cv::Mat` 是opencv重要的数据结构之一,它的本质是一个多维数组,用于创建,访问和操作图像和矩阵数据;需要注意的是`cv::Mat`对象是按照**行优先存储的**

`cv::imread`

`cv::imread(const String& filename, int flags = IMREAD_COLOR)`

- `filename` 图像文件的**路径**
- 可选标志,用于指定如何表示图像
  - `IMREAD_COLOR` 三通道彩色图像BGR
  - `IMREAD_GRAYSCALE` 单通道灰度图
  - `IMREAD_UNCHANGED` 与输入格式相同

## 显示图像

`cv::imshow`

`cv::imshow(const String& winname,inputArray mat)`

- `winname` 显示图像窗口的名称
- `mat` 想要显示的图像

## 写入图像

`cv::imwrite`

`bool cv::imwrite(const String& filename, InputArray img)`

- `filename` 图像写入路径,图像必须包含扩展名(.jpg .png等).
- `img` 我们要写入的图像对象.

`cv::waitKey`

`int cv::waitKey(int delay = 0)`

- `delay` 窗口等待时间,单位为ms;单值为**0**时,程序等待案件的输入,并返回输入的按键*ASCII码*,当值**大于0**时等待指定的时间后返回-1(**无按键输入**).

!!! warning
    需要注意的是,`cv::waitKey`在没有窗口显示的情况下是无效的,在使用前需要保证至少有一个显示了图像的窗口对象.
