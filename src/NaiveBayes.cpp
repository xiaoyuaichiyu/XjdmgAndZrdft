#include "NaiveBayes.h"

NaiveBayes::NaiveBayes(/* args */)
{
}

NaiveBayes::~NaiveBayes()
{
}
vector<double> NaiveBayes::calP_y(vector<vector<int>> &Ck_index, vector<int> &Ck_count)
{
   vector<double> VecP_y;
   for (size_t i = 0; i < TrainlabelVec.rows(); i++)
   {
      int temp = TrainlabelVec(i);
      Ck_count.at(temp)++;
      Ck_index.at(temp).push_back(i);
   }
   for (size_t i = 0; i < Ck_count.size(); i++)
   {
      double tempP_y = ((double)Ck_count.at(i) + 1) / ((double)TrainlabelVec.rows() + Ck_count.size()); //原因见原书第四章公式4.11
      VecP_y.push_back(log(tempP_y));
   }
   return VecP_y;
}
vector<vector<vector<double>>> NaiveBayes::calPx_y(vector<vector<int>> Ck_index)
{
   vector<vector<int>> Px_yVal(10, vector<int>(784, 0));

   for (size_t category = 0; category < Ck_index.size(); category++)
   {
      for (size_t index = 0; index < Ck_index.at(category).size(); index++)
      {
         for (size_t dime = 0; dime < 784; dime++)
         {
            //cout<<TraindataMat(dime,Ck_index.at(category).at(index))<<endl;
            //int mm=TraindataMat(dime,Ck_index.at(category).at(index));
            if (TraindataMat(dime, Ck_index.at(category).at(index)) == 1)
            {
               Px_yVal.at(category).at(dime)++;
            }
         }
      }
   }
   //vector<vector<double>> Px_y(10,vector<double>(784,0));
   vector<vector<vector<double>>> Px_y(10, vector<vector<double>>(784, vector<double>(2, 0)));
   //tianwen(m,vector< vector<int> >(n,vector<int>(p,1)))
   for (size_t category = 0; category < 10; category++)
   {
      for (size_t dime = 0; dime < 784; dime++)
      {
         Px_y.at(category).at(dime).at(0) = //原因见4.2.3贝叶斯估计 公式4.10
             log((double)(Ck_index.at(category).size() - Px_yVal.at(category).at(dime) + 1) / (double)(Ck_index.at(category).size() + 2));

         Px_y.at(category).at(dime).at(1) = //原因见4.2.3贝叶斯估计 公式4.10
             log((double)(Px_yVal.at(category).at(dime) + 1) / (double)(Ck_index.at(category).size() + 2));
      }
   }
   return Px_y;
}
int NaiveBayes::TrainNaiveBayes(const string trainFilename)
{
   vector<vector<int>> TrainInData = GetData(trainFilename); //处理训练集
   VecToMatrixDatabin(TrainInData, TraindataMat, TrainlabelVec);

   vector<vector<int>> Ck_index(10);
   Ck_index.reserve(70000);
   vector<int> Ck_count(10, 0);

   P_y = calP_y(Ck_index, Ck_count);
   Px_y = calPx_y(Ck_index);

   return 0;
}
double NaiveBayes::TestNaiveBayes(const string testFilename)
{
   int errorCount = 0;
   vector<vector<int>> TestInData = GetData(testFilename); //处理测试
   VecToMatrixDatabin(TestInData, TestdataMat, TestlabelMat);
   vector<double> grade(10, 0);
   for (size_t count = 0; count < TestlabelMat.rows(); count++) //测试样例数目
   {
      grade = P_y;
      for (size_t category = 0; category < 10; category++) //10 类
      {
         for (size_t dime = 0; dime < 784; dime++)
         {
            if (TestdataMat(dime, count) == 1)
               grade.at(category) += Px_y.at(category).at(dime).at(1);
            else
               grade.at(category) += Px_y.at(category).at(dime).at(0);
         }
      }
      int maxindex = max_element(grade.begin(), grade.end()) - grade.begin();
      if (maxindex != TestlabelMat(count))
      {
         errorCount++;
      }
   }
   double accuracy = 1 - (double)errorCount / (double)TestlabelMat.rows();
   return accuracy;
}
int NaiveBayes::runNaiveBayes(const string trainFilename, const string testFilename)
{
   auto start = system_clock::now();
   TrainNaiveBayes(trainFilename);
   double accuracy = TestNaiveBayes(testFilename);
   cout <<"accuracy" <<accuracy << endl;
   auto end = system_clock::now();
   auto duration = duration_cast<microseconds>(end - start);
   cout << "run" << double(duration.count()) * microseconds::period::num / microseconds::period::den << " seconds." << endl;
   return 0;
}