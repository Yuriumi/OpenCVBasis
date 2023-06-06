# 图像的缩放

如果我们想更改图像的大小, 我们可以使用比例因子或者设置我们想要的高度和宽度(沿轴进行缩放)

* 如果想维持与原图相同的宽高比, 我们需要存储图像原始的宽高比.
* 缩小图像需要对像素进行重新采样
* 放大图像需要重绘图像, 意味着要插入新的像素

## C++ 代码

``` cpp {.line-numbers}
int main()
{
 cv:: Mat image = cv::imread("./image/car_image.jpg"); 
 cv::imshow("Origin Image", image); 

 int down_width = 300; 
 int down_height = 200; 
 cv:: Mat resized_down_image; 

 cv::resize(image, resized_down_image, cv:: Size(down_width, down_height), cv:: INTER_LINEAR); 

 int up_width = 600; 
 int up_height = 400; 
 cv:: Mat resized_up_image; 

 cv::resize(image, resized_up_image, cv:: Size(up_width, up_height), cv:: INTER_LINEAR); 

 cv::imshow("resize down image", resized_down_image); 
 cv::imshow("resize up image", resized_up_image); 

 cv::waitKey(); 

 cv::destroyAllWindows(); 
 return 0; 
}
```

## 图像基本属性获取

* `image.rows` 图像高度
* `image.cols` 图像宽度

使用`size`也可以获取

* `image.size().width` 图像宽度
* `image.size().height` 图像高度

## 图像的缩放

`cv::resize`

`void cv::resize(InputArray src, OutputArray dst, Size dsize,int interpolation = cv::INTER_LINEAR)`

* `src` 输入图像
* `dst` 输出图像
* `dsize` 目标图像的缩放大小
* `interpolation` 插值方法

!!!warning
    我们通过定义新的高度和宽度参数的显式值来调整图像的大小可能会导致图像的失真.

## 使用比例因子调整大小

使用比例因子进行调整不会引入严重的失真,相比于显式指定宽高,使用比例因子可以保证图像的长宽比,并更好的保证图像的视觉内容.

``` cpp {.line-numbers}
double scale_up_x = 1.2;
double scale_up_y{ scale_up_x };

double scale_down = 0.6;

cv::Mat scaled_up_image, scaled_down_image;

cv::resize(image, scaled_up_image, cv::Size(), scale_up_x, scale_up_y, cv::INTER_LINEAR);
cv::resize(image, scaled_down_image, cv::Size(), scale_down, scale_down, cv::INTER_LINEAR);

cv::imshow("scale down image", scaled_down_image);
cv::imshow("scale up image", scaled_up_image);
```