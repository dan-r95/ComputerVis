
#include <cmath>
#include <math.h>
#include <stdlib.h>  
#include <opencv2/opencv.hpp>
using namespace cv; // um nicht cv::function schreiben zu m�ssen
//https://docs.opencv.org/2.4/doc/tutorials/imgproc/histograms/template_matching/template_matching.html


int main() {

	Mat img, templ, result;

	templ = imread("../Daten/OpenCV-13/Img13a00.jpg");
	if (!templ.data) {
		printf("Error: Couldn't open the Img13a00 file.\n");
		return 1;
	}
	
	img = imread("../Daten/OpenCV-13/Img13a01.jpg");
	if (!img.data) {
		printf("Error: Couldn't open the Img13a01 file.\n");
		return 1;
	}

	/// Do the Matching and Normalize
	//matchTemplate(img, templ, result, CV_TM_SQDIFF_NORMED);
	matchTemplate(img, templ, result, CV_TM_SQDIFF);
	//Create a window
	namedWindow("img1", 1);

	double min, max;
	Point pMin, pMax;
	Point matchLoc;
	/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
	minMaxLoc(result, &min, &max, &pMin, &pMax, Mat());

	matchLoc = pMin;
	//for all images ...
	// minmaxloc 
	//recttangle draw ´bounding box
	// 


	/// Show me what you got
	//rectangle(img_display, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);
	rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar::all(0), 2, 8, 0);

	namedWindow("Image:");
	imshow("Image:", result);

	//namedWindow("Result:");
	//imshow("")

	waitKey(0);
	// Closes all the windows
	destroyAllWindows();
}