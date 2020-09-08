
#include "AlgorimatrixQt.h"
#include "ParseException.h"
#include "ExtendParser.h"
#include <QStandardItemModel>
#include <iostream>
using std::endl;

AlgorimatrixQt::AlgorimatrixQt(QWidget *parent)
    : QMainWindow(parent)
{
    m_ui.setupUi(this);
    connect(m_ui.m_in, SIGNAL(returnPressed()), this, SLOT(onInput()));
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Size"));
    m_ui.m_map ->setModel(model);
}


void AlgorimatrixQt::onInput() {
    QString qstr = m_ui.m_in-> text();
    m_ui.m_out -> appendPlainText(">> " + qstr);
    parser.input(qstr.toStdString());
    try {
        ParseResult result = parser.processS();
        m_ui.m_out -> appendPlainText(QString::fromStdString(result.getMessage()));
        updateTable(result);
    } catch (MatrixException &exception) {
        m_ui.m_out -> appendHtml(QString("<html><font color=\"#FF0000\">ERROR: matrix error:  ").append(QString::fromStdString(exception.msg())).append("</font></html>"));
    } catch (ParseException &exception) {
        m_ui.m_out -> appendHtml(QString("<html><font color=\"#FF0000\">ERROR: parse error:  ").append(QString::fromStdString(exception.msg())).append("</font></html>"));
    }
    m_ui.m_in -> clear();
}

void AlgorimatrixQt::updateTable(ParseResult &result) {
    QStandardItemModel* model = dynamic_cast<QStandardItemModel *>(m_ui.m_map->model());
    QList<QStandardItem *> items = model -> findItems(QString::fromStdString(result.getVariable()));
    if (result.isRemove() && items.size() > 0) {
        model -> removeRow(items[0] -> row());
    } else if (!result.isRemove() && items.size() > 0){
        items[0] -> setText(QString::fromStdString(result.getSize()));
    } else if (!result.isRemove() && items.size() == 0) {
        int index = model->rowCount();
        model->setItem(index, 0, new QStandardItem(QString::fromStdString(result.getVariable())));
        model->setItem(index, 1, new QStandardItem(QString::fromStdString(result.getSize())));

    }
}
