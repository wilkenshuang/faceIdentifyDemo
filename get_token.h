#ifndef GET_TOKEN_H_
#define GET_TOKEN_H_
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include "base64.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

using namespace std;

int get_access_token(std::string &access_token, const std::string &AK, const std::string &SK);
int add(const std::string & base64string, std::string &json_string, std::string &json_result, const std::string &access_token);
int search(const std::string & base64string, std::string &json_result, const std::string &access_token);
void ReadJson_string(const std::string & strValue, std::string key, std::string &value);
void ReadJson_userid_string(const std::string & strValue, std::string &value);
void baiduAPI(cv::Mat & image);
#endif
