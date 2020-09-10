//
// Created by colors_wind on 2020/9/9.
//

#ifndef ALGORIMATRIX_WORKTHREADQT_H
#define ALGORIMATRIX_WORKTHREADQT_H


#include <QtCore/QThread>
#include <QtCore/QSemaphore>
#include <QtCore/QString>
#include <QQueue>
#include "ExtendParser.h"


class WorkThreadQt : public QThread
{
    Q_OBJECT
private:
    QSemaphore m_semaphore;
    QQueue<QString> m_queue;
    ExtendParser m_parser;
public:
    WorkThreadQt();
    ~WorkThreadQt() override;
    void run() override;
    void input(QString &qstr);
signals:
    void plainText(const QString &message);
    void htmlText(const QString &message);
    void statusbar(int rest);
    void done(const ParseResult &result);
};


#endif //ALGORIMATRIX_WORKTHREADQT_H
