#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "../include/canvas.h"
#include "../include/coordinate.h"
using namespace std;
int main(int argc, char*argv[])
{
	Canvas *object = Canvas::getInstance();
    cout << object << endl;
    vector<vector<int>> res = object->getData();
    for (const auto & v : res) {
        for (const auto & i : v) {
            cout << i << " ";
        }
        cout << endl;
    }
    Coordinate coor = Coordinate(0, 0);
    object->setData(coor, 5);
    // cout << ptr << " " << *ptr << endl;
    cout << endl;
    Canvas *obj2 = Canvas::getInstance();
    // cout << ptr << " " << *ptr << endl;
    cout << obj2 << endl;
    vector<vector<int>> res2 = object->getData();
    for (const auto & v : res2) {
        for (const auto & i : v) {
            cout << i << " ";
        }
        cout << endl;
    }
    // cout << ptr << " " << *ptr << endl;
	return 0;
}