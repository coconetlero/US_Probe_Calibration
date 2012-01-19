//
//  CalibrationPointsSquaresFunction.h
//  US_Probe_Calibration
//
//  Created by Zian Fanti on 16/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef US_Probe_Calibration_CalibrationPointsSquaresFunction_h
#define US_Probe_Calibration_CalibrationPointsSquaresFunction_h

#include <vnl/vnl_least_squares_function.h>
#include <vnl/vnl_matrix.h>
#include <vector> 

class CalibrationPointsSquaresFunction : public vnl_least_squares_function {
    
public:
    
    CalibrationPointsSquaresFunction
    (std::vector<vnl_matrix<double> *> * transformationSet, vnl_matrix<int> * _points);
    
    virtual ~CalibrationPointsSquaresFunction();
    
    virtual void f(vnl_vector<double> const &x, vnl_vector<double> &fx);

private:
    
    std::vector<vnl_matrix<double> *> *data;
    
    vnl_matrix<int> * points;
    
};

#endif
