#pragma once
#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>
#include "preproccess.h"

using namespace std;
using namespace cv;
#define segmentlength 20
typedef struct thesevensegment{
	int up[segmentlength];
	int down[segmentlength];
	int mid[segmentlength];
	int left_up[segmentlength];
	int left_down[segmentlength];
	int right_up[segmentlength];
	int right_down[segmentlength];
}segment,*pSegment;

typedef struct eachvalue{
	int Each_value[10][7];
}eachvalue,*pEachvalue;
class SEGD
{
public:
	SEGD(void);
	~SEGD(void);
public:
	void seven_segment(Mat imgfigure,segment &sevensegment,eachvalue &out,int n);
	void segmentinit(segment &seg);
	void showthefigure(Mat imgfigure,segment seven);
	int changethesegment(int (&theline)[segmentlength]);//return 1 ÎªºÚ return 0Îª°×
	void Judgement(eachvalue out,int count,pPoint focus);
	int Half_Judge(eachvalue out,int count,int half);
};

