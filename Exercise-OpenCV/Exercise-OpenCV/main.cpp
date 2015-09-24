#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int getImage() {
	for (int i = 0; i <= 5; i++)
	{
		//comment
		cout << i;
	}
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



int main(int, char)
{
	return 0;
}