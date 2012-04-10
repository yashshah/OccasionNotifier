//Developed by Yash Shah

#include "MainWindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QListWidget>
#include<QListWidgetItem>
#include<QString>
#include<QStaticText>
#include<QListView>
#include<QListView>

MainWindow::MainWindow(dataStorageInterface* dataStorageType,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->dataStorageType = dataStorageType;
    ui->setupUi(this);

    //Reset all the input fields
    resetFields();
    ui->dateEdit->setDisplayFormat("dd - MMMM - yyyy");

    //Display today's Occasion from the existing data
    displayOccasions();

    //Connecting to the Slots
    connect(ui->pushAdd, SIGNAL(clicked()),this, SLOT(validateData()));
    connect(ui->pushAdd, SIGNAL(clicked()),this, SLOT(resetFields()));
    connect(ui->pushSave, SIGNAL(clicked()),this, SLOT(saveData()));
    connect(ui->pushReset, SIGNAL(clicked()),this, SLOT(resetFields()));
    connect(ui->pushRevert, SIGNAL(clicked()),this, SLOT(revert()));
}

//Reset all the input fields
void MainWindow::resetFields()
{
    ui->lineName->clear();
    ui->lineEmail->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineName->setFocus();
}

//Validate the data for all input fields
void MainWindow::validateData()
{
    //regular expression for the email address
    QRegExp emailValidate("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    emailValidate.setCaseSensitivity(Qt::CaseInsensitive);
    emailValidate.setPatternSyntax(QRegExp::RegExp);

    //Validating Name entry
    if(ui->lineName->text()==NULL)
    {
        QMessageBox::critical(this,"Invalid Data", "Form Incomplete! Enter the Name", QMessageBox::Ok);
        return;
    }
    //Validating email entry
    else if(!emailValidate.exactMatch(ui->lineEmail->text()))
    {
        QMessageBox::critical(this,"Invalid Data", "Form Incomplete! Enter the Email address correctly", QMessageBox::Ok);
        return;
    }
    else
    {
        getData();
    }
}

//Get the Data from the input fields
void MainWindow::getData()
{
    eventData event;
    event.setName(ui->lineName->text());
    event.setEmailId(ui->lineEmail->text());
    event.setDate(ui->dateEdit->date().toString("dd - MMMM - yyyy"));
    event.setEventType(ui->comboBox->currentText());
    addToBuffer(event);
}

//Add the event to the buffer incase the user wants to revert
void MainWindow::addToBuffer(eventData event)
{
    eventBufferList.append(event);
    displayEntriesAdded(event);
}

//Displays the entries which are added to the buffer ready to be written
void MainWindow::displayEntriesAdded(eventData event)
{
    ui->listview->addItem(new QListWidgetItem(event.getEventType() + " - " + event.getName() + " - " + event.getDate()));
}

//Write the data from the buffer to the file
void MainWindow::saveData()
{
    if(eventBufferList.empty())
    {
        QMessageBox::critical(this,"Empty List", "List is empty. Nothing to add ", QMessageBox::Ok);
        return;
    }
    else
    {
        this->dataStorageType->addOccasions(eventBufferList);
        eventBufferList.clear();
        ui->listview->clear();
        displayOccasions();
    }
}

//Displays the Name and Occasions in the QListWidget
void MainWindow::displayOccasions()
{
    QList<eventData> eventListRetrieved = this->dataStorageType->retrieveOcassions();
    ui->listname->clear();

    for(int i=0;i<eventListRetrieved.count();i++)
    {
        ui->listname->addItem(new QListWidgetItem(eventListRetrieved.at(i).getEventType() + " - " + eventListRetrieved.at(i).getName()));

    }
}

//Clears the buffer data
void MainWindow::revert()
{
    if(eventBufferList.empty())
    {
        QMessageBox::critical(this,"Empty List", "List is empty. Nothing to revert back ", QMessageBox::Ok);
        return;
    }
    else
    {
        ui->listview->clear();
        eventBufferList.clear();
        ui->lineName->setFocus();
    }
}

//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}
