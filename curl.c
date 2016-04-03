#include <stdio.h>
#include <curl/curl.h>
#include "curl.h"
#define ACCEPT "Accept: application/json"
#define CONTENT_TYPE "Content-Type: application/json"
#define CHARSET "charsets: utf-8"

int curl(const char *url, const char *method, const char *postfield, const char *header){
	CURL *curl;
	CURLcode res;
    long http_code = 0;
    char *aux = "";

	struct curl_slist *headers=NULL;

	curl = curl_easy_init();
	if(curl) {
		headers = curl_slist_append(headers, ACCEPT);
		headers = curl_slist_append(headers, CONTENT_TYPE);
		headers = curl_slist_append(headers, CHARSET);
        if(header && *header != '\0') 
            headers = curl_slist_append(headers, header);
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS,postfield);
        if(!strcmp(method,"POST"))
            curl_easy_setopt(curl, CURLOPT_POST, 1);
        if(!strcmp(method,"PUT"))
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        printf("HTTP_CODE: %ld\n\n", http_code);

		/* Check for errors */ 
		if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
	return 0;
}

