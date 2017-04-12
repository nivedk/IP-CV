#include "opencv2/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat img, templ, result;

int main(){
	img = imread("OscarSelfie.jpg");
	templ = imread("template2.png");
	matchTemplate(img, templ, result, CV_TM_SQDIFF);

	double minVal; double maxVal; Point minLoc; Point maxLoc;
	minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
	rectangle( img, minLoc, Point( minLoc.x + templ.cols , minLoc.y + templ.rows ), Scalar::all(0), 2, 8, 0 );

	CascadeClassifier eye;
	std::vector<Rect> rects;
	eye.load("/Users/nived/opencv/data/haarcascades/haarcascade_eye.xml");
	eye.detectMultiScale(img, rects, 1.01, 7, 0, Size(50,50), Size(70,70) );
	for(size_t i = 0; i<rects.size(); i++){
		if(minLoc.x < rects[i].x &&rects[i].x < minLoc.x + templ.cols && minLoc.y < rects[i].y && rects[i].y < minLoc.y + templ.cols){
			rectangle(img, Point(rects[i].x, rects[i].y), Point(rects[i].x + rects[i].width, rects[i].y + rects[i].height), Scalar(0, 0, 0), 2, 8, 0);

			cout<<"Red:  "<<(int)img.at<Vec3b>(rects[i].x + rects[i].width/2, rects[i].y + rects[i].height/2)[2]<<"  Green:  "<<(int)img.at<Vec3b>(rects[i].x + rects[i].width/2, rects[i].y + rects[i].height/2)[1]<<"  Blue:  "<<(int)img.at<Vec3b>(rects[i].x + rects[i].width/2, rects[i].y + rects[i].height/2)[0]<<endl;
		}
	}

	imshow("Image", img);
	waitKey(0);
	destroyAllWindows();
}