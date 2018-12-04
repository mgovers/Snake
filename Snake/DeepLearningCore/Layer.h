#ifndef __LAYER_H_
#define __LAYER_H_

#include <Eigen/Dense>


class Layer
{

public:
  
  /// The optimizer
  enum OptimizerType {
    GradientDescent = 0
  };

  struct OptimizerSettings
  {
    double learningRate = 1.0;
    OptimizerType optType = GradientDescent;
  };

  /// <summary>
  /// Perform a feed-forward step of this layer.
  /// </summary>
  /// <param name="input"></param>
  /// <returns></returns>
  virtual Eigen::VectorXd feedForward(const Eigen::VectorXd input) = 0;

  /// <summary>
  /// Perform a backpropagation step of this layer.
  /// </summary>
  /// <param name="gradient"></param>
  /// <returns></returns>
  virtual Eigen::VectorXd feedBackward(
    const Eigen::VectorXd gradient,
    const Eigen::VectorXd activation,
    const Eigen::VectorXd activationPrev,
    const OptimizerSettings &opt) = 0;

  ///<summary> The input size of the Layer </summary>
  virtual int inputSize() = 0;

  ///<summary> The output size of the Layer </summary>
  virtual int outputSize() = 0;

  virtual std::string toString() = 0;

};

#endif