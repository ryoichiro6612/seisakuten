// seisakuten_project.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"


#include <iostream>
#include <sstream>
#include <iomanip>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#define NUMBERIMAGE 10 //読み込む写真の数
#define THRESHOLD 80



string ImageFilePath(const string& dir, int num)
{
	stringstream file_name;
	file_name << dir << setfill('0') << setw(4) << right << num << ".jpg";
	return file_name.str();
}

int main(int argc, char const* argv[])
{
	/*
	VideoCapture cap = VideoCapture("./movie/MVI_2827.MOV");
	if (!cap.isOpened()) {
		printf("video not found");
		return -1;
	}
	Mat frame;
	int i = 0;
	while (1) {
		cap >> frame;
		if (frame.rows == 0) {
			break;
		}
		char fstr[30];
		sprintf(fstr, "./image/image%d.jpg", i);
		imwrite(fstr, frame);
		i++;
	}
	return 0;
	*/
	
	int first =253;
	int last = 273;
	
	int num = first;
	string firstFrame_name;
	sprintf(&firstFrame_name[0], "./image/image%d.jpg", num);
	cv::Mat compositeFrame = cv::imread(&firstFrame_name[0], 1);
	for (; num < last ; num++) {
		string nowFrame_name;
		string nextFrame_name;
		sprintf(&nowFrame_name[0], "./image/image%d.jpg", num);
		sprintf(&nextFrame_name[0], "./image/image%d.jpg", num+1);

		cout << "number: " << num << endl;
		cv::Mat nowFrame = cv::imread(&nowFrame_name[0]);
		cv::Mat nextFrame = cv::imread(&nextFrame_name[0]);

		//比較明合成
		for (int y = 0; y < compositeFrame.rows; y++) {
			for (int x = 0; x < compositeFrame.cols; x++) {
				cv::Vec3b &p_composite = compositeFrame.at<cv::Vec3b>(y, x);
				cv::Vec3b &p_now = nowFrame.at<cv::Vec3b>(y, x);
				cv::Vec3b &p_next = nextFrame.at<cv::Vec3b>(y, x);
				int average_now = (p_now[0] + p_now[1] + p_now[2]) / 3.0;
				int average_next = (p_next[0] + p_next[1] + p_next[2]) / 3.0;
				if (average_next - average_now > THRESHOLD) {
					p_composite[0] = p_next[0];
					p_composite[1] = p_next[1];
					p_composite[2] = p_next[2];
					//cout << "*";
				}
			}

		}
		cout << endl;
	}
	char composite_name[40];
	sprintf(composite_name, "./composite_image/composite%d_%d.jpg", first, last);
	cv::imwrite(&composite_name[0], compositeFrame);
	return 0;
}