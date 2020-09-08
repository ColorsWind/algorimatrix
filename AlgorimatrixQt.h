#pragma once

#include <QtWidgets/QMainWindow>
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
    ExtendParser parser;
    Ui::AlgorimatrixQtClass m_ui{};
    void updateTable(ParseResult &result);
};
