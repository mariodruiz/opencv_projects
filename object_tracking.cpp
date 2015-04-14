/*
Author Mario Ruiz */

#include <iostream>
#include <stdlib.h>
#ifdef __arm__
	#include <raspicam/raspicam_cv.h>
	using namespace raspicam;
#endif
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

 
void help(){
	cout << "Is no flag define yellow is a default color for tracking" << endl;
	cout << "-o for tracking orange color ./object_tracking -o" << endl;
	cout << "-y for tracking yellow color ./object_tracking -y" << endl;
	cout << "-g for tracking green color ./object_tracking -g" << endl;
	cout << "-b for tracking blue color ./object_tracking -b" << endl;
	cout << "-v for tracking violet color ./object_tracking -v" << endl;
	cout << "-r for tracking red color ./object_tracking -r" << endl;
}


int main ( int argc,char **argv ) {

	int hue_low = 22; 
	int hue_high = 38; // for yellow color

	if (argc==2) {
		if (strcmp(argv[1], "-h")==0) {
			help();
			return 0;
		}
		else if (strcmp(argv[1], "-o")==0) {
			hue_low = 0; 
		        hue_high = 22; // for yellow color
		}
        else if (strcmp(argv[1], "-g")==0) {
                hue_low = 38; 
                hue_high = 75; // for yellow color
        }
        else if (strcmp(argv[1], "-b")==0) {
                hue_low = 75; 
                hue_high = 130; // for yellow color
        }
        else if (strcmp(argv[1], "-v")==0) {
                hue_low = 130; 
                hue_high = 160; // for yellow color
        }
        else if (strcmp(argv[1], "-r")==0) {
                hue_low = 160; 
                hue_high = 179; // for yellow color
        }
	}

	#ifdef __arm__
    	RaspiCam_Cv Camera; //Camera object 
		if (!Camera.open()){
			cerr << "Error opening camera" << endl;
			return -1;
		}	
		int heigth_crop=210;
	    Rect myArea(0,210,Camera.get(CV_CAP_PROP_FRAME_WIDTH),Camera.get(CV_CAP_PROP_FRAME_HEIGHT)-heigth_crop);
		Mat imgLines = Mat::zeros(Camera.get(CV_CAP_PROP_FRAME_HEIGHT)-heigth_crop,Camera.get(CV_CAP_PROP_FRAME_WIDTH), CV_8UC3 ); // define matrix of lines traking
		
	#else
		VideoCapture Camera(0); // Camera object	
		if (! Camera.isOpened()){
			cerr << "Error opening camera" << endl;
			return -1;
		}
	#endif
	cout << "Open Camera Correctly" << endl;
	Mat image_camera,croped_image;


	int iLastX = -1; 
 	int iLastY = -1;
	int posX,posY;

	Mat image_HSV;
	Mat image_Thresholded;

	while  (1){
	
		#ifdef __arm__
			Camera.grab(); 						// next frame from raspicam!
			Camera.retrieve(image_camera); 				// save frame in image_camera
			croped_image=image_camera(myArea);
			flip(croped_image,croped_image,0);			// rotate 180º image
		#else
			Camera >> croped_image;
		#endif

		cvtColor(croped_image, image_HSV, COLOR_BGR2HSV); 	//Convert the captured frame from BGR to HSV

		inRange(image_HSV, Scalar(hue_low,100,100), Scalar(hue_high,255, 255), image_Thresholded); 	//Threshold the image
		
		#ifndef __arm__
			//morphological opening (removes small objects from the foreground)
	  		erode(image_Thresholded, image_Thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
	  		dilate(image_Thresholded, image_Thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

			//morphological closing (removes small holes from the foreground)
	  		dilate( image_Thresholded, image_Thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
	  		erode(image_Thresholded, image_Thresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  		#endif

  		//Calculate the moments of the thresholded image
  		Moments oMoments = moments(image_Thresholded);

   		double dM01 = oMoments.m01;
  		double dM10 = oMoments.m10;
  		double dArea = oMoments.m00;

		if (dArea > 10000) {

			posX = dM10/dArea;
			posY = dM01/dArea;

			circle(croped_image,Point(posX,posY),10,Scalar(0,0,255),-1, 5,0);
			#ifdef __arm__
 				line(croped_image,Point(posX,0),Point(posX,Camera.get(CV_CAP_PROP_FRAME_HEIGHT)-heigth_crop),Scalar(0,255,0),1); // vertical line
 				line(croped_image,Point(0,posY),Point(Camera.get(CV_CAP_PROP_FRAME_WIDTH),posY),Scalar(0,255,0),1); // horizontal line
			#else
 				line(croped_image,Point(posX,0),Point(posX,croped_image.rows),Scalar(0,255,0),1); // vertical line
 				line(croped_image,Point(0,posY),Point(croped_image.cols,posY),Scalar(0,255,0),1); // horizontal line
 			#endif	
		}

 		imshow("Tracking",croped_image); //show the original image
			
		if ( waitKey(1) >=0 ) break;						// wait 1 mS
	}

	return 0;
}
