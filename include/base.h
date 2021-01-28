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
    //将vector转换成矩阵，并将标签进行二分类,数据进行归一化
    int VecToMatrixBin(vector<vector<int>> InData,MatrixXf &dataMat,VectorXf &labelMat);    
    //将vector转换成矩阵   
    int VecToMatrix(vector<vector<int>> InData,MatrixXf &dataMat,VectorXf &labelMat);  
    //对特征进行二值处理。主要目的：简化模型，减少每个特征的可选值，否则得到同样的准确率，需要更多的数据            
    int VecToMatrixDatabin(vector<vector<int>> InData,MatrixXi &dataMat,VectorXi &labelMat);            
public:
    Base(){};
    ~Base(){};
};

