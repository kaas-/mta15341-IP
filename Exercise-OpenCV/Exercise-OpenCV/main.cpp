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

int ChangeBrightness() {
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


int main(int, char)
{
	getImage();

	return 0;
}