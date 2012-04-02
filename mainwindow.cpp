//Developed by Yash Shah

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QTextStream>
#include<QtXml/QDomDocument>
#include<QtXml/QDomElement>
#include<QtXml/QDomNode>
#include<QMessageBox>
#include<QListWidget>
#include<QListWidgetItem>
#include<QString>
#include<QStaticText>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resetfields();
    ui->dateEdit->setDisplayFormat("dd - MMMM - yyyy");
    checkOccasions();

    InitializeXML();
    connect(ui->pushAdd, SIGNAL(clicked()),this, SLOT(addOccasions()));
    connect(ui->pushAdd, SIGNAL(clicked()),this, SLOT(resetfields()));
    connect(ui->pushReset, SIGNAL(clicked()), this, SLOT(resetfields()));

//    QFont font("Helvetica", 11, QFont::Bold);
//    ui->notificationsBar->setFont(font);
}

//Displays the Name and Occasion on the QListWidget

void MainWindow::displayOccasions(QString name, QString type)
{
    if ((QString::compare(type,"Birthday"))==0)
    {
        ui->listname->addItem(new QListWidgetItem("Birthday - " + name));
    }

    if ((QString::compare(type,"Wedding Anniversary"))==0)
    {
        ui->listname->addItem(new QListWidgetItem("Anniversary - " + name));
    }
}

//Write the XML file it doesn't exist for storing the data
void MainWindow::InitializeXML()
{

        QFile file( "Data.xml" );
        if(!file.exists())
        {
            doc = (QDomDocument)"OccasionNotifier";
            root = doc.createElement( "Occasions" );
            doc.appendChild(root);
            if( !file.open(QIODevice::WriteOnly))
                return;

            QTextStream ts( &file );
            ts << doc.toString();
            file.close();

        }

}

//Reset all the input fields to blank
void MainWindow::resetfields()
{
    ui->lineName->clear();
    ui->lineEmail->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineName->setFocus();
}

//Adds an Event to the data.xml File
QDomElement MainWindow::EventToNode( QDomDocument &DomDocument)
{
    QDomElement EventEntry = DomDocument.createElement( "Event" );
    QString type = ui->comboBox->currentText();
    EventEntry.setAttribute( "Type", type);
    QDomElement name = DomDocument.createElement( "Name" );
    QDomText txtName = DomDocument.createTextNode(QString(ui->lineName->text()));
    name.appendChild(txtName);
    EventEntry.appendChild(name);

    QDomElement email = DomDocument.createElement( "Email" );
    QDomText emailid = DomDocument.createTextNode(QString(ui->lineEmail->text()));
    email.appendChild(emailid);
    EventEntry.appendChild(email);

    QString DateAsString = ui->dateEdit->date().toString("dd - MMMM - yyyy");
    QDomElement date = DomDocument.createElement( "Date" );
    QDomText Date = DomDocument.createTextNode(DateAsString);
    date.appendChild(Date);
    EventEntry.appendChild(date);

    if(date.text()==QDate::currentDate().toString("dd - MMMM - yyyy"))
    {
        displayOccasions(name.text(), type);
    }

    return EventEntry;
}

//Add Records input by the user to the XML file
void MainWindow::addOccasions()
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
    //Validatin email entry
    else if(!emailValidate.exactMatch(ui->lineEmail->text()))
    {
        QMessageBox::critical(this,"Invalid Data", "Form Incomplete! Enter the Email address correctly", QMessageBox::Ok);
        return;
    }
    else
    {
        // Reading Xml file
        QFile file( "Data.xml" );
        doc = (QDomDocument)"OccasionNotifier";

        /* If we can't open it, let's show an error message. */
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this,"Error", "Couldn't open data.xml for reading", QMessageBox::Ok);
            return;
        }

        if (!doc.setContent(&file))
        {
            return;
        }

        //Get the root element
        QDomElement root = doc.documentElement();
        root.appendChild(EventToNode(doc));

        file.close();

        // Writing Xml file
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this,"Error", "Couldn't open Data.xml for writing", QMessageBox::Ok);
            return;
        }

        QTextStream ts( &file );
        ts << doc.toString();
        file.close();
        QMessageBox::information(this,"Occasion Notifier", "Event Added!");

    }
}

//Reads the XML file on the application startup to display today's occasion
void MainWindow::checkOccasions()
{

    QFile file( "Data.xml" );

    /* If we can't open it, let's show an error message. */
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       return;
    }

    QDomDocument domDocument("OccasionNotifier");
    if (!domDocument.setContent(&file))
    {
        return;
    }

    //Get the root element
    QDomElement docElem = domDocument.documentElement();


    // get the node list
    QDomNodeList nodeList = docElem.elementsByTagName("Event");

    //Check each node one by one.
    for(int i = 0;i < nodeList.count(); i++)
    {
        // get the current one as QDomElement
        QDomElement currentElement = nodeList.at(i).toElement();

        // get the attribute type
        QString type = currentElement.attribute("Type");

        //get all data for the element, by looping through all child elements
        QDomNode Entries = currentElement.firstChild();
        QString name, email,date;

        //Check for current data
        while(!Entries.isNull())
        {
            QDomElement currentData = Entries.toElement();
            QString tagName = currentData.tagName();

            if(tagName == "Name")
            {
                name = currentData.text();
            }
            else if(tagName == "Email")
            {
                email = currentData.text();
            }
            else if(tagName == "Date")
            {
                date = currentData.text();
            }

            Entries = Entries.nextSibling();
        }

        if(date==QDate::currentDate().toString("dd - MMMM - yyyy"))
        {
            displayOccasions(name, type);
        }
    }
}




//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}
