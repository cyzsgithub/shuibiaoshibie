#pragma once
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include <cstring>
#include <iterator>
using namespace std;
using namespace cv;

typedef struct point{
	int x;
	int y;
	int FullorHalf;
}point,*pPoint;

class preproccess
{
public:
	preproccess(void);
	~preproccess(void);
public:
	unsigned int count;
public:
	unsigned char* Level_map(Mat imageGray);
	unsigned char* Vert_map(Mat imageGray);
	void showmap(Mat imageGray,string name,unsigned char *num,int way);
	void Remove_Connect_SmallArea(Mat imageGray);
	void SaltNoiseRemove(Mat imageGray);
	void NoiseRemove(Mat imageGray);
	void Clean_longline(Mat imageGray);
	void Clean_longline_repair(Mat imageGray);
	void expand_black(Mat imageGray);
	void erosion_black(Mat imageGray);
	void Clean_updown(Mat imageray);
	int left_max(int left,int right,unsigned char * num);
	int right_max(int left,int right,unsigned char * num);
	void Clean_LandR(Mat imageGray); 
	void Clean_mid(Mat imageGray,int mid,unsigned char * num_Vert);
	pPoint getonlyfigure(Mat imageGray,pPoint focus);
	unsigned int GetFigureNumber();
};

