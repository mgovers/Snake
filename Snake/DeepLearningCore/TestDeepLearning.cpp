// TestDeepLearning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>

#include <Eigen/Dense>

#include "Network.h"
#include "FullyConnectedLayer.h"

#include "QuadraticLossFunction.h"
#include "CrossEntropyLossFunction.h"

/// <summary> Test setting up the network.</summary>
void testSetup()
{
  Network nn = Network();
  nn.push_back(new FullyConnectedLayer(10, 5));
  nn.push_back(new FullyConnectedLayer(5, 2));
}

/// <summary> Test a simple feedforward input.</summary>
void testInput()
{
  // Setup network
  Network nn = Network();
  nn.push_back(new FullyConnectedLayer(10, 5));
  nn.push_back(new FullyConnectedLayer(5, 2));

  // Test an input

  Eigen::VectorXd input = Eigen::VectorXd(10).setZero();
  input(0) = 1;
  Eigen::VectorXd label = Eigen::VectorXd(2).setZero();
  label(0) = 1;

  Eigen::MatrixXd output = nn.feedForward(input);
  //std::cout << "Input:\n" << input << std::endl;
  //std::cout << "Output:\n" << output << std::endl;
}

/// <summary> Test the training and evaluation of a simple classification network.</summary>
void testClassification()
{
  // Settings
  // todo configurable
  
  const int nInputs = 10;

  const int nEpisodes = 100;
  const int nTests = 100;

  /*
        SETUP
   */

  // Setup the network
  Network nn = Network();
  nn.push_back(new FullyConnectedLayer(nInputs, 5));
  nn.push_back(new FullyConnectedLayer(5, 2, FullyConnectedLayer::Softmax));

  nn.setLearningRate(0.1);

  /* Learn a simple behavior:
   *
   * One-of-n input: 
   *  if <5 :  output = 0
   *  else  :  output = 1
   *
   */


  /*
      TRAIN
  */

  std::cout << "Training...";

  // TEST
  auto input = Eigen::VectorXd(nInputs).setZero();
  input(0) = 1;
  auto label = Eigen::VectorXd(2).setZero();
  label(0) = 1;

  nn.feedBackward(input, label);
  
  std::vector<double> losses;
  for (int epi = 0; epi < nEpisodes; epi++)
  {
    int rnd = std::rand();
    int inputIdx = rnd % nInputs;
    int outputIdx = (inputIdx < nInputs / 2) ? 0 : 1;
    auto input = Eigen::VectorXd(nInputs).setZero();
    input(inputIdx) = 1;
    auto label = Eigen::VectorXd(2).setZero();
    label(outputIdx) = 1;

    losses.push_back( nn.feedBackward(input, label) );
  }

  std::cout << "Done." << std::endl;

  /*
      TEST
  */

  int nCorrect = 0;
  for (int i = 0; i < nTests; i++)
  {
    int rnd = std::rand();
    int inputIdx = rnd % nInputs;
    int outputIdx = (inputIdx < nInputs / 2) ? 0 : 1;
    auto input = Eigen::VectorXd(nInputs).setZero();
    input(inputIdx) = 1;
    
    // Apply
    auto output = nn.feedForward(input);
    std::cout << "In: " << inputIdx <<  ", Out: [" << output.transpose() << "]" << std::endl;

    // Check output
    int maxIdx;
    double prob = output.maxCoeff(&maxIdx);
    double minProb = output.minCoeff();
    if (maxIdx == outputIdx && prob!=0 && prob!=minProb)
      nCorrect++;
  }

  std::cout << nn[0]->toString() << std::endl;

  // Report losses
  std::cout << "Losses over training: " << std::endl;;
  for (int i = 0; i < losses.size(); i++)
    std::cout << losses[i] << std::endl;

  // Compute accuracy
  double accuracy = (double)(nCorrect) / nTests * 100;
  std::cout << "Test accuracy: " << accuracy << "%" << std::endl;


}

/// <summary> Test the training and evaluation of a simple regression network.</summary>
void testRegression()
{

  /*
    Attempt to learn the function
    y = x^2
    by a neural network.
  */

  // Settings
  const int nEpisodes = 100;
  const double learningRate = 0.0001;
  const int nTests = 20;

  // Which values to sample for training: range [-R,R]
  const double trainRange = 10;

  // Setup network
  Network nn = Network();
  nn.push_back(new FullyConnectedLayer(1, 5, FullyConnectedLayer::ReLu));
  nn.push_back(new FullyConnectedLayer(5, 5, FullyConnectedLayer::ReLu));
  nn.push_back(new FullyConnectedLayer(5, 1, FullyConnectedLayer::None));

  nn.setLearningRate(learningRate);

  std::vector<double> losses;
  for (int epi = 0; epi < nEpisodes; epi++)
  {
    // Inputs
    Eigen::VectorXd input = Eigen::VectorXd(1).setZero();
    Eigen::VectorXd label = Eigen::VectorXd(1);
    input(0) = -trainRange + ((float)rand() / (float)RAND_MAX) * (2*trainRange);
    // Tru function value
    label(0) = input(0)*input(0);
    
    losses.push_back(nn.feedBackward(input, label));
  }

  // Report losses
  std::cout << "Losses over training: " << std::endl;;
  for (int i = 0; i < losses.size(); i++)
    std::cout << losses[i] << std::endl;

  /*
      TEST
  */
  
  std::cout << "Tests: " << std::endl;

  std::vector<double> inputs;
  std::vector<double> outputs;
  std::vector<double> refs;
  for (int i = 0; i < nTests; i++)
  {
    // Random input
    Eigen::VectorXd input(1);
    input << -trainRange + ((double)(i)/nTests)*2*trainRange;
    
    // True function value
    Eigen::VectorXd ref(1);
    ref << input(0)*input(0);  

    Eigen::VectorXd output = nn.feedForward(input);

    inputs.push_back(input(0));
    refs.push_back(ref(0));
    outputs.push_back(output(0));

    // Report squared error
    std::cout << "f(" << input(0) << ") = " << output(0) 
      << " \t Ref: " << ref(0) << ", \t L2_Err " << (output(0) - ref(0))*(output(0)-ref(0)) << std::endl;
  }
}

int main()
{
    std::cout << "Hello World!\n"; 

    srand(time(NULL));
    /*
        Perform Tests
    */

    //testSetup();
    //testInput();
    testClassification();
    //testRegression();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
