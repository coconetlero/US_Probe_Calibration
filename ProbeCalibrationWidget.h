/* 
 * File:   ProbeCalibrationWidget.h
 * Author: coconetlero
 *
 * Created on 23 de diciembre de 2011, 0:38
 */

#ifndef PROBECALIBRATIONWIDGET_H
#define	PROBECALIBRATIONWIDGET_H

#include "ui_ProbeCalibrationWidget.h"
#include "mainwindow.h"

#include <QWidget>

#include <vtkSmartPointer.h>
#include <vtkImageData.h>

#include <vnl/vnl_matrix.h>


class ProbeCalibrationWidget : public QWidget, private Ui::ProbeCalibrationWidget
{
    Q_OBJECT
    
public:
    
    /** Constructor */
    ProbeCalibrationWidget(QWidget* parent = 0);
    
    virtual ~ProbeCalibrationWidget();
    
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
    
    
    /** Set the window to display the crop images */
    void setMainWindow(MainWindow* mainwindow);
    
    
    
    
private:
    
    bool workWithStack;
    
    
    /** \brief an Array of vtkImageData to work */
    std::vector< vtkSmartPointer<vtkImageData> > imageStack;
    
    
    /** \brief a vnl_matrix to store the translations of each image given by the tracker */
    vnl_matrix<double> translations;
    
    
    /** \brief a vnl_matrix to store the rotations of each image given by the tracker */
    vnl_matrix<double> rotations;
    
    
    /** the main window to call it */
    MainWindow* mainWindow;
    
    
    /** \brief the vtkImageData to work */
    vtkSmartPointer<vtkImageData> image;
    
    
    /** Crop ultrasound image depnding of the depth type*/
    vtkSmartPointer<vtkImageData> cropProbeImage(vtkSmartPointer<vtkImageData> image, int depthType);
    
    
    /** \brief a vnl_matrix to store the selected coordinates on each image */
    vnl_matrix<int> coords;
    
    
    
    
private slots:
    /**
     * \brief crop the 
     */
    void crop();
    
    
    void getCoordinates();
    
    
    void calibrate();
    
    
    void loadRotationsFile();
    
    
    void loadTranslationsFile();
    
};




#endif	/* PROBECALIBRATIONWIDGET_H */

