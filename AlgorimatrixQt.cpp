
#include "AlgorimatrixQt.h"
#include "ParseException.h"
#include "ExtendParser.h"
#include <QStandardItemModel>

AlgorimatrixQt::AlgorimatrixQt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connect(ui.m_in, SIGNAL(returnPressed()), this, SLOT(onInput()));
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Size"));
    ui.m_map ->setModel(model);
}

#include <iostream>
using std::endl;
void AlgorimatrixQt::onInput() {
    QString qstr = ui.m_in-> text();
    ExtendParser parser;
    parser.input(qstr.toStdString());
    try {
        ui.m_out -> appendPlainText(QString::fromStdString(parser.processS()));
    } catch (MatrixException &exception) {
        ui.m_out -> appendHtml(QString("<html><font color=\"#FF0000\">ERROR: matrix error:  ").append(QString::fromStdString(exception.msg())).append("</font></html>"));
    } catch (ParseException &exception) {
        ui.m_out -> appendHtml(QString("<html><font color=\"#FF0000\">ERROR: parse error:  ").append(QString::fromStdString(exception.msg())).append("</font></html>"));
    }
    ui.m_in -> clear();
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Size"));

    int i = 0;
    for(auto iter=parser.m_matrix.begin();i<parser.m_matrix.size();i++, iter++) {
        model->setItem(i, 0,  new QStandardItem(QString::fromStdString(iter -> first)));
        model->setItem(i, 1, new QStandardItem(QString::fromStdString(iter -> second.sizeString())));
    }
    ui.m_map ->setModel(model);
}
