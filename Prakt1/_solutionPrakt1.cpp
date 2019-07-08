
// OpenCV_Helloworld 
/*
Bilddaten einlesen, durch Pixel durchiterieren
Pixelwerte erhöhen (Helligkeit) (Bildfehler entstehen durch Pixelwerte über 255
Bilder anzeigen
*/
#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	int brightness = 2;
	cv::Mat image, new_image;
	image = cv::imread("../Daten/OpenCV-01/Img01a.jpg");
	new_image = cv::Mat::zeros(image.size(), image.type());

	if (!image.data) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}
	/* Farbkanäle tauschen */
	for (int x = 0; x < image.rows; x++)
	{
		for (int y = 0; y < image.cols; y++)
		{
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(x, y)[c] = image.at<Vec3b>(x, y)[c];
			}
		}
	}

	for (int x = 0; x < 300; x++)
	{
		for (int y = 0; y < 200; y++)
		{
			for (int c = 0; c < 3; c++) {
				new_image.at<Vec3b>(x, y)[c] = image.at<Vec3b>(x, y)[c] + 50;
			}
		}
	}
	cv::Mat greyImage;
	/* Grauwerte */
	cvtColor(image, greyImage, COLOR_RGB2GRAY);

	/* Zerlegung in Kanäle */
	Mat bgr[3];   //destination array
	split(image, bgr); //split source  
	imwrite("blue.png", bgr[0]); //blau
	imwrite("green.png", bgr[1]); //grün
	imwrite("red.png", bgr[2]); //rot






	cv::namedWindow("Image:");
	cv::namedWindow("New Image:");

	cv::imshow("Image:", image);
	cv::imshow("New Image:", new_image);

	cv::waitKey(0);
	cv::destroyWindow("Image:");
	return 0;
}
