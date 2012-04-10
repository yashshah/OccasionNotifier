//Developed by Yash Shah

#include <QtGui/QApplication>
#include "MainWindow.h"
#include "dataStorageInterface.h"
#include "dataStorageXML.h"
#include "dataStorageCSV.h"
#include<QMessageBox>
#include <string.h>
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dataStorageInterface* dataStorageType;
    if(argv[1] && strcmp(argv[1], "-xml")==0)
    {

        dataStorageType = new dataStorageXML();
    }
    else if(argv[1] && strcmp(argv[1], "-csv")==0)
    {
        dataStorageType = new dataStorageCSV();
    }
    else
    {
        qDebug()<<"Data storage argument Expected!";
        qDebug()<<"-csv for CSV Data Storage";
        qDebug()<<"-xml for XML Data Storage";
        return 0;
    }

    MainWindow *w = new MainWindow(dataStorageType);
    w->show();
    return a.exec();
}


