#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void MatchingMethod(int, void*);

Mat img; Mat templates[9]; Mat result;
char* image_window = "Source Image";
char* result_window = "Result window";

int match_method;
int max_Trackbar = 5;

int main() {

	/// Load image and template
	img = imread("../Daten/OpenCV-13/Img13a00.jpg", 1); //image
	if (!img.data) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}

	for (int i = 1; i <= 9; i++) {
		String test = "../Daten/OpenCV-13/Img13a0";
		test += std::to_string(i);
		test += ".JPG";
		cout << test;
		//flag 1 means color
		Mat tmp;
		tmp = imread(test, 1); //template   
		if (!tmp.data) {
			printf("Error: Couldn't open the image file.\n");
			return 1;
		}
		templates[i - 1] = tmp;
	}

	/// Create windows
	namedWindow(image_window, WINDOW_AUTOSIZE);
	namedWindow(result_window, WINDOW_AUTOSIZE);

	/// Create Trackbar
	char* trackbar_label = "Method: \n 0: SQDIFF \ n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
	createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar, MatchingMethod);

	MatchingMethod(0, 0);
	waitKey();
}

void MatchingMethod(int, void*)
{
	/// Source image to display
	Mat img_display;
	img.copyTo(img_display);

	/// Create the result matrix
	int result_cols = img.cols - templates[0].cols + 1;
	int result_rows = img.rows - templates[0].rows + 1;

	result.create(result_rows, result_cols, CV_32FC1);

	/// Do the Matching and Normalize
	matchTemplate(img, templates[0], result, match_method); // 0 at beginning
	normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

	/// Localizing the best match with minMaxLoc
	double minVal; double maxVal; Point minLoc; Point maxLoc;
	Point matchLoc;

	minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

	/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
	if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
	{
		matchLoc = minLoc;
	}
	else
	{
		matchLoc = maxLoc;
	}

	/// Show me what you got
	rectangle(img_display, matchLoc, Point(matchLoc.x + templates[0].cols, matchLoc.y + templates[0].rows), Scalar::all(0), 2, 8, 0);
	rectangle(result, matchLoc, Point(matchLoc.x + templates[0].cols, matchLoc.y + templates[0].rows), Scalar::all(0), 2, 8, 0);

	imshow(image_window, img_display);
	imshow(result_window, result);

	return;
}
