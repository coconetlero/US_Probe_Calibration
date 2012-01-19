//
//  CalibrationPointsSquaresFunction.cpp
//  US_Probe_Calibration
//
//  Created by Zian Fanti on 16/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CalibrationPointsSquaresFunction.h"

#include <math.h>
#include <iostream>

CalibrationPointsSquaresFunction::
CalibrationPointsSquaresFunction(std::vector<vnl_matrix<double> *> * transformationSet, vnl_matrix<int> * _points) :
vnl_least_squares_function(11, 3 * _points->rows(), vnl_least_squares_function::no_gradient)
{
    this->data = transformationSet;
    this->points = _points;
}

CalibrationPointsSquaresFunction::~CalibrationPointsSquaresFunction() 
{

}

void CalibrationPointsSquaresFunction::f(vnl_vector<double> const &x, vnl_vector<double> &fx)
{
    double t_1x, t_1y, t_1z, t_3x, t_3y, t_3z, w_3x, w_3y, w_3z, s_x, s_y;
    double w_1x, w_1y, w_1z;
    
    t_1x = x(0);
    t_1y = x(1); 
    t_1z = x(2);
    t_3x = x(3);
    t_3y = x(4);
    t_3z = x(5);    
    w_3x = x(6);
    w_3y = x(7);
    w_3z = x(8); 
    s_x = x(9);
    s_y = x(10);

    w_1x = 0;
    w_1y = 0;
    w_1z = 0; 
    
    vnl_matrix<double> cTt(4, 4);
    vnl_matrix<double> tTr(4, 4);
    vnl_matrix<double> rTp(4, 4);
    vnl_matrix<double> xP(4,1);
    
    
    for (unsigned int i = 0; i < data->size(); i++) {
        vnl_matrix<double> * transformation = data->at(i);    
        
        cTt.put(0, 0, cos(w_1x) * cos(w_1y));
        cTt.put(0, 1, (cos(w_1x) * sin(w_1y) * sin(w_1z)) - (sin(w_1x) * cos(w_1z)));
        cTt.put(0, 2, (cos(w_1x) * sin(w_1y) * cos(w_1z)) + (sin(w_1x) * sin(w_1z)));
        cTt.put(0, 3, t_1x);
        cTt.put(1, 0, sin(w_1x) * cos(w_1y));
        cTt.put(1, 1, (sin(w_1x) * sin(w_1y) * sin(w_1z)) - (cos(w_1x) * cos(w_1z)));
        cTt.put(1, 2, (sin(w_1x) * sin(w_1y) * cos(w_1z)) + (cos(w_1x) * sin(w_1z)));
        cTt.put(1, 3, t_1y);
        cTt.put(2, 0, -sin(w_1y));
        cTt.put(2, 1, cos(w_1y) * sin(w_1z));
        cTt.put(2, 2, cos(w_1y) * cos(w_1z));
        cTt.put(2, 3, t_1z);
        cTt.put(3, 0, 0);
        cTt.put(3, 1, 0);
        cTt.put(3, 2, 0);
        cTt.put(3, 3, 1);                
        
        tTr.put(0, 0, transformation->get(0, 0));
        tTr.put(0, 1, transformation->get(0, 1));
        tTr.put(0, 2, transformation->get(0, 2));
        tTr.put(0, 3, transformation->get(0, 3));
        tTr.put(1, 0, transformation->get(1, 0));
        tTr.put(1, 1, transformation->get(1, 1));
        tTr.put(1, 2, transformation->get(1, 2));
        tTr.put(1, 3, transformation->get(1, 3));
        tTr.put(2, 0, transformation->get(2, 0));
        tTr.put(2, 1, transformation->get(2, 1));
        tTr.put(2, 2, transformation->get(2, 2));
        tTr.put(2, 3, transformation->get(2, 3));
        tTr.put(3, 0, transformation->get(3, 0));
        tTr.put(3, 1, transformation->get(3, 1));
        tTr.put(3, 2, transformation->get(3, 2));
        tTr.put(3, 3, transformation->get(3, 3));
        
        
        rTp.put(0, 0, cos(w_3x) * cos(w_3y));
        rTp.put(0, 1, (cos(w_3x) * sin(w_3y) * sin(w_3z)) - (sin(w_3x) * cos(w_3z)));
        rTp.put(0, 2, (cos(w_3x) * sin(w_3y) * cos(w_3z)) + (sin(w_3x) * sin(w_3z)));
        rTp.put(0, 3, t_3x);
        rTp.put(1, 0, sin(w_3x) * cos(w_3y));
        rTp.put(1, 1, (sin(w_3x) * sin(w_3y) * sin(w_3z)) - (cos(w_3x) * cos(w_3z)));
        rTp.put(1, 2, (sin(w_3x) * sin(w_3y) * cos(w_3z)) + (cos(w_3x) * sin(w_3z)));
        rTp.put(1, 3, t_3y);
        rTp.put(2, 0, -sin(w_3y));
        rTp.put(2, 1, cos(w_3y) * sin(w_3z));
        rTp.put(2, 2, cos(w_3y) * cos(w_3z));
        rTp.put(2, 3, t_3z);
        rTp.put(3, 0, 0);
        rTp.put(3, 1, 0);
        rTp.put(3, 2, 0);
        rTp.put(3, 3, 1);
        
        xP.put(0, 0, s_x * points->get(i, 0));
        xP.put(1, 0, s_y * points->get(i, 1));
        xP.put(2, 0, 1);
        xP.put(3, 0, 1);
        
        vnl_matrix<double> M = cTt * tTr * rTp * xP;
        
        fx[3 * i] = M.get(0, 0);
        fx[(3 * i) + 1] = M.get(1, 0);
        fx[(3 * i) + 2] = M.get(2, 0);        
    } 
    
}










