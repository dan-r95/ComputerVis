
// OpenCV_Helloworld

#include <opencv2/opencv.hpp>
//#include <opencv.hpp>
#include <cmath>
#include <math.h>
#include <stdlib.h>  
using namespace cv; // um nicht cv::function schreiben zu m�ssen


int main() {
	Mat image;
	image = imread("../Daten/OpenCV-01/Img01a.jpg");
	if (!image.data) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}
	//image = image.at<Vec3b>(100, 100)[0];  // [kanal] 
	//aufhellen --> multiplizieren, alle Kan�le!
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
		}
	}
	//opencv prakt 2 weiter machen --> statistiken ueber bild in zweitem fenster anzeigen lassen
	mean(image);
	Mat mean, stddev;
	meanStdDev(image, mean, stddev); //, Mat()
	Point p1, p2;
	double min, max;
	minMaxLoc(image, &min, &max, &p1, &p2);  //, Mat()

	namedWindow("Image:");
	imshow("Image:", image);
	waitKey(0);

	namedWindow("Stats:");
	imshow("Stats:", image);
	waitKey(0);
	destroyWindow("Image:");
	return 0;
}
