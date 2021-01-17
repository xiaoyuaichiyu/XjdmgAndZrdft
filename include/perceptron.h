#pragma once
#include "base.h"
//数据集：Mnist
//训练集数量：60000
//测试集数量：10000
//正确率：79.43%（二分类）
//运行时长：407s

class Perceptron : public Base
{
private:
    VectorXd w;       //初始权重w
    double b = 0;     //偏置b为0
    float h = 0.0001; //步长，梯度下降过程中的n，控制梯度下降速率
public:
    int PerceptronTrain(int iter,const string filename); //感知机训练
    float PerceptronTest(const string filename); //感知机训练
    int PerceptronRun(const string trainFilename,const string testFilename,int iter);//感知机运行
public:
    Perceptron(/* args */);
    ~Perceptron();
};

int Perceptron::PerceptronTrain(int iter,const string filename)
{
    vector<vector<int>> InData=GetData(filename);
    MatrixXf dataMat;           //数据集的数据
    VectorXf labelMat;          //数据集的标签
    VecToMatrixBin(InData,dataMat,labelMat);
    w.resize(dataMat.rows());
    for (size_t i = 0; i < w.rows(); i++) //未找到相应函数，待完善
        w(i) = 0;
    //cout<<w.head(10)<<endl;
    cout<<"开始训练，迭代次数为："<<iter<<endl;
    int testC=0;
    vector<float> testdf;
    for (size_t iterCount = 0; iterCount < iter; iterCount++) //迭代次数
    {
        cout<<"开始第"<<iterCount<<"次迭代"<<endl;
        for (size_t dataCount = 0; dataCount < dataMat.cols(); dataCount++) //样本个数
        {
            VectorXd singleData; //单个样本
            singleData.resize(dataMat.rows());
            for (size_t i = 0; i < dataMat.rows(); i++)
            {
                singleData(i) = dataMat(i, dataCount);
            }
            double lableValue = *(labelMat.data() + dataCount); //标签
            double wXi = (w.transpose() * singleData);
            double flag = (-1) * lableValue * (wXi + b);
            testdf.push_back(flag);
            if ((flag - 0) >= -0.000000001)//(flag - 0) >= -0.000000001
            {

                testC++;;
                w = w + h * lableValue * singleData;
                b = b + h * lableValue;
            }
        }
        cout << testC << endl;
    }
    cout << testC << endl;
    cout << "ddd" << b << endl;
    return 0;
}
float Perceptron::PerceptronTest(const string filename)
{
    vector<vector<int>> InData=GetData(filename);
    MatrixXf dataMat;           //测试集的数据
    VectorXf labelMat;          //测试集的标签
    VecToMatrixBin(InData,dataMat,labelMat);
    int errorCount=0;//错误样本数计数
    cout<<"开始测试"<<endl;
    for (size_t dataCount = 0; dataCount < dataMat.cols(); dataCount++)
    {
         VectorXd singleData; //单个样本
        singleData.resize(dataMat.rows());
        for (size_t i = 0; i < dataMat.rows(); i++)
        {
            singleData(i) = dataMat(i, dataCount);
        }
        double lableValue = *(labelMat.data() + dataCount); //标签
        double wXi = (w.transpose() * singleData);
        double flag = (-1) * lableValue * (wXi + b);
        if ((flag - 0) >= -0.00000000000001)
        {
          errorCount++;  
        }
    }
    float accruRate = 1 - ((float)errorCount / (float)dataMat.cols());
    cout<<"accruRate:"<<accruRate<<endl;
    return accruRate;
}
int Perceptron::PerceptronRun(const string trainFilename,const string testFilename,int iter)
{
    auto start = system_clock::now();
    this->PerceptronTrain(iter,trainFilename);
    this->PerceptronTest(testFilename);
    auto end   = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
cout<<"run" << double(duration.count()) * microseconds::period::num / microseconds::period::den << " seconds." << endl;
    return 0;
}


Perceptron::Perceptron()
{
}

Perceptron::~Perceptron()
{
}
