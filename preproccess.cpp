#include "preproccess.h"

preproccess::preproccess(void)
{
}

preproccess::~preproccess(void)
{
}
//关键参数
#define scale_L 0.8 //Clean_longline 中的水平比例
#define scale_V 0.95 //清除垂直过长比例的线
/*Remove_Connect_SmallArea*/
#define minh 10 //清除小连通区中，清除掉比该值还扁的连通区
#define maxh 47 //清除小连通区中，清除掉比该值还厚的连通区（或）
#define maxw 25 
#define minw1 2

#define maxw1 7 //清除小连通区中，清除掉比数字1宽的连通区
#define minw 12 //清除小连通区中，清除掉比数字窄的连通区（且），由于0的内圆也算一个连通区，所以该值不能取太大
/*getonlyfigure*/
#define thewidth_figure 10   //截取一个数字的宽和高
#define theheight_figure 20
/*showmap*/
#define Level 1  //1为水平投影，0为垂直投影
#define Vert  0


/*
未加入对输入的图片的类型进行的判断
*/
unsigned char* preproccess::Level_map(Mat imageGray)
{
	unsigned char point; 
	unsigned char* num_L=new unsigned char[imageGray.rows];
	memset(num_L,0,imageGray.rows);
	for (int j=0;j<imageGray.rows;j++)
		for(int i=0;i<imageGray.cols;i++)
		{
			point=imageGray.at<uchar>(j,i);
			if(point==0)
				num_L[j]++;
		}
	return num_L;
}
unsigned char* preproccess::Vert_map(Mat imageGray)
{
	unsigned char point; 
	unsigned char* num_V=new unsigned char[imageGray.cols];
	memset(num_V,0,imageGray.cols);
	for (int j=0;j<imageGray.cols;j++)
		for(int i=0;i<imageGray.rows;i++)
		{
			point=imageGray.at<uchar>(i,j);
			if(point==0)
				num_V[j]++;
		}
		return num_V;
}
void preproccess::showmap(Mat imageGray,string name,unsigned char *num,int way)
{
	int height=imageGray.rows;
	int width=imageGray.cols;
	imageGray.setTo(255);
	if(way==Level)
	{
		for (int j=0;j<height;j++)
			for (int i=0;i<num[j];i++)
				imageGray.data[j*width+i]=0;
	}
	else
	{
		for (int j=0;j<width;j++)
			for (int i=0;i<num[j];i++)
			{
				imageGray.data[(height-i-1)*width+j-1]=0;
			}
	}
	imshow(name,imageGray);
}

void preproccess::Remove_Connect_SmallArea(Mat imageGray)
{
	vector<vector<Point>> contours(0);        //  检测轮廓数组，每一个轮廓都用point类型的vector表示
	vector<Vec4i> hierarchy(0);      

	//  复制Mat对象，拥有独自的矩阵
	Mat imageGrayDeal;
	imageGray.copyTo(imageGrayDeal);
	/// 找到轮廓
	findContours(imageGrayDeal,contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));
	/// 多边形逼近轮廓 + 获取矩形
	vector<vector<Point> > contours_poly(contours.size() );
	vector<Rect> boundRect( contours.size() );
	for(unsigned int i = 0; i < contours.size(); i++ )
	{ 
		//approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		//boundRect[i] = boundingRect( Mat(contours_poly[i]) );
		boundRect[i] = boundingRect( Mat(contours[i]) );
	}
	// 连通小区域的去除
	//const double minarea=30.0;     //  轮廓里黑像素点的个数小于阈值minarea的将黑像素点擦除
	//double rect_blackPiexl_cnt=0;       //  矩形框内黑像素点计数 
	//for( int i = 0; i < contours.size(); i++ )     //  从第0个矩形框开始进行遍历
	//{
	//	for(int y=boundRect[i].tl().y;y<boundRect[i].br().y-1;y++)           //  遍历矩形框每个像素点
	//		for (int x=boundRect[i].tl().x;x<boundRect[i].br().x-1;x++)
	//		{
	//			if(imageGray.at<uchar>(y,x)==0)
	//				rect_blackPiexl_cnt++;            //  记录每个矩形框黑像素的点的个数

	//		}
	//		if(rect_blackPiexl_cnt<minarea)           //  像素点个数少于规定的个数，将矩形框内的黑色像素刷白
	//		{
	//			for(int y=boundRect[i].tl().y;y<boundRect[i].br().y-1;y++)           //  遍历矩形框每个像素点
	//				for (int x=boundRect[i].tl().x;x<boundRect[i].br().x-1;x++)
	//					imageGray.at<uchar>(y,x)=255;

	//		}
	//		rect_blackPiexl_cnt=0;
	//}
	vector<Rect>::iterator beg;//去除大连通区
	for(beg=boundRect.begin();beg!=boundRect.end();beg++)
	{
		if((*beg).width>=imageGray.cols-5||(*beg).height>=imageGray.rows-5)
			beg=boundRect.erase(beg);
	}
	for(unsigned int i = 0; i < boundRect.size(); i++ )    	//tl()返回左上角点坐标，br()返回右下角点坐标
	{
		if (boundRect[i].br().y-boundRect[i].tl().y<minh||boundRect[i].br().y-boundRect[i].tl().y>maxh//竖向,过滤掉太扁的连通区,和太厚的连通区
			||boundRect[i].br().x-boundRect[i].tl().x>maxw||boundRect[i].br().x-boundRect[i].tl().x<minw1)
		{
			for(int y=boundRect[i].tl().y;y<boundRect[i].br().y-1;y++)           //  遍历矩形框每个像素点
				for (int x=boundRect[i].tl().x;x<boundRect[i].br().x-1;x++)
					imageGray.at<uchar>(y,x)=255;
		}
		if (boundRect[i].br().x-boundRect[i].tl().x>maxw1&&boundRect[i].br().x-boundRect[i].tl().x<minw)//宽度大于1的宽度且小于数字的宽度
		{
			for(int y=boundRect[i].tl().y;y<boundRect[i].br().y-1;y++)           //  遍历矩形框每个像素点
				for (int x=boundRect[i].tl().x;x<boundRect[i].br().x-1;x++)
					imageGray.at<uchar>(y,x)=255;
		}
		//if (boundRect[i].br().y-boundRect[i].tl().y<25//竖向要小于25
		//	&&boundRect[i].br().x-boundRect[i].tl().x<15)//横向小于15
		//{
		//	for(int y=boundRect[i].tl().y;y<boundRect[i].br().y-1;y++)           //  遍历矩形框每个像素点
		//		for (int x=boundRect[i].tl().x;x<boundRect[i].br().x-1;x++)
		//			imageGray.at<uchar>(y,x)=255;
		//}
	}
}
/*
四连通
*/
void preproccess::SaltNoiseRemove(Mat imageGray)
{
	for(int x=1;x<imageGray.cols-1;++x)
		for(int y=1;y<imageGray.rows-1;++y)
		{
			if( (imageGray.at<uchar>(y-1,x)+
				imageGray.at<uchar>(y+1,x)+
				imageGray.at<uchar>(y,x+1)+
				imageGray.at<uchar>(y,x-1)
				)==255*4)                  //  四连接
			{
				imageGray.at<uchar>(y,x)=255;
			}
			if( (imageGray.at<uchar>(y-1,x)+
				imageGray.at<uchar>(y+1,x)+
				imageGray.at<uchar>(y,x+1)+
				imageGray.at<uchar>(y,x-1)
				)==255*3)                  
			{
				imageGray.at<uchar>(y,x)=255;
			}
		}
}
/*
	清除过长的线
*/
void preproccess::Clean_longline(Mat imageGray)
{
	unsigned char* num_L=new unsigned char[imageGray.rows];
	unsigned char* num_V=new unsigned char[imageGray.cols];
	int height=imageGray.rows;
	int width=imageGray.cols;
	num_L=Level_map(imageGray);
	num_V=Vert_map(imageGray);
	//for (int j=0;j<height;j++)
	//	if (num_L[j]>scale_L*width)
	//		for (int i=0;i<width;i++)
	//			imageGray.data[j*width+i]=255;
	for (int j=0;j<width;j++)
		if(num_V[j]>scale_V*height)
			for(int i=0;i<height;i++)
				imageGray.data[(height-i-1)*width+j]=255;
	delete num_L;
	delete num_V;
}
/*
如果出现有在数字中间被清除了，该函数可以补全
*/
void preproccess::Clean_longline_repair(Mat imageGray)
{
	int point;
	int height=imageGray.rows;
	int width=imageGray.cols;
	unsigned char* num_L=new unsigned char[width];
	memset(num_L,0,width);
	for (int j=0;j<width;j++)
		for(int i=0;i<height;i++)
		{
			point=imageGray.at<uchar>(i,j);
			if(point==0)
				num_L[j]++;
		}
		for (int j=1;j<width-1;j++)
			if(num_L[j]==0&&num_L[j-1]!=0&&num_L[j+1]!=0)
				for(int i=0;i<height;i++)
					if (imageGray.data[(height-i-1)*width+j-1]==0&&imageGray.data[(height-i-1)*width+j+1]==0)
						imageGray.data[(height-i-1)*width+j]=0;
}
/*
八连通
直接在原图上处理，没有在新图像上判断。
*/
void preproccess::NoiseRemove(Mat imageGray)
{
	int average;
	int height=imageGray.rows;
	int width=imageGray.cols;
	for (int j=1;j<height-1;j++)
		for (int i=1;i<width-1;i++)
		{
			average=0;
			average=((imageGray.data[(j-1)*width+(i-1)]+imageGray.data[(j-1)*width+i]//周围8个像素点像素相加
			+imageGray.data[(j-1)*width+i+1]+imageGray.data[j*width+i-1]
			+imageGray.data[j*width+i+1]+imageGray.data[(j+1)*width+i-1]
			+imageGray.data[(j+1)*width+i]+imageGray.data[(j+1)*width+i+1])/8);
			if(abs(average-imageGray.data[j*width+i])>127.5)
				imageGray.data[j*width+i]=255;
		}
}

/*
膨胀
*/
void preproccess::expand_black(Mat imageGray)
{
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(imageGray,imageGray,element);
}
/*
腐蚀
*/
void preproccess::erosion_black(Mat imageGray)
{
	Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate( imageGray,imageGray,element);//腐蚀
}

/*
自己写的清除上下部分的函数
*/
void preproccess::Clean_updown(Mat imageGray)
{
	int height=imageGray.rows;
	int width=imageGray.cols;
	unsigned char* num_L=new unsigned char[imageGray.rows];
	num_L=Level_map(imageGray);
	int  border1,border2,border1_value,border2_value;
	border1=0;
	border1_value=num_L[0];
	border2=height-1;
	border2_value=num_L[height-1];
	for (int i=1;i<(height/2-1);i++)
	{	
		if (border1_value<num_L[i])
		{
			border1_value=num_L[i];
			border1=i;
		}
		if (border2_value<num_L[height-1-i])
		{
			border2_value=num_L[height-1-i];
			border2=height-1-i;
		}
	}
	int border3,border3_value,border4,border4_value;
	border3=border1;
	border3_value=border1_value;
	border4=border2;
	border4_value=border2_value;
	for (int i=1;i<15;i++)
	{	
		if (border3_value>num_L[border1+i])
		{
			border3_value=num_L[border1+i];
			border3=border1+i;
		}
		if (border4_value>num_L[border2-i])
		{
			border4_value=num_L[border2-i];
			border4=border2-i;
		}
	}
	for (int j=0;j<border3;j++)
		for (int i=0;i<width;i++)
		{
			imageGray.data[j*width+i]=255;
		}
		for (int j=height-1;j>border4;j--)
			for (int i=0;i<width;i++)
			{
				imageGray.data[j*width+i]=255;
			}
}

int preproccess::left_max(int left,int right,unsigned char * num)
{
	int the_max=left;
	int max_value=num[left];
	right=right-1;
	for (int j=left+1;j<=right;j++)
	{
		if(max_value<num[j])
		{
			max_value=num[j];
			the_max=j;
		}
	}
	return the_max;
}
int preproccess::right_max(int left,int right,unsigned char * num)
{
	int the_max=left+1;
	int max_value=num[left+1];
	for (int j=left+1;j<=right;j++)
	{
		if(max_value<num[j])
		{
			max_value=num[j];
			the_max=j;
		}
	}
	return the_max;
}

void preproccess::Clean_LandR(Mat imageGray)
{
	int height=imageGray.rows;
	int width=imageGray.cols;
	unsigned char* num_V=new unsigned char[imageGray.cols];//申请水平投影的数组
	num_V=Vert_map(imageGray);//水平投影
	int bord_left=(int)0.3*width;//初始点左边界
	int bord_right=(int)0.5*width;//右边界
	int mid=right_max(bord_left,bord_right,num_V);//左右边界中最大的点
	Clean_mid(imageGray,mid,num_V);//清除边界

	int bord_left_L=bord_left;
	int bord_left_R=bord_left;
	int bord_right_L=bord_right;
	int bord_right_R=bord_right;
	int mid_L=mid;
	int mid_R=mid;

	int flag_L=0;
	while(flag_L==0)
	{
		bord_left_L=(int)(mid_L-0.17*width);
		if(bord_left_L<0)
			bord_left_L=0;
		bord_right_L=mid_L;
		mid_L=left_max(bord_left_L,bord_right_L,num_V);
		/*在此添加清除代码*/
		Clean_mid(imageGray,mid_L,num_V);
		if(bord_left_L==0)
			flag_L=1;
	}
	int flag_R=0;
	while(flag_R==0)
	{
		bord_right_R=(int)(mid_R+0.17*width);
		if(bord_right_R>width)
			bord_right_R=width;
		bord_left_R=mid_R;
		mid_R=right_max(bord_left_R,bord_right_R,num_V);
		int a=mid_R;
		/*在此添加清除代码*/
		Clean_mid(imageGray,mid_R,num_V);
		if(bord_right_R==width)
			flag_R=1;
	}
}

void preproccess::Clean_mid(Mat imageGray,int mid,unsigned char * num_Vert)
{
	int height=imageGray.rows;
	int width=imageGray.cols;
	unsigned char* lpsrc_mid=imageGray.data;
	int min_left,min_right;
	min_left=mid;
	min_right=mid;
	for(int i=1;i<15;i++)
	{
		if(num_Vert[min_right]>num_Vert[mid+i])
			min_right=mid+i;
		if(num_Vert[min_left]>num_Vert[mid-i])
			min_left=mid-i;
	}
	for (int i=min_left;i<min_right;i++)
		for (int j=0;j<height;j++)
			lpsrc_mid[j*width+i]=255;
}

/*
截取数字
*/

//Rect roi(30,30,20,20);
//Mat figure;
//img5(roi).copyTo(figure);
//imshow("roi",figure);

pPoint preproccess::getonlyfigure(Mat imageGray,pPoint focus)
{
	vector<vector<Point>> contours(0);        //  检测轮廓数组，每一个轮廓都用point类型的vector表示
	vector<Vec4i> hierarchy(0);      
	String name[10]={"1","2","3","4","5","6","7","8","9","10"};
	//  复制Mat对象，拥有独自的矩阵
	Mat imageGrayDeal;
	imageGray.copyTo(imageGrayDeal);
	// 找到轮廓
	findContours(imageGrayDeal,contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point(0, 0));
	//获取矩形
	vector<Rect> boundRect( contours.size() );
	for(unsigned int i = 0; i < contours.size(); i++ )
	{ 
		boundRect[i] = boundingRect( Mat(contours[i]) );
	}
	//去除大连通区
	vector<Rect>::iterator beg;
	for(beg=boundRect.begin();beg!=boundRect.end();beg++)
	{
		if((*beg).width>=imageGray.cols-5||(*beg).height>=imageGray.rows-5)
			beg=boundRect.erase(beg);
	}
	for (beg=boundRect.begin();beg!=boundRect.end();)//对最后一位不进行处理
	{
		for (int i=0;i<boundRect.size();i++)
		{
			//if(beg==boundRect.end()-1)
			//	if((*beg).tl().x>boundRect[i].tl().x&&(*beg).tl().y>boundRect[i].tl().y
			//		&&(*beg).br().x<boundRect[i].br().x&&(*beg).br().y<boundRect[i].br().y)
			//		boundRect.end()=boundRect.end()-1;
			if((*beg).tl().x>boundRect[i].tl().x&&(*beg).tl().y>boundRect[i].tl().y
				&&(*beg).br().x<boundRect[i].br().x&&(*beg).br().y<boundRect[i].br().y)
				{	
					beg=boundRect.erase(beg);
				}
		}
		if(beg!=boundRect.end())//对于图26，删除了最后一个连通区，导致.end前移一个，则beg==.end 此时再beg++就出界。每次++前对其进行一次判断。
			beg++;
	}
	count=boundRect.size();
	for(unsigned i = 0; i < boundRect.size(); i++ )
	{
		focus[i].x=(boundRect[i].tl().x+boundRect[i].br().x)/2-thewidth_figure;//获取每个数字的左上角的点
		focus[i].y=(boundRect[i].tl().y+boundRect[i].br().y)/2-theheight_figure;
		if(boundRect[i].height<1.4*theheight_figure/*&&(boundRect[i].tl().y+boundRect[i].br().y)/2<0.5*imageGray.rows*/)
			{
				if((boundRect[i].tl().y+boundRect[i].br().y)/2>0.5*imageGray.rows)
					focus[i].FullorHalf=2;
				else
					focus[i].FullorHalf=1;
				focus[i].x=boundRect[i].tl().x;
				focus[i].y=boundRect[i].tl().y;
			}
		else
			focus[i].FullorHalf=0;
	}
	int temp1;
	for(int p=0;p<boundRect.size();p++)//给连通区域从左到右排序
		for(int q=p+1;q<boundRect.size();q++)
			if(focus[p].x>focus[q].x)
			{
				temp1=focus[q].x;
				focus[q].x=focus[p].x;
				focus[p].x=temp1;
				temp1=focus[q].y;
				focus[q].y=focus[p].y;
				focus[p].y=temp1; 
			}
	//显示数字
	//for(unsigned int i=0;i<boundRect.size();i++)
	//{
	//Rect roi(focus[i].x,focus[i].y,2*thewidth_figure,2*theheight_figure);
	//Mat figure(2*thewidth_figure,2*theheight_figure,CV_8UC1,255);
	//imageGray(roi).copyTo(figure);
	//imshow(name[i],figure);
	//}
	
	return focus;
}

unsigned int preproccess::GetFigureNumber()
{
	return count;
}





