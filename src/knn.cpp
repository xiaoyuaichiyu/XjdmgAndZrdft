#include "knn.h"

knn::knn(/* args */)
{
}

knn::~knn()
{
}

int knn::calcDist( VectorXd x1,  VectorXd x2)
{
    if ( x1.rows()!=x2.rows())
        return -1;
    
    
   
    return 0;
}
 int knn::knnRun(const string trainFilename,const string testFilename, int Kpoint)
 {
    vector<vector<int>> TrainInData=GetData(trainFilename);  //处理训练集
    MatrixXf TraindataMat;           //训练集数据集的数据
    VectorXf TrainlabelMat;          //训练集数据集的标签
    VecToMatrixBin(TrainInData,TraindataMat,TrainlabelMat);

    vector<vector<int>> TestInData=GetData(testFilename);  //处理测试
    MatrixXf TestdataMat;           //测试集数据集的数据
    VectorXf TestlabelMat;          //测试集数据集的标签
    VecToMatrixBin(TestInData,TestdataMat,TestlabelMat);
    getClosest(TraindataMat,TrainlabelMat,TestdataMat,Kpoint);


    return 0;
 }
int knn::getClosest( MatrixXf TraindataMat,VectorXf TrainlabelMat,MatrixXf TestdataMat, int Kpoint)
{
    vector<int> resDistance;


    return 0;    
}