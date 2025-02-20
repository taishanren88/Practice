#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <vector>
#include <cassert>
#include <fstream>
#include <curl/curl.h>


// Loop through input
// Check URL is in cache
// If not insert in the cache
// During insertion, if current size exceeds capacity
// evict form front of cache until enough size
// maintain a map of urls to  iterator of images
// Maintain a list of images
using namespace std;

struct Image {

    std::string url;
    vector<unsigned char> data;
};


class LRUCache {
public:
    LRUCache(int capacity)
    : m_capacity(capacity), m_size(0) { }

    bool get(string key, Image& oImage) {
        if (m_map.find(key) == m_map.end())
            return false;
        else {
            // move the image to the front of the list
            m_imageOrdering.splice(m_imageOrdering.begin(), m_imageOrdering, m_map[key]);
            oImage = m_imageOrdering.front();
            return true;
        }
    }

    bool put( Image& image) {
        auto key = image.url;
        if (m_map.find(key) != m_map.end())
        {
            // if url already exists, jsut return
            get(key, image);
            return true;
        }

        if (m_capacity < image.data.size()) // edge case - if image doesn't fit anyways
            return false;

        const auto requiredSize = image.data.size();
        const auto remainingSize = m_capacity - m_size;
        auto removed = 0;
        while ( ((remainingSize - removed) < requiredSize)
                &&
                !m_imageOrdering.empty()) {
            auto currSize = m_imageOrdering.back().data.size();
            m_map.erase(m_imageOrdering.back().url);

            m_imageOrdering.pop_back();
            removed += currSize;
        }

        m_imageOrdering.push_front(image);
        m_map[image.url] = m_imageOrdering.begin();
        m_size = m_size - removed + image.data.size();
        return true;
    }

    int getSize() const {
        return m_size;
    }

    // Test Method
    Image getFrontKey() const {
        if (m_imageOrdering.empty())
            return Image();

        return  m_imageOrdering.front();
    }

    private:
    const int m_capacity;
    int m_size;
    unordered_map<std::string, std::list<Image>::iterator> m_map;
    list<Image> m_imageOrdering;
};

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        auto vecPtr = ((std::vector<unsigned char>*)userp);
        for (int i = 0; i < size * nmemb; i++ ) {
            vecPtr->push_back(*((unsigned char*)contents + i));
        }
        return size * nmemb;
}
static bool debug = false;
Image fetchUrl(string url) {
    static unordered_map<string, vector<unsigned char>> mockData = {
        {"www.a.com", vector<unsigned char>(93606, '\0')},
        {"www.b.com", vector<unsigned char>(317908, '\0')}
    };
    Image image;

    if (debug) {
        image.data = mockData[url];
        image.url = url;
        return image;
    } else {
        // really fetch images from internet.
                 Image oImage;

        string outfilename = url.substr(url.rfind('/') + 1);
        CURL *curl = curl_easy_init();
        if (curl)
        {

            printf("Trying to fetch...%s\n", outfilename.c_str());
              FILE *fp = fopen(outfilename.c_str(),"wb");
              if (fp ) {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

                vector<unsigned char> imageData;
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) &imageData);
                cout << "HERE" << endl;
                 CURLcode res = curl_easy_perform(curl);
                curl_easy_cleanup(curl);

                 oImage.url = url;
                 oImage.data = imageData;

                 // testing
                  ofstream myfile("example_" + outfilename, ios::out | ios::binary);
                  myfile.write(( char*)oImage.data.data(), oImage.data.size());
                  printf(" Image size :%d", (int) oImage.data.size());
                  myfile.close();
             fclose(fp);
            }
            return oImage;
        }
    // Clean up the resources
    }
    return image;
}

void execute(string inputFile) {
  ifstream myfile (inputFile);
  if (myfile.is_open()) {

        string firstLine, secondLine;
        getline(myfile, firstLine);
        getline(myfile, secondLine);
        vector<string> urls;
        int numLines = atoi(secondLine.c_str());
        for (int i = 0; i < numLines; i++) {
            string url;
            getline(myfile, url);
            urls.push_back(url);
        }
        const auto capacity = atoi(firstLine.c_str());
        LRUCache mycache(capacity);
        for (auto& url : urls) {
            Image oImage;
            if (mycache.get(url, oImage)) {
                printf("%s IN_CACHE :%lu\n", url.c_str(), oImage.data.size());
            }
            else {
                auto image = fetchUrl(url);
                mycache.put(image);
                mycache.get(url, oImage);
                printf("%s DOWNLOADED :%lu\n", url.c_str(), oImage.data.size());
            }
        }

  }
}
int main() {
    LRUCache images(30);
    Image one, two, three;
    one.url = "www.yahoo.com";
    one.data = vector<unsigned char>(10, '\0');

    two.url = "www.google.com";
    two.data = vector<unsigned char>(20, '\0');
    images.put(one);

    assert(images.getFrontKey().url == one.url);
    assert(images.getSize() == 10);

    images.put(two);
    assert(images.getFrontKey().url == two.url && images.getFrontKey().data.size() == 20);
    assert(images.getSize() == 30);
    Image oImage;
    assert(images.get(two.url, oImage) && oImage.url == two.url);
    three.url = "www.a.com";
    three.data = vector<unsigned char> (5, '\0');
    images.put(three);
    assert(images.getSize() == 25);
    assert(images.getFrontKey().url == "www.a.com");
    assert(!images.get(one.url, oImage));
    assert(images.get(two.url, oImage) && oImage.url == two.url && images.getFrontKey().url == two.url);
    assert(images.get(three.url, oImage)  && oImage.url == three.url && images.getFrontKey().url == three.url);

    execute("image_cache_input.txt");
}