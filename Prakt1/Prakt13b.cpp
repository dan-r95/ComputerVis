#include <cmath>
#include <math.h>
#include <stdlib.h>  
#include <opencv2/opencv.hpp>
using namespace cv; // um nicht cv::function schreiben zu m�ssen
using namespace ml; // um nicht cv::function schreiben zu müssen

//https://docs.opencv.org/2.4/doc/tutorials/imgproc/histograms/template_matching/template_matching.html



float imgresp0, imgrespl;
Mat image, templ;
int x, y;
Ptr<ANN_MLP> mlp = ANN_MLP::create();
int layer_sz[] = { 2, 5, 2 };
Mat layer_sizes = Mat(1, 3, CV_32S, layer_sz);
Mat train_data = Mat(3, 2, CV_32F);
Mat train_resp = Mat(3, 2, CV_32F);


void main() {
	mlp->setLayerSizes(layer_sizes); image = imread("ImageOl.jpg");

	for (int i = 0; i < 3; i++) {
		// select region of interest to train features 
		x = ...; y = ...;
		// ...
		// selectROI
		// 4 eingang 4 ausgang´--> 4 klassen 
		//, hidden?
		templ = getTempl(image, x, y);
		train_data.at<float>(i, 0) = templ.at<Vec3b>(2, 4)[0];
		train_data.at<float>(i, 1) = templ.at<Vec3b>(10, 5)[1];
		train_resp.at<float>(i, 0) = imgresp0;
		train_resp.at<float>(i, 1) = imgrespl;
	}
	mlp->setTermCriteria
	(TermCriteria(TermCriteria::COUNT + TermCriteria::EPS, 300, 0.01));
	mlp->setTrainMethod(ANN_MLP::BACKPROP);
	mlp->setActivationFunction(ANN_MLP::SIGMOID_SYM);
	mlp->setBackpropMomentumScale(0.1);
	mlp->setBackpropWeightScale(0.1);
	Ptr<TrainData> traindata = TrainData::create(train_data, ROW_SAMPLE, train_resp);
	mlp->train(traindata);
	for (int i = 1; i < 10; i++) {
		x = ...; y = ...;
		templ = getTempl(image, x, y);
		train_data.at<float>(0, 0) = templ.at<Vec3b>(2, 4)[0];
		train_data.at<float>(0, 1) = templ.at<Vec3b>(10, 5)[1];
		mlp->predict(train_data, train_resp);
		imgresp0 = train_resp.at<float>(0, 0);
		imgrespl = train_resp.at<float>(0, 1);
	}
}
