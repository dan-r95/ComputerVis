#include <opencv2/opencv.hpp>
using namespace cv;
#include <stdio.h>
using namespace std;

int main() {

	Mat frame0;
	UMat frame1, frame2;
	CascadeClassifier face_cascade;
	CascadeClassifier eye_cascade;
	//face_cascade.load("U:/Dokumente/CVBV/CVBV/Daten/OpenCV-04/haarcascade_frontalface_alt.xml");
	eye_cascade.load("../Daten/OpenCV-04/haarcascade_eye.xml");
	if (eye_cascade.empty()) {
		cout << "cant load cascade";
		return 1;
	}

	face_cascade.load("../Daten/OpenCV-04/haarcascade_frontalface_alt.xml");
	if (face_cascade.empty()) {
		cout << "cant load cascade";
		return 1;
	}

	/*frame0 = imread("../Daten/OpenCV-04/Img04c.png");
	if (frame0.empty()) {
		cout << "cant load frame";
		return 1;
	}*/

	frame0 = imread("../Daten/OpenCV-04/Img04b.jpg");
	if (frame0.empty()) {
		cout << "cant load frame";
		return 1;
	}
	frame0.copyTo(frame1);
	cvtColor(frame1, frame2, COLOR_BGR2GRAY);
	std::vector<Rect> faces;
	face_cascade.detectMultiScale(frame2, faces,
		1.1, 2, 0, Size(30, 30));
	/*eye_cascade.detectMultiScale(frame2, faces,
		1.1, 2, 0, Size(30, 30));*/
	for (size_t i = 0; i < faces.size(); i++) {
		Point center(faces[i].x + faces[i].width*0.5,
			faces[i].y + faces[i].height*0.5);
		ellipse(frame1, center, Size(faces[i].width*0.5,
			faces[i].height*0.5), 0, 0, 360,
			Scalar(255, 0, 255), 4, 8, 0);
	}
	imshow("Detection", frame1);
	waitKey(0);
	return 0;
}