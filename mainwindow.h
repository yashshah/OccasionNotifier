//Developed by Yash Shah

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QtXml/QDomDocument>
#include<QtXml/QDomElement>
#include<QtXml/QDomNode>
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void displayOccasions(QString,QString);
    QDomElement EventToNode( QDomDocument &);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void InitializeXML();

public slots:
        void addOccasions();
        void checkOccasions();
        void resetfields();

private:
    Ui::MainWindow *ui;
    QDomDocument doc;
    QDomElement root;
};

#endif // MAINWINDOW_H
