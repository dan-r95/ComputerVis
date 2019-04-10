
// OpenCV_Helloworld

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
//#include <opencv.hpp>
#include <cmath>
#include <math.h>
#include <stdlib.h> 
#include <stdio.h>
//#include <iostream.h>
using namespace cv; // um nicht cv::function schreiben zu m�ssen
using namespace std;


int main() {
	Mat image;
	Mat splitImage[3];
	image = imread("../../Daten/OpenCV-03/Img03a.jpg");
	if (!image.data) {
		printf("Error: Couldn't open the image file.\n");
		return 1;
	}
	printf("%d", image.rows);
	printf("%d", image.cols);
	//image = image.at<Vec3b>(image.rows, image.cols);

	//anderer kanal
	//cvtColor(image, image, COLOR_BGR2RGBA);

	// zu grauwertbild einkan�lig

	//cvtColor(image, image, COLOR_BGR2GRAY);

	// drei einkan�lige
	split(image, splitImage);
	
	namedWindow("Image:");
	namedWindow("Image1:");
		namedWindow("Image2:");
		
	imshow("Image:", splitImage[0]);
	imshow("Image1:", splitImage[1]);
	imshow("Image2:", splitImage[2]);
		/*
	*/

		// write to different formats
		imwrite("../../Daten/OpenCV-03/Img03a_grey0.jpg", splitImage[0]);
	imwrite("../../Daten/OpenCV-03/Img03a_grey1.tiff", splitImage[1]);
	imwrite("../../Daten/OpenCV-03/Img03a_grey2.png", splitImage[2]);

	// video show
	VideoCapture cap("../../Daten/Vid03a.mov"); // open the default camera
	double framecount = cap.get(CAP_PROP_FRAME_COUNT);
	if (!cap.isOpened())  // check if we succeeded
		return -1;
	Mat edges;
	namedWindow("edges", 1);

	// write to AVI
	//int ex = static_cast<int>(cap.get(fourcc('P', 'I', 'M', '1')));
	Size S = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),    // Acquire input size
		(int)cap.get(CAP_PROP_FRAME_HEIGHT));
	VideoWriter outputVideo;                                        // Open the output

	outputVideo.open("../Daten/OpenCV-03/video.avi", outputVideo.fourcc('M', 'J', 'P', 'G'), cap.get(CAP_PROP_FPS), S, true);
	if (!outputVideo.isOpened())
	{
		//cout << "Could not open the output video for write: " << "video.mp4" << endl;
		return -1;
	}
	Mat src, res;
	vector<Mat> spl;


	for (int i = 0; i < framecount;i++)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera

		// gray hat nur 1 kanal also merge ... oder so 
		cvtColor(frame, frame, COLOR_BGR2RGB);
		//cvtColor(frame, frame, COLOR_BGR2GRAY);
		//GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		//Canny(edges, edges, 0, 30, 3);
		imshow("edges", frame);

		// write
		//split(src, spl);
		//merge(spl, res);
		//outputVideo.write(res); //save or
		outputVideo << frame;


		//VideoWriter
		if (waitKey(30) >= 0) break;
	}

	waitKey(0);
	//destroyWindow("Image:");
	return 0;
}
