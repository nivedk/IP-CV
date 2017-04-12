#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat img; Mat gray;
int main( int argc, char** argv ){
	// Load source image and convert it to gray
	img = imread("jellyfish.jpg");

	// Convert image to gray and blur it
	cvtColor( img, gray, CV_BGR2GRAY );
	blur( gray, gray, Size(3,3) );


	Mat threshold_output;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	// Detect edges using Threshold
	threshold( gray, threshold_output, 95, 120, THRESH_BINARY );
	// Find contours
	findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	vector<vector<Point> > contours_poly( contours.size() );
	//vector<Rect> boundRect( contours.size() );
	vector<Point2f>center( contours.size() );
	vector<float>radius( contours.size() );

	for( int i = 0; i < contours.size(); i++ ){
		approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
	}
	
	for( int i = 0; i< contours.size() ; i++ ){
		if((int)radius[i]>5){
			circle( img, center[i], (int)radius[i], Scalar(255, 255, 255), 1, 8, 0 );
			line(img, Point(center[i].x -5, center[i].y -5), Point(center[i].x +5, center[i].y +5), Scalar(0, 0, 255), 2, 8, 0 );
			line(img, Point(center[i].x +5, center[i].y -5), Point(center[i].x -5, center[i].y +5), Scalar(0, 0, 255), 2, 8, 0 );
		}
	}

	cout<<"sdfgsdjgchsd";
	//namedWindow( "jellyfish", CV_WINDOW_AUTOSIZE );
	imshow( "jellyfish", img );

	waitKey(0);
	return(0);
}