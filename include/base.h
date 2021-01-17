#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>
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
    int VecToMatrixBin(vector<vector<int>> InData,MatrixXf &dataMat,VectorXf &labelMat);       //将vector转换成矩阵，并将标签进行二分类
    int VecToMatrix(vector<vector<int>> InData,MatrixXf &dataMat,VectorXf &labelMat);            //将vector转换成矩阵
    //int stest(int m);
public:
    Base(){};
    ~Base(){};
};

vector<vector<int>> Base::GetData(const string filename)
{
    vector<vector<int>> InData;
    if (filename == "Mnist/mnist_test.csv") //针对数据集占用空间进行优化
    {
        InData.reserve(11000);
    }
    if (filename == "Mnist/mnist_train.csv") //针对数据集占用空间进行优化
    {
        InData.reserve(61000);
    }
    vector<int> Data;
    int onepoint;
    string line;
    InData.clear();
    ifstream inCsv(filename);
    cout << "开始读取" << filename << "数据" << endl;
    int j=0;
    while (!inCsv.eof())
    {
        j++;
        //if (j==500)break;//暂取999
        Data.reserve(785); //针对数据集维数占用空间进行优化
        getline(inCsv, line);
        if (line.empty())
            continue;
        char checkChar;
        string StrVal;
        istringstream stringin(line);
        for (size_t i = 0; i < line.size(); i++)
        {
            stringin >> checkChar;
            if (checkChar == ',')
            {
                int intStr = atoi(StrVal.c_str());
                StrVal.clear();
                Data.push_back(intStr);
                continue;
            }
            StrVal.push_back(checkChar);
            if (i == (line.size() - 1))
            {
                int intStr = atoi(StrVal.c_str());
                Data.push_back(intStr);
                continue;
            }
        }
        InData.push_back(Data);
        Data.clear();
    }
    cout << "InData数据容量为：" << InData.size() << endl;
    cout << "数据维数" << InData.at(0).size() << endl;
    return InData;
}
int Base::VecToMatrixBin(vector<vector<int>> InData,MatrixXf &dataMat,VectorXf &labelMat)
{
    cout<<"开始将ector导入矩阵，二值"<<endl;
    int colData = InData.size();
    int rowData= InData.at(0).size() - 1;
    //dataArr.resize
    dataMat.resize(rowData, colData);

    int rowLabel = InData.size();
    labelMat.resize(rowLabel);
    for (size_t j = 0; j < InData.size(); j++)
    {   
        for (size_t i = 0; i < InData.at(j).size(); i++)
        {
            if (i == 0)
            {
                if (InData.at(j).at(i) < 5)
                    labelMat(j) = -1;
                else
                    labelMat(j) = 1;
                continue;
            }
            dataMat( i - 1,j) = (double)InData.at(j).at(i)/255;
        }
    }
    //cout<<labelMat.topRows(15)<<endl;
    cout << "dataMat：" << dataMat.rows() << "*" << dataMat.cols() << endl;
    cout << "二分类labelMat：" << labelMat.rows() << endl;
    return 0;
}
int Base::VecToMatrix(vector<vector<int>> InData,MatrixXf &dataMat,VectorXf &labelMat)
{
    int  colData= InData.size();
    int  rowData= InData.at(0).size() - 1;
    //dataArr.resize
    dataMat.resize(rowData, colData);

    int rowLabel = InData.size();
    labelMat.resize(rowLabel);
    for (size_t j = 0; j < InData.size(); j++)
    {
        for (size_t i = 0; i < InData.at(j).size(); i++)
        {
            if (i == 0)
            {
                labelMat(j) = InData.at(j).at(i);
                continue;
            }
            dataMat( i - 1,j) = (double)InData.at(j).at(i)/255;
        }
    }
    cout << "dataMat：" << dataMat.rows() << "*" << dataMat.cols() << endl;
    cout << "labelMat：" << labelMat.rows() << endl;
    return 0;
}
