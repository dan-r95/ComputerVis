// Kantendetektion

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
	cout << "The sample uses Sobel or Scharr OpenCV functions for edge detection\n\n";

	// First we declare the variables we are going to use
	Mat image, src, src_gray;
	Mat grad;
	const String window_name = "Sobel Demo - Simple Edge Detector";
	int ddepth = CV_16S;
	int ksize = 1, scale = 2, delta = 0;
	// As usual we load our source image (src)
	image = imread("../Daten/OpenCV-07/Img07a.jpg", IMREAD_COLOR); // Load an image
	// Check if image is loaded fine
	if (image.empty())
	{
		printf("Error opening image: %s\n", image);
		return 1;
	}
	for (;;)
	{
		// Remove noise by blurring with a Gaussian filter ( kernel size = 3 )
		GaussianBlur(image, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
		// Convert the image to grayscale
		cvtColor(src, src_gray, COLOR_BGR2GRAY);
		Mat grad_x, grad_y;
		Mat abs_grad_x, abs_grad_y;
		// ableitung der grauwertfunktion in x
		// ableitung der grauwertfunktion in y
		Sobel(src_gray, grad_x, ddepth, 2, 0, ksize, scale, delta, BORDER_DEFAULT);
		Sobel(src_gray, grad_y, ddepth, 0, 1, ksize, scale, delta, BORDER_DEFAULT);
		// converting back to CV_8U
		convertScaleAbs(grad_x, abs_grad_x);
		convertScaleAbs(grad_y, abs_grad_y);
		//dst = src1*alpha + src2*beta + gamma;
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

		// binary treshhold
		threshold(grad, grad, 0.9, 255, THRESH_TOZERO);
		imshow(window_name, grad);
		char key = (char)waitKey(0);
		
	}
	return 0;
}