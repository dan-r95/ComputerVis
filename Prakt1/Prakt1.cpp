
// OpenCV_Helloworld

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
//#include <opencv.hpp>
#include <cmath>
#include <math.h>
#include <stdlib.h>  
using namespace cv; // um nicht cv::function schreiben zu m�ssen


int main() {
	Mat image;
	image = imread("../Daten/Img01a.jpg");
	if (!image.data) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}
	//image = image.at<Vec3b>(100, 100)[0];  // [kanal] 

	namedWindow("Image:");
	imshow("Image:", image);
	waitKey(0);

	//aufhellen --> multiplizieren, alle Kan�le!
	//for (int i = 0; i < 100; i++){
	//	for (int j = 0; j < 100; j++){
	//		//printf("%04x ", image.at<char>(i, j));
	//		image.at<Vec3b>(i, j) = image.at<Vec3b>(i, j) *1.5 ;                            //bgr   
	//	}
	//}
	

	////mittelwert zweier benachbarter pixel
	//for (int i = 200; i < 450; i++){
	//	for (int j = 200; j < 450; j++){
	//		if (j != 0){
	//			Vec3b mean = (image.at<Vec3b>(i, j - 1) + image.at<Vec3b>(i, j + 1)) / 2;
	//			image.at<Vec3b>(i, j) = mean;
	//		}
	//		                      
	//	}
	//}


	//TODO 
	//differenz zweier benachbarter pixel     x,y --> zeile, spalte
	for (int i = 900; i < 1200; i++){
		for (int j = 900; j < 1200; j++){
			if (i != 0){
				Vec3b diff = abs(1-0.5);
				image.at<Vec3b>(i - 1, j) - image.at<Vec3b>(i + 1, j);
				image.at<Vec3b>(i, j) = diff;
			}

		}
	}

	namedWindow("Image:");
	imshow("Image:", image); 
	waitKey(0);
	destroyWindow("Image:");
	return 0;
}
