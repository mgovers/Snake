#include "FullyConnectedLayer.h"
#include <iostream>
#include <exception>

std::string VecToString(Eigen::VectorXd &mat)
{
  std::stringstream s;
  s << mat;
  return s.str();
}

void FullyConnectedLayer::initWeights()
{
  switch (this->weightInitialization)
  {
    // Random between [-1,1]
  case RandUniform:
    w.setRandom();
    b.setRandom();
    break;
    // All equal entries (not recommended, debug only)
  case Constant:
    w.setOnes();
    b.setOnes();
    break;
  default:
    std::cerr << "Unrecognized weight initialization encountered." << std::endl;
    break;
  }
}

Eigen::VectorXd FullyConnectedLayer::feedForward(const Eigen::VectorXd input)
{

  // Parse inputs
  if (input.rows() != this->w.cols())
  {
    auto msg = std::stringstream();
    msg << "Matrix dimensions do not agree (expected " << w.cols() <<
      "xN, but got " << input.rows() << "xN instead)." << std::endl;
    throw std::invalid_argument(msg.str());
  }

  // Compute the intermediate weighted input (linear operation)

  Eigen::VectorXd wi = w * input + b;
  
  // Compute the activations by means of the activation function (non-linear operation)

  switch (this->activationFunction)
  {
  case Sigmoid:
    // Sigmoid: f = exp(a) / (exp(a)+1)
    return wi.array().exp() / (wi.array().exp() + 1);
    
  case ReLu:
    // ReLu: f = { a if a>0, 0 otherwise }
    return wi.cwiseMax(0.0);
  
  case None:
    // Default do nothing, f = a
    return wi;
  
  case Softmax:
    // Softmax: exp(w)/sum(exp(w)) (Use for probability output)
    return wi.array().exp() / wi.array().exp().sum();

  default:
    std::cout << "Warning: unrecognized activation function encountered." << std::endl;
    return wi;
  }

}

Eigen::VectorXd FullyConnectedLayer::feedBackward(const Eigen::VectorXd gradient, 
  const Eigen::VectorXd activation,
  const Eigen::VectorXd activationPrev,
  const Layer::OptimizerSettings &opt)
{
    
  /*
      Compute prev layer gradient
  */
  Eigen::VectorXd activationFuncGrad;
  Eigen::VectorXd prevGrad;
  switch (this->activationFunction)
  {
  // Compute the gradient of the activation function and apply it

  case Sigmoid:
    // Sigmoid: exp(x) / (1+2exp(x)+exp(2x))
    activationFuncGrad = activationPrev.array().exp()
      / (1 + 2 * (activationPrev.array().exp()) + (2 * activationPrev.array().exp()));
    break;
  
  case ReLu:
    // Relu: 1 if x>0 else 0
    activationFuncGrad = Eigen::VectorXd(activationPrev.size()).setZero();
    activationFuncGrad = ((activationPrev.array() > 0.0).select(1.0, activationFuncGrad));
    break;

  case Softmax:
  {
    // Softmax: (exp(x)*sum(exp(x))-exp(2x))/(sum(exp(x))^2)
    double expsum = activationPrev.array().exp().sum();
    activationFuncGrad = (activationPrev.array().exp()*expsum - (2 * activationPrev).array().exp())
      / (expsum * expsum);
    break;
  }
  case None:
  default:
    // No activation function
    activationFuncGrad = Eigen::VectorXd(activationPrev.size()).setOnes();
    break;

  }
  // Compute the previous layer gradient
  prevGrad = activationFuncGrad.array() * (this->w.transpose() * gradient).array();

  /* 
    Update the weights and biases
  */
  switch (opt.optType)
  {
    // Update parameters
  case GradientDescent:

    // Update biases
    this->b -= opt.learningRate * gradient;

    //Update weights
    this->w -= opt.learningRate * (gradient * activationPrev.transpose());

    break;
  default:
    throw std::invalid_argument("Unrecognized optimizer encountered.");
    break;
  }

  return prevGrad;
}