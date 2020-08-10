#pragma once
#include<iostream>
#include<string>
using namespace std;
class Point
{
private:
	int x;
	int y;
public:
	void setPorint(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void showPoint() {
		cout << "(" << x << "," << y << ")" << endl;
	}
};

