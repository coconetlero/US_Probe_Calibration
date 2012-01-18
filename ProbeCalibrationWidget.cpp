/* 
 * File:   ProbeCalibrationWidget.cpp
 * Author: Zian Fanti
 * 
 * Created on 23 de diciembre de 2011, 0:38
 */

#include "ProbeCalibrationWidget.h"
#include "CalibrationPointsSquaresFunction.h"

#include <QErrorMessage>
#include <QString>
#include <QFile>
#include <QTextStream>

#include <vtkExtractVOI.h>

#include <vnl/vnl_quaternion.h>
#include <vnl/vnl_vector_fixed.h>
#include <vnl/algo/vnl_levenberg_marquardt.h>
#include <vnl/vnl_double_2.h>


ProbeCalibrationWidget::ProbeCalibrationWidget(QWidget* parent) : QWidget(parent)
{
    this->setupUi(this);
    
    QStringList header;
    header << "Frame" << "X" << "Y";
    tableWidget->setHorizontalHeaderLabels(header);
}


ProbeCalibrationWidget::~ProbeCalibrationWidget()
{
    this->image = NULL;
    delete this;
}


void ProbeCalibrationWidget::crop()
{
    int depth = 0;
    vtkSmartPointer<vtkImageData> cropImage;
    std::vector< vtkSmartPointer<vtkImageData> > cropStack;
    
    if (this->radioButton_4->isChecked())
    {
        depth = 4;
        if (workWithStack)
        {
            cropStack.reserve(imageStack.size());
            for (uint i = 0; i < imageStack.size(); i++)
            {
                cropStack.push_back(this->cropProbeImage(imageStack.at(i), depth));
            }
        }
        else
        {
            cropImage = this->cropProbeImage(this->image, depth);
        }
    }
    else if (this->radioButton_5->isChecked())
    {
        depth = 5;
        if (workWithStack)
            for (uint i = 0; i < imageStack.size(); i++)
                imageStack.at(i) = this->cropProbeImage(imageStack.at(i), depth);
        else
            cropImage = this->cropProbeImage(this->image, depth);
    }
    else if (this->radioButton_6->isChecked())
    {
        depth = 6;
        if (workWithStack)
            for (uint i = 0; i < imageStack.size(); i++)
                this->cropProbeImage(imageStack.at(i), depth);
        else
            cropImage = this->cropProbeImage(this->image, depth);
    }
    else if (this->radioButton_8->isChecked())
    {
        depth = 8;
        if (workWithStack)
            for (uint i = 0; i < imageStack.size(); i++)
                this->cropProbeImage(imageStack.at(i), depth);
        else
            cropImage = this->cropProbeImage(this->image, depth);
    }
    else
    {
        QErrorMessage errorMessage(this);
        errorMessage.showMessage("<b>No Depth selected</b> <br /> Select one depth before crop");
        errorMessage.exec();
        return;
    }
    
    // show croped images
    //    MainWindow* w = dynamic_cast<MainWindow*> (this->parentWidget());    
    if (0 != mainWindow)
    {
        if (workWithStack)
        {
            mainWindow->getDisplayWidget()->setAndDisplayMultipleImages(cropStack);
            
            QString str = "crop image stack with depth = ";
            QString num;
            num.setNum(depth);
            mainWindow->addLogText(str + num);
        }
        else
        {
            mainWindow->getDisplayWidget()->setAndDisplayImage(cropImage);
            
            QString str = "crop image with depth = ";
            QString num;
            num.setNum(depth);
            mainWindow->addLogText(str + num);
            
            cropImage = NULL;
        }
    }
}


void ProbeCalibrationWidget::setImage(vtkSmartPointer<vtkImageData> image)
{
    this->workWithStack = false;
    this->image = image;
}


void ProbeCalibrationWidget::
setImageStack(std::vector<vtkSmartPointer<vtkImageData> > imagestack)
{
    this->workWithStack = true;
    this->imageStack = imagestack;
    this->coords.set_size(imageStack.size(), 2);
}


vtkSmartPointer<vtkImageData> ProbeCalibrationWidget::
cropProbeImage(vtkSmartPointer<vtkImageData> image, int depthType)
{
    vtkSmartPointer<vtkExtractVOI> extractVOI = vtkSmartPointer<vtkExtractVOI>::New();
    
    
    int* dim = image->GetDimensions();
    
    switch (depthType)
    {
        case 4:
        {
            extractVOI->SetInput(image);
            extractVOI->SetVOI(91, 478, dim[1] - 446, dim[1] - 49, 0, 0);
            extractVOI->Update();
            return extractVOI->GetOutput();
        }
        case 5:
        {
            extractVOI->SetInput(image);
            extractVOI->SetVOI(136, 435, dim[1] - 446, dim[1] - 49, 0, 0);
            extractVOI->Update();
            return extractVOI->GetOutput();
        }
        case 6:
        {
            extractVOI->SetInput(image);
            extractVOI->SetVOI(155, 414, dim[1] - 446, dim[1] - 49, 0, 0);
            extractVOI->Update();
            return extractVOI->GetOutput();
        }
        case 8:
        {
            extractVOI->SetInput(image);
            extractVOI->SetVOI(188, 380, dim[1] - 446, dim[1] - 49, 0, 0);
            extractVOI->Update();
            return extractVOI->GetOutput();
        }
        default:
        {
            //                MainWindow* w = dynamic_cast<MainWindow*> (this->parentWidget());
            //                if (0 != w)
            if (mainWindow != 0)
            {
                //                        w->addLogText("depth not found, nothing made");
                mainWindow->addLogText("depth not found, nothing made");
            }
            return image;
        }
    }
}


void ProbeCalibrationWidget::setMainWindow(MainWindow* mainwindow)
{
    this->mainWindow = mainwindow;
}


bool setCoordsSize = false;


void ProbeCalibrationWidget::getCoordinates()
{
    int x = mainWindow->getDisplayWidget()->getXPicked();
    int y = mainWindow->getDisplayWidget()->getYPicked();
    
    QString str;
    
    if (workWithStack)
    {
        this->coords.set_size(imageStack.size(), 2);
        
        
        tableWidget->setRowCount(imageStack.size());
        int row = mainWindow->getDisplayWidget()->getImageDisplayedIndex();
        tableWidget->setItem(row, 0, new QTableWidgetItem(str.setNum(row)));
        tableWidget->setItem(row, 1, new QTableWidgetItem(str.setNum(x)));
        tableWidget->setItem(row, 2, new QTableWidgetItem(str.setNum(y)));
        
        coords[row][0] = x;
        coords[row][1] = y;
    }
    else
    {
        tableWidget->setRowCount(1);
        tableWidget->setItem(0, 0, new QTableWidgetItem(str.setNum(1)));
        tableWidget->setItem(0, 1, new QTableWidgetItem(str.setNum(x)));
        tableWidget->setItem(0, 2, new QTableWidgetItem(str.setNum(y)));
        std::cout << "PC -> (x = " << x << ", y = " << y << ")" << std::endl;
    }
}


void ProbeCalibrationWidget::loadRotationsFile()
{
    QString rotationFilename = QFileDialog::getOpenFileName(this, tr("Load Rotations File"), QDir::currentPath());
    
    if (!rotationFilename.isEmpty())
    {
        
        QFile file(rotationFilename);
        if (!file.open(QIODevice::ReadOnly))
            return;
        
        QTextStream stream(&file);
        QString line;
        
        // declare a rotation matrix 
        this->rotations.set_size(imageStack.size(), 4);
        
        int idx = 0;
        while (!stream.atEnd())
        {
            line = stream.readLine();
            QStringList lineList = line.split(" ");
            
            for (int j = 0; j < lineList.size(); j++)
            {
                rotations.put(idx, j, lineList.at(j).toDouble());                 
            }
            
            idx++;            
            std::cout << line.toAscii().data() << std::endl;
        }
        file.close();        
        rotationsLabel->setText("Rotations file are loaded");
    }
}


void ProbeCalibrationWidget::loadTranslationsFile()
{
    QString translationFilename = QFileDialog::getOpenFileName(this, tr("Load Translations File"), QDir::currentPath());
    
    if (!translationFilename.isEmpty())
    {
        
        QFile file(translationFilename);
        if (!file.open(QIODevice::ReadOnly))
            return;
        
        QTextStream stream(&file);
        QString line;
        
        // declare a translation matrix 
        this->translations.set_size(imageStack.size(), 4); 
        
        int idx = 0;
        while (!stream.atEnd())
        {
            line = stream.readLine();
            QStringList lineList = line.split(" ");
            
            for (int j = 0; j < lineList.size(); j++)
            {
                translations.put(idx, j, lineList.at(j).toDouble());        
            }
            idx++;   
            std::cout << line.toAscii().data() << std::endl;
        }
        file.close(); // when your done.        
        translationsLabel->setText("Translations file are loaded");
    }
}


void ProbeCalibrationWidget::calibrate()
{

    // gnerate the transformation (rotation and translation) matrixes for each image
    std::cout << "Transformation matrices" << std::endl;
    std::cout << std::endl;
    
    std::vector<vnl_matrix<double>* > transformationSet(imageStack.size());
    
    for (uint i = 0; i < imageStack.size(); i++) {            
        
        // the given parameters is [0]=scale factor, [1]=x, [2]=y, [3]=z                       
        vnl_quaternion<double> quaternion(rotations[i][1], rotations[i][2], rotations[i][3], rotations[i][0]);        
        vnl_matrix<double> transformation = quaternion.rotation_matrix_transpose_4();
        transformation = transformation.transpose();
        
        transformation.put(0, 3, translations[i][0]);
        transformation.put(1, 3, translations[i][1]);
        transformation.put(2, 3, translations[i][2]);
        
        transformationSet[i] = &transformation;
        std::cerr << transformation;
        std::cout << std::endl;                
        
    }
    
    coords.print(std::cout);
    std::cout << std::endl;
    
    CalibrationPointsSquaresFunction optimizationFunction(&transformationSet, &coords);

  

    vnl_vector<double> x0(11);
    x0.fill(1.0);
    vnl_vector<double> x1 = x0.as_ref();
    vnl_levenberg_marquardt LM(optimizationFunction);
    LM.minimize(x1);
    
    LM.diagnose_outcome(cout);
    cout << "x1 = " << x1 << endl;
    
}










