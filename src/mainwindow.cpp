#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"
#include "Chess_tournament_64.h"
#include <vector>
#include "resultdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), T(new Round_Robin_Tournament(""))
{
    ui->setupUi(this);
    ui->comboTitleIn->setCurrentIndex(7);
    ui->MatchesTW->setColumnWidth(0, 40);
    ui->MatchesTW->setColumnWidth(1, 260);
    ui->MatchesTW->setColumnWidth(2, 260);
    ui->MatchesTW->setColumnWidth(3, 60);
    ui->MatchesTW->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->TableTV->setColumnWidth(0, 140);
    ui->TableTV->setColumnWidth(1, 160);
    ui->TableTV->setColumnWidth(2, 100);
    ui->TableTV->setColumnWidth(3, 72);
    ui->TableTV->setColumnWidth(4, 73);
    ui->TableTV->setColumnWidth(5, 73);
    ui->TableTV->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->TableTV->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->MatchesTW->setAutoFillBackground(false);
    ui->TabForm->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ExitButton_clicked()
{
     this->close();
}

void MainWindow::on_AddPlayerButton_clicked()
{
    if(T->getCurrentTourn()==0&&ui->lineNameIn->text()!=""&&ui->lineSurnameIn->text()!="")
    {
        T->addPlayer(Player(Chess_Player(ui->lineNameIn->text().toStdString(),
                                         ui->lineSurnameIn->text().toStdString(),
                                         ui->dateBirthdayIn->date().day(),
                                         ui->dateBirthdayIn->date().month(),
                                         ui->dateBirthdayIn->date().year(),
                                         ui->spinRatingIn->value(),
                                         ui->comboTitleIn->currentIndex()),T));
        ui->labelMenuInfo->setText("Player was added!");
        ui->lineNameIn->setText("");
        ui->lineSurnameIn->setText("");
        ui->dateBirthdayIn->setDate(QDate(1990,1,1));
        ui->spinRatingIn->setValue(1600);
        ui->comboTitleIn->setCurrentIndex(7);
    }
    else
        ui->labelMenuInfo->setText("Player wasn't added.");
}

void MainWindow::on_ReloadButton_clicked()
{
    ui->labelMenuInfo->setText("Tournament table was updated");
    std::vector<Player> V=T->getTable(T->getCurrentTourn());
    int i=0;
    for (vector<Player>::iterator iter = V.begin(); iter!=V.end(); iter++)
    {
        if(ui->TableTV->rowCount()<=i)
        {
            ui->TableTV->insertRow(i);
            ui->TableTV->setRowHeight(i, 20);
            Player p = *iter;
            QTableWidgetItem *item0=new QTableWidgetItem;
            QTableWidgetItem *item1=new QTableWidgetItem;
            QTableWidgetItem *item2=new QTableWidgetItem;
            QTableWidgetItem *item3=new QTableWidgetItem;
            QTableWidgetItem *item4=new QTableWidgetItem;
            QTableWidgetItem *item5=new QTableWidgetItem;
            ui->TableTV->setItem(i, 0, item0);
            ui->TableTV->setItem(i, 1, item1);
            ui->TableTV->setItem(i, 2, item2);
            ui->TableTV->setItem(i, 3, item3);
            ui->TableTV->setItem(i, 4, item4);
            ui->TableTV->setItem(i, 5, item5);
            item0->setText(QString(p.getName().c_str()));
            item1->setText(QString(p.getSurname().c_str()));
            item2->setText(QString(p.getTitle_F().c_str()));
            item3->setText(QString().setNum(0.5*p.getPoints()));
            item4->setText(QString().setNum(0.5*p.getBukholz()));
            item5->setText(QString().setNum(0.25*p.getBerger()));
        }
        else
        {
            Player p = *iter;
            ui->TableTV->item(i, 0)->setText(QString(p.getName().c_str()));
            ui->TableTV->item(i, 1)->setText(QString(p.getSurname().c_str()));
            ui->TableTV->item(i, 2)->setText(QString(p.getTitle_F().c_str()));
            ui->TableTV->item(i, 3)->setText(QString().setNum(0.5*p.getPoints()));
            ui->TableTV->item(i, 4)->setText(QString().setNum(0.5*p.getBukholz()));
            ui->TableTV->item(i, 5)->setText(QString().setNum(0.25*p.getBerger()));
        }
        ++i;
    }/**/
    ui->TableTV->verticalHeader()->activateWindow();
    ui->TableTV->setColumnWidth(0, 140-ui->TableTV->verticalHeader()->width());
}

void MainWindow::on_StartTournamentButton_clicked()
{
    if(T->startTournament())
    {
        ui->labelMenuInfo->setText("Tournament was started!");
        ui->StartTournamentButton->setEnabled(false);
        ui->NextTournButton->setEnabled(true);
        ui->TabForm->setTabEnabled(1,false);
        std::vector<vector<Match>::iterator> V=T->getTourn(T->getCurrentTourn());
        int i=0;
        for (std::vector<vector<Match>::iterator>::iterator iter = V.begin(); iter!=V.end(); iter++)
        {
            ui->MatchesTW->insertRow(i);
            Match m = **iter;
            QTableWidgetItem *item0=new QTableWidgetItem;
            QTableWidgetItem *item1=new QTableWidgetItem;
            QTableWidgetItem *item2=new QTableWidgetItem;
            QTableWidgetItem *item3=new QTableWidgetItem;
            ui->MatchesTW->setItem(i, 0, item0);
            ui->MatchesTW->setItem(i, 1, item1);
            ui->MatchesTW->setItem(i, 2, item2);
            ui->MatchesTW->setItem(i, 3, item3);
            item0->setText(QString().setNum(i+1));
            item1->setText(QString(T->getPlayer(m.getWhite()).getSurname().c_str()));
            item2->setText(QString(T->getPlayer(m.getBlack()).getSurname().c_str()));
            item3->setText("N/A");
            ++i;
        }
    }
    else
        ui->labelMenuInfo->setText("Needs more then three players for start.");
}

void MainWindow::on_NextTournButton_clicked()
{
    if(T->getCurrentTourn()>T->getNumberOfTourns())
    {
        ui->labelMenuInfo->setText("Tournament was finished");
        return;
    }
    std::vector<vector<Match>::iterator> V=T->getTourn(T->getCurrentTourn());
    int i=0;
    std::string src;
    for (std::vector<vector<Match>::iterator>::iterator iter = V.begin(); iter!=V.end(); iter++)
    {
        //Match m = **iter;
        src=ui->MatchesTW->item(i,3)->text().toStdString();
        if(src=="1:0") (**iter).setResult(0);
        if(src=="1/2") (**iter).setResult(1);
        if(src=="0:1") (**iter).setResult(2);
        if(src=="+:-") (**iter).setResult(3);
        if(src==" = ") (**iter).setResult(4);
        if(src=="-:+") (**iter).setResult(5);
        ++i;
    }
    bool flag=false;
    if(!T->NextTourn())
        ui->labelMenuInfo->setText("You must specify the results of matches");
    else{
        V=T->getTourn(T->getCurrentTourn());
        if(T->getCurrentTourn()>T->getNumberOfTourns())
            ui->TabForm->setTabEnabled(2,false);
        flag=true;
        on_ReloadButton_clicked();
        ui->labelMenuInfo->setText("Next tourn started");
    }
    i=0;
    for (std::vector<vector<Match>::iterator>::iterator iter = V.begin(); iter!=V.end(); iter++)
    {
        Match m = **iter;
        ui->MatchesTW->item(i, 0)->setText(QString().setNum(i+1));
        ui->MatchesTW->item(i, 1)->setText(QString(T->getPlayer(m.getWhite()).getSurname().c_str()));
        ui->MatchesTW->item(i, 2)->setText(QString(T->getPlayer(m.getBlack()).getSurname().c_str()));
        if(flag)
            ui->MatchesTW->item(i, 3)->setText("N/A");
        ++i;
    }
}

void MainWindow::on_MatchesTW_itemClicked(QTableWidgetItem *item)
{
    QString text=QString(ui->MatchesTW->item(item->row(),1)->text())+=QString("-")+=QString(ui->MatchesTW->item(item->row(),2)->text());
    ResultDialog *result=new ResultDialog(text, ui->MatchesTW->item(item->row(),3),this);
    result->open();
}
