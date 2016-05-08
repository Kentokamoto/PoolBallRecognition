/*
 * Project: PoolTable
 * File: Main.cpp
 * Date: 3/27/2016
 * By: Kento Okamoto
 */

#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "find_pool_table.h"
#include "warp.h"

using namespace std;

int main(int argv, char* argc[]){

	printf("Hit ESC key to quit\n");
	cv::VideoCapture cap("./src/Photos/IMG_1367.MOV");//1285 or 1367
	//cv::VideoCapture cap(0);
	if (!cap.isOpened()) {          // check if we succeeded
		printf("error - can't open the video file; hit enter key to quit\n");
		cin.ignore().get();
		return EXIT_FAILURE;
	}

	while (true){
		cv::Mat imageInput;
		cap >> imageInput;
		if (imageInput.empty()) break;

		cv::Mat outputImage;
		cv::resize(imageInput, outputImage, cv::Size(imageInput.cols/2, imageInput.rows/2));	
		vector<cv::Point> corners = findTable(outputImage);
		if(corners.size() == 4){
			cv::Mat ortho = warpImage(corners, outputImage);
			findBalls(ortho);
		}
		

		//cv::namedWindow("My Image", cv::WINDOW_NORMAL);
		cv::imshow("Marker", outputImage);
		if (cv::waitKey(1) == 27)  break;  // hit ESC (ascii code 27) to quit

	}
	return EXIT_SUCCESS;
}
