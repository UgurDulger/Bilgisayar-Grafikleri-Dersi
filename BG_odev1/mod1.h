#ifndef MOD1_H
#define MOD1_H

#include <QMainWindow>
#include <QMainWindow>
#include <QApplication>
#include <QStyle>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include "nesneler.h"
#include "clickablelabel.h"

namespace Ui {
class mod1;
}

class mod1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit mod1(QWidget *parent = nullptr);
    ~mod1();

public slots:
    void sureYaz();
    void balonuret();
    void yerdegistir();
    void patlat();
    void gizle();
    void balontime();

    void doldur(int x, int y, QRgb zemin, QRgb yeniRenk, QLabel *lblDoldur);
    void cizdir(QPoint ilk, QPoint son, QLabel *l);
    void simetriBul(int X, int Y);

    void olceklendir();
    void renksec();
    void kareciz(QLabel *label);
    void besgenciz(QLabel *label);
    void ucgenciz(QLabel *label);
    void eskenarkareciz(QLabel *label);
    void dikdortgenciz(QLabel *label);
    void altigencizdir(QLabel *label);
private:
    Ui::mod1 *ui;

    QPoint ilkNokta , sonNokta;
    QImage res;
    QRgb renk;

    QList<ClickableLabel*> _nesneler;
    QList<ClickableLabel*> kuyruktaki_nesneler;
    QList<ClickableLabel*> silinen_nesneler;

    int uzunluk;
    int genislik;

    QTimer *zaman_sayac;
    QTimer *olusma_sayac;
    QTimer *yazma_sayac;


    QPoint Noktalar;
    QList<QPoint> Koseler;
};

#endif // MOD1_H
