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

int PictureThresholds() {
	return 0;
}

int main(int, char)
{
	getImage();

	return 0;
}