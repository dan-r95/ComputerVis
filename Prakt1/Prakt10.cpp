
//#include <opencv.hpp>
#include <cmath>
#include <math.h>
#include <stdlib.h>  
#include <opencv2/opencv.hpp>
using namespace cv; // um nicht cv::function schreiben zu müssen



int main() {

	Mat img09a, img1, img2;

	img09a = imread("Daten/Img09a.jpg");
	if (!img09a.data) {
		printf("Error: Couldn't open the img09a file.\n");
		return 1;
	}
	img1 = img09a(Rect(0, 0, img09a.cols / 2, img09a.rows));
	img2 = img09a(Rect(img09a.cols / 2, 0, img09a.cols / 2, img09a.rows));

	//Create a window
	namedWindow("img1", 1);
	namedWindow("img2", 1);


	//show the image
	imshow("img1", img1);
	imshow("img2", img2);

	waitKey(0);

	// Closes all the windows
	destroyAllWindows();
}