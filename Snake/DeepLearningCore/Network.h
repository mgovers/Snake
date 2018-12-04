#ifndef __NETWORK_H_
#define __NETWORK_H_

#include "Layer.h"
#include "QuadraticLossFunction.h"

#include <Eigen/Dense>
#include <memory>
#include <iostream>
#include <vector>

class Network
{

public:

  Network() {}

  Network(std::vector<std::shared_ptr<Layer>> layers_) 
  {
    layers = layers_;
  }

  ///<summary> Perform a feedforward step of the network. </summary>
  /// <param name="input">The vector of inputs</param>
  /// <param name="input">(optional) All activations of every layer.</param>
  /// <returns>The activations of the last layer.</returns>
  Eigen::VectorXd feedForward(const Eigen::VectorXd input, std::vector<Eigen::VectorXd> &outputActivations);
  Eigen::VectorXd feedForward(const Eigen::VectorXd input);
  
  /// <summary>
  /// Performs backpropagation on the network with a single input.
  /// </summary>
  /// <param name="input">The input.</param>
  /// <param name="label">The expected output.</param>
  /// <param name="activations">The intermediate activations per layer.</param>
  double feedBackward(Eigen::VectorXd input, Eigen::VectorXd label);
  double feedBackward(Eigen::VectorXd input, std::vector<Eigen::VectorXd> activations, Eigen::VectorXd label);

  void push_back(Layer* newLayer) { layers.push_back(std::shared_ptr<Layer>(newLayer)); }
  void clear() { layers.clear(); }
  std::shared_ptr<Layer> operator[] (int index) { return layers[index]; }

  ///<summary> Verify whether the input and output sizes of the network layers match. </summary>
  bool validLayers();

  /// Input size of the network
  int inputSize() { return layers.size()>0 ? layers[0]->inputSize() : -1; }
  /// Output size of the network
  int outputSize() { return layers.size() > 0 ? layers[layers.size()-1]->outputSize() : -1; }

  void setLearningRate(double rate) { this->optimizer.learningRate = rate; }
  double getLearningRate() { return this->optimizer.learningRate; }

  void setOptimizer(Layer::OptimizerType type) { this->optimizer.optType = type; }
  Layer::OptimizerType getOptimizer() { return this->optimizer.optType; }

  void setLossFunction(std::shared_ptr<LossFunction> lFunc) { this->lossFunc = lFunc; }
  std::shared_ptr<LossFunction> getLossFunction() { return this->lossFunc; }

private:

  /// The layers of the network
  /// Currently, only sequential networks are supported
  std::vector<std::shared_ptr<Layer>> layers;

  /*
      /// TRAINING \\\
  */

  /// The optimizer to use for training
  Layer::OptimizerSettings optimizer = 
  { 
    1.0,
    Layer::OptimizerType::GradientDescent
  };

  /// The loss function to use
  std::shared_ptr<LossFunction> lossFunc = std::shared_ptr<LossFunction>(new QuadraticLossFunction());

};

#endif