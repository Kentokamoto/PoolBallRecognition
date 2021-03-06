/*
 * Project: PoolTable
 * File: Main.cpp
 * Date: 3/27/2016
 * By: Kento Okamoto
 */

#include <iostream>
#include "opencv2/opencv_modules.hpp"
#include <opencv2/xfeatures2d/nonfree.hpp>
#include <stdio.h>
#include "find_pool_table.h"
#include "warp.h"
#include "Stitch.h" 
#include "TableStitch.h"

#define USEVIDEO	0//Set the value if you are using a video or image

using namespace std;
int main(int argv, char* argc[]){

	printf("Hit ESC key to quit\n");
#if USEVIDEO
	 cv::VideoCapture cap("./src/Photos/TableHalf/MovieScan.mp4");//1285 or 1367
	 //cv::VideoCapture cap(0);
	 if (!cap.isOpened()) {          // check if we succeeded
	 	printf("error - can't open the video file; hit enter key to quit\n");
	 	cin.ignore().get();
	 	return EXIT_FAILURE;
	 }
	 Mat src;
	 cap >> src;
	 VideoWriter writer;
	 int codec = cap.get(CV_CAP_PROP_FOURCC);
	 int fps = cap.get(CV_CAP_PROP_FPS);
    string filename = "live.mp4";             // name of the output video file
    writer.open(filename, codec, fps, src.size(), true);
    // check if we succeeded
    if (!writer.isOpened()) {
    	cerr << "Could not open the output video file for write\n";
    	return -1;
    }

	// Stitch stitch;
	// cv::Mat outputImage = stitch.stitchImages(cap);
	// if(outputImage.empty()){
	// 	exit(EXIT_FAILURE);
	// }
	// std::vector<cv::Point> corners = findTable(outputImage);
	// if(corners.size() == 4){
	// 		std::cout << "Found Corners" << std::endl;
	// 		cv::Mat ortho = warpImage(corners, outputImage);
	// 		vector<int> compression_params;
	// 		compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	// 		compression_params.push_back(9);
	// 		imwrite("Ortho.png", ortho,compression_params );


	// 		imshow("Orthonormal", ortho);
	// 		if(waitKey(0) == 27){
	// 				exit(EXIT_FAILURE);
	// 		}
	// }
    while (true){
	 	// Read in the image
    	cv::Mat imageInput;
    	cap >> imageInput;
    	if (imageInput.empty()) break;

	 	// Resize the image and put it in outputImage
    	TableStitch tableStitcher;
    	tableStitcher.compute(imageInput);
    	cv::Mat outputImage = tableStitcher.getStitchedTable();
    	writer.write( outputImage);
	// 	std::vector<cv::Point> corners = findTable(outputImage);
	// 	if(corners.size() == 4){
	// 		cv::Mat ortho = warpImage(corners, outputImage);
	// 		findBalls(ortho);
    }


	// 	//cv::namedWindow("My Image", cv::WINDOW_NORMAL);
	// 	//cv::imshow("Marker", outputImage);
	// 	if (cv::waitKey(1) == 27)  break;  // hit ESC (ascii code 27) to quit

	// }
#else
    if(argv != 3){
    	cerr << "Error: Input must be ./PoolTable <leftImageFile> <rightImagePath>" << endl;
    	return 0;
    }
    Mat left = cv::imread(argc[1]);
    Mat right = cv::imread(argc[2]);
    std::vector<Mat> list;
    TableStitch tableStitcher;
    cv::resize(left, left, cv::Size(left.cols/2, left.rows/2));
    cv::resize(right, right, cv::Size(right.cols/2, right.rows/2));
    std::vector<Point2i> leftPockets = tableStitcher.compute(left);
    std::vector<Point2i> rightPockets = tableStitcher.compute(right);

    if( leftPockets.size() == 4){
    	Mat orthoLeft;
    	orthoLeft = tableStitcher.warpImage(left, leftPockets);

    	std::vector<int> compression_params;
    	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    	compression_params.push_back(9);
    	imwrite("LeftOrtho.png", orthoLeft,compression_params );

    }

    if( rightPockets.size() == 4){
    	Mat orthoRight;
    	orthoRight = tableStitcher.warpImage(right, rightPockets);

    	std::vector<int> compression_params;
    	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    	compression_params.push_back(9);
    	imwrite("RightOrtho.png", orthoRight,compression_params );

    }

    if(rightPockets.size() == 4 && leftPockets.size() == 4){
    	Mat output, orthoLeft, orthoRight;
    	orthoLeft = tableStitcher.warpImage(left, leftPockets);
    	orthoRight = tableStitcher.warpImage(right, rightPockets);
    	output = tableStitcher.combineImages(orthoLeft, orthoRight);

    	std::vector<int> compression_params;
    	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    	compression_params.push_back(9);
    	imwrite("Stitched.png", output,compression_params );

    }
	// Stitcher stitcher = Stitcher::createDefault();
	// stitcher.setRegistrationResol(-1); /// 0.6
	// stitcher.setSeamEstimationResol(-1);   /// 0.1
	// stitcher.setCompositingResol(-1);   //1
	// stitcher.setPanoConfidenceThresh(-1);   //1
	// stitcher.setWaveCorrection(true);
	// stitcher.setWaveCorrectKind(detail::WAVE_CORRECT_HORIZ);
	// Mat output;
	// Stitcher::Status status = stitcher.stitch(list, output);
	// if(status == Stitcher::OK){
	// 	std::vector<int> compression_params;
	// 	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	// 	compression_params.push_back(9);
	// 	imwrite("Stitched.png", output,compression_params );
	// }else{
	// 	std::cout << "Failed" << std::endl;
	// }



	//cv::resize(outputImage, outputImage, cv::Size(outputImage.cols/2, outputImage.rows/2));
	//imshow("Stitch", outputImage);
	//waitKey(0);
	//std::vector<cv::Point> corners = findTable(image);
	//if(corners.size() == 4){
	//	cv::Mat ortho = warpImage(corners, image);
	//	imshow("Ortho", ortho);
	//	if(waitKey(0) == 27){
	//			exit(EXIT_FAILURE);
	//	}
	//	findBalls(ortho);
	//}	
	//cv::namedWindow("Initial Image",cv::WINDOW_AUTOSIZE);
//	cv::imshow("Initial Image", image);
	//if (cv::waitKey(0) == 27)  return EXIT_SUCCESS;
#endif
    return EXIT_SUCCESS;
}
