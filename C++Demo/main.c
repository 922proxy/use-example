

#include <iostream>  
#include <stdio.h>
#include <string>
#include <Windows.h>

#include "curl/curl.h"

#pragma comment(lib, "libcurl.lib")

using namespace std;

static size_t write_buff_data(char* buffer, size_t size, size_t nitems, void* outstream)
{//Copy the received data to the cache
	memcpy(outstream, buffer, nitems * size);
	return nitems * size;
}
/*
Use HTTP proxy
*/
int GetUrlHTTP(char* url, char* buff)
{
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_PROXY, "http://ip:port");//Set HTTP proxy address
		curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "User name: password");//Proxy username password
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)buff);//Set Read-Write Cache
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buff_data);//Set Callback Function
		curl_easy_setopt(curl, CURLOPT_URL, url);//Set URL address
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 10L);//Sets a long integer to control how many seconds CURLOPT_LOW_SPEED_LIMIT bytes are passed
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50L);//Set a long integer to control how many bytes are transferred
		curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 2000000L);//Maximum download speed

		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (res == CURLE_OK) {
			return res;
		}
		else {
			printf("error code:%d\n", res);
			MessageBox(NULL, TEXT("Get IP Error"), TEXT("assistant"), MB_ICONINFORMATION | MB_YESNO);
		}
	}
	return res;
}
/*
Use Socks5 proxy
*/
int GetUrlSocks5(char* url, char* buff)
{
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_PROXY, "socks5://ip:port");//Set Socks5 proxy address
		curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "User name: Password");//Proxy username password
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)buff);//Set Read-Write Cache
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buff_data);//Set Callback Function
		curl_easy_setopt(curl, CURLOPT_URL, url);//Set URL address
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 10L);//Sets a long integer to control how many seconds CURLOPT_LOW_SPEED_LIMIT bytes are passed
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50L);//Set a long integer to control how many bytes are transferred;
		curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 2000000L);/*Maximum download speed*/
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (res == CURLE_OK) {
			return res;
		}
		else {
			printf("error code:%d\n", res);
			MessageBox(NULL, TEXT("Get IP Error"), TEXT("assistant"), MB_ICONINFORMATION | MB_YESNO);
		}
	}
	return res;
}
/*
Do not use proxy
*/
int GetUrl(char* url, char* buff)
{
	CURL* curl;
	CURLcode res;
	//Initialize curl library using curl Library
	curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)buff);//Set Read-Write Cache
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_buff_data);//Set Callback Function
		curl_easy_setopt(curl, CURLOPT_URL, url);//Set URL address
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 10L);//Sets a long integer to control how many seconds CURLOPT_LOW_SPEED_LIMIT bytes are passed
		curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 50L);//Set a long integer to control how many bytes are transferred
		curl_easy_setopt(curl, CURLOPT_MAX_RECV_SPEED_LARGE, 2000000L);/*Maximum download speed*/

		string testurl = url;
		std::string strHead = testurl.substr(0, 5);
		if (strHead != "https")
		{
		}
		else
		{
			curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
		}


		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (res == CURLE_OK)
		{
			return res;
		}
		else {
			printf("error code:%d\n", res);
			MessageBox(NULL, TEXT("Get IP Error"), TEXT("assistant"), MB_ICONINFORMATION | MB_YESNO);
		}
	}
	return res;
}

int func()
{
	cout << "Please enter the URL\n";
	string strUrl;
	cin >> strUrl;
	char* buff = (char*)malloc(1024 * 1024);
	memset(buff, 0, 1024 * 1024);
	//Do not use HTTP proxy
	GetUrl((char*)strUrl.c_str(), buff);
	printf("Now IP:%s\n", buff);
	//Use HTTP proxy
	memset(buff, 0, 1024 * 1024);
	GetUrlHTTP((char*)strUrl.c_str(), buff);
	printf("Http results:%s\n", buff);
	//Use Socks5 proxy
	memset(buff, 0, 1024 * 1024);
	GetUrlSocks5((char*)strUrl.c_str(), buff);
	printf("Socks5 result:%s\n", buff);
	free(buff);
	return 0;
}

int main()
{
	return func();
}
