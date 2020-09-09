#pragma once

#include <QtWidgets/QMainWindow>
#include <QStringListModel>
#include <string>
#include "ui_AlgorimatrixQt.h"
#include "ParseResult.h"
#include "ExtendParser.h"
#include "WorkThreadQt.h"

class AlgorimatrixQt : public QMainWindow {
    Q_OBJECT

public slots:

    void onInput();

    void updateStatusBar(int rest);

    void processDone(ParseResult result);

    void appendPlainText(QString qstr);

    void appendHtmlText(QString qstr);

public:
    AlgorimatrixQt(QWidget *parent = Q_NULLPTR);

private:
    QStringList m_history;
    WorkThreadQt *m_workThread;
    QStringListModel *m_listModel;
    Ui::AlgorimatrixQtClass m_ui;

    void updateTable(ParseResult &result);

};