//
//  probeCalibration_Dialog.cpp
//  US_Probe_Calibration
//
//  Created by Zian Fanti on 15/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include <QErrorMessage>

#include <vtkExtractVOI.h>
#include <vtkImageCast.h>

#include "ProbeCalibrationDialog.h"
#include "QVTKImageWidget.h"

ProbeCalibrationDialog::ProbeCalibrationDialog(QWidget* parent) : QDialog(parent)
{
    ui.setupUi(this);
}

ProbeCalibrationDialog::~ProbeCalibrationDialog() 
{
    this->image = NULL;    
}


void ProbeCalibrationDialog::crop()
{
//    int* dim = this->currentImage->GetDimensions();
//    std::cout << "dims: " << dim[0] << ", " << dim[1] << std::endl;
    
    
    vtkSmartPointer<vtkExtractVOI> extractVOI = vtkSmartPointer<vtkExtractVOI>::New();
    if (ui.radioButton_4->isChecked()) {
        if (workWithStack) {
            for (uint i = 0; i < imageStack.size(); i++) {
                
            }
        }
        else {
            extractVOI->SetInput(image);
            extractVOI->SetVOI(91, 478, 49, 446, 0, 0);
            extractVOI->Update();
            currentImage = extractVOI->GetOutput();
            
            vtkSmartPointer<vtkImageCast> cropCastFilter = vtkSmartPointer<vtkImageCast>::New();
            cropCastFilter->SetInputConnection(currentImage->GetProducerPort());
            cropCastFilter->SetOutputScalarTypeToUnsignedChar();
            cropCastFilter->Update();
            
            ((QVTKImageWidget) parentWidget()).setAndDisplayImage(cropCastFilter->GetOutput());                        
        }
    }
    else if (ui.radioButton_5->isChecked()) {
        
    }
    else if (ui.radioButton_6->isChecked()) {
        
    }
    else if (ui.radioButton_8 ->isChecked()) {
        
    }
    else {
        QErrorMessage errorMessage(this);
        errorMessage.showMessage("<b>No Depth selected</b> <br /> Select one depth before crop");
        errorMessage.exec();
        return;
    }        
}


void ProbeCalibrationDialog::setImage(vtkSmartPointer<vtkImageData> image) 
{
    this->workWithStack = false;
    this->image = image;
    this->currentImage = image;
}


void ProbeCalibrationDialog::
setImageStack(std::vector<vtkSmartPointer<vtkImageData> > imageStack)
{
    this->workWithStack = true;
    this->imageStack = imageStack;
    this->currentImage = imageStack.at(0);
}


