#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std; 

int IsNumber(string s) {
    int length = s.length();
    for (int i = 0; i < length; i++) {
        if (!isdigit(s[i])) return false;
    }
    return !s.empty();
}

void writeArrayData(int* arr, int n, string filename)
{
    ofstream fout(filename);
    fout << n << endl;
    for (int i = 0; i < n; i++)
        fout << arr[i] << " ";
    fout.close();
}

string displayOrderName(int id) {
    switch (id) {
    case 1: return "Randomize";
    case 2: return "Nearly Sorted";
    case 3: return "Sorted";
    case 4: return "Reversed";
    }
    return "not found";
}