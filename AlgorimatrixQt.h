#pragma once

#include <QtWidgets/QMainWindow>
#include <QStringListModel>
#include <string>
#include "ui_AlgorimatrixQt.h"
#include "ParseResult.h"
#include "ExtendParser.h"

class AlgorimatrixQt : public QMainWindow
{
    Q_OBJECT

public slots:
    void onInput();
public:
    AlgorimatrixQt(QWidget* parent = Q_NULLPTR);

private:
    QStringList m_history;
    ExtendParser m_parser;
    QStringListModel* m_listModel;
    Ui::AlgorimatrixQtClass m_ui;
    void updateTable(ParseResult &result);
};
