//
//  Image.h
//  OpenCV
//
//  Created by Daniil Vinogradov on 03.01.17.
//  Copyright © 2017 noname. All rights reserved.
//

#ifndef Image_h
#define Image_h
#include <iostream>
#include <fstream>

using namespace std;

const vector<string> explode(const string& s, const char& c)
{
    string buff{""};
    vector<string> v;
    
    for(auto n:s)
    {
        if(n != c) buff+=n; else
            if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);
    
    return v;
}

class Image{
    int* img;
    int mx;
    int my;
public:
    Image(){
        img = NULL;
        mx = 0;
        my = 0;
    }
    Image(int tmx, int tmy){
        img = new int[tmx*tmy];
        mx = tmx;
        my = tmy;
    }
    
    Image(Image const &_img){
        mx = _img.mx;
        my = _img.my;
        img = new int[mx * my];
        for (int i = 0; i < _img.mx; i++){
            for (int j = 0; j < _img.my; j++){
                img[(j*i)+i] = _img.img[(j*i)+i];
            }
        }
    }
    
    int getMx() { return mx; }
    int gerMy() { return my; }
    
    void load(char* fname){
        std::ifstream file(fname);
        if (!file.is_open()) // если файл не открыт
            std::cout << "Файл не может быть открыт!\n";
        
        std::string str = "";
        
        std::string str1;
        std::getline(file, str1);
        if (str1 != "P2"){
            cout << "Некорректный файл" << endl;
            return;
        }
        std::getline(file, str1);
        std::getline(file, str1);
        vector<string> v{explode(str1, ' ')};
        mx = stoi(v[0]);
        my = stoi(v[1]);
        img = new int[mx*my];
        std::getline(file, str1);
        
        int i = 0;
        while(file) {
            std::string str1;
            std::getline(file, str1);
            vector<string> v{explode(str1, ' ')};
            for(auto n:v){ img[i] = stoi(n); i++;}
        }
        
    }
    
    Image& operator=(const Image& src){
        return *new Image(src);
    }
    
    void show(){
        for (int i = 0; i < my; i++) {
            for (int j = 0; j < mx; j++)
            {
                cout << get(i, j) << " ";
            }
            cout << endl;
        }
    }
    void init(){
        for (int i = 0; i<my; i++)
            for (int j = 0; j < mx; j++)
            {
                set(i,j,0);
            }
    }
    void set(int y, int x, int c){
        img[mx*y + x] = c;
    }
    int get(int y, int x){
        return img[mx*y + x];
    }
};

#endif /* Image_h */
