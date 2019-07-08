#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main() {
	VideoCapture src("../Daten/OpenCV-11/Vid11d.avi");

	Mat flow, frame;
	UMat  flowUmat, prevgray;

	// write to AVI
	//int ex = static_cast<int>(cap.get(fourcc('P', 'I', 'M', '1')));
	Size S = Size((int)src.get(CAP_PROP_FRAME_WIDTH),    // Acquire input size
		(int)src.get(CAP_PROP_FRAME_HEIGHT));
	VideoWriter outputVideo;                                        // Open the output

	outputVideo.open("../Daten/OpenCV-11/video.avi", outputVideo.fourcc('M', 'J', 'P', 'G'), src.get(CAP_PROP_FPS), S, true);
	if (!outputVideo.isOpened())
	{
		//cout << "Could not open the output video for write: " << "video.mp4" << endl;
		return -1;
	}

	while (1) {

		Mat frame;
		src >> frame;

		if (frame.empty())
			break;

		cv::Mat img, original;
		src.retrieve(img, CAP_OPENNI_POINT_CLOUD_MAP);
		img.copyTo(original);
		cvtColor(img, img, COLOR_BGR2GRAY);

		if (prevgray.empty() == false) {
			calcOpticalFlowFarneback(prevgray, img, flowUmat, 0.4, 1, 12, 2, 8, 1.2, 0);
			flowUmat.copyTo(flow);

			for (int y = 0; y < original.rows; y += 5) {
				for (int x = 0; x < original.cols; x += 5)
				{
					const Point2f flowatxy = flow.at<Point2f>(y, x) * 10;
					arrowedLine(original, Point(x, y), Point(cvRound(x + flowatxy.x), cvRound(y + flowatxy.y)), Scalar(255, 0, 0));
					circle(original, Point(x, y), 1, Scalar(0, 0, 0), -1);
				}
			}
			namedWindow("prew", WINDOW_AUTOSIZE);
			imshow("prew", original);
			outputVideo << original;
			img.copyTo(prevgray);

		}
		else {
			img.copyTo(prevgray);
		}

		int key1 = waitKey(20);
		//VideoWriter
		if (waitKey(30) >= 0) break;
	}
}