//
//  TestLM.cpp
//  US_Probe_Calibration
//
//  Created by Zian Fanti on 18/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CalibrationPointsSquaresFunction.h"

#include <vector>
#include <vnl/vnl_quaternion.h>
#include <vnl/vnl_vector_fixed.h>
#include <vnl/algo/vnl_levenberg_marquardt.h>



int main( int argc, char *argv[] )
{

    const int point_size = 7;
    
    vnl_matrix<int> points(point_size, 2);
    points[0][0] = 199;
    points[0][1] = 168;
    points[1][0] = 211;
    points[1][1] = 197;
    points[2][0] = 82;
    points[2][1] = 177;
    points[3][0] = 226;
    points[3][1] = 185;
    points[4][0] = 188;
    points[4][1] = 204;
    points[5][0] = 327;
    points[5][1] = 217;
    points[6][0] = 255;
    points[6][1] = 181;
    
    
    vnl_matrix<double> rotations(point_size, 4);
    
    double r0 [] = {-0.372, 0.894, -0.233, 0.094};
    double r1 [] = {-0.228, 0.523, -0.783, 0.248};
    double r2 [] = {-0.078, -0.012, 0.925, -0.372};
    double r3 [] = {-0.333, 0.777, -0.495, 0.199};
    double r4 [] = {-0.225, 0.288, -0.882, 0.297};
    double r5 [] = {-0.357, 0.931, 0.073, 0.024};
    double r6 [] = {-0.451, 0.890, -0.046, 0.047};
    
    rotations.set_row(0, r0);
    rotations.set_row(1, r1);
    rotations.set_row(2, r2);
    rotations.set_row(3, r3);
    rotations.set_row(4, r4);
    rotations.set_row(5, r5);
    rotations.set_row(6, r6);
    
    vnl_matrix<double> translations(point_size, 3);
    
    double t0 [] = {279.010, 157.851, 63.233};
    double t1 [] = {305.487, 149.455, 66.491};
    double t2 [] = {291.314, 126.426, 62.004};
    double t3 [] = {291.800, 162.819, 64.538};
    double t4 [] = {304.505, 136.624, 68.660};
    double t5 [] = {255.105, 151.850, 63.597};
    double t6 [] = {266.262, 151.553, 66.177};
    
    translations.set_row(0, t0);
    translations.set_row(1, t1);
    translations.set_row(2, t2);
    translations.set_row(3, t3);
    translations.set_row(4, t4);
    translations.set_row(5, t5);
    translations.set_row(6, t6);
    
    
    std::cout << "\n " << "Rotations" << rotations << "\n" << std::endl;
    
    std::cout << "\n " << "Transtaltions" << translations << "\n" << std::endl;
    
    
    // gnerate the transformation (rotation and translation) matrixes for each image
    std::cout << "Transformation matrices" << std::endl;
    std::cout << std::endl;
    
    std::vector< vnl_matrix<double> * > transformationSet(point_size);
    
    vnl_matrix<double> transformationArray [point_size];
    
    for (int i = 0; i < point_size; i++) {            
        
        // the given parameters is [0]=scale factor, [1]=x, [2]=y, [3]=z                       
        vnl_quaternion<double> quaternion(rotations[i][1], rotations[i][2], rotations[i][3], rotations[i][0]);        
        vnl_matrix<double> transformation = quaternion.rotation_matrix_transpose_4();
        transformation = transformation.transpose();
        
        transformation.put(0, 3, translations[i][0]);
        transformation.put(1, 3, translations[i][1]);
        transformation.put(2, 3, translations[i][2]);
                
        transformationArray[i] = transformation;
        transformationSet[i] = &transformationArray[i];
        
        std::cerr << transformation;
        std::cout << std::endl;                
        
    }
    
    points.print(std::cout);
    std::cout << std::endl;

    
    std::cout << "\n " << "t0 - (0,0)" << transformationSet.at(0)[0][0] << "\n" << std::endl;
    std::cout << "\n " << "t0 - (0,0)" << *transformationSet.at(0)[0][0] << "\n" << std::endl;
    
    std::cout << "\n " << "t1 - (0,0)" << transformationSet.at(1)[0][0] << "\n" << std::endl;
    std::cout << "\n " << "t1 - (0,0)" << *transformationSet.at(1)[0][0] << "\n" << std::endl;
    
    
//    
//    CalibrationPointsSquaresFunction optimizationFunction(&transformationSet, &points);        
//    
//    vnl_vector<double> x0(11);
//    x0.fill(1.0);
//    vnl_vector<double> x1 = x0.as_ref();
//    vnl_levenberg_marquardt LM(optimizationFunction);
//    LM.minimize(x1);
//    
//    LM.diagnose_outcome(cout);
//    cout << "x1 = " << x1 << endl;
    
    
    
}