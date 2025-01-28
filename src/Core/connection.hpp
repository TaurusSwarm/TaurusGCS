#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <QObject>
#include <mavsdk/mavsdk.h>

using namespace mavsdk;

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr);
    ~Connection() = default;
    void connect();

public slots:
    // void connection_changed();


signals:

private:
    Mavsdk* _mavsdk;
};

#endif // CONNECTION_HPP
