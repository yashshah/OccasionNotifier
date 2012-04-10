#ifndef EVENTDATA_H
#define EVENTDATA_H
#include <QString>

class eventData
{
public:
    eventData();
    QString getName() const;
    QString getEmailID() const;
    QString getDate() const;
    QString getEventType() const;
    void setName(QString name);
    void setEmailId(QString emailId);
    void setDate(QString date);
    void setEventType(QString eventType);
    ~eventData();

private:
    QString name,emailId,date,eventType;
};

#endif // EVENTDATA_H
