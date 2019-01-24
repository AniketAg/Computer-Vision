#include <fstream>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main()
{
	Mat image,gray;
	image = imread("C:/Users/Aniket Agarwal/Desktop/Tcd Study/Computer Vision/CamVidLights/CamVidLights01.png", CV_LOAD_IMAGE_COLOR);
	gray = imread("C:/Users/Aniket Agarwal/Desktop/Tcd Study/Computer Vision/CamVidLights/CamVidLights01.png", COLOR_BGR2GRAY);
	namedWindow("Original img", 1);   
	imshow("Original img", image);

	// Load light cascade (.xml files)
	CascadeClassifier light_cascade,colour_red,colour_yellow,colour_green;
	light_cascade.load("C:/Users/Aniket Agarwal/Desktop/Tcd Study/Computer Vision/lights.xml");
	colour_red.load("C:/Users/Aniket Agarwal/Desktop/Tcd Study/Computer Vision/red.xml");
	colour_yellow.load("C:/Users/Aniket Agarwal/Desktop/Tcd Study/Computer Vision/yellow.xml");
	colour_green.load("C:/Users/Aniket Agarwal/Desktop/Tcd Study/Computer Vision/green.xml");
	
	// Detect lights
	std::vector<Rect> lights, red, yellow, green;
	light_cascade.detectMultiScale(gray, lights, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	colour_red.detectMultiScale(gray, red, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	colour_yellow.detectMultiScale(gray, yellow, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	colour_green.detectMultiScale(gray, green, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
	
	for (size_t i = 0; i < lights.size() && i < 2 ; i++)// I have included the i < 2 condition because otherwise there were multiple boxes getting created around the same traffic light and circles around the colour
	{
		Point center_r(red[i].x + red[i].width, red[i].y + red[i].height);
		Point center_y(yellow[i].x + yellow[i].width, yellow[i].y + yellow[i].height);
		Point center_g(green[i].x + green[i].width, green[i].y + green[i].height);

		Scalar l_color = Scalar(200, 213, 48);//turquoise
		Scalar g_color = Scalar(60, 192, 3);//green 
		Scalar y_color = Scalar(0, 223, 225);//yellow
		Scalar r_color = Scalar(0, 0, 225);//red

		// Draw rectangles around the detected traffic lights
		rectangle(image, cvPoint(cvRound(lights[i].x), cvRound(lights[i].y)*0.5), cvPoint(cvRound((lights[i].x + lights[i].width - 1)), cvRound((lights[i].y + lights[i].height - 1))*0.1), l_color, 3, 8, 0);
		// Draw circles on the detected colours 
		ellipse(image, center_r, Size(red[i].width*0.09, red[i].height*0.09), 0, 0, 360, r_color, 3, 8, 0);
		ellipse(image, center_y, Size(yellow[i].width*0.09, yellow[i].height*0.09), 0, 0, 360, y_color, 3, 8, 0);
		ellipse(image, center_g, Size(green[i].width*0.09, green[i].height*0.09), 0, 0, 360, g_color, 3, 8, 0);
	}

	imshow("Detected light", image);

	waitKey(0);
	return 0;

}