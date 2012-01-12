#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

#include "QVTKImageWidget.h"
#include <vtkEventQtSlotConnect.h>


class QAction;

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void addLogText(QString str);

  /**
   * \brief return this display widget
   * \param[out] this display widget 
   */
  QVTKImageWidget* getDisplayWidget();



private:
  Ui::MainWindow *ui;

  /** \brief The filename of each selected image */
  QStringList imagesFilenames;

  QString textOnTextArea;

  /**
   * Central widget for display image purposes
   */
  QVTKImageWidget *displayWidget;


  vtkSmartPointer<vtkEventQtSlotConnect> Connections;

private slots:

  /**
   * \brief Add image folder to application
   */
  void addImages();

  /** 
   * \brief Display selected image with the image slider
   */
  void displaySelectedImage(int idx);

  /**
   * \brief Implements a ultrasound 3D probe calibration, for navigate with the 
   * probe
   */
  void probeCalibration();

  
  void print();
};




#endif // MAINWINDOW_H
