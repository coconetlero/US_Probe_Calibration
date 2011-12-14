//
//  OnMouseMovePtr.h
//  US_Probe_Calibration
//
//  Created by Zian Fanti on 07/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef US_Probe_Calibration_OnMouseMovePtr_h
#define US_Probe_Calibration_OnMouseMovePtr_h

#include "QVTKImageWidget.h"

#include <vtkCommand.h>
#include <vtkPropPicker.h>
#include <vtkCornerAnnotation.h>
#include <vtkSmartPointer.h>

/** 
 * The mouse motion callback, to pick the image and recover pixel values
 */
class QVTKImageWidgetCommand : public vtkCommand
{
public:

  static QVTKImageWidgetCommand *New();

  QVTKImageWidgetCommand();

  ~QVTKImageWidgetCommand();

  void SetPicker(vtkSmartPointer<vtkPropPicker> picker);

  void SetAnnotation(vtkSmartPointer<vtkCornerAnnotation> annotation);

  /**
   * \brief Set the 2d image widget related to this 2d event manager
   * \param[in] viewer QVTKImageWidget target 2D image
   */
  void SetImageWidget(QVTKImageWidget* imageWidget);

  /**
   *
   */
  virtual void Execute(vtkObject *, unsigned long vtkNotUsed(event), void *);

private:

  /** Pointer to the picker */
  vtkSmartPointer<vtkPropPicker> Picker;

  /** Pointer to the annotation */
  vtkSmartPointer<vtkCornerAnnotation> Annotation;

  /** The widget related to the mouse events */
  QVTKImageWidget* ImageWidget;
};

#endif
