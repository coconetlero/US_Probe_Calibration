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

#include "ui_ProbeCalibrationDialog.h"

class ProbeCalibrationDialog : public QDialog
{
    Q_OBJECT
    
public:
    
    ProbeCalibrationDialog(QWidget* parent = 0);    
    virtual ~ProbeCalibrationDialog();
    
private:
    
    Ui::ProbeCalibrationDialog ui;
    
};


#endif
