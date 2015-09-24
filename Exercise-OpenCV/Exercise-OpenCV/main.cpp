#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int getImage() {
	Mat image;
		image = imread("papir.jpg", 1); //FLAG = 1 = CV_LOAD_IMAGE_COLOR

	return 0;
}

Mat PictureThresholds(Mat src, int r_thres1, int r_thres2, int g_thres1, int g_thres2, int b_thres1, int b_thres2) {
	if (src.data && !src.empty())
	{
		for (size_t y = 0; y < src.rows; ++y)
		{
			for (size_t x = 0; x < src.cols; ++x)
			{
				if (src.at<Vec3b>(x, y)[0] < b_thres1 || src.at<Vec3b>(x, y)[0] > b_thres2)
					src.at<Vec3b>(x, y)[0] = 0;
				else
					src.at<Vec3b>(x, y)[0] = 255;

				if (src.at<Vec3b>(x, y)[1] < g_thres1 || src.at<Vec3b>(x, y)[1] > g_thres2)
					src.at<Vec3b>(x, y) = 0;
				else
					src.at<Vec3b>(x, y)[1] = 255;

				if (src.at<Vec3b>(x, y)[2] < r_thres1 || src.at<Vec3b>(x, y)[2] > r_thres2)
					src.at<Vec3b>(x, y)[2] = 0;
				else
					src.at<Vec3b>(x, y)[2] = 255;
			}
		}
	}

	return src;
}
int ChangeBrightness(Mat image) {
	double alpha;
	int beta;
	Mat new_image = Mat::zeros(image.size(), image.type());
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; y < image.cols; x++) {
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(y, x)[c] = //it takes each pixel from the the image rows and columns 
					saturate_cast<uchar>(alpha*(image.at<Vec3b>(y, x)[c]) + beta); //saturate_cast make sure that the pixel is a valid pixel.
				//To make it faster you could use "image.convertTo(new_image, -1, alpha, beta);" insted of the 2 lines above.
			}
		}
	}
}


int main()
{
	getImage();

	return 0;
}