#include "SEGD.h"


SEGD::SEGD(void)
{
}


SEGD::~SEGD(void)
{
}

#define threshold 10
void SEGD::segmentinit(segment &seg)
{
	for(int i=0;i<segmentlength;i++) 
	{
		seg.down[i]=0;
		seg.left_down[i]=0;
		seg.left_up[i]=0;
		seg.mid[i]=0;
		seg.right_down[i]=0;
		seg.right_up[i]=0;
		seg.up[i]=0;
	}
}

void SEGD::seven_segment(Mat imgfigure,segment &sevensegment,eachvalue &out,int n)
{
	unsigned char point; 
	int temp=0;
	//对第一段进行投影 up	
	for (int i=0;i<segmentlength/2;i++)
		for(int j=0;j<=i;j++)
		{
			point=imgfigure.at<uchar>(j,i);
			if(point==0)
				sevensegment.up[i]++;
			point=imgfigure.at<uchar>(j,segmentlength-1-i);
			if(point==0)
				sevensegment.up[segmentlength-1-i]++;
		}
		out.Each_value[n][0]=changethesegment(sevensegment.up);
		/*for (int i=0;i<segmentlength;i++)
		{
		if(sevensegment.up[i]!=0)
		temp++;
		}
		if(temp>=threshold)
		{
		out.Each_value[0][0]=temp;
		}
		else
		for (int i=0;i<segmentlength;i++)
		{
		sevensegment.up[i]=0;
		}
		temp=0;*/
	//对第二段进行投影 right_up
	for (int i=0;i<segmentlength/2;i++)
		for(int j=0;j<=i;j++)
		{
			point=imgfigure.at<uchar>(i,segmentlength-1-j);
			if(point==0)
				sevensegment.right_up[i]++;
			point=imgfigure.at<uchar>(segmentlength-1-i,segmentlength-1-j);
			if(point==0)
				sevensegment.right_up[segmentlength-1-i]++;
		}
		out.Each_value[n][1]=changethesegment(sevensegment.right_up);
		//for (int i=0;i<segmentlength;i++)
		//{
		//	if(sevensegment.right_up[i]!=0)
		//		temp++;
		//}
		//if(temp>=threshold)
		//{
		//	out.Each_value[0][1]=temp;
		//}
		//else
		//	for (int i=0;i<segmentlength;i++)
		//	{
		//		sevensegment.right_up[i]=0;
		//	}
		//temp=0;
	//对第三段进行投影 right_down
	for (int i=0;i<segmentlength/2;i++)
		for(int j=0;j<=i;j++)
		{
			point=imgfigure.at<uchar>(segmentlength+i,segmentlength-1-j);
			if(point==0)
				sevensegment.right_down[i]++;
			point=imgfigure.at<uchar>(2*segmentlength-1-i,segmentlength-1-j);
			if(point==0)
				sevensegment.right_down[segmentlength-1-i]++;
		}
		out.Each_value[n][2]=changethesegment(sevensegment.right_down);
		/*for (int i=0;i<segmentlength;i++)
		{
			if(sevensegment.right_down[i]!=0)
				temp++;
		}
		if(temp>=threshold)
		{
			out.Each_value[0][2]=temp;

		}
		else
			for (int i=0;i<segmentlength;i++)
			{
				sevensegment.right_down[i]=0;
			}
					temp=0;*/
		//对第四段进行投影 down
		for (int i=0;i<segmentlength/2;i++)
			for(int j=0;j<=i;j++)
			{
				point=imgfigure.at<uchar>(2*segmentlength-1-j,i);
				if(point==0)
					sevensegment.down[i]++;
				point=imgfigure.at<uchar>(2*segmentlength-1-j,segmentlength-1-i);
				if(point==0)
					sevensegment.down[segmentlength-1-i]++;
			}
			out.Each_value[n][3]=changethesegment(sevensegment.down);
		/*	for (int i=0;i<segmentlength;i++)
			{
				if(sevensegment.down[i]!=0)
					temp++;
			}
			if(temp>=threshold)
			{
				out.Each_value[0][3]=temp;

			}
			else
				for (int i=0;i<segmentlength;i++)
				{
					sevensegment.down[i]=0;
				}
						temp=0;*/
		//对第五段进行投影 left_down
		for (int i=0;i<segmentlength/2;i++)
			for(int j=0;j<=i;j++)
			{
				point=imgfigure.at<uchar>(segmentlength+i,j);
				if(point==0)
					sevensegment.left_down[i]++;
				point=imgfigure.at<uchar>(2*segmentlength-1-i,j);
				if(point==0)
					sevensegment.left_down[segmentlength-1-i]++;
			}
			out.Each_value[n][4]=changethesegment(sevensegment.left_down);
	/*		for (int i=0;i<segmentlength;i++)
			{
				if(sevensegment.left_down[i]!=0)
					temp++;
			}
			if(temp>=threshold)
			{
				out.Each_value[0][4]=temp;

			}
			else
				for (int i=0;i<segmentlength;i++)
				{
					sevensegment.left_down[i]=0;
				}
			temp=0;*/
		//对第六段进行投影 left_up
		for (int i=0;i<segmentlength/2;i++)
			for(int j=0;j<=i;j++)
			{
				point=imgfigure.at<uchar>(i,j);
				if(point==0)
					sevensegment.left_up[i]++;
				point=imgfigure.at<uchar>(segmentlength-1-i,j);
				if(point==0)
					sevensegment.left_up[segmentlength-1-i]++;
			}
			out.Each_value[n][5]=changethesegment(sevensegment.left_up);
			/*for (int i=0;i<segmentlength;i++)
			{
				if(sevensegment.left_up[i]!=0)
					temp++;
			}
			if(temp>=threshold)
			{
				out.Each_value[0][5]=temp;
			}
			else
				for (int i=0;i<segmentlength;i++)
				{
					sevensegment.left_up[i]=0;
				}
		temp=0;*/
		//对第七段进行投影 mid
		for (int i=6;i<segmentlength/2;i++)
			for(int j=0;j<=i;j++)
			{
				point=imgfigure.at<uchar>(segmentlength-1-j,i);
				if(point==0)
					sevensegment.mid[i]++;
				point=imgfigure.at<uchar>(segmentlength-1+j,i);
				if(point==0)
					sevensegment.mid[i]++;

				point=imgfigure.at<uchar>(segmentlength-1-j,segmentlength-1-i);
				if(point==0)
					sevensegment.mid[segmentlength-1-i]++;
				point=imgfigure.at<uchar>(segmentlength-1+j,segmentlength-1-i);
				if(point==0)
					sevensegment.mid[segmentlength-1-i]++;
			}
			for (int i=6;i<segmentlength-6;i++)
			{
				if(sevensegment.mid[i]!=0)
					temp++;
			}
			if(temp!=0)
			{
				out.Each_value[n][6]=temp;
				for (int i=0;i<segmentlength;i++)
				{
					sevensegment.mid[i]=1;
				}
			}
}

void SEGD::showthefigure(Mat imgfigure,segment seven)
{

	for (int i=0;i<segmentlength;i++)
	{
		if (seven.up[i]!=0)
		{
			imgfigure.at<uchar>(0,i)=0;
		}
		if (seven.right_up[i]!=0)
		{
			imgfigure.at<uchar>(i,segmentlength-1)=0;
		}
		if (seven.right_down[i]!=0)
		{
			imgfigure.at<uchar>(segmentlength+i,segmentlength-1)=0;
		}
		if (seven.down[i]!=0)
		{
			imgfigure.at<uchar>(2*segmentlength-1,i)=0;
		}
		if (seven.left_down[i]!=0)
		{
			imgfigure.at<uchar>(segmentlength+i,0)=0;
		}
		if (seven.left_up[i]!=0)
		{
			imgfigure.at<uchar>(i,0)=0;
		}
		if (seven.mid[i]!=0)
		{
			imgfigure.at<uchar>(segmentlength,i)=0;
		}
	}
}

int SEGD::changethesegment(int (&theline)[segmentlength])
{
	int sum=0;
	for (int i=0;i<segmentlength;i++)
	{
		if(theline[i]!=0)
			sum++;
		else
		{
			if(sum>=threshold)
			{
					for (int j=0;j<segmentlength;j++)
						theline[j]=1;
				return 1;
			}
			else if(sum>0)
				for(int j=0;j<sum;j++)
					theline[i-j-1]=0;
			sum=0;
		}
		//if(i==segmentlength-1&&sum<threshold)
		//	for(int j=0;j<=sum;j++)
		//		theline[i-j]=0;		
	}
	if(sum<threshold)
		{
			for(int j=0;j<=sum;j++)
			theline[segmentlength-j-1]=0;
			return 0;
		}
	else
		{
			for (int j=0;j<segmentlength;j++)
				theline[j]=1;
			return 1;
		}
}

void SEGD::Judgement(eachvalue out,int count,pPoint focus)
{
	for (int i=0;i<count;i++)
	{
		if(out.Each_value[i][0]==1
			&&out.Each_value[i][1]==1
			&&out.Each_value[i][2]==1
			&&out.Each_value[i][3]==1
			&&out.Each_value[i][4]==1
			&&out.Each_value[i][5]==1
			&&out.Each_value[i][6]>=0)
			cout<<"0"<<endl;
		else if(out.Each_value[i][0]==0
				&&out.Each_value[i][1]==0
				&&out.Each_value[i][2]==0
				&&out.Each_value[i][3]==0
				&&out.Each_value[i][4]==0
				&&out.Each_value[i][5]==0
				&&out.Each_value[i][6]>=1)
				cout<<"1"<<endl;
		else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][2]==0
				&&out.Each_value[i][3]==1
				&&out.Each_value[i][4]==1
				&&out.Each_value[i][5]==0
				&&out.Each_value[i][6]>=1)
				cout<<"2"<<endl;
		else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][2]==1
				&&out.Each_value[i][3]==1
				&&(out.Each_value[i][4]==0||out.Each_value[i][4]==1)
				&&out.Each_value[i][5]==0
				&&(out.Each_value[i][6]==0||out.Each_value[i][6]>=1))
				cout<<"3"<<endl;
		else if(out.Each_value[i][0]==0
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][2]==1
				&&out.Each_value[i][3]==0
				&&out.Each_value[i][4]==0
				&&(out.Each_value[i][5]==0||out.Each_value[i][5]==1)
				&&out.Each_value[i][6]>=1)
				cout<<"4"<<endl;
		else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==0
				&&out.Each_value[i][2]==1
				&&out.Each_value[i][3]==1
				&&out.Each_value[i][4]==0
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]>=1)
				cout<<"5"<<endl;
		else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==0
				&&out.Each_value[i][2]==1
				&&out.Each_value[i][3]==1
				&&out.Each_value[i][4]==1
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]>=1)
				cout<<"6"<<endl;
		else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][2]==0
				&&out.Each_value[i][3]==0
				&&out.Each_value[i][4]==0
				&&out.Each_value[i][5]==0
				&&out.Each_value[i][6]>=1)
				cout<<"7"<<endl;
		else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][2]==1
				&&out.Each_value[i][3]==1
				&&out.Each_value[i][4]==1
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]>=1)
				cout<<"8"<<endl;
		else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][2]==1
				&&(out.Each_value[i][3]==1||out.Each_value[i][3]==0)
				&&out.Each_value[i][4]==0
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]>=1)
				cout<<"9"<<endl;
		else
		{
			int thenum=0;
			thenum=Half_Judge(out,count,focus[i].FullorHalf);
			if(focus[i].FullorHalf==1)
			cout<<thenum-1<<".5"<<endl;
			else
			cout<<thenum<<".5"<<endl;
		}
	}
}

int SEGD::Half_Judge(eachvalue out,int count,int half)
{
	int thenum=0;
	if(half!=2)
		for (int i=0;i<count;i++)
		{
			if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]>=0)
				thenum=0;
			else if(out.Each_value[i][0]==0
				&&out.Each_value[i][1]==0
				&&out.Each_value[i][5]==0
				&&out.Each_value[i][6]>=1)
				thenum=1;
			else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==0
				&&out.Each_value[i][6]>=1)
				thenum=2;
			else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==0
				&&(out.Each_value[i][6]==0||out.Each_value[i][6]>=1))
				thenum=3;
			else if(out.Each_value[i][0]==0
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==0
				&&out.Each_value[i][6]>=1)
				thenum=4;
			else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==0
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]>=1)
				thenum=5;
			else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==0
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]>=1)
				thenum=6;
			else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==0
				&&out.Each_value[i][6]>=1)
				thenum=7;
			else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]>=1)
				thenum=8;
			else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]>=1)
				thenum=9;
			else
				thenum=11;
		}
	else if(half==2)
		for (int i=0;i<count;i++)
		{
			if(out.Each_value[i][0]==0
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]==1)
				thenum=0;
			else if((out.Each_value[i][0]==0||out.Each_value[i][6]>=1)
				&&out.Each_value[i][1]==0
				&&out.Each_value[i][5]==0)
				thenum=1;
			else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==0
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]>=1)
				thenum=2;
			else if((out.Each_value[i][0]==0||out.Each_value[i][0]>=1)
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==0
				&&(out.Each_value[i][6]==0||out.Each_value[i][6]>=1))
				thenum=3;
			else if(out.Each_value[i][0]==0
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==0
				&&out.Each_value[i][6]>=1)
				thenum=4;
			else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==0
				&&out.Each_value[i][6]>=1)
				thenum=5;
			else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]>=1)
				thenum=6;
			else if(out.Each_value[i][0]==0
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==0
				&&out.Each_value[i][6]>=0)
				thenum=7;
			else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==1
				&&out.Each_value[i][6]>=1)
				thenum=8;
			else if(out.Each_value[i][0]==1
				&&out.Each_value[i][1]==1
				&&out.Each_value[i][5]==0
				&&out.Each_value[i][6]>=1)
				thenum=9;
			else
				thenum=11;
		}
		return thenum;
}