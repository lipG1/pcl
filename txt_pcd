#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<opencv2/core.hpp>
#include <opencv2\imgcodecs.hpp>

using namespace std;
using namespace cv;


float stringToNum(const string& str)
{
	istringstream iss(str);
	float num;
	iss >> num;
	return num;
}

int main()
{
	string filepath = "F:\\point.txt";
	ifstream infile (filepath);
	//ifstream infile1("F:\\max.txt");
	//ofstream outfile("F:\\point_sp.txt");
	if (infile.bad())
		cout << "input error !" << endl;
	string line,line1;
	Mat z=Mat::zeros(1800,595,CV_32FC1);
	
	int n = 0;//��������
	int m = 0;//��������
	//float e = 39.001;
	int size=0;
	//int m1 = 592;
	vector<vector<string>>cols;
	vector<vector<float>>index;
	while (getline(infile, line1))
	{
		istringstream instr1(line1);//y�ı仯Ϊ-0.22����С��ֻ��334�����595��-65.380-65.30��
		vector<float> fields1;
		string field1;
		while (getline(instr1, field1,','))
		{
			float temp = stringToNum(field1);
			fields1.push_back(temp);
		}
		index.push_back(fields1);
		float y = -0.22 * n;
		if (y == index[size][1])
		{
			float col = (index[size][0] + 65.380) / 0.22;
		    int c = (int)(col*10+5)/10;//floatתint����������
			z.at<float>(n,c) = index[size][2];
		}
		else 
		{
			n++;
		}
		size++;

		/*if (n == 1423)
			outfile << fields[0] << " " << fields[1] << " " << fields[2] << endl;*/
		
	}
	Mat final = z.clone();
	for (int k = 0; k < 1800; k++)
	{
		const float* inData = z.ptr<float>(k);
		float* outData = final.ptr<float>(k);
		for (int i = 0; i < 595; i++)
		{
			float value = inData[i];
			if (i < 30)
			{
				if (value <= 0.0)
                   outData[i] = (float)39.0;//���ǵ���˵�ȱֵ
			}
			else
			{
				int a = i - 1, b = i - 2, c = i - 3;
				float value1 = inData[a];
				if (value <= 0.0)
				{
					if (value1 <= 50.0)
					{
						outData[i] = (float)39.0;
					}//����������˵����ο�����39��������ȡ39������ȡ������������ƽ��
					if(value1>50.0)
					{
						float value2 = inData[b];
						float value3 = inData[c];
						float sum = value2 + value3 + value1;
						outData[i] = sum / 3;
					}
				}
				
			}
			
		}
	}
	 /*imwrite("F:\\1_2.jpg", z);
	 imwrite("F:\\1_3.jpg", final);*/
	 Mat img = final.clone();
	 Mat img1 = img;
	 int m1 = 0;
	 int n1 = 0;
	 int mid1 = 0;
	 int count1 = 0;
	 for (int i = 80; i < 1450; i++)
	 {
		 float temp = 60.0;
		 float temp1 = 60.0;


		 for (int j = 30; j < 550; j++)
		 {
			 float pixel = img.at<float>(i, j);
			 if (count1 == 0)
			 {
				 if ( pixel >= (float)50.0)
				 {
					 m1 = j;
					 temp = pixel;
					 ++count1;
				 }
			 }
		 }
		 for (int j = 550; j >= 30; j--)
		 {
			 float pixel = img.at<float>(i, j);
			 if (count1 == 1)
			 {
				 if (pixel <= (float)100.0 && pixel >= (float)50.0)
				 {
					 n1 = j;
					 temp1 = pixel;
					 ++count1;
				 }
			 }
		 }

		 count1 = 0;
		 mid1 = (n1 + m1) / 2;
		 int c = m1;
		 int c1 = mid1;
		 //float z, z1;
		 if (mid1 != 0)//91-1443
		 {
			 int dis = (n1 - m1) / 2;
			 if (dis > 100)
			 {

				 for (int j = m1; j < m1 + 100; j++)
				 {
					 float pixel = img.at<float>(i, j);
					 if (temp <= pixel)
					 {
						 temp = pixel;
						 c = j;
					 }
				 }
				 //z=img1.at<float>(i, c) ;
				 img1.at<float>(i, c) = 0.0;
				 //int c1=mid;
				 c1 = n1 - 100;
				 for (int j = c1; j <= n1; j++)//�ټӸ���Χ�������Ǵ��м䵽���ߣ�Ӧ�����ߵľֲ�����
				 {
					 float pixel = img.at<float>(i, j);
					 if (temp1 <= pixel)
					 {
						 temp1 = pixel;
						 c = j;
					 }
				 }
				 //z1=img1.at<float>(i, c1) ;
				 img1.at<float>(i, c) = 0.0;
			 }
			 else
			 {

				 for (int j = m1; j < mid1; j++)
				 {
					 float pixel = img.at<float>(i, j);
					 if (temp <= pixel)
					 {
						 temp = pixel;
						 c = j;
					 }
				 }
				 //z = img1.at<float>(i, c);

				 img1.at<float>(i, c) = 0.0;
				 for (int j = mid1; j <= n1; j++)//�ټӸ���Χ�������Ǵ��м䵽���ߣ�Ӧ�����ߵľֲ�����
				 {
					 float pixel = img.at<float>(i, j);
					 if (temp1 <= pixel)
					 {
						 temp1 = pixel;
						 c = j;
					 }
				 }
				 //z1 = img1.at<float>(i, c1);
				 img1.at<float>(i, c) = 0.0;
			 }
			/* output << 0.22 * c - 65.380 << " " << -0.22 * i << endl;
			 output << 0.22 * c1 - 65.380 << " " << -0.22 * i << endl;*/
		 }


	 }

	 imwrite("F:\\max.jpg", img1);
	

	//while (getline(infile,line))
	//{
	//	istringstream instr(line);//y�ı仯Ϊ-0.22����С��ֻ��334�����595��-65.380-65.30��
	//	vector<string> fields;
	//	string field;
	//	while (getline(instr, field, ','))
	//		fields.push_back(field);
	//	/*if (n == 1423)
	//		outfile << fields[0] << " " << fields[1] << " " << fields[2] << endl;*/
	//	
	//		float n1 = index[n][1];
	//		float temp = stringToNum(fields[1]);
	//		float temp1 = stringToNum(fields[0]);
	//		if (temp == n1)
	//		{
	//			m++;
	//			cols.push_back(fields);
	//			/*float sub = index[n][0]-temp1;
	//			if (sub< 0.219)
	//			{
	//				outfile << fields[0] << " " << fields[1] << " " << fields[2] << endl;
	//				n++;
	//			}*/
	//		}
	//	
	//	//else
	//	//{
	//	//	/*int col = (592-m) / 2;
	//	//	if (col < 0)
	//	//		col = 0;
	//	//	for (int a = 0; a < col; a++)
	//	//	{
	//	//		z.at<uchar>(n, a) = e;
	//	//	}
	//	//	if (col + cols.size() <= 592)
	//	//		 size = col + cols.size();
	//	//	else
	//	//		 size = 592;
	//	//	for (int a = col; a < size; a++)
	//	//		z.at<uchar>(n, a) = stringToNum(cols[a - col][2]);
	//	//	for (int a = col + cols.size(); a < 592; a++)
	//	//		z.at<uchar>(n, a) = e;*/
	//	//	for (int i = 0; i < cols.size(); i++)
	//	//	{
	//	//	    float col = (stringToNum(cols[i][0]) + 65.380) / 0.22;
	//	//		int c = (int)(col*10+5)/10;//floatתint����������
	//	//		z.at<uchar>(n,c) = stringToNum(cols[i][2]);

	//	//	}
	//		
	//		

	//		//if (m!=0&&m < m1)
	//		/*if (m>m1)
	//			m1 = m;*/
	//		/*m = 0;
	//		n++;
	//		cols.clear();*/
	//	//}
	//		/*z.at<uchar>(n, m) = stringToNum(fields[2]);
	//	m++;
	//	if (590 < m)
	//	{
	//		m = 0;
	//		n++;
	//	}*/
	//		
	//}
	//imwrite("F:\\1.jpg", z);
	//cout << m1 << endl;
	return 0;
}
