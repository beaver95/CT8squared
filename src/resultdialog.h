#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(const QString &text, QTableWidgetItem *item, QWidget *parent);
    ~ResultDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ResultDialog *ui;
    QTableWidgetItem *item;

};

#endif // RESULTDIALOG_H
