#include "resultdialog.h"
#include "ui_resultdialog.h"

ResultDialog::ResultDialog(const QString &text, QTableWidgetItem *item, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);
    ui->label->setText(text);
    this->item=item;
}

ResultDialog::~ResultDialog()
{
    delete ui;
}
void ResultDialog::on_pushButton_clicked()
{
    item->setText(ui->comboBox->currentText());
    this->close();
}
