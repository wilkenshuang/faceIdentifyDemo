#include "get_token.h"

//std::string access_token_result;
std::string add_result;
std::string search_result;

static size_t callback(void *ptr, size_t size, size_t nmemb, void *stream) {
	// 获取到的body存放在ptr中，先将其转换为string格式
	string s((char *)ptr, size * nmemb);
	// 开始获取json中的access token项目
	Json::Reader reader;
	Json::Value root;
	// 使用boost库解析json
	reader.parse(s, root);
	std::string* access_token_result = static_cast<string*>(stream);
	*access_token_result = root["access_token"].asString();
	return size * nmemb;
}

int get_access_token(string &access_token, const string &AK, const string &SK) {
	CURL *curl;
	CURLcode result_code;
	const string access_token_url = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials";
	int error_code = 0;
	curl = curl_easy_init();
	if (curl) {
		string url = access_token_url + "&client_id=" + AK + "&client_secret=" + SK;
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
		string access_token_result;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &access_token_result);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
		result_code = curl_easy_perform(curl);
		if (result_code != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(result_code));
			return 1;
		}
		access_token = access_token_result;
		curl_easy_cleanup(curl);
		error_code = 0;
	}
	else {
		fprintf(stderr, "curl_easy_init() failed.");
		error_code = 1;
	}
	return error_code;
}

static size_t callback_add(void *ptr, size_t size, size_t nmemb, void *stream) {
	// 获取到的body存放在ptr中，先将其转换为string格式
	std::string s((char *)ptr, size * nmemb);
	add_result = std::string((char *)ptr, size * nmemb);
	Json::Reader reader;
	Json::Value root;
	reader.parse(s, root);
	std::string* detailed_result = static_cast<string*>(stream);
	*detailed_result =root["error_msg"].asString();
	return size * nmemb;
}

int add(const string & base64string, std::string &json_string,std::string &json_result, const std::string &access_token) {
	const static std::string request_url = "https://aip.baidubce.com/rest/2.0/face/v3/faceset/user/add";
	std::string url = request_url + "?access_token=" + access_token;
	CURL *curl = NULL;
	CURLcode result_code;
	int is_success;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_httppost *post = NULL;
		curl_httppost *last = NULL;
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "image", CURLFORM_COPYCONTENTS, base64string.data(), CURLFORM_END);
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "image_type", CURLFORM_COPYCONTENTS, "BASE64", CURLFORM_END);
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "group_id", CURLFORM_COPYCONTENTS, "aikq_test", CURLFORM_END);
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "user_id", CURLFORM_COPYCONTENTS, "test", CURLFORM_END);
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
		string detailed_result;
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &detailed_result);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_add);
		result_code = curl_easy_perform(curl);
		if (result_code != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(result_code));
			is_success = 1;
			return is_success;
		}
		json_string = add_result;
		json_result = detailed_result;
		curl_easy_cleanup(curl);
		is_success = 0;
	}
	else {
		fprintf(stderr, "curl_easy_init() failed.");
		is_success = 1;
	}
	return is_success;
}

static size_t callback_search(void *ptr, size_t size, size_t nmemb, void *stream) {
	// 获取到的body存放在ptr中，先将其转换为string格式
	search_result = std::string((char *)ptr, size * nmemb);
	return size * nmemb;
}

int search(const string & base64string, std::string &json_result,const std::string &access_token)
{
	const static std::string request_url = "https://aip.baidubce.com/rest/2.0/face/v3/search";
	std::string url = request_url + "?access_token=" + access_token;
	CURL *curl = NULL;
	CURLcode result_code;
	int is_success;
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url.data());
		curl_easy_setopt(curl, CURLOPT_POST, 1);
		curl_httppost *post = NULL;
		curl_httppost *last = NULL;
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "image", CURLFORM_COPYCONTENTS, base64string.data(), CURLFORM_END);
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "image_type", CURLFORM_COPYCONTENTS, "BASE64", CURLFORM_END);
		curl_formadd(&post, &last, CURLFORM_COPYNAME, "group_id_list", CURLFORM_COPYCONTENTS, "aikq_test", CURLFORM_END);
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result_status);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &search_result);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback_search);
		result_code = curl_easy_perform(curl);
		if (result_code != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
				curl_easy_strerror(result_code));
			is_success = 1;
			return is_success;
		}
		//json_status = result_status;
		json_result = search_result;
		curl_easy_cleanup(curl);
		is_success = 0;
	}
	else {
		fprintf(stderr, "curl_easy_init() failed.");
		is_success = 1;
	}
	return is_success;
}

void ReadJson_string(const std::string & strValue, std::string key, std::string &value)
{
	Json::Reader reader;
	Json::Value  root;
	if (reader.parse(strValue, root))
	{
		value = root[key].asString();
	}
}

void ReadJson_userid_string(const std::string & strValue, std::string &value)
{
	Json::Reader reader;
	Json::Value  root;
	if (reader.parse(strValue, root))
	{
		value = root["result"]["user_list"][(uint)0]["user_id"].asString();;
	}
}

void ReadJson_userscore_string(const std::string & strValue, int &value)
{
	Json::Reader reader;
	Json::Value  root;
	if (reader.parse(strValue, root))
	{
		value = root["result"]["user_list"][(uint)0]["score"].asDouble();
	}
}

void baiduAPI(cv::Mat & image) {
	vector<uchar> vecImg;
	vector<int> vecCompression_params;
	vector<uchar> vectest;
	vecCompression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	vecCompression_params.push_back(100);
	cv::imencode(".jpg", image, vecImg, vecCompression_params);
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
	int score;
	if (tokNum == 0) {
		search(base64Img, res, access_token);
		ReadJson_string(res, "error_msg", status);
		if (status == "SUCCESS") {
			ReadJson_userscore_string(res, score);
			if (score >= 70) {
				ReadJson_userid_string(res, user_id);
				cout << user_id << endl;
			}
			else
				cout << "Visitor" << endl;
		}
		else
		{
			cout << "Visitor" << endl;
		}
	}
}