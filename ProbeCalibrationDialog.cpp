//
//  probeCalibration_Dialog.cpp
//  US_Probe_Calibration
//
//  Created by Zian Fanti on 15/12/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include <QErrorMessage>

#include "ProbeCalibrationDialog.h"

ProbeCalibrationDialog::ProbeCalibrationDialog(QWidget* parent) : QDialog(parent)
{
    ui.setupUi(this);
}

ProbeCalibrationDialog::~ProbeCalibrationDialog() {}


void ProbeCalibrationDialog::crop()
{
    if (ui.radioButton_4->isChecked()) {
        
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

