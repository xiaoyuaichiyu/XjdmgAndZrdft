
#include "../include/base.h"
vector<vector<int>> Base::GetData(const string filename)
{
    cout << "开始将ector导入矩阵" << endl;
    cout << "开始读取数据集" << filename << endl;
    vector<vector<int>> InData;
    if (filename.empty())
        return InData;
    if (filename == "Mnist/mnist_test.csv") //针对数据集占用空间进行优化
    {
        InData.reserve(784 * 11000);
    }
    if (filename == "Mnist/mnist_train.csv") //针对数据集占用空间进行优化
    {
        InData.reserve(784 * 61000);
    }
    vector<int> Data;
    int onepoint;
    string line;
    InData.clear();
    ifstream inCsv(filename);
    cout << "开始读取" << filename << "数据" << endl;
    int j = 0;
    while (!inCsv.eof())
    {
        j++;
        //if (j == 500)break;         //暂取999
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
int Base::VecToMatrixBin(vector<vector<int>> InData, MatrixXf &dataMat, VectorXf &labelMat)
{
    cout << "开始将ector导入矩阵，二值" << endl;
    int colData = InData.size();
    int rowData = InData.at(0).size() - 1;
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
            dataMat(i - 1, j) = (double)InData.at(j).at(i) / 255;
        }
    }
    //cout<<labelMat.topRows(15)<<endl;
    //InData.~vector();
    cout << "dataMat：" << dataMat.rows() << "*" << dataMat.cols() << endl;
    cout << "二分类labelMat：" << labelMat.rows() << endl;
    return 0;
}
int Base::VecToMatrix(vector<vector<int>> InData, MatrixXf &dataMat, VectorXf &labelMat)
{
    int colData = InData.size();
    int rowData = InData.at(0).size() - 1;
    //dataArr.resize
    dataMat.resize(rowData, colData);

    int rowLabel = InData.size();
    labelMat.resize(rowLabel);

    //dataMat. row(0)= VectorXf::Map(&InData[0][0],InData.at(0).size());//转化成矩阵  ??? 不支持？？？
    for (size_t j = 0; j < InData.size(); j++)
    {
        for (size_t i = 0; i < InData.at(j).size(); i++)
        {
            if (i == 0)
            {
                labelMat(j) = InData.at(j).at(i);
                continue;
            }
            dataMat(i - 1, j) = (double)InData.at(j).at(i);
        }
    }
    //InData.~vector();
    cout << "dataMat：" << dataMat.rows() << "*" << dataMat.cols() << endl;
    cout << "labelMat：" << labelMat.rows() << endl;
    return 0;
}
int Base::VecToMatrixDatabin(vector<vector<int>> InData, MatrixXi &dataMat, VectorXi &labelMat)
{
    //Map<MatrixXi> mf((InData.at(0)).data(), rowData, colData);//利用c风格指针直接倒入matrix
    int colData = InData.size();
    int rowData = InData.at(0).size() - 1;
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
            if (InData.at(j).at(i)>128)
                dataMat(i - 1, j)=1;
            else
                dataMat(i - 1, j)=0;
        }
    }
    cout << "dataMat：" << dataMat.rows() << "*" << dataMat.cols() << endl;
    cout << "labelMat：" << labelMat.rows() << endl;
    return 0;
}
