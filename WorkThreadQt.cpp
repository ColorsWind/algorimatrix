//
// Created by colors_wind on 2020/9/9.
//

#include <QtCore/QtCore>
#include "WorkThreadQt.h"
#include "ParseException.h"



void WorkThreadQt::run() {
    while (true) {
        m_semaphore.acquire();
        QString qstr = m_queue.dequeue();
        m_parser.input(qstr.toStdString());
        try {
            ParseResult result = m_parser.processS();
            emit plainText(QString::fromStdString(result.getMessage()));
            emit done(result);
        } catch (MatrixException &exception) {
            emit htmlText(QString("<html><font color=\"#FF0000\">ERROR: matrix error:  ").append(QString::fromStdString(exception.msg())).append("</font></html>"));
        } catch (ParseException &exception) {
            emit htmlText(QString("<html><font color=\"#FF0000\">ERROR: parse error:  ").append(QString::fromStdString(exception.msg())).append("</font></html>"));
        }
        emit statusbar(m_queue.size());
    }
}

void WorkThreadQt::input(QString &qstr) {
    m_queue.enqueue(qstr);
    statusbar(m_queue.size());
    m_semaphore.release();
}

WorkThreadQt::WorkThreadQt() = default;

WorkThreadQt::~WorkThreadQt() = default;

