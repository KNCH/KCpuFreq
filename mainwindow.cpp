#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QProcess>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listCPUs->setCurrentRow(0);
    /* move the mainwindow to the center of the desktop */
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonSet_clicked()
{


    QProcess *process = new QProcess(); // process for shell execution
    QList<QListWidgetItem*> items = ui->listCPUs->selectedItems(); // selected CPU(s)

    if (items.count()==1) // only one item selected
    {
        if (ui->listCPUs->currentRow()==0) // all cores
        {
            if (ui->actionCpupower->isChecked()) // use cpupower
            {
                process->execute("sudo cpupower frequency-set -g " + ui->comboBoxGovernor->currentText());
                qDebug() << "sudo cpupower frequency-set -g " + ui->comboBoxGovernor->currentText();
            }
            else // use cpufreq
            {
                process->execute("cpufreq-set -r -g " + ui->comboBoxGovernor->currentText());
                qDebug() << "cpufreq-set -r -g " + ui->comboBoxGovernor->currentText();
            }
        }
        else // a single core selected
        {
            if (ui->actionCpupower->isChecked()) // use cpupower
            {
                process->execute("sudo cpupower -c " + QString::number(ui->listCPUs->currentIndex().row()-1) + " frequency-set -g " + ui->comboBoxGovernor->currentText());
                qDebug() << "sudo cpupower -c " + QString::number(ui->listCPUs->currentIndex().row()-1) + " frequency-set -g " + ui->comboBoxGovernor->currentText();
            }
            else // use cpufreq
            {
                process->execute("cpufreq-set -c " + QString::number(ui->listCPUs->currentIndex().row()-1) + " -g " + ui->comboBoxGovernor->currentText());
                qDebug() << "cpufreq-set -c " + QString::number(ui->listCPUs->currentIndex().row()-1) + " -g " + ui->comboBoxGovernor->currentText();
            }
        }
    }
    else
    {
        foreach (QListWidgetItem *i, items)
        {
            if (ui->listCPUs->row(i)==0) // all cores, break iteration after this step
            {
                if (ui->actionCpupower->isChecked()) // use cpupower
                {
                    process->execute("sudo cpupower frequency-set -g " + ui->comboBoxGovernor->currentText());
                    qDebug() << "sudo cpupower frequency-set -g " + ui->comboBoxGovernor->currentText();
                }
                else // use cpufreq
                {
                    process->execute("cpufreq-set -r -g " + ui->comboBoxGovernor->currentText());
                    qDebug() << "cpufreq-set -r -g " + ui->comboBoxGovernor->currentText();
                }
                break;
            }
            else // apply settings for each selected core
            {
                if (ui->actionCpupower->isChecked()) // use cpupower
                {
                    process->execute("sudo cpupower -c " + QString::number(ui->listCPUs->row(i)-1) + " frequency-set -g " + ui->comboBoxGovernor->currentText());
                    qDebug() << "sudo cpupower -c " + QString::number(ui->listCPUs->row(i)-1) + " frequency-set -g " + ui->comboBoxGovernor->currentText();
                }
                else // use cpufreq
                {
                    process->execute("cpufreq-set -c " + QString::number(ui->listCPUs->row(i)-1) + " -g " + ui->comboBoxGovernor->currentText());
                    qDebug() << "cpufreq-set -c " + QString::number(ui->listCPUs->row(i)-1) + " -g " + ui->comboBoxGovernor->currentText();
                }
            }
        }
    }

}

void MainWindow::on_buttonClose_clicked()
{
}

void MainWindow::on_actionCpufreq_triggered()
{
    ui->actionCpupower->setChecked(false);
}

void MainWindow::on_actionCpupower_triggered()
{
    ui->actionCpufreq->setChecked(false);
}
