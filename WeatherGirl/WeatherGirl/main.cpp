#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat getImage(String name) {
	Mat image;
	image = imread(name, CV_LOAD_IMAGE_COLOR); //FLAG = 1 = CV_LOAD_IMAGE_COLOR

	return image;
}

Mat PictureThresholds(Mat src1, Mat src2, int b_thres1, int b_thres2) {
	Mat output(src1.size(), CV_8UC3);
	//imshow("1", src1);
	//imshow("2", src2);
	//imshow("BLANK", output);
	//waitKey(0);
	if (src1.data && !src1.empty())
	{
		for (size_t y = 0; y < src1.rows; ++y)
		{
			for (size_t x = 0; x < src1.cols; ++x)
			{
				if (src1.at<Vec4b>(y, x)[0] < b_thres1 && src1.at<Vec3b>(y, x)[0] > b_thres2)
				{
					output.at<Vec3b>(y, x) = src2.at<Vec3b>(y, x);
				}
				else
				{
					output.at<Vec3b>(y, x) = src1.at<Vec3b>(y, x);
				}
				imshow("OUTPUT", output);

				//cout << "R: " << src.at<Vec3b>(y, x)[2] << " G: " << src.at<Vec3b>(y, x)[1] << " B: " << src.at<Vec3b>(y, x)[2] << endl;
			}
		}
	}

	return output;
}

int main()
{
	Mat img1, img2, output;

	try 
	{
		img1 = getImage("1.png");
		img2 = getImage("2.png");
	}
	catch (Exception e)
	{
		return 1;
	}

	try 
	{
		Mat output = PictureThresholds(img1, img2, 50, 200);
	}
	catch (Exception e)
	{
		cout << e.msg;
		return 2;
	}


	try
	{
		imshow("1", img1);
		imshow("2", img2);
		//imshow("IMAGE", output);
		waitKey(0);
	}
	catch (Exception e)
	{
		return 3;
	}

	return 0;
}