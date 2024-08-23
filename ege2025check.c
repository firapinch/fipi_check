#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>

#define CHECK_INTERVAL_SECONDS 180

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    strcat((char *)userdata, (char *)ptr);
    return size * nmemb;
}

int check_for_string(const char *html_content, const char *search_string) {
    return strstr(html_content, search_string) != NULL;
}

int main(void) {
    CURL *curl;
    CURLcode res;
    char html_content[100000] = "";
    char search_string[] = "2025";
    int minutes_passed = 0;
    int first_run = 1;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        while (1) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://doc.fipi.ru/ege/demoversii-specifikacii-kodifikatory/");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, html_content);

            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            } else {
                if (check_for_string(html_content, search_string)) {
                    printf("Строка \"%s\" найдена в содержимом страницы.\n", search_string);
                } else {
                    printf("Строка \"%s\" не найдена в содержимом страницы.\n", search_string);
                }
            }

            memset(html_content, 0, sizeof(html_content));

            if (first_run) {
                printf("Прошло минут: %d\n", minutes_passed);
                first_run = 0;
            }

            minutes_passed += CHECK_INTERVAL_SECONDS / 60;

            sleep(CHECK_INTERVAL_SECONDS);
        }

        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Ошибка при инициализации CURL.\n");
        return 1;
    }

    curl_global_cleanup();

    return 0;
}
