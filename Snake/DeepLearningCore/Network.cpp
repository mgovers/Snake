#include "Network.h"
#include <Eigen/Dense>

Eigen::VectorXd Network::feedForward(const Eigen::VectorXd input)
{
  std::vector<Eigen::VectorXd> activations;
  return this->feedForward(input, activations);
}

Eigen::VectorXd Network::feedForward(const Eigen::VectorXd input, std::vector<Eigen::VectorXd>& outputActivations)
{
  Eigen::VectorXd in = input;
  Eigen::VectorXd out;

  if (!validLayers())
  {
    std::stringstream msg;
    msg << "Error during feedforward: layer sizes do not match. Check the sizes of your layers." << std::endl;
    throw std::invalid_argument(msg.str());
  }

  // Feed the input through each layer
  for (int i = 0; i < this->layers.size(); i++)
  {
    outputActivations.push_back( layers[i]->feedForward(in) );
    in = outputActivations[outputActivations.size()-1];
  }

  return outputActivations[outputActivations.size() - 1];
}

double Network::feedBackward(Eigen::VectorXd input, Eigen::VectorXd label)
{
  std::vector<Eigen::VectorXd> activations;
  // First compute and store all activations
  auto output = feedForward(input, activations);
  // Perform backpropagation step
  return feedBackward(input, activations,label);
}

double Network::feedBackward(Eigen::VectorXd input, std::vector<Eigen::VectorXd> activations, Eigen::VectorXd label)
{
  // Parse inputs

  if (activations.size() != this->layers.size())
    throw std::invalid_argument("Number of activations does not match the number of layers.");
  
  // Define the first gradient by the networks loss function

  double loss = this->lossFunc->value(activations[activations.size() - 1], label);
  auto gradient = this->lossFunc->gradient(activations[activations.size()-1],label);

  // Propagate backwards through the network

  for (int i = this->layers.size() - 1; i >= 0; i--)
  {
    if (i>0)
      gradient = layers[i]->feedBackward(gradient, activations[i], activations[i-1], optimizer);
    else
      gradient = layers[i]->feedBackward(gradient, activations[i], input, optimizer);
  }

  return loss;
}

bool Network::validLayers()
{
  if (this->layers.size() <= 1) 
    return true;
  
  for (int i = 0; i < this->layers.size()-1; i++)
  {
    if (this->layers[i + 1]->inputSize() != this->layers[i]->outputSize())
      return false;
  }
  return true;
}