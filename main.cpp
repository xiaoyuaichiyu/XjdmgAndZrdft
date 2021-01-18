#include "include/perceptron.h"
#include "include/base.h"
#include <iostream>

int main(int argc, char **argv)
{
    Perceptron  kkk;
    kkk.PerceptronRun("Mnist/mnist_train.csv","Mnist/mnist_test.csv",50);

    MatrixXd m(2, 2);
    m<<1,2,3,4;
  
    return 0;
}
