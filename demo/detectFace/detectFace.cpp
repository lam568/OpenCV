#include <iostream>
#include <cv.h>
#include <highgui.h>

using namespace std;
using namespace cv;
#include <string>
#include <time.h>
#include <sys/time.h>

#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#ifndef DETECT_H
#define DETECT_H
int DetectFaceEyes();   //检测人脸定位人眼
#endif // !DETECT_H

string imagePath;

void showUsecond(int line){
	struct timeval tv;
    struct timezone tz; 
	gettimeofday(&tv, &tz);
	unsigned long long tmsec = tv.tv_sec*1000+tv.tv_usec/1000;
	cout<<"line:"<<line<<",time_ms:"<< tmsec<<endl;;
}

int DetectFaceEyes()
{
#if 0

#else
	showUsecond(__LINE__);
    Mat heying,hyGray;
    map<string,string> Map;
    string obj[2]={"Cat","Person"};
    //string Sxml[2];
    Map[obj[1]]="/home/lam/opencv3/opencv-3.4.14/data/haarcascades/haarcascade_frontalcatface.xml";
    Map[obj[0]]="/home/lam/opencv3/opencv-3.4.14/data/haarcascades/haarcascade_frontalface_alt2.xml";
    
    bool foundFace=false;
    showUsecond(__LINE__);
    cout<<"objSize:"<<sizeof(obj)/sizeof(obj[0])<<endl;
    showUsecond(__LINE__);
    for(int j=0;j<sizeof(obj)/sizeof(obj[0]);j++){
    	showUsecond(__LINE__);
    	//cout<<"j:"<<j<<endl;
		//read image
		heying = imread(imagePath);	//5ms
		hyGray = imread(imagePath, 0);
		showUsecond(__LINE__);
	
		vector<Rect> faces;
		
		CascadeClassifier faceCasade;
		
		//load xml
		showUsecond(__LINE__);
		if (!faceCasade.load(Map[obj[j]]))	//10ms
		{
		    cout << obj[j]<<"检测级联分类器没找到！！" << endl;
		    return -1;
		}
		showUsecond(__LINE__);
		
		equalizeHist(hyGray, hyGray); //1ms
		showUsecond(__LINE__);
		
		faceCasade.detectMultiScale(hyGray, faces, 1.1, 5, 0, Size(100, 100),hyGray.size());	//60ms
		showUsecond(__LINE__);
		
		for(auto b : faces)
		{
		    cout << "输出"<< obj[j] <<" 位置：(x,y):" << "(" << b.x << "," << b.y << "),(width,heigh):(" << b.width << "," << b.height << ")\n";
		    if(1){
				if (faces.size() > 0)
				{
					for (size_t i = 0; i < faces.size(); i++)
					{
						// putText(heying,"xxx", cvPoint(faces[i].x, faces[i].y - 10), FONT_HERSHEY_PLAIN, 2.0, Scalar(0, 0, 255));
						showUsecond(__LINE__);
						rectangle(heying, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0, 255, 0), 1, 8);//0.5ms
						showUsecond(__LINE__);
						cout << faces[i] << endl;
						putText(heying,obj[j],Point(faces[i].x, faces[i].y-7),3,1.2,Scalar(0,255,0),2,1,0);//0.5ms
						showUsecond(__LINE__);

					/*
						Mat face_ = hyGray(faces[i]);    // 选定人脸的基础上定位眼睛
						eyeCascade.detectMultiScale(face_, eyes, 1.2, 2, 0, Size(30, 30));
						for (size_t j = 0; j < eyes.size(); j++)
						{
							// 在原图上标注眼睛，需要人脸在原图上的坐标
							Point eyeCenter(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
							int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
							circle(heying, eyeCenter, radius, Scalar(0, 128, 0), 4, 8, 0);
						}
						*/
					}
				}
				showUsecond(__LINE__);
				imshow("result", heying);//30ms
				showUsecond(__LINE__);
				waitKey(500);
				showUsecond(__LINE__);
				foundFace=true;
			}
		}
		if(foundFace)break;
		cout<<"here"<<endl;
	}
#endif
    
    return 0;
}

int main(int argc,char* argv[])
{
    int isFaceDetect;
    cout<<"argc:"<<argc<<endl;
    if(argc!=2){
    	cout<<"param need image path."<<endl;
    	return 0;
    }
    imagePath = argv[1];
    cout<<"image:"<<imagePath<<endl;
    // 测试图片中的人脸
    isFaceDetect = DetectFaceEyes();
    return 0;
}
