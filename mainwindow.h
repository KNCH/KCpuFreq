#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QSettings>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /*!
     * \fn MainWindow(QWidget *parent = 0);
     *
     * \brief Default constructor.
     * Sets up main window.
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    /*!
     * \fn on_buttonSet_clicked();
     *
     * \brief Sets up frequency governor for selected CPU(s).
     */
    void on_buttonSet_clicked();

    /*!
     * \fn on_buttonClose_clicked();
     *
     * \brief Closes the application.
     */
    void on_buttonClose_clicked();

    /*!
     * \fn on_actioCpufreq_triggered();
     *
     * \brief Unchecks menu "cpupower".
     */
    void on_actionCpufreq_triggered();

    /*!
     * \fn on_actionCpupower();
     *
     * \brief Unchecks menu "cpufreq".
     */
    void on_actionCpupower_triggered();

private:
    /*!
     * \var ui
     *
     * \brief UI of the main window.
     */
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
