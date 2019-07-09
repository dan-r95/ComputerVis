
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
Mat src, src_gray, cdstP, colorDst;
Mat dst, detected_edges;
int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";
static void CannyThreshold(int, void*)
{
	//Canny edge code
	//blur(src_gray, detected_edges, Size(3, 3));
	//Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
	//dst = Scalar::all(0);
	///src.copyTo(dst, detected_edges);
	//imshow(window_name, dst);
	// end canny edge

	 // Edge detection
	Canny(src, dst, lowThreshold, 200, 3);
	imshow(window_name, dst);
	 // Copy edges to the images that will display the results in BGR
	cvtColor(dst, colorDst, COLOR_GRAY2BGR);
	cdstP = colorDst.clone();

	// Standard Hough Line Transform
	std::vector<Vec2f> lines; // will hold the results of the detection
	HoughLines(dst, lines, 1, CV_PI / 180, 150, 0, 0); // runs the actual detection
	// Draw the lines
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(colorDst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
	}
	// Probabilistic Line Transform
	std::vector<Vec4i> linesP; // will hold the results of the detection
	HoughLinesP(dst, linesP, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection
	// Draw the lines
	for (size_t i = 0; i < linesP.size(); i++)
	{
		Vec4i l = linesP[i];
		line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}
	// Show results
	imshow("Source", src);
	imshow("Detected Lines (in red) - Standard Hough Line Transform", colorDst);
	imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);


}
int main(int argc, char** argv)
{
	src = imread("../Daten/OpenCV-12/Img12a.jpg", IMREAD_COLOR); //image
	if (src.empty()) 
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		return -1;
	}
	dst.create(src.size(), src.type());
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	namedWindow(window_name, WINDOW_AUTOSIZE);
	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);
	CannyThreshold(0, 0);
	waitKey(0);
	return 0;
}