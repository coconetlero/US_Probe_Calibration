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
    
    /** \brief a 2D array to store the translations of each image given by the tracker */
    float (*translations)[3];
    
    /** \brief a 2D array to store the rotations of each image given by the tracker */
    float (*rotations)[4];
    
    
    /** the main window to call it */
    MainWindow* mainWindow;
    
    
    /** \brief the vtkImageData to work */
    vtkSmartPointer<vtkImageData> image;
    
    
    /** Crop ultrasound image depnding of the depth type*/
    vtkSmartPointer<vtkImageData> cropProbeImage(vtkSmartPointer<vtkImageData> image, int depthType);
    
    
    void func(double *p, double *hx, int m, int n, void *adata);
        
    /** \brief a 2D vector to store the selected coordinates on each image */
    std::vector< std::vector<int> > coords;
    
    
    float (*trans_matrix)[4];
    
    /** \brief*/
    double* result;
    
    
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

