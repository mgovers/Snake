#ifndef _QLOSSFUNCTION_H_
#define _QLOSSFUNCTION_H_

#include "LossFunction.h"
#include <Eigen/Dense>
#include <math.h>

class QuadraticLossFunction : public LossFunction
{

  double value(Eigen::VectorXd input, Eigen::VectorXd target) override
  {
    return pow( (input - target).norm(), 2);
  }

  Eigen::VectorXd gradient(Eigen::VectorXd input, Eigen::VectorXd target) override
  {
    return 2 * (input - target);
  }

};

#endif