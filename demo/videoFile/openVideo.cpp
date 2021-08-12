#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <time.h>
#include <sys/time.h>

using namespace std;
using namespace cv;

bool detect_and_draw(CascadeClassifier *faceCasade,Mat *image);
bool personFace_faceCasadeXml_load(CascadeClassifier *faceCasade,string xml);
bool personFace_detect(CascadeClassifier *faceCasade,Mat *mat,vector<Rect> *face);

void showUsecond(int line){
	struct timeval tv;
	struct timezone tz; 
	gettimeofday(&tv, &tz);
	unsigned long long tmsec = tv.tv_sec*1000+tv.tv_usec/1000;
	cout<<"line:"<<line<<",time_ms:"<< tmsec<<endl;;
}

int main(int argc, char*argv[])
{
	if(argc!=2){
		cout<<"Need param: camera or video file!"<<endl;
		return -1;
	}
	VideoCapture cap(argv[1]); // open the default camera
	if(!cap.isOpened()){ // check if we succeeded
		cout<<"Open camera or video file error."<<endl;
		return -1;
	}

	map<string,string> Map;
	string obj[2]={"Person_face","Cat_face"};

	Map[obj[1]]="/home/lam/opencv3/opencv-3.4.14/data/haarcascades/haarcascade_frontalcatface.xml";
	Map[obj[0]]="/home/lam/opencv3/opencv-3.4.14/data/haarcascades/haarcascade_frontalface_alt2.xml";

	CascadeClassifier faceCasade;
	personFace_faceCasadeXml_load(&faceCasade,Map[obj[0]]);

	Mat edges;
	namedWindow("face detecting",0);
	resizeWindow("face detecting", 320, 240);
	for(;;)
	{
		Mat frame;
		showUsecond(__LINE__);
		cap >> frame; // get a new frame from camera
		showUsecond(__LINE__);
		//cvtColor(frame, edges, COLOR_BGR2GRAY);
		showUsecond(__LINE__);

		detect_and_draw(&faceCasade,&frame);
	}
	return 0;
}

bool personFace_faceCasadeXml_load(CascadeClassifier *faceCasade,string xml){
	if (!faceCasade->load(xml))
	{
		cout << "Person face faceCasade xml not found！！" << endl;
		return false;
	}
	return true;
}

bool personFace_detect(CascadeClassifier *faceCasade,Mat *mat,vector<Rect> *faces){
	faceCasade->detectMultiScale(*mat, *faces, 1.1, 3, 0, Size(100, 100),mat->size());
	return true;
}

bool detect_and_draw(CascadeClassifier *faceCasade,Mat *image)
{
	showUsecond(__LINE__);
	Mat heying,hyGray;
	vector<Rect> faces;

	heying = *image;
	cvtColor(*image, hyGray, COLOR_BGR2GRAY);
	//cvtColor(*image, hyGray, COLOR_BGR2RGB);
	equalizeHist(hyGray, hyGray); 

	showUsecond(__LINE__);

	if(!personFace_detect(faceCasade,&hyGray,&faces))return false;

	showUsecond(__LINE__);

	for(auto b : faces)
	{
		cout << "Output person face position：(x,y):" << "(" << b.x << "," << b.y << "),(width,heigh):(" << b.width << "," << b.height << ")"<<endl;;
		if(1){
			if (faces.size() > 0)
			{
				for (size_t i = 0; i < faces.size(); i++)
				{
					rectangle(heying, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 255, 0), 1, 8);
					//cout << faces[i] << endl;
					// putText(heying,"xxx", cvPoint(faces[i].x, faces[i].y - 10), FONT_HERSHEY_PLAIN, 2.0, Scalar(0, 0, 255));
					putText(heying,"Person_face",Point(faces[i].x, faces[i].y-10),CV_FONT_HERSHEY_PLAIN,1.0,Scalar(0,255,0),1,LINE_4,0);
				}
			}
		}
	}
	imshow("result", heying);
	waitKey(1);
	cout<<"--------------------------------------------"<<endl;
	return 0;
}
