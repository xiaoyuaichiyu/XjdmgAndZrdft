#pragma once
#include "base.h"
//数据集：Mnist
//训练集数量：60000
//测试集数量：10000
class knn : public Base
{
private:

    int calcDist(VectorXd x1,  VectorXd x2);
    vector<int> getClosest( MatrixXf TraindataMat,VectorXf TrainlabelMat,MatrixXf TestdataMat,int Kpoint);
    vector<float>  testTest;
    int getCategory(vector<float> distanceValueTemp,vector<float> distanceValue, int Kpoint,VectorXf TrainlabelMat);
    int calAccuracy(vector<int> CategoryVector,VectorXf TestlabelMat);
public:
    int knnRun(const string trainFilename,const string testFilename, int Kpoint);
    knn(/* args */);
    ~knn();
};

