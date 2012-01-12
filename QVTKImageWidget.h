//
//  QVTKImageWidget.h
//  US_Probe_Calibration
//
//  Created by Zian Fanti on 01/12/11.
//  Copyright (c) 2011 __UNAM__. All rights reserved.
//

#ifndef US_Probe_Calibration_QVTKImageWidget_h
#define US_Probe_Calibration_QVTKImageWidget_h

#include <QtGui>
#include <QWidget>
#include <QVTKWidget.h>

#include <itkImage.h>
#include <itkRGBPixel.h>

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkImageActor.h>

#include <vtkCommand.h>
#include <vtkImageViewer2.h>
#include <vtkCornerAnnotation.h>


typedef itk::RGBPixel< unsigned char > RGBPixelType;
typedef itk::Image< unsigned char > ImageType;
typedef itk::Image< RGBPixelType, 2> RGBImageType;


class QVTKImageWidget : public QWidget {
    Q_OBJECT    
    
public:
    /** 
     * Constructor for this ImageWidget 
     */
    QVTKImageWidget(QWidget *parent = 0);
    
    /**
     * Destructor
     */
    virtual ~QVTKImageWidget();
    
    /**
     * Sets and display an image from a given image path
     */
    void setAndDisplayImage(QString imageFilename);
    
    
    /**
     * \brief Sets and display the given vtkImageData
     * \param[in] a vtkImageData to set and display
     */
    void setAndDisplayImage(vtkSmartPointer<vtkImageData> image);
    
    
    /**
     * \brief Set and display multiple images from a given images filenames. Display 
     * the image corresponding to the first element on the filenmaes list.
     * \param[in] a QStringList that contain the filename of each image 
     */
    void setAndDisplayMultipleImages(QStringList filenames);
    
    
    /**
     * \brief Set and display multiple images from a given vtkImageData Array.      
     * \param[in] a std::vector of vtkImageData 
     */
    void setAndDisplayMultipleImages(std::vector< vtkSmartPointer<vtkImageData> > imageStack);
    
    
    /**
     * \brief display an image stored in this imageStack. 
     * \param[in] the index in the stack position of the image 
     */
    void displaySelectedImage(int idx);
    
    
    /***************************
     *   get and set methods
     ***************************/
    QString getPixelType();
    
    QString getImageType();
    
    QString getNumOfDimesions();
    
    /** \brief return this image stack */
    std::vector< vtkSmartPointer<vtkImageData> > getImageStack();
    
    /** 
     * returns an array with the width and height of the image
     */ 
    int* getImageSize();
    
    /**
     * returns this image width
     */
    int getImageWidth();
    
    /**
     * returns this image heigth
     */
    int getImageHeigth();
    
    /**
     * \brief Return the mouse x coordinate position when mouse left button is pressed
     * \param[out] int x position
     */
    int getXPicked();
    
    /**
     * \brief Return the mouse y coordinate position when mouse left button is pressed
     * \param[out] int y position
     */
    int getYPicked();
    
    /**
     * \brief Set the mouse x coordinate position when mouse left button is pressed
     * \param[out] int x position
     */
    void setXPicked(int xPosition);
    
    /**
     * \brief Set the mouse y coordinate position when mouse left button is pressed
     * \param[out] int y position
     */
    void setYPicked(int yPosition);
    
    
    
    /**
     * \brief Return this widget image viewer
     * \param[out] imageViewer vtkImageViewer2 target 2D image.
     */
    vtkSmartPointer<vtkImageViewer2> getImageViewer();
    
    /**
     * \brief Return this qvtkWidget 
     * \param[out] the QVTKWidget
     */
    QVTKWidget* getQVTKWidget();
    
    
    /** \brief If an image stack is loaded, then return the index in the image 
     * stack of displayed image 
     */
    int getImageDisplayedIndex();
    
    
    /** \brief Flag to know if it's displayed an image stack */
    bool isImageStackLoaded;
    
    
private:    

    /** 
     * The QVTKWidget for display and interact with the images
     */
    QVTKWidget* qvtkWidget;
    
    /** The grayscale image displayed in this widget */
    ImageType::Pointer itkImage;
    
    /** The RGB image displayed for this widget */
    RGBImageType::Pointer rgbItkImage;
    
    /** The VTK image to display i this window */
    vtkSmartPointer <vtkImageData> vtkImage;    
    
    /** \brief A vtkImageData Vector for keep the image references when load an 
     * image stack.
     */
    std::vector< vtkSmartPointer<vtkImageData> > imageStack;

    /** The type of the image pixels */
    std::string pixelType;
    
 
    /** the number of scalar components in the image 1 => grayscale, 3 => rgb */
    int imageType;
    
    /** The number of the image dimensions */
    size_t numDimensions;
    
    /** Width of the image */
    int imageWidth;
    
    /** Heigth of the image */
    int imageHeight;
     
    /** current x coordinate of mouse position over the image */
    int xPosition;
    
    /** current y coordinate of mouse position over the image */
    int yPosition;

    /** The x coordinate of the picked position over the image */
    int xPicked;
    
    /** current y coordinate of picked position over the image */
    int yPicked;
    
    /** If image stack is displayed this sets a reference to current image displayed */
    int imageDisplayedIndex;
    
    
    /**
     * Set the needed image properties (pixelType, imageType, num of dimensions)     
     */
    void setImageProperties(bool verbose);
    
    /**
     * Display the given vtkImage
     */
    void displayImage(vtkImageData *image);
    
    
 
    
    /* -------- necesary vtk objects to display an image ------ */
    
    /** the image viewer for display images */
    vtkSmartPointer<vtkImageViewer2> imageViewer;
    
    /** \brief Object for display information in the corners of the vtkImageViewer2 */
    vtkSmartPointer<vtkCornerAnnotation> cornerAnnotation;
    
    /** the actor for the image */
//    vtkSmartPointer<vtkImageActor> actor;
    /** the camera to include into imageViewer */
//    vtkSmartPointer<vtkCamera> camera;
    
//    vtkSmartPointer<vtkRenderer> renderer;
//    vtkSmartPointer<vtkRenderWindow> renderWindow;
//    vtkSmartPointer<vtkRenderWindowInteractor> interactor; 
    
};

#endif
