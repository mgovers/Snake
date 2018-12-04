#ifndef __FCLAYER_H_
#define __FCLAYER_H_
#include "Layer.h"

class FullyConnectedLayer : public Layer
{

public:

  enum ActivationFunctionType
  {
    None = 0,
    Sigmoid = 1,
    ReLu = 2,
    Softmax = 3
  };

  enum InitMode
  {
    Constant = 0,
    RandUniform = 1
  };
  
  FullyConnectedLayer(int inputSize, int outputSize, ActivationFunctionType actFunc = ReLu, InitMode initMode = RandUniform)
  {
    w = Eigen::MatrixXd(outputSize, inputSize);
    b = Eigen::VectorXd(outputSize);
    this->activationFunction = actFunc;
    this->weightInitialization = initMode;
    initWeights();
  }

  /// <summary> Feed the input forward through the layer. 
  /// This operation is defined as out = f(w*x + b), where
  /// f is the activation function and w, b are the weights and biases.</summary>
  Eigen::VectorXd feedForward(const Eigen::VectorXd input) override;

  /// <summary> Feed the input forward backwards through the layer and update weights. </summary>
  Eigen::VectorXd feedBackward(
    const Eigen::VectorXd gradient, 
    const Eigen::VectorXd activation,
    const Eigen::VectorXd activationPrev,
    const OptimizerSettings &opt) override;

  std::string toString() override 
  {
    std::stringstream sstr;
    sstr << "FullyConnectedLayer:\n---\nWeights:\n[" << this->w << "]\nBiases:\n[" << this->b << "]\n";
    return sstr.str();
  }

  /// <summary> The input size of the layer. </summary>
  int inputSize()  { return this->w.cols(); }

  /// <summary> The output size of the layer. </summary>
  int outputSize() { return this->w.rows(); }


  Eigen::MatrixXd getW() { return this->w; }

  Eigen::VectorXd getb() { return this->b; }

private:

  ///<summary>Initialize the weights and biases of the network.</summary>
  void initWeights();

  /*
      PROPERTIES
  */

  /// <summary> The weights of the FC layer.
  /// Size [Nout x Nin] </summary>
  Eigen::MatrixXd w;

  /// <summary> The biases of the FC layer.
  /// Size [Nout x 1] </summary>
  Eigen::VectorXd b;

  /// The activation function.
  // todo make configurable
  ActivationFunctionType activationFunction = ReLu;

  /// The weight initialization mode.
  // todo make configurable
  InitMode weightInitialization = Constant;

};

#endif