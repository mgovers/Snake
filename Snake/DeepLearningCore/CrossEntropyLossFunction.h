#ifndef _CELOSSFUNCTION_H_
#define _CELOSSFUNCTION_H_

#include "LossFunction.h"
#include <Eigen/Dense>
#include <math.h>

class CrossEntropyLossFunction : public LossFunction
{

  double value(Eigen::VectorXd input, Eigen::VectorXd target) override
  {
    return - (target.array() * (input.array().log())).sum();
  }

  Eigen::VectorXd gradient(Eigen::VectorXd input, Eigen::VectorXd target) override
  {
    return - target.array() / input.array();
  }

};

#endif