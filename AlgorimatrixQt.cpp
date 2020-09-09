
#include "AlgorimatrixQt.h"
#include "ParseException.h"
#include "WorkThreadQt.h"
#include <QStandardItemModel>
#include <QCompleter>
#include <iostream>
#include <QStringListModel>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

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
    auto com = new QCompleter(m_listModel, m_ui.m_in);
    com->setCompletionMode(QCompleter::CompletionMode::PopupCompletion);
    com->setCaseSensitivity(Qt::CaseInsensitive);
    m_ui.m_in ->setCompleter(com);
    m_workThread = new WorkThreadQt();
    m_workThread -> moveToThread(new QThread(this);
    m_workThread->start();
    connect(m_workThread, SIGNAL(plainText(QString)), this, SLOT(appendPlainText(QString)), Qt::QueuedConnection);
    connect(m_workThread, SIGNAL(htmlText(QString)), this, SLOT(appendHtmlText(QString)), Qt::QueuedConnection);
    connect(m_workThread, SIGNAL(statusbar(int)), this, SLOT(updateStatusBar(int)), Qt::QueuedConnection);
    connect(m_workThread, SIGNAL(done(ParseResult)), this, SLOT(processDone(ParseResult)), Qt::QueuedConnection);
    updateStatusBar(0);
}

void AlgorimatrixQt::appendPlainText(QString qstr) {
    m_ui.m_out -> appendPlainText(qstr);
}

void AlgorimatrixQt::appendHtmlText(QString qstr) {
    m_ui.m_out -> appendHtml(qstr);
}

void AlgorimatrixQt::onInput() {
    QString qstr = m_ui.m_in -> text();
    m_ui.m_out -> appendPlainText(">> " + qstr);
    m_workThread-> input(qstr);
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

void AlgorimatrixQt::updateStatusBar(int rest) {
    if (rest > 0) {
        m_ui.m_statusBar -> setStyleSheet("color:red");
        m_ui.m_statusBar -> showMessage(QString::fromStdString("Busy #" + to_string(rest)));
    } else {
        m_ui.m_statusBar -> setStyleSheet("color:green");
        m_ui.m_statusBar -> showMessage(tr("Ready"));
    }

}

void AlgorimatrixQt::processDone(ParseResult result) {
    m_history.append(QString::fromStdString(result.getCommand()));
    m_listModel->setStringList(m_history);
    updateTable(result);
}

