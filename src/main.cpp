#include "perceptron.h"
#include "knn.h"

#include "NaiveBayes.h"

int main(int argc, char **argv)
{
    NaiveBayes nnn;
    nnn.runNaiveBayes("Mnist/mnist_train.csv","Mnist/mnist_test.csv");


    //Perceptron oo;
    //oo.PerceptronRun("Mnist/mnist_train.csv","Mnist/mnist_train.csv",50);
    // knn kkk;
    // kkk.knnRun("Mnist/mnist_train.csv","Mnist/mnist_test.csv",25);
  //  kkk.calcDist(5, 5);

    return 0;  
}
