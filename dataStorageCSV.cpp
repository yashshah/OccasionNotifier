#include "dataStorageCSV.h"
#include <QtGui/QApplication>
#include<QStringList>
#include<QMessageBox>
#include<QDate>

dataStorageCSV::dataStorageCSV()
{
    //Write the CSV file it doesn't exist for storing the data
    file.setFileName("data.csv");
}

//Writes the data to the file in the order NAME,EMAILID,EVENTTYPE,DATE
bool dataStorageCSV::addOccasions(QList<eventData> eventListToBeAdded)
{
    if ( file.open( QIODevice::Append ) )
    {
        QTextStream stream( &file );
        for(int i=0;i<eventListToBeAdded.count();i++)
            stream <<eventListToBeAdded.at(i).getName()<< "," <<eventListToBeAdded.at(i).getEmailID()<< "," <<eventListToBeAdded.at(i).getEventType()<<","<<eventListToBeAdded.at(i).getDate()<<"\n";
    }
    file.close();
    return true;
}

//Returns the list of today's Occasion
QList<eventData> dataStorageCSV::retrieveOcassions()
{
    QList<eventData> eventListRetrieved;
    if ( file.open(QIODevice::ReadOnly) )
    {
        QString stream,name,email,type,date;
        stream = file.readAll();
        QRegExp csv(",|\n");
        QStringList values = stream.split(csv);

        for (int i=0;i<values.size()-1;i=i+4)
        {
            name = values.at(i);
            email = values.at(i+1);
            type = values.at(i+2);
            date = values.at(i+3);

            //Check if the Occassion is today, then append to the list
            if(date==QDate::currentDate().toString("dd - MMMM - yyyy"))
            {
                eventData temp;
                temp.setName(name);
                temp.setEmailId(email);
                temp.setDate(date);
                temp.setEventType(type);
                eventListRetrieved.append(temp);
            }
        }
    }

    file.close();
    return eventListRetrieved;
}
