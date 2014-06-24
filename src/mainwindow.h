#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtablewidget.h>
#include "Chess_tournament_64.h"
#include "Date.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ExitButton_clicked();

    void on_NextTournButton_clicked();

    void on_AddPlayerButton_clicked();

    void on_ReloadButton_clicked();

    void on_StartTournamentButton_clicked();

    void on_MatchesTW_itemClicked(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
    Tournament *T;
};

#endif // MAINWINDOW_H
