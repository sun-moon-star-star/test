/**
 * @file http_test.h
 * @author sun-moon-star-star
 */

#include <sstream>
#include <string>

#include "json/json.h" // jsoncpp
#include "curl/curl.h" // libcurl

namespace test {

namespace http {

class http_helper {
    public:
    typedef size_t(*CURL_WRITEFUNCTION_PTR)(void*, size_t, size_t, void*);

    http_helper(const std::string& url):url(url){};

    int post_json(const std::string& post_fields, std::string* resp) {
        CURL *curl = curl_easy_init();
        if (curl == NULL)
        {
            return -1;
        }

        // 设置url
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        // 允许重定向
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        // HTTP报文头
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers,
                    "Content-Type:application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // 设置为非0表示本次操作为POST
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        // 设置要POST的JSON数据
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());
        // 设置上传json串长度,这个设置可以忽略
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, post_fields.size());
        
        // 设置接收数据的处理函数和存放变量
        std::stringstream out;
        auto write_func = [](void *ptr, size_t size, size_t nmemb, void *stream) -> size_t{
            std::string data((const char*) ptr, (size_t) size * nmemb);
            *((std::stringstream*) stream) << data;
            return size * nmemb;
        };
        // 设置回调函数
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, 
            static_cast<CURL_WRITEFUNCTION_PTR>(write_func));
        // 设置写数据
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

        // 执行
        CURLcode res = curl_easy_perform(curl);
        long res_code = 0;
        res = curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &res_code);

        // 释放资源
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        // 检查返回值
        if (res != CURLE_OK || (res_code != 200 && res_code != 201)) {
            return -1;
        }

        // 获取请求结果
        *resp = out.str();
        return 0;
    }

    private:
    std::string url;
};

} // namespace http

} // namespace test

int main() {
    return 0;
}
