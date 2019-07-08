#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int alpha_slider;
double alpha;
double beta;
int pos[2];

Mat image;
Mat new_image;
Mat dst;



void mouseCallback(int event, int x, int y, int flags, void* userdata) {
	char str[80];
	sprintf(str, "%d | %d | %d | %d\n", event, x, y, flags);
	if (event == EVENT_LBUTTONDOWN) {
		printf("pups");
	}
	cv::putText(new_image, str,
		Point(50, 50),
		FONT_HERSHEY_SIMPLEX,
		1,
		(255, 255, 255),
		2);
	cv::imshow("Image:", new_image);
}

void trackbarFunc(int slidervalue, void*) {
	alpha = (double)alpha_slider / 255;
	printf("%f\n", alpha);
	printf("%d\n", slidervalue);

	double min, max;
	int number, count;
	Scalar mean, stddev;

	for (int x = 0; x < image.rows; x++)
	{
		for (int y = 0; y < image.cols; y++)
		{
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(x, y)[c] = image.at<Vec3b>(x, y)[c] * alpha;
			}
		}
	}
	cv::minMaxLoc(new_image, &min, &max);
	cv::meanStdDev(new_image, mean, stddev);

	printf("Spalten: %d\nZeilen: %d\n", new_image.cols, new_image.rows);
	printf("Maximum: %f\nMinimum: %f\nMedian: %f\nStandardabweichung: %f\n", max, min, mean, stddev);

	cv::imshow("Image:", new_image);
}

int main() {

	image = cv::imread("../Daten/OpenCV-02/Img02.jpg");
	new_image = cv::Mat::zeros(image.size(), image.type());

	if (!image.data) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}




	cv::namedWindow("Image:");
	cv::imshow("Image:", image);
	//cv::namedWindow("Test");


	//cv::imshow("New Image:", new_image);

	alpha_slider = 255;
	setMouseCallback("Image:", mouseCallback, NULL);

	createTrackbar("Trackbar", "Image:", &alpha_slider, 255, trackbarFunc, 0);
	trackbarFunc(alpha_slider, 0);

	cv::waitKey(0);
	cv::destroyWindow("Image:");
	return 0;
}
