#include "knn.h"

knn::knn(/* args */)
{
}

knn::~knn()
{
}

int knn::calcDist(VectorXd x1, VectorXd x2)
{
    if (x1.rows() != x2.rows())
        return -1;

    return 0;
}
int knn::knnRun(const string trainFilename, const string testFilename, int Kpoint)
{
    auto start = system_clock::now();
    vector<vector<int>> TrainInData = GetData(trainFilename); //处理训练集
    MatrixXf TraindataMat;                                    //训练集数据集的数据
    VectorXf TrainlabelMat;                                   //训练集数据集的标签
    VecToMatrix(TrainInData, TraindataMat, TrainlabelMat);

    vector<vector<int>> TestInData = GetData(testFilename); //处理测试
    MatrixXf TestdataMat;                                   //测试集数据集的数据
    VectorXf TestlabelMat;                                  //测试集数据集的标签
    VecToMatrix(TestInData, TestdataMat, TestlabelMat);
    vector<int> CategoryVector = getClosest(TraindataMat, TrainlabelMat, TestdataMat, Kpoint);
    calAccuracy(CategoryVector, TestlabelMat);

    auto end = system_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "run" << double(duration.count()) * microseconds::period::num / microseconds::period::den << " seconds." << endl;

    return 0;
}
vector<int> knn::getClosest(MatrixXf TraindataMatSource, VectorXf TrainlabelMat, MatrixXf TestdataMat, int Kpoint)
{
    vector<int> CategoryVector;
    CategoryVector.reserve(TestdataMat.cols());
    if (TestdataMat.rows() != 784)
        cout << "按照实际维数修改block值" << endl;
    VectorXf kk(784);
    vector<float> distanceValue;
    MatrixXf TraindataMat;
    for (size_t i = 0; i < TestdataMat.cols(); i++) //测试集样本数
    {
        if (i == 200)
            break;
        TraindataMat = TraindataMatSource;
        kk = TestdataMat.col(i);
        TraindataMat.colwise() -= kk;
        distanceValue.clear();
        distanceValue.reserve(TraindataMat.cols());
        for (size_t j = 0; j < TraindataMat.cols(); j++) //训练集样本数
        {
            float temp = TraindataMat.col(j).squaredNorm();
            distanceValue.push_back(sqrt(temp));
        }
        vector<float> distanceValueTemp;
        distanceValueTemp = distanceValue;
        nth_element(distanceValueTemp.begin(), distanceValueTemp.begin() + Kpoint, distanceValueTemp.end());
        //cout<<distanceValueTemp.at(3)<<endl;
        int Category = getCategory(distanceValueTemp, distanceValue, Kpoint, TrainlabelMat);
        CategoryVector.push_back(Category);
    }
    return CategoryVector;
}
int knn::getCategory(vector<float> distanceValueTemp, vector<float> distanceValue, int Kpoint, VectorXf TrainlabelMat)
{
    vector<int> resVec(10, 0);
    for (size_t i = 0; i < Kpoint; i++)
    {
        auto distanceValueIt = find(distanceValue.begin(), distanceValue.end(), distanceValueTemp.at(i));
        int mm = distanceValueIt - distanceValue.begin();
        //cout<<mm<<endl;
        int index = (int)*(TrainlabelMat.data() + mm);
        resVec.at(index)++;
    }
    //cout<<resVec.at(3)<<endl;
    return max_element(resVec.begin(), resVec.end()) - resVec.begin();
}
int knn::calAccuracy(vector<int> CategoryVector, VectorXf TestlabelMat)
{
    float Accur = 0;
    int errorCount = 0;

    for (size_t i = 0; i < CategoryVector.size(); i++)
    {
        if (CategoryVector.at(i) != (int)*(TestlabelMat.data() + i))
        {
            errorCount++;
        }
    }
    float accruRate = 1 - ((float)errorCount / (float)CategoryVector.size());
    cout << "正确率:" << accruRate << endl;
    return 0;
}