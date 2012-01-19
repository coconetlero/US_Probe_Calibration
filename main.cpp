#include <QtGui/QApplication>
#include "mainwindow.h"


class MainApplication : public QApplication
{
public:
    MainApplication(int argc, char** argv) : QApplication(argc, argv) {}
    
    virtual ~MainApplication() {}
    
    // reimplemented from QApplication so we can throw exceptions in slots
    virtual bool notify(QObject * receiver, QEvent * event) {
        try {
            return QApplication::notify(receiver, event);
        } catch(std::exception& e) {
            qCritical() << "Exception thrown:" << e.what();
        }
        return false;
    }
};


int main(int argc, char *argv[])
{
    MainApplication app(argc, argv);
    MainWindow *window = new MainWindow;
    window->show();

    return app.exec();
}


