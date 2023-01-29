#define CURL_STATICLIB

#include <iostream>
#include <chrono>
#include <thread>
#include <cstring>
#include <string>
#include "curl/curl.h"
#include "valute.h"
#include "nlohmann/json.hpp"

using namespace std;
using namespace nlohmann;

static bool STOP_REQUEST = false;

static void get_argv(int &argc, char* argv[], string &valute_name, int &interval) {
    
    valute_name = "EUR";
    interval = 10000;
    
    if (argc < 2) {
        return;
    }

    for (int i = 1; i < argc; i++) {
        string str = argv[i];
        if (str.find("--valute=") == 0) {
            valute_name = str.substr(9);
        } else if (str.find("--interval=") == 0) {
            interval = stoi(str.substr(11))*1000;
        }
    }

    return;
}



static void parcero(string &data, string &value_pos, Valute &cur) {
    auto j = json::parse(data);
    json::json_pointer p(value_pos);

    double val = j.value(p, j.at(p));;
    cur.add_value(val);
}

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size *nmemb;
}

static void get_curl(string &valute, int &interval, Valute &cur) {
    CURL* curl = curl_easy_init();
    CURLcode response;
    string data_buffer;
    long http_code = 0;

    while(!STOP_REQUEST) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.cbr-xml-daily.ru/daily_json.js");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data_buffer);
        response = curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        if (http_code == 200 && response != CURLE_ABORTED_BY_CALLBACK) {
            parcero(data_buffer, valute, cur);
            this_thread::sleep_for(chrono::milliseconds(interval));
        } else {
            cout << "RESPONSE ERROR" << endl;
        }
        
        data_buffer.clear();    
    }

    curl_easy_cleanup(curl);
}

int main(int argc, char** argv) { 
    string valute_name;
    int interval;

    get_argv(argc, argv, valute_name, interval);
    
    Valute cur(valute_name);
    string value_pos = "/Valute/" + valute_name + "/Value";
    cout << interval << ' '<< value_pos << endl;

    thread fun_thread(get_curl, ref(value_pos), ref(interval), ref(cur));
	fun_thread.detach();

	if (cin.get() == 0)
	{
		STOP_REQUEST = true;
		fun_thread.join();
	}

    cout << "Средннее значение: " << cur.get_avarage() << std::endl << "Медиана значений: " << cur.get_mid() << endl;

    return 0;
}