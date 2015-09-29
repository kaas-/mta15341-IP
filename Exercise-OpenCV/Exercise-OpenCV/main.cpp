#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat getImage() {
	Mat image;
	image = imread("rgb.tif", 1); //FLAG = 1 = CV_LOAD_IMAGE_COLOR

	return image;
}

int histfunc(Mat src) {

	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	int histSize = 256;

	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true;

	Mat b_hist, g_hist, r_hist;
	//Mat hist;

	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	//calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	//normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
		//line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
		//	Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
		//	Scalar(125, 125, 125), 2, 8, 0);
	}
	namedWindow("histogram", CV_WINDOW_AUTOSIZE);
	imshow("histogram", histImage);
	return 0;
}

Mat PictureThresholds(Mat src, size_t r_thres1, size_t r_thres2, size_t g_thres1, size_t g_thres2, size_t b_thres1, size_t b_thres2) {
	if (src.data && !src.empty())
	{
		for (size_t y = 0; y < src.rows; ++y)
		{
			for (size_t x = 0; x < src.cols; ++x)
			{
				if (src.at<Vec3b>(y, x)[0] > b_thres1 && src.at<Vec3b>(y, x)[0] < b_thres2 && src.at<Vec3b>(y, x)[1] > g_thres1 && src.at<Vec3b>(y, x)[1] < g_thres2 && src.at<Vec3b>(y, x)[2] > r_thres1 && src.at<Vec3b>(y, x)[2] < r_thres2)
				{
					src.at<Vec3b>(y, x)[0] = 255;
					src.at<Vec3b>(y, x)[1] = 255;
					src.at<Vec3b>(y, x)[2] = 255;
				}
				else
				{
					src.at<Vec3b>(y, x)[0] = 0;
					src.at<Vec3b>(y, x)[1] = 0;
					src.at<Vec3b>(y, x)[2] = 0;
				}

				//cout << "R: " << src.at<Vec3b>(y, x)[2] << " G: " << src.at<Vec3b>(y, x)[1] << " B: " << src.at<Vec3b>(y, x)[2] << endl;
			}
		}
	}

	return src;
}
Mat ChangeBrightness(Mat image) {
	double alpha = -1.5;
	int beta = 2;
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
		//cvtColor(image, rgb_image, COLOR_YCrCb2BGR);
		imshow("Original", image);
		//imshow("RGB", rgb_image);
		
		//image = ChangeBrightness(image);
		histfunc(image);
		image = PictureThresholds(image, 30, 255, 30, 255, 30, 255);
		histfunc(image);
		imshow("Hello World!", image);
		waitKey(0);
	}
	catch (Exception e) {
		cout << "Error: " << e.msg << endl;
		return 1;
	}
	return 0;
}