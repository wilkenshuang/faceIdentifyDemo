#include "get_token.h"
#include "base64.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace cv;

int main() {
	Mat image = imread("/app/huang/MTCNN/face_2.png");
	vector<uchar> vecImg;
	vector<int> vecCompression_params;
	vector<uchar> vectest;
	vecCompression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	vecCompression_params.push_back(100);
	imencode(".jpg", image, vecImg, vecCompression_params);
	string base64Img = Encode(vecImg.data(), vecImg.size());
	string access_token;
	const string AK = "hZp7PAVeBGdN8YcFpCflVLn4";
	const string SK = "5mU1lGbsy4pkZOcR8Twz2zwGhWgS9zMj";
	int tokNum = get_access_token(access_token, AK, SK);//��ȡtoken���ɹ�Ϊ0��ʧ��Ϊ1
	string res;
	string status;
	/*
	//ע������
	int resNum;
	if (tokNum == 0) {
	resNum = add(base64Img, res, status,access_token);
	//cout << res<< endl;
	cout << status << endl;
	}
	*/

	//��������
	string user_id;
	if (tokNum == 0) {
		search(base64Img, res, access_token);
		ReadJson_string(res, "error_msg", status);
		if (status == "SUCCESS") {
			ReadJson_userid_string(res, user_id);
			//cout << res << endl;
			cout << user_id << endl;
		}
	}
	return 0;
}