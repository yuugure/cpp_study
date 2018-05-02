
#include <iostream>
#include <string>
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(void)
{
  CURL *curl;
  // ハンドラの初期化(セッション開始）
  curl = curl_easy_init();
  if(curl) {
    CURLcode res;
    std::string readBuffer;
    // curl 実行オプション設定 (実際まだリクエストしていない状態)
    curl_easy_setopt(curl, CURLOPT_URL, "http://www.starbucks.co.jp/");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    // 設定したオプションでリクエスト
    res = curl_easy_perform(curl);
    // セッション終了
    curl_easy_cleanup(curl);
    std::cout << readBuffer << std::endl;
  }
  return 0;
}