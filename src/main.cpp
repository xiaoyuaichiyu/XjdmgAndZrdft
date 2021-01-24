#include "perceptron.h"
#include "knn.h"

int main(int argc, char **argv)
{
    //Perceptron oo;
    //oo.PerceptronRun("Mnist/mnist_train.csv","Mnist/mnist_train.csv",50);
    knn kkk;
    kkk.knnRun("Mnist/mnist_train.csv","Mnist/mnist_test.csv",25);
  //  kkk.calcDist(5, 5);
    cout << "fff" << endl;
    return 0;
}
