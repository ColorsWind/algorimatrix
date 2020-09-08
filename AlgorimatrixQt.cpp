
#include "AlgorimatrixQt.h"
#include "ParseException.h"
#include <QStandardItemModel>
#include <QCompleter>
#include <iostream>
#include <QStringListModel>

AlgorimatrixQt::AlgorimatrixQt(QWidget *parent)
    : QMainWindow(parent)
{
    m_ui.setupUi(this);
    connect(m_ui.m_in, SIGNAL(returnPressed()), this, SLOT(onInput()));
    auto model = new QStandardItemModel(this);
    model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Size"));
    m_ui.m_map ->setModel(model);
    m_listModel = new QStringListModel(m_history, this);

    auto *com = new QCompleter(m_listModel, m_ui.m_in);
    com->setCompletionMode(QCompleter::CompletionMode::PopupCompletion);
    com->setCaseSensitivity(Qt::CaseInsensitive);
    m_ui.m_in ->setCompleter(com);
}


void AlgorimatrixQt::onInput() {
    QString qstr = m_ui.m_in -> text();
    m_ui.m_out -> appendPlainText(">> " + qstr);
    m_parser.input(qstr.toStdString());
    try {
        ParseResult result = m_parser.processS();
        m_ui.m_out -> appendPlainText(QString::fromStdString(result.getMessage()));
        m_history.append(qstr);
        m_listModel->setStringList(m_history);
        updateTable(result);
    } catch (MatrixException &exception) {
        m_ui.m_out -> appendHtml(QString("<html><font color=\"#FF0000\">ERROR: matrix error:  ").append(QString::fromStdString(exception.msg())).append("</font></html>"));
    } catch (ParseException &exception) {
        m_ui.m_out -> appendHtml(QString("<html><font color=\"#FF0000\">ERROR: parse error:  ").append(QString::fromStdString(exception.msg())).append("</font></html>"));
    }
    m_ui.m_in -> clear();

}


void AlgorimatrixQt::updateTable(ParseResult &result) {
    auto model = dynamic_cast<QStandardItemModel *>(m_ui.m_map->model());
    QList<QStandardItem *> items = model -> findItems(QString::fromStdString(result.getVariable()));
    if (result.isRemove() && !items.empty()) {
        model -> removeRow(items[0] -> row());
    } else if (!result.isRemove() && !items.empty()){
        model -> item(items[0]->row(), 1) -> setText(QString::fromStdString(result.getSize()));
    } else if (!result.isRemove() && items.empty()) {
        int index = model->rowCount();
        auto qStandardItem = new QStandardItem(QString::fromStdString(result.getVariable()));
        qStandardItem -> setEditable(false);
        model->setItem(index, 0, qStandardItem);
        qStandardItem = new QStandardItem(QString::fromStdString(result.getSize()));
        model->setItem(index, 1, qStandardItem);
        qStandardItem -> setEditable(false);
    }
}

