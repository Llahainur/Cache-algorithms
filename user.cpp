#include "user.h"

User::User()
{

}

void User::run(int mode)
{
    while(1)
    {
        qDebug("running");
        this->msleep(500);
    }
}
