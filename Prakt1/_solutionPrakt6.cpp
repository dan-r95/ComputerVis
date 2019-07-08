using namespace std;
#include <opencv2/opencv.hpp>
using namespace cv;


void trackbarFunc(int slidervalue, void*) {

}

int main() {
	// video show
	VideoCapture cap("../Daten/OpenCV-06/Vid06a.avi"); // open the default camera
	double framecount = cap.get(CAP_PROP_FRAME_COUNT);
	if (!cap.isOpened()) {  // check if we succeeded
		cout << "Error opening video stream or file" << endl;
		return -1;
	}
	int slider = 0;
	namedWindow("Frame");
	namedWindow("Transform");
	createTrackbar("Trackbar", "Frame", &slider, 2, trackbarFunc, 0);
	trackbarFunc(slider, 0);

	Mat frame, dst;
	for (int i = 0; i < framecount; i++)
	{
		cap >> frame;

		if (frame.empty())
			break;
		int a = (slider % 3);
		switch (a) {
		case 0: // räumliche Glättung
			blur(frame, dst, Size(100, 1));
			break;
		case 1:// zeitliche Glättung
			medianBlur(frame, dst, 11);  break;
		case 2: // Histogrammangleichung
			cvtColor(frame, frame, COLOR_RGB2GRAY);
			equalizeHist(frame, dst); break;
		}





		imshow("Frame", frame);
		imshow("Transform", dst);

		char c = (char)waitKey(25);
		if (c == 27)
			break;
	}

	cap.release();
	destroyAllWindows();
}