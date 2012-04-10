//Developed by Yash Shah

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QtXml/QDomDocument>
#include<QtXml/QDomElement>
#include<QtXml/QDomNode>
#include <QMainWindow>
#include "dataStorageInterface.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(dataStorageInterface* dataStorageType, QWidget *parent = 0);
    void getData();
    void addToBuffer(eventData event);
    void displayEntriesAdded(eventData event);
    void displayOccasions();
    ~MainWindow();

private slots:
    void validateData();
    void resetFields();
    void saveData();
    void revert();

private:
    Ui::MainWindow *ui;
    QDomDocument doc;
    QDomElement root;
    dataStorageInterface* dataStorageType;
    QList<eventData> eventBufferList;
};

#endif // MAINWINDOW_H
