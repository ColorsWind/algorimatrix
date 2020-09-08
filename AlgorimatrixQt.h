#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_AlgorimatrixQt.h"

class AlgorimatrixQt : public QMainWindow
{
    Q_OBJECT

public slots:
    void onInput();
public:
    AlgorimatrixQt(QWidget* parent = Q_NULLPTR);

private:
    Ui::AlgorimatrixQtClass ui;


};
