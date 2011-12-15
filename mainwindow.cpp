

#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    this->setAttribute(Qt::WA_DeleteOnClose);
    
    this->displayWidget = new QVTKImageWidget();
    
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->QLayout::addWidget(displayWidget);
    ui->imageWidget->setLayout(layout);
    
    // hide the slider andonly show if an image stack is load
    ui->imageSlider->hide();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::addImages()
{
    
    //    this->imagePath = QFileDialog::getExistingDirectory(); 
    //    addLogText("Set image path: <b>" + imagePath + "</b>");   
    //    printf("Image Path: %s \n", imagePath.toAscii().data());
    
    this->imagesFilenames = QFileDialog::getOpenFileNames(this, tr("Open Images"), QDir::currentPath());
    if (!imagesFilenames.isEmpty())
    {
        if (imagesFilenames.size() == 1)
        {
            ui->imageSlider->hide();
            
            addLogText("Loading: <b>" + imagesFilenames.first() + "</b>");
            displayWidget->setAndDisplayImage(imagesFilenames.first());
            
            addLogText("Image Type: <b>" + displayWidget->getImageType() + "</b>");
            addLogText("Pixel Type: <b>" + displayWidget->getPixelType() + "</b>");
            addLogText("Num of Dimensions: <b>" + displayWidget->getNumOfDimesions() + "</b>");
        }
        else
        {
            // if selected multiple files
            ui->imageSlider->show();
            ui->imageSlider->setTickInterval(1);
            ui->imageSlider->setRange(0, imagesFilenames.size() - 1);
            
            displayWidget->setAndDisplayMultipleImages(imagesFilenames);             
            for (int i = 0; i < imagesFilenames.size(); i++)
            {               
                addLogText("Loading: <b>" + imagesFilenames.at(i) + "</b>");
            }            
        }
    }
    else
    {
        QErrorMessage errorMessage;
        errorMessage.showMessage("No file specified for loading");
        errorMessage.exec();
        return;
    }
}


void MainWindow::probeCalibration()
{
    std::cout << "probe calibration" << std::endl;
}


void MainWindow::displaySelectedImage(int idx) 
{

    std::cout << idx << std::endl;
}


void MainWindow::addLogText(QString str)
{
    ui->textEdit->append(str);
    
    // move the cursor to the end of the last line
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
}




