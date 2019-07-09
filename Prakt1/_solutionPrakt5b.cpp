#include <opencv2/opencv.hpp>
using namespace cv;
#include <stdio.h>
using namespace std;

#include <math.h>
#include <stdlib.h>

int main() {
	cv::Mat src, gray, dftOutput, dst, equalized;
	src = cv::imread("../Daten/OpenCV-05/Img05a.jpg");
	if (!src.data) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}
	// convert to grayscale
	gray = cv::Mat::zeros(src.size(), src.type());
	cvtColor(src, gray, COLOR_BGR2GRAY);

	// floating point matrix is needed 
	Mat planes[] = { Mat_<float>(gray), Mat::zeros(gray.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

	dft(complexI, complexI); // real und imaginaer anteil
	split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = betrag  
	Mat magI = planes[0];

	//Switch to a logarithmic scale. 
	magI += Scalar::all(1);                    // switch to logarithmic scale
	log(magI, magI);

	//Crop and rearrange.
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

	// Transform the matrix with float values into a viewable image form
	//(float between values 0 and 1).
	normalize(magI, magI, 0, 1, NORM_MINMAX); 
	imshow("original", gray);
	imshow("dft", magI);
	
	// zum beispiel nun maske anwenden, welche hoehen wegschneidet --> unschaerfe --> noise reduction
	Mat inverseTransform, invDFTcvt;
	idft(complexI, inverseTransform, DFT_SCALE | DFT_REAL_OUTPUT);
	//or do: 
	//normalize(inverseTransform, inverseTransform, 0, 1, NORM_MINMAX);
	inverseTransform.convertTo(invDFTcvt, CV_8U);
	imshow("idft", invDFTcvt);

	waitKey(0);
	destroyAllWindows;
	return 0;
}