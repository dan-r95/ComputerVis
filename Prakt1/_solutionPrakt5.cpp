#include <opencv2/opencv.hpp>
using namespace cv;
#include <stdio.h>
using namespace std;

#include <math.h>
#include <stdlib.h>

int main() {
	cv::Mat src, gray, tmp, dst;
	src = cv::imread("../Daten/OpenCV-05/Img05a.jpg");
	if (!src.data) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}

	gray = cv::Mat::zeros(src.size(), src.type());
	cvtColor(src, gray, COLOR_BGR2GRAY);
	int histSize = 256;    // bin size
	float range[] = { 0, 255 };
	const float *ranges[] = { range };

	tmp = src;
	dst = tmp;

	// Calculate histogram
	MatND hist;
	calcHist(&gray, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);

	// Plot the histogram
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}

	// Gauß-Pyramide & Laplace Pyramid
	while (true)
	{
		int c;
		c = waitKey(10);

		if ((char)c == 27)
		{
			break;
		}
		if ((char)c == 'u')
		{
			//folgendes ist NICHT die Laplace-Pyramide!
			pyrUp(tmp, dst, Size(tmp.cols * 2, tmp.rows * 2));
			printf("** Zoom In: Image x 2 \n");
		}
		else if ((char)c == 'd')
			// gausssche pyramide
		{
			pyrDown(tmp, dst, Size(tmp.cols / 2, tmp.rows / 2));
			printf("** Zoom Out: Image / 2 \n");
		}

		imshow("Test", dst);
		tmp = dst;
	}

	imshow("Test", dst);
	imshow("Source", src);
	imshow("Gray", gray);
	imshow("Result", histImage);
	waitKey(0);
	destroyAllWindows;
	return 0;
}