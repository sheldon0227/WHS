#include <database.h>
#include <QDebug>

bool connect(const QString& dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open()) {
        qDebug() << "Database Error!";
        return false;
    }
    return true;
}
