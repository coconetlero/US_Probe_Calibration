/* 
 * File:   ProbeCalibrationWidget.cpp
 * Author: Zian Fanti
 * 
 * Created on 23 de diciembre de 2011, 0:38
 */

#include "ProbeCalibrationWidget.h"


#include <QErrorMessage>
#include <QString>
#include <QFile>
#include <QTextStream>

#include <vtkExtractVOI.h>

#include <vnl/vnl_quaternion.h>
#include <vnl/vnl_vector_fixed.h>



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
    imageStack = imagestack;
    coords.resize(imageStack.size(), std::vector<int>(2));
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
        coords.resize(imageStack.size(), std::vector<int>(2));
        
        
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
                rotations.put(idx, j, lineList.at(j).toFloat());                 
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
                translations.put(idx, j, lineList.at(j).toFloat());        
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
    
    for (uint i = 0; i < imageStack.size(); i++) {            
        
        // the given parameters is [0]=scale factor, [1]=x, [2]=y, [3]=z                       
        vnl_quaternion<float> quaternion(rotations[i][1], rotations[i][2], rotations[i][3], rotations[i][0]);        
        vnl_matrix<float> transformation = quaternion.rotation_matrix_transpose_4();
        transformation = transformation.transpose();
        
        transformation.put(0, 3, translations[i][0]);
        transformation.put(1, 3, translations[i][1]);
        transformation.put(2, 3, translations[i][2]);
        
        std::cerr << transformation;
        std::cout << std::endl;
    }
    
    //  float tm[imageStack.size() * 4][4];
    //
    //  for (uint i = 0; i < imageStack.size(); i++)
    //    {
    //      Quaternions * quat = Quaternions::New();
    //      quat->TransMatrix(rotations[i], translations[i]);
    //      tm[i * 4][0] = quat->trans[0][0];
    //      tm[i * 4][1] = quat->trans[0][1];
    //      tm[i * 4][2] = quat->trans[0][2];
    //      tm[i * 4][3] = quat->trans[0][3];
    //      tm[i * 4 + 1][0] = quat->trans[1][0];
    //      tm[i * 4 + 1][1] = quat->trans[1][1];
    //      tm[i * 4 + 1][2] = quat->trans[1][2];
    //      tm[i * 4 + 1][3] = quat->trans[1][3];
    //      tm[i * 4 + 2][0] = quat->trans[2][0];
    //      tm[i * 4 + 2][1] = quat->trans[2][1];
    //      tm[i * 4 + 2][2] = quat->trans[2][2];
    //      tm[i * 4 + 2][3] = quat->trans[2][3];
    //      tm[i * 4 + 3][0] = quat->trans[3][0];
    //      tm[i * 4 + 3][1] = quat->trans[3][1];
    //      tm[i * 4 + 3][2] = quat->trans[3][2];
    //      tm[i * 4 + 3][3] = quat->trans[3][3];
    //    }
    //
    //  trans_matrix = tm;
    

    //
    //    
    //    //LEVMAR
    //  double res[imageStack.size() * 3];
    //
    //  int m, n;
    //  m = 11;
    //  n = imageStack.size() * 3;
    //
    //  double p[11];
    //  p[0] = 1;
    //  p[1] = 1;
    //  p[2] = 1;
    //  p[3] = 1;
    //  p[4] = 1;
    //  p[5] = 1;
    //  p[6] = 1;
    //  p[7] = 1;
    //  p[8] = 1;
    //  p[9] = 1;
    //  p[10] = 1;
    //  
    //   
    //  int ret = dlevmar_dif(func, p, NULL, m, n, 2, NULL, NULL, NULL, NULL, NULL);
    //
    //
    //  std::cout << "Solution result: " << ret << std::endl;
    //  std::cout << std::endl;
    //
    //  std::cout << "Equation solutions" << std::endl;
    //  std::cout << std::endl;
    //
    //  for (int i = 0; i < n; i++)
    //    {
    //      std::cout << p[i] << std::endl;
    //    }
    //
    //  std::cout << std::endl;
    //  std::cout << "Last equation evaluations" << std::endl;
    //  std::cout << std::endl;
    //
    //  for (int i = 0; i < m; i++)
    //    {
    //      std::cout << res[i] << std::endl;
    //    }
    //
    //  result = res;
    //
    //
    //  std::cout << std::endl;
    //  std::cout << "Press Enter to Exit" << std::endl;
    //
    //  bool exit = true;
    //
    //  while (exit)
    //    {
    //      if (std::cin.get() == '\n')
    //        exit = false;
    //    }
    //
    //  return;
}



////LEVMAR
//
//void ProbeCalibrationWidget::func(double* p, double* hx, int m, int n, void* adata)
//{
//
//  float x_x, y, z, a, b, c, x2, y2, z2, a2, b2, c2;
//  x_x = p[0];
//  y = p[1];
//  z = p[2];
//  a = p[3];
//  b = p[4];
//  c = p[5];
//  x2 = p[8];
//  y2 = p[9];
//  z2 = p[10];
//  a2 = 0;
//  b = 0;
//  c = 0;
//
//  Matrix<float> rTp(4, 4);
//  Matrix<float> cTt(4, 4);
//  Matrix<float> tTr(4, 4);
//  Matrix<float> p1(4, 1);
//
//  rTp.llenar(3, 0, 0);
//  rTp.llenar(3, 1, 0);
//  rTp.llenar(3, 2, 0);
//  rTp.llenar(3, 3, 1);
//  cTt.llenar(3, 0, 0);
//  cTt.llenar(3, 1, 0);
//  cTt.llenar(3, 2, 0);
//  cTt.llenar(3, 3, 1);
//  p1.llenar(2, 0, 0);
//  p1.llenar(3, 0, 1);
//
//  Matrix<float> temp(4, 1);
//
//  
//  for (uint i = 0; i < imageStack.size(); i++)
//    {
//
//      p1.llenar(0, 0, p[6] * coords[i][0]);
//      p1.llenar(1, 0, p[7] * coords[i][1]);
//
//      rTp.llenar(0, 0, cos(a) * cos(b));
//      rTp.llenar(0, 1, cos(a) * sin(b) * sin(c) - sin(a) * cos(c));
//      rTp.llenar(0, 2, cos(a) * sin(b) * cos(c) + sin(a) * sin(c));
//      rTp.llenar(0, 3, x_x);
//      rTp.llenar(1, 0, sin(a) * sin(b));
//      rTp.llenar(1, 1, sin(a) * sin(b) * sin(c) + cos(a) * cos(c));
//      rTp.llenar(1, 2, sin(a) * sin(b) * cos(c) - cos(a) * sin(c));
//      rTp.llenar(1, 3, y);
//      rTp.llenar(2, 0, -sin(b));
//      rTp.llenar(2, 1, cos(b) * sin(c));
//      rTp.llenar(2, 2, cos(b) * cos(c));
//      rTp.llenar(2, 3, z);
//
//      tTr.llenar(0, 0, trans_matrix[i * 4][0]);
//      tTr.llenar(0, 1, trans_matrix[i * 4][1]);
//      tTr.llenar(0, 2, trans_matrix[i * 4][2]);
//      tTr.llenar(0, 3, trans_matrix[i * 4][3]);
//      tTr.llenar(1, 0, trans_matrix[i * 4 + 1][0]);
//      tTr.llenar(1, 1, trans_matrix[i * 4 + 1][1]);
//      tTr.llenar(1, 2, trans_matrix[i * 4 + 1][2]);
//      tTr.llenar(1, 3, trans_matrix[i * 4 + 1][3]);
//      tTr.llenar(2, 0, trans_matrix[i * 4 + 2][0]);
//      tTr.llenar(2, 1, trans_matrix[i * 4 + 2][1]);
//      tTr.llenar(2, 2, trans_matrix[i * 4 + 2][2]);
//      tTr.llenar(2, 3, trans_matrix[i * 4 + 2][3]);
//      tTr.llenar(3, 0, trans_matrix[i * 4 + 3][0]);
//      tTr.llenar(3, 1, trans_matrix[i * 4 + 3][1]);
//      tTr.llenar(3, 2, trans_matrix[i * 4 + 3][2]);
//      tTr.llenar(3, 3, trans_matrix[i * 4 + 3][3]);
//
//      cTt.llenar(0, 0, cos(a2) * cos(b2));
//      cTt.llenar(0, 1, cos(a2) * sin(b2) * sin(c2) - sin(a2) * cos(c2));
//      cTt.llenar(0, 2, cos(a2) * sin(b2) * cos(c2) + sin(a2) * sin(c2));
//      cTt.llenar(0, 3, x2);
//      cTt.llenar(1, 0, sin(a2) * sin(b2));
//      cTt.llenar(1, 1, sin(a2) * sin(b2) * sin(c2) + cos(a2) * cos(c2));
//      cTt.llenar(1, 2, sin(a2) * sin(b2) * cos(c2) - cos(a2) * sin(c2));
//      cTt.llenar(1, 3, y2);
//      cTt.llenar(2, 0, -sin(b2));
//      cTt.llenar(2, 1, cos(b2) * sin(c2));
//      cTt.llenar(2, 2, cos(b2) * cos(c2));
//      cTt.llenar(2, 3, z2);
//
//      temp = cTt * tTr * rTp*p1;
//
//      result[i * 3] = temp.accesar(0, 0);
//      result[i * 3 + 1] = temp.accesar(1, 0);
//      result[1 * 3 + 2] = temp.accesar(2, 0);
//    }
//}



