//
//  QVTKImageWidget.cpp
//  US_Probe_Calibration
//
//  Created by Zian Fanti on 01/12/11.
//  Copyright (c) 2011 __UNAM__. All rights reserved.
//

#include "QVTKImageWidget.h"
#include "QVTKImageWidgetCommand.h"

#include <QSize>
#include <QVBoxLayout>

#include <itkImage.h>
#include <itkImageFileReader.h>

#include <vtkImageReader2.h>
#include <vtkImageReader2Factory.h>

#include <vtkCornerAnnotation.h>
#include <vtkPropPicker.h>
#include <vtkTextProperty.h>

#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>

//#include <vtkImageStack.h>

QVTKImageWidget::QVTKImageWidget(QWidget *parent) : QWidget(parent)
{
  qvtkWidget = new QVTKWidget(this);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->setContentsMargins(0, 0, 0, 0);
  layout->setSpacing(0);
  layout->addWidget(qvtkWidget);
  this->setLayout(layout);

  // create the essentials vtk objects to display the images    
  this->imageViewer = vtkSmartPointer<vtkImageViewer2>::New();

  // to display data in the corners of the image viewer
  this->cornerAnnotation = vtkSmartPointer< vtkCornerAnnotation >::New();

  // Create image actor
  //	this->actor = vtkSmartPointer<vtkImageActor>::New();
  //    
  //    // Create a camera 
  //  this->camera = vtkSmartPointer<vtkCamera>::New();
  //
  //  this->renderer = vtkSmartPointer<vtkRenderer>::New();
  //	this->renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
  //	this->renderWindow->AddRenderer(renderer);
}


QVTKImageWidget::~QVTKImageWidget()
{
  //	renderWindow->Finalize();
  itkImage = NULL;
  vtkImage = NULL;
  qvtkWidget = NULL;
  imageViewer = NULL;
}


void QVTKImageWidget::setAndDisplayImage(QString imageFilename)
{
  // if the image is alredy defined 
  itkImage = NULL;
  rgbItkImage = NULL;
  vtkImage = NULL;

  this->setImageProperties(imageFilename, true);

  // reads a vtkImage for display purposes
  vtkSmartPointer <vtkImageReader2Factory> readerFactory =
          vtkSmartPointer <vtkImageReader2Factory>::New();

  vtkSmartPointer <vtkImageReader2> reader =
          readerFactory->CreateImageReader2(imageFilename.toAscii().data());

  reader->SetFileName(imageFilename.toAscii().data());  
  reader->Update();

  this->vtkImage = reader->GetOutput();

  int* dim = vtkImage->GetDimensions();

  std::cout << dim[0] << "," << dim[1] << "," << dim[2] << std::endl;


  this->displayImage(vtkImage);



  readerFactory = NULL;
  reader = NULL;






  this->setImageProperties(imageFilename, true);

  //  // set itk image depending on the image type 
  //  // if image type is grayscale
  //  if (imageType.compare("scalar") == 0)
  //    {
  //      // read the image
  //      typedef itk::ImageFileReader <ImageType> ReaderType;
  //      ReaderType::Pointer reader = ReaderType::New();
  //      reader->SetFileName(imagePath.toAscii().data());
  //      reader->Update();
  //
  //      // set the image data provided bye the reader
  //      this->itkImage = reader->GetOutput();
  //    }
  //  else
  //    {
  //      // if the image is RGB
  //      typedef itk::ImageFileReader <RGBImageType> ReaderType;
  //      ReaderType::Pointer reader = ReaderType::New();
  //      reader->SetFileName(imagePath.toAscii().data());
  //      reader->Update();
  //
  //      // set the image data provided bye the reader
  //      this->rgbItkImage = reader->GetOutput();
  //    }



}

void QVTKImageWidget::setAndDisplayMultipleImages(QStringList filenames)
{  
    int size = filenames.size();
//  vtkSmartPointer<vtkImageData> imageStack = vtkSmartPointer<vtkImageStack>::New();
    
    
    
    
  for (int i = 0; i < filenames.size(); i++)
    {
      QString filename = filenames.at(i);
      

    }

}


void QVTKImageWidget::displayImage(vtkImageData *image)
{
  imageViewer->SetInput(image);
  imageViewer->GetRenderer()->ResetCamera();

  // make qt-vtk connection
  qvtkWidget->SetRenderWindow(imageViewer->GetRenderWindow());

  // disable interpolation, so we can see each pixel
  vtkImageActor* imageActor = imageViewer->GetImageActor();
  imageActor->InterpolateOff();

  // Picker to pick pixels
  vtkSmartPointer<vtkPropPicker> propPicker = vtkSmartPointer<vtkPropPicker>::New();
  propPicker->PickFromListOn();

  // Give the picker a prop to pick

  propPicker->AddPickList(imageActor);

  // Annotate the image with mouse over pixel information
  cornerAnnotation->SetLinearFontScaleFactor(2);
  cornerAnnotation->SetNonlinearFontScaleFactor(1);
  cornerAnnotation->SetMaximumFontSize(15);
  //    cornerAnnotation->SetText(3, "<window>\n<level>");
  cornerAnnotation->GetTextProperty()->SetColor(1, 0, 0);
  imageViewer->GetRenderer()->AddViewProp(cornerAnnotation);

  //listen to MouseMoveEvents invoked by the interactor's style
  vtkSmartPointer<QVTKImageWidgetCommand> callback =
          vtkSmartPointer<QVTKImageWidgetCommand>::New();
  callback->SetImageWidget(this);
  callback->SetAnnotation(cornerAnnotation);
  callback->SetPicker(propPicker);

  vtkSmartPointer<vtkInteractorStyleImage> imageStyle =
          vtkSmartPointer<vtkInteractorStyleImage>::New();
  imageViewer->GetRenderWindow()->GetInteractor()->SetInteractorStyle(imageStyle);
  imageStyle->AddObserver(vtkCommand::MouseMoveEvent, callback);
  imageStyle->AddObserver(vtkCommand::LeftButtonPressEvent, callback);

  // render image viewer
  imageViewer->Render();
}


void QVTKImageWidget::setImageProperties(QString path, bool verbose)
{
  std::string filename = path.toAscii().data();

  // Obtain image information
  typedef itk::ImageIOBase::IOComponentType ScalarPixelType;

  itk::ImageIOBase::Pointer imageIO =
          itk::ImageIOFactory::CreateImageIO(filename.c_str(), itk::ImageIOFactory::ReadMode);

  imageIO->SetFileName(filename);
  imageIO->ReadImageInformation();

  pixelType = imageIO->GetComponentTypeAsString(imageIO->GetComponentType());
  imageType = imageIO->GetPixelTypeAsString(imageIO->GetPixelType());
  numDimensions = imageIO->GetNumberOfDimensions();


  if (verbose)
    {
      std::cout << "Pixels type: " << pixelType << std::endl;
      std::cout << "Image type: " << imageType << std::endl;
      std::cout << "Num of Dimensions: " << numDimensions << std::endl;
      //        std::cout << "x = " << dim[0] << std::endl;
      //        std::cout << "y = " << dim[1] << std::endl;
    }
}


vtkSmartPointer<vtkImageViewer2> QVTKImageWidget::getImageViewer()
{
  return this->imageViewer;
}


int QVTKImageWidget::getXPicked()
{
  return this->xPicked;
}


int QVTKImageWidget::getYPicked()
{
  return this->yPicked;
}


void QVTKImageWidget::setXPicked(int xPosition)
{
  this->xPicked = xPosition;
}


void QVTKImageWidget::setYPicked(int yPosition)
{
  this->yPicked = xPosition;
}


QString QVTKImageWidget::getImageType()
{
  return QString(imageType.data());
}


QString QVTKImageWidget::getPixelType()
{
  return QString(pixelType.data());
}


QString QVTKImageWidget::getNumOfDimesions()
{
  QString out;
  out.setNum(numDimensions);
  return out;
}