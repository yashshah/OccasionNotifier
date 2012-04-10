#include "dataStorageXML.h"
#include<QFile>
#include<QTextStream>
#include<QMessageBox>
#include<QListWidget>
#include<QListWidgetItem>
#include<QString>
#include<QStaticText>
#include<QtXml/QDomDocument>
#include<QtXml/QDomElement>
#include<QtXml/QDomNode>
#include<QDate>

dataStorageXML::dataStorageXML()
{
    file.setFileName("data.xml");
}

bool dataStorageXML::addOccasions(QList<eventData> eventListToBeAdded)
{
    if(!file.exists())
    {
        doc = (QDomDocument)"OccasionNotifier";
        root = doc.createElement( "Occasions" );
        doc.appendChild(root);
        if( !file.open(QIODevice::WriteOnly))
            return false;

        QTextStream stream( &file );
        stream << doc.toString();
        file.close();

    }

    // Reading Xml file
    doc = (QDomDocument)"OccasionNotifier";

    /* If we can't open it, let's show an error message. */
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(0,"Error", "Couldn't open data.xml for reading", QMessageBox::Ok);
        return false;
    }


    if (!doc.setContent(&file))
    {
        QMessageBox::critical(0,"Error", "Couldn't read the content of the XML file", QMessageBox::Ok);
        return false;
    }

    //Get the root element
    root = doc.documentElement();
    QList<QDomElement> eventToNodeList = eventToNode(doc,eventListToBeAdded);
    for(int i=0; i < eventToNodeList.count();i++)
    {
        root.appendChild(eventToNodeList.at(i));
    }


    file.close();

    //Writing Xml file
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(0,"Error", "Couldn't open Data.xml for writing", QMessageBox::Ok);
        return false;
    }

    QTextStream stream( &file );
    stream << doc.toString();
    file.close();

    return true;
}

//Returns the list of today's Occasion
QList<eventData> dataStorageXML::retrieveOcassions()
{
    QList<eventData> eventListRetrieved;

    /* If we can't open it, let's show an error message. */
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //return ;
    }

    QDomDocument domDocument("OccasionNotifier");
    if (!domDocument.setContent(&file))
    {
        //return;
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

        //Check if there is any Occassion today and appending them to the list
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

    return eventListRetrieved;
}

QList<QDomElement> dataStorageXML::eventToNode(QDomDocument &DomDocument, QList<eventData> eventListToBeAdded)
{
    QList<QDomElement> eventEntryList;
    QDomElement eventEntry;

    for(int i=0;i<eventListToBeAdded.count();i++)
    {
        eventEntry = DomDocument.createElement( "Event" );
        QString type = eventListToBeAdded.at(i).getEventType();
        eventEntry.setAttribute( "Type", type);
        QDomElement name = DomDocument.createElement( "Name" );
        QDomText txtName = DomDocument.createTextNode(eventListToBeAdded.at(i).getName());
        name.appendChild(txtName);
        eventEntry.appendChild(name);

        QDomElement email = DomDocument.createElement( "Email" );
        QDomText emailid = DomDocument.createTextNode(eventListToBeAdded.at(i).getEmailID());
        email.appendChild(emailid);
        eventEntry.appendChild(email);

        QString DateAsString = eventListToBeAdded.at(i).getDate();
        QDomElement date = DomDocument.createElement( "Date" );
        QDomText Date = DomDocument.createTextNode(DateAsString);
        date.appendChild(Date);
        eventEntry.appendChild(date);
        eventEntryList.append(eventEntry);
    }

    return eventEntryList;
}

