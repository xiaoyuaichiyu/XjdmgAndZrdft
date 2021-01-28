#pragma once
#include "base.h"
//数据集：Mnist
//训练集数量：60000
//测试集数量：10000
//accuracy:0.8433
//run:24.2633 seconds.
class NaiveBayes : public Base
{
private:
    MatrixXi TraindataMat;                                    //训练集数据集的数据
    VectorXi TrainlabelVec;                                   //训练集数据集的标签
    MatrixXi TestdataMat;                                   //测试集数据集的数据
    VectorXi TestlabelMat;                                  //测试集数据集的标签
    //某种意义上可以认为是模型
    vector<double> P_y;
    vector<vector<vector<double>>> Px_y;
    //计算P（y=C_k）  Ck_count为各个类别（10种）的数量  Ck_index为每个类别，在数据集中的序号
    //返回值为各个类别（10种）的概率
    vector<double> calP_y(vector<vector<int>> &Ck_index,vector<int> &Ck_count);
    //计算P（X=a_jl|Y=C_k）
    vector<vector<vector<double>>> calPx_y(vector<vector<int>> Ck_index);
    int TrainNaiveBayes(const string trainFilename); 
    double TestNaiveBayes(const string testFilename);
public:

    int runNaiveBayes(const string trainFilename, const string testFilename);
    NaiveBayes(/* args */);
    ~NaiveBayes();
};


