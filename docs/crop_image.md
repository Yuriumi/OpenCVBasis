# 裁剪图像

## C++代码

``` cpp {.line-numbers}
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
```

`cv::Mat img = image(cv::Range(80, 280), cv::Range(150, 330));`

- 第一个参数是我们要裁剪的行的范围(高度)
- 第二个参数是我们要裁剪的列的范围(宽度)