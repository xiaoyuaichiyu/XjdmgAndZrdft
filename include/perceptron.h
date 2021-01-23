#pragma once
#include "base.h"
//数据集：Mnist
//训练集数量：60000
//测试集数量：10000
//正确率：79.43%（二分类）
//运行时长：407s




//PerceptronRun("Mnist/mnist_train.csv","Mnist/mnist_train.csv",50);  训练集  测试集  迭代次数
class Perceptron : public Base
{
private:
    VectorXd w;       //初始权重w
    double b = 0;     //偏置b为0
    float h = 0.0001; //步长，梯度下降过程中的n，控制梯度下降速率
    int PerceptronTrain(int iter,const string filename); //感知机训练
    float PerceptronTest(const string filename); //感知机训练
public:

    int PerceptronRun(const string trainFilename,const string testFilename,int iter);//感知机运行
public:
    Perceptron(/* args */);
    ~Perceptron();
};

