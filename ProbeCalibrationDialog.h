//
//  ProbeCalibrationDialog.h
//  US_Probe_Calibration
//
//  Created by Zian Fanti on 15/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef US_Probe_Calibration_ProbeCalibrationDialog_h
#define US_Probe_Calibration_ProbeCalibrationDialog_h

#include <QDialog>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>

#include "ui_ProbeCalibrationDialog.h"

class ProbeCalibrationDialog : public QDialog
{
    Q_OBJECT
    
public:
    
    ProbeCalibrationDialog(QWidget* parent = 0);    
    virtual ~ProbeCalibrationDialog();
    
    /**
     * \brief Set this stack of vtkImageData 
     * \param[in] a std Vector of vtkImageData
     */
    void setImageStack(std::vector< vtkSmartPointer<vtkImageData> > imageStack);
    
    /**
     * \brief Set this vtkImageData 
     * \param[in] a smart Pointer of vtkImageData
     */
    void setImage(vtkSmartPointer<vtkImageData> image);
    
    
private:
    
    Ui::ProbeCalibrationDialog ui;
    
    bool workWithStack;
    
    /** \brief the vtkImageData to work */
    vtkSmartPointer<vtkImageData> image;
    
    /** \brif a copy of one image */
    vtkSmartPointer<vtkImageData> currentImage;
    
    /** \brief an Array of vtkImageData to work */
    std::vector< vtkSmartPointer<vtkImageData> > imageStack;
    
    
private slots:
    /**
     * \brief crop the 
     */
    void crop();
};


#endif
