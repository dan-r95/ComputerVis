#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/calib3d.hpp>
using namespace cv;

int main() {
	cv::Mat image1, image2, image3, image4, h1, h2, stereo, stereo8;
	image1 = cv::imread("../Daten/OpenCV-10/Img10a01.png");
	if (!image1.data) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}
	image2 = cv::imread("../Daten/OpenCV-10/Img10a02.png");
	if (!image2.data) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}

	cvtColor(image1, image1, COLOR_BGR2GRAY);
	cvtColor(image2, image2, COLOR_BGR2GRAY);

	cv::imshow("Image 1", image1);
	cv::imshow("Image 2", image2);


	Ptr<StereoBM> bm = StereoBM::create();
	bm->setPreFilterCap(31);
	bm->setBlockSize(31);
	bm->setMinDisparity(0);
	bm->setNumDisparities(16);
	bm->setTextureThreshold(10);
	bm->setUniquenessRatio(15);
	bm->setSpeckleWindowSize(100);
	bm->setSpeckleRange(32);
	bm->setDisp12MaxDiff(11);
	bm->compute(image1, image2, stereo);

	normalize(stereo, stereo, 0, 255, NORM_MINMAX);
	stereo.convertTo(stereo8, CV_8U);


	cv::imshow("Disp", stereo8);

	cv::waitKey(0);
	cv::destroyAllWindows;
	return 0;
}