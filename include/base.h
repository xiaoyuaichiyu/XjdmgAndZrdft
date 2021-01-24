#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;
using namespace chrono;
// using Eigen::MatrixXd;
// using Eigen::Matrix;
// using Eigen::VectorXd;

class Base
{
public:
//    vector<vector<int>> InData; //从文件读取的数据存放于此
    // MatrixXf dataMat;           //数据集的数据
    // VectorXf labelMat;          //数据集的标签

    vector<vector<int>> GetData(const string filename); //csv转换成InData
    int VecToMatrixBin(vector<vector<int>> InData,MatrixXf &dataMat,VectorXf &labelMat);       //将vector转换成矩阵，并将标签进行二分类,数据进行归一化
    int VecToMatrix(vector<vector<int>> InData,MatrixXf &dataMat,VectorXf &labelMat);            //将vector转换成矩阵
    //int stest(int m);
public:
    Base(){};
    ~Base(){};
};

