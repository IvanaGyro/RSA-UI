#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bigint.h>

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
    void on_pButton_genkey_clicked();

    void on_pButton_goC_clicked();

    void on_pButton_goP_clicked();

    void on_rButton_512_toggled(bool checked);

    void on_rButton_1024_toggled(bool checked);

    void on_rButton_2048_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    //Bigint p, q, n, fi_n, d, e = 0x10001;
    Bigint p, q, n, fi_n, fi_fi_n, d, e, cp, cq;
    int bits_of_n = 128;
    int bytes_of_curkey;

};

#endif // MAINWINDOW_H
