#ifndef USER_H
#define USER_H

#include <QThread>
#include <QDebug>
#include <QListWidget>
#include <QTimer>


class User:public QThread
{
public:
    User();
    void run(int mode);
    QListWidget * cache;
    QListWidget * file;
};

#endif // USER_H
