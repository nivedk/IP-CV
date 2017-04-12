#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(){
	//cout<< "hello";
	CascadeClassifier face;
	//CascadeClassifier eye;
	face.load("/Users/nived/opencv/data/haarcascades/haarcascade_frontalface_default.xml");
	//eye.load("/Users/nived/opencv/data/haarcascades/haarcascade_eye.xml");

	Mat img = imread("OscarSelfie.jpg");

	std::vector<Rect> rects;//each rectangle contains a detected object

	face.detectMultiScale(img, rects, 1.01, 7, 0, Size(80,80), Size(200,200) );
	for(size_t i = 0; i<rects.size(); i++){
		rectangle(img, Point(rects[i].x-20, rects[i].y-20), Point(rects[i].x + rects[i].width+20, rects[i].y + rects[i].height+20), Scalar(255, 0, 0), 2, 8, 0);
	}

	imshow("Image", img);
	waitKey(0);
	destroyAllWindows();

}