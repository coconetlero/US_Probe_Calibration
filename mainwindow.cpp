

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
    
    this->imagePath = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::currentPath()); 
    addLogText("Loading: <b>" + imagePath + "</b>");
    
    displayWidget->setAndDisplayImage(imagePath);

    
    
    addLogText("Image Type: <b>" + displayWidget->getImageType() + "</b>");
    addLogText("Pixel Type: <b>" + displayWidget->getPixelType() + "</b>");
    addLogText("Num of Dimensions: <b>" + displayWidget->getNumOfDimesions() + "</b>");
}


void MainWindow::addMasks() 
{
    this->maskPath = QFileDialog::getExistingDirectory();    
    addLogText("Set mask path: <b>" + maskPath + "</b>");
}


void MainWindow::addLogText(QString str) {
    ui->textEdit->append(str);   
        
    // move the cursor to the end of the last line
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
}