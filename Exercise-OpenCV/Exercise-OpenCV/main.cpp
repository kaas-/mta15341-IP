#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat getImage() {
	Mat image;
	image = imread("rgb.jpg", 1); //FLAG = 1 = CV_LOAD_IMAGE_COLOR

	return image;
}

Mat PictureThresholds(Mat src, size_t r_thres1, size_t r_thres2, size_t g_thres1, size_t g_thres2, size_t b_thres1, size_t b_thres2) {
	if (src.data && !src.empty())
	{
		for (size_t y = 0; y < src.rows; ++y)
		{
			for (size_t x = 0; x < src.cols; ++x)
			{
				if (src.at<Vec3b>(y, x)[0] < b_thres1 || src.at<Vec3b>(y, x)[0] > b_thres2)
					src.at<Vec3b>(y, x)[0] = 0;
				else
					src.at<Vec3b>(y, x)[0] = 255;

				if (src.at<Vec3b>(y, x)[1] < g_thres1 || src.at<Vec3b>(y, x)[1] > g_thres2)
					src.at<Vec3b>(y, x) = 0;
				else
					src.at<Vec3b>(y, x)[1] = 255;

				if (src.at<Vec3b>(y, x)[2] < r_thres1 || src.at<Vec3b>(y, x)[2] > r_thres2)
					src.at<Vec3b>(y, x)[2] = 0;
				else
					src.at<Vec3b>(y, x)[2] = 255;
			}
		}
	}

	return src;
}
Mat ChangeBrightness(Mat image) {
	double alpha = 60;
	int beta = 20;
	for (int y = 0; y < 449; ++y) {
		//cout << y << " : " << image.rows << endl;
		for (int x = 0; x < 599; ++x) {
			for (int c = 0; c < 3; c++) {
				image.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta); //saturate_cast make sure that the pixel is a valid pixel.
				//To make it faster you could use "image.convertTo(new_image, -1, alpha, beta);" insted of the 2 lines above.
			}
			//cout << x << " : " << image.cols << endl;;
		}
	}
	return image;
}


int main()
{
	try {
		Mat rgb_image;
		Mat image = getImage();
		cvtColor(image, rgb_image, COLOR_YCrCb2BGR);
		imshow("Original", image);
		imshow("RGB", rgb_image);
		
		//image = ChangeBrightness(image);
		image = PictureThresholds(rgb_image, 50, 255, 200, 255, 200, 255);
		
		imshow("Hello World!", image);
		waitKey(0);
	}
	catch (Exception e) {
		cout << "Error: " << e.msg << endl;
		return 1;
	}
	return 0;
}