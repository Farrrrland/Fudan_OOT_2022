#include "draw.hpp"
#include <dirent.h>
#include <sys/types.h>
#include <cstdio>
#include <vector>
#include <cstring>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

bool endsWith(const string& str, const string& end) {
    int n = str.length();
    int m = end.length();
    if (n < m) {
        return false;
    }
    for (int i = 0; i < m; i++) {
        if (str[n - m + i] != end[i]) {
            return false;
        }
    }
    return true;
}

void getFiles(string path, vector<string>& filenames) {
    DIR* directory;
    struct dirent* ptr;
    if (!(directory = opendir(path.c_str()))) {
        cout << "Folder doesn't Exist!"<<endl;
        return;
    }
    while ((ptr = readdir(directory)) != 0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0) {
            filenames.push_back(path + "/" + ptr->d_name);
        }
    }
    closedir(directory);
}

int main() {
    vector<string> files;
    getFiles(".", files);
    sort(files.begin(), files.end());
    for (int i = 0, size = files.size() - 1; i < size; i++) {
        string input = files[i];
        string output = files[i + 1];
        int n = input.size(), m = output.size();
        // validate test files 
        if ((!endsWith(input, ".txt") || !endsWith(output, ".txt"))
           ||(!endsWith(output.substr(0, m - 4), "_result"))
           ||(input.substr(0, n - 4) != output.substr(0, m - 11))) {
            continue;
        }
        // configure colors
        int color = 0;
        if (endsWith(input.substr(0, n - 4), "-g2")) {
            color = 2;
        } else if (endsWith(input.substr(0, n - 4), "-g256")) {
            color = 256;
        } else {
            continue;
        }
        // configure params and temp file to store middle results
        string tmp_file = "tmp.txt";
        FILE* tmp = freopen(tmp_file.c_str(), "w", stdout);
        const char* cmd[4] = {"draw", "-g", to_string(color).c_str(), input.c_str()};
        run(4, (char**)cmd);
        fclose(tmp);
        // compare with standard
        ifstream outputStream;
        string str1, str2;
        outputStream.open(output);
        while(!outputStream.eof()) {
            str1 += outputStream.get();
        }
        outputStream.close();
        outputStream.open(tmp_file);
        while(!outputStream.eof()) {
            str2 += outputStream.get();
        }
        outputStream.close();
        remove(tmp_file.c_str());
        if (str1 != str2) {
            FILE* fail_file = freopen("test.failure", "w", stdout);
            cout << cmd[0] << " "  << cmd[1] << " " << cmd[2] << " " << cmd[3] << " " << endl;
            cout << "------- Wrong Output of " << input <<" -------" << endl;
            cout << str2 << endl;
            cout << "------- Standard Output -------" << endl;
            cout << str1 << endl;
            fclose(fail_file);
            return 0;
        }
    }
    fclose(stdout);
    fprintf(stderr, "OK");
    return 0;
}