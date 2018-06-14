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
	int tokNum = get_access_token(access_token, AK, SK);//获取token，成功为0，失败为1
	string res;
	string status;
	/*
	//注册人脸
	int resNum;
	if (tokNum == 0) {
	resNum = add(base64Img, res, status,access_token);
	//cout << res<< endl;
	cout << status << endl;
	}
	*/

	//搜索人脸
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