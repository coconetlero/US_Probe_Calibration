//
//  OnMouseMovePtr.cpp
//  US_Probe_Calibration
//
//  Created by Zian Fanti on 07/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include "QVTKImageWidgetCommand.h"

#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkVariant.h>
#include <vtkMath.h>
#include <vtkCommand.h>
#include <vtkImageViewer2.h>

QVTKImageWidgetCommand* QVTKImageWidgetCommand::New()
{
    return new QVTKImageWidgetCommand;
}

QVTKImageWidgetCommand::QVTKImageWidgetCommand()
{     
}

QVTKImageWidgetCommand::~QVTKImageWidgetCommand()
{
    this->ImageWidget = NULL;
    this->Picker = NULL;
    this->Annotation = NULL;
}


void QVTKImageWidgetCommand::SetPicker(vtkSmartPointer<vtkPropPicker> picker)
{
    this->Picker = picker;
}


void QVTKImageWidgetCommand::SetAnnotation(vtkSmartPointer<vtkCornerAnnotation> annotation)
{
    this->Annotation = annotation;
}


void QVTKImageWidgetCommand::SetImageWidget(QVTKImageWidget* imageWidget)
{
    this->ImageWidget = imageWidget;
}

void QVTKImageWidgetCommand::
Execute(vtkObject* caller, unsigned long event, void *vtkNotUsed(callData))
{
    vtkSmartPointer<vtkImageViewer2> Viewer = ImageWidget->getImageViewer();

    
    vtkSmartPointer<vtkRenderWindowInteractor> interactor = 
    Viewer->GetRenderWindow()->GetInteractor();
    
    // if the mose is moving inside the viewer
    if (event == vtkCommand::MouseMoveEvent)
    {        
        int* windowPosition = interactor->GetEventPosition();
        
        int xWindow = windowPosition[0];
        int yWindow = windowPosition[1];
        int zWindow = windowPosition[2];
        
        this->Picker->Pick(xWindow, yWindow, zWindow, Viewer->GetRenderer());
        
        double* imPos = this->Picker->GetPickPosition();
        int xImagePosition = vtkMath::Round(imPos[0]);
        int yImagePosition = vtkMath::Round(imPos[1]);
        int zImagePosition = Viewer->GetSlice();
        
        std::string message = "Location: ( "
        + vtkVariant(xImagePosition).ToString() + ", "
        + vtkVariant(yImagePosition).ToString() + ", "
        + vtkVariant(zImagePosition).ToString() + ")"; 
        
        
        this->Annotation->SetText(3, message.c_str() );
        interactor->Render();
        
        vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(interactor->GetInteractorStyle());
        style->OnMouseMove();    
    }
    
    // if the mouse left button is pressed    
    if (event == vtkCommand::LeftButtonPressEvent)
    {
        int* windowPosition = interactor->GetEventPosition();
        
        int xWindow = windowPosition[0];
        int yWindow = windowPosition[1];
        int zWindow = windowPosition[2];
        
        this->Picker->Pick(xWindow, yWindow, zWindow, Viewer->GetRenderer());
        
        double* imPos = this->Picker->GetPickPosition();
        int xImagePosition = vtkMath::Round(imPos[0]);
        int yImagePosition = vtkMath::Round(imPos[1]);
        int zImagePosition = Viewer->GetSlice();
        
        this->ImageWidget->setXPicked(xImagePosition);
        this->ImageWidget->setYPicked(yImagePosition);
        
        std::cout << "x: " << xImagePosition << " y: " << yImagePosition << std::endl;
        
        vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(interactor->GetInteractorStyle());
        style->OnLeftButtonDown();
    }
}

