#ifndef _LOSSFUNCTION_H_
#define _LOSSFUNCTION_H_

#include <Eigen/Dense>

class LossFunction
{
  
public:
  
  virtual double value(Eigen::VectorXd input, Eigen::VectorXd target) = 0;

  virtual Eigen::VectorXd gradient(Eigen::VectorXd input, Eigen::VectorXd target) = 0;

};

#endif
