#include "eventData.h"

eventData::eventData()
{
}

QString eventData::getName() const
{
    return this->name;
}

QString eventData::getEmailID() const
{
    return this->emailId;
}

QString eventData::getDate() const
{
    return this->date;
}

QString eventData::getEventType() const
{
    return this->eventType;
}

void eventData::setName(QString name)
{
    this->name = name;
}

void eventData::setEmailId(QString emailid)
{
    this->emailId = emailid;
}

void eventData::setDate(QString date)
{
    this->date = date;
}

void eventData::setEventType(QString type)
{
    this->eventType = type;
}

//Destructor
eventData::~eventData()
{
}

