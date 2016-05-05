
#include "preproccess.h"
#include "SEGD.h"
#define test 4
preproccess pro;
SEGD segGD;
int main()
{
	
	const char *imagename="E:\\相关文件\\查水表\\数字\\武汉表\\21.bmp";
	Mat img=imread(imagename);
	imshow("原图",img);//显示原图

	Mat img1=img.clone();
	cvtColor(img,img1,CV_RGB2GRAY);//灰度化图片

	int height,width;
	height=img1.rows;
	width=img1.cols;
	//*
	//去噪处理
	//*/
	GaussianBlur(img1,img1,Size(3,3),1.5);//高斯去噪
	//adaptiveThreshold(img1,img1, 255,CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,3,5);//自适应阈值二值化图片
	adaptiveThreshold(img1,img1, 255,CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,11,5);
	imshow("二值化",img1);

	//unsigned char* num=new unsigned char[height];
	//unsigned char* num1=new unsigned char[width];
	//num=pro.Level_map(img1);
	//num1=pro.Vert_map(img1);
	////Mat img2=img1.clone();
	////Mat img3=img1.clone();
	////pro.showmap(img2,"img2",num,1);
	////pro.showmap(img3,"img3",num1,0);

	Mat img4=img1.clone();
	pro.Clean_longline(img4);
	pro.Clean_LandR(img4);
	pro.Clean_updown(img4);
	Mat img5=img4.clone();
	pro.erosion_black(img5);
	pro.Remove_Connect_SmallArea(img5);
	pro.expand_black(img5);
	imshow("腐蚀去除连通区",img5);

	point focus[10];
	pro.getonlyfigure(img5,focus);
	//将5个数字分别放到一个单独的10*20的图片中
	int count;
	count=pro.GetFigureNumber();
	String name[10]={"1","2","3","4","5","6","7","8","9","10"};
	Mat figure[10];
	for (int i=0;i<count;i++)
	{
		Rect roi(focus[i].x,focus[i].y,2*10,2*20);
		img5(roi).copyTo(figure[i]);
	}
	/*
	定义7段的数组，记录投影，由于斜率恰好是正负1，所以比较方便。
	*/
	//const char *imagename="C:\\Users\\Administrator\\Desktop\\数字\\二值化\\5.png";
	//Mat img=imread(imagename);
	//cvtColor(img,img,CV_RGB2GRAY);//灰度化图片
	eachvalue each_bord_value;
	for(int i=0;i<10;i++)
		for(int j=0;j<7;j++)
			each_bord_value.Each_value[i][j]=0;
	segment sevensegment[10];
	for(int i=0;i<10;i++)
		segGD.segmentinit(sevensegment[i]);
	for(int i=0;i<count;i++)
	{
		segGD.seven_segment(figure[i]/*img*/,sevensegment[i],each_bord_value,i);
	}
	segGD.Judgement(each_bord_value,count,focus);

	imshow("1234",figure[test]/*img*/);
	Mat aaa(400,200,CV_8UC1,255);
	segGD.showthefigure(aaa,sevensegment[test]);
	imshow("123",aaa);

	/*
	Mat yuantu[20];
    char *imagename="E:\\相关文件\\查水表\\数字\\武汉单个数字\\0.png";
	yuantu[0]=imread(imagename);
	imagename="E:\\相关文件\\查水表\\数字\\武汉单个数字\\0-1.png";
	yuantu[1]=imread(imagename);
	imagename="E:\\相关文件\\查水表\\数字\\武汉单个数字\\1-1.png";
	yuantu[2]=imread(imagename);
	imagename="E:\\相关文件\\查水表\\数字\\武汉单个数字\\2-1.png";
	yuantu[3]=imread(imagename);
	imagename="E:\\相关文件\\查水表\\数字\\武汉单个数字\\3-1.png";
	yuantu[4]=imread(imagename);
	imagename="E:\\相关文件\\查水表\\数字\\武汉单个数字\\4-1.png";
	yuantu[5]=imread(imagename);
	imagename="E:\\相关文件\\查水表\\数字\\武汉单个数字\\5-1.png";
	yuantu[6]=imread(imagename);
	imagename="E:\\相关文件\\查水表\\数字\\武汉单个数字\\6-1.png";
	yuantu[7]=imread(imagename);
	imagename="E:\\相关文件\\查水表\\数字\\武汉单个数字\\8-1.png";
	yuantu[8]=imread(imagename);
	imagename="E:\\相关文件\\查水表\\数字\\武汉单个数字\\9-1.png";
	yuantu[9]=imread(imagename);
	Mat figure[10];
	for(int i=0;i<10;i++)
		{figure[i]=yuantu[i].clone();
	cvtColor(figure[i],figure[i],CV_RGB2GRAY);//灰度化图片
	threshold(figure[i], figure[i], 75, 255, CV_THRESH_BINARY); 
	}
	
	eachvalue each_bord_value;
	for(int i=0;i<20;i++)
		for(int j=0;j<7;j++)
			each_bord_value.Each_value[i][j]=0;
	segment sevensegment[20];
	for(int i=0;i<20;i++)
	segGD.segmentinit(sevensegment[i]);
	for(int i=0;i<10;i++)
	{
		segGD.seven_segment(figure[i],sevensegment[i],each_bord_value,i);
	}
	point focus[20];
	segGD.Judgement(each_bord_value,10,focus);

	Mat aaa(400,200,CV_8UC1,255);
	imshow("1234",figure[9]);
	segGD.showthefigure(aaa,sevensegment[9]);
	imshow("123",aaa);*/
	/*结束*/
	waitKey();
	return 0;
}