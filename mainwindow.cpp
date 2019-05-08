#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <func_bigint.h>
#include <time.h>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(0));
    e.setbits(32);
    e = 0x10001;
    ui->tBrowser_P->setText(QString("Computing 1024 bits of key needs 162secs.\n2048 needs twice\ndefault is 128bits"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pButton_genkey_clicked()
{

    Bigint tmp(bits_of_n*2);
    p.setbits(bits_of_n/2);
    q.setbits(bits_of_n/2);
    n.setbits(bits_of_n);
    fi_n.setbits(bits_of_n);
    fi_fi_n.setbits(bits_of_n);
    d.setbits(bits_of_n);
    cp.setbits(bits_of_n/2);
    cq.setbits(bits_of_n/2);
    fi_n = 0;
    cp = 0;
    cq = 0;
    bytes_of_curkey = bits_of_n/32;
    unsigned int mr_times = 0;
    while(bits_of_n ^ (1<<mr_times)) mr_times++;
    mr_times += 2;

    while(fi_n % e == 0){    
        p.random1__1();
        q.random1__1();
        while(!Func_Bigint::mr(p,mr_times)) p.random1__1();
        while(!Func_Bigint::mr(q,mr_times)) q.random1__1();
        n = p * q;
        fi_n = (p-1)*(q-1);
    }
    Bigint x((e.getbytes4_num()+fi_n.getbytes4_num())*32), y((e.getbytes4_num()+fi_n.getbytes4_num())*32);
    bool xp, yp;
    Func_Bigint::xGCD(e, fi_n, x, y, xp, yp);
    d = x;
    x = e *d;
    x = x%fi_n;
    if(x != 1) on_pButton_genkey_clicked();
    else{
        ui->tBrowser_P->setText(QString(p.toString_dec().c_str()));
        ui->tBrowser_Q->setText(QString(q.toString_dec().c_str()));
    }
}

void MainWindow::on_pButton_goC_clicked()
{
    std::string s_tmp = ui->tEdit_Plain->toPlainText().toStdString();
    std::string ciphertext = "";
    const unsigned int* plaintext = (unsigned int*)s_tmp.c_str();
    const char* cptr;
    unsigned int magic_bits = 0x7efefeff;
    Bigint Bp((bytes_of_curkey)*32), Btmp((bytes_of_curkey)*32), Btmp2((bytes_of_curkey)*32);

    while(plaintext){
        Bp = 0;
        for(unsigned int i = 0; i<Bp.getbytes4_num()-1 && plaintext; i++){
            if ((((*plaintext + magic_bits) ^ ~*plaintext) & ~magic_bits) != 0 ) {
                cptr = (const char*)plaintext;
                int count = 0;
                while(*cptr != 0){
                    *(Bp.getnum()+i) |= (((int)*cptr)<<(8*count));
                    cptr++;
                    count++;
                }
                plaintext = NULL;
            }
            else{
                *(Bp.getnum()+i) = *plaintext;
                plaintext++;
            }
        }
        std::cout << Bp.toString_bin() << std::endl;
        Bp = Func_Bigint::power(Bp, e, n);
        ciphertext += Bp.toString_0dec();
        std::cout << Bp.toString_bin() << std::endl;
    }
    ui->tEdit_Cipher->setText(QString(ciphertext.c_str()));
}

void MainWindow::on_pButton_goP_clicked()
{
    Bigint Bc(bytes_of_curkey*32);

    std::string s_tmp = ui->tEdit_Cipher->toPlainText().toStdString();
    std::string plaintext = "";
    char* cptr;
    int Bc_num, digit;
    std::string::iterator siter;

    if(s_tmp.size() % ((int)(Bc.getbytes4_num()*32*_log2)+1) != 0) plaintext = "The wrong ciphertext.";
    else{
        digit = Bc.getbytes4_num()*32*_log2+1;
        Bc_num = s_tmp.size()/digit;
        siter = s_tmp.begin();
        for(int i = 0; i<Bc_num; i++){
            Bc = 0;
            for(int j = 0; j<digit; j++){
                Bc += (*siter - 48);
                if(j < digit - 1) Bc *= 10;
                siter++;
            }
            std::cout << Bc.toString_bin() << std::endl;
            Bc = Func_Bigint::CRT(p, q, d, Bc, cp, cq);
            std::cout << Bc.toString_bin() << std::endl;
            cptr = (char*)Bc.getnum();
            while(*cptr){
                plaintext += *cptr;
                cptr++;
            }
        }

    }

    ui->tEdit_Plain->setText(QString(plaintext.c_str()));
    std::cout << s_tmp.size() << std::endl;

}

void MainWindow::on_rButton_512_toggled(bool checked)
{
    if(checked) bits_of_n = 512;
}

void MainWindow::on_rButton_1024_toggled(bool checked)
{
    if(checked) bits_of_n = 1024;
}

void MainWindow::on_rButton_2048_toggled(bool checked)
{
    if(checked) bits_of_n = 2048;
}
