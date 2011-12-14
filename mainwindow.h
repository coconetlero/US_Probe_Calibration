#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

#include "QVTKImageWidget.h"

class QAction;
    
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void addLogText(QString str);
    
    
private:
    Ui::MainWindow *ui;
    
    /** \brief The filename of each selected image */
    QStringList imagesFilenames;
    
    QString textOnTextArea;
    
    /**
     * Central widget for display image purposes
     */
    QVTKImageWidget *displayWidget;
    
    
    
    
private slots:
    
    /**
     * \brief Add image folder to application
     */
    void addImages();
    
    /**
     * \brief Implements a ultrasound 3D probe calibration, for navigate with the 
     * probe
     */
    void probeCalibration();
    
};




#endif // MAINWINDOW_H
