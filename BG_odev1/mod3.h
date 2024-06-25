#ifndef MOD3_H
#define MOD3_H

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
class mod3;
}

class mod3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit mod3(QWidget *parent = nullptr);
    ~mod3();

public slots:
    void sureYaz();
    void balonuret();
    void yerdegistir();
    void patlat();
    void gizle();

    void doldur(int x, int y, QRgb zemin, QRgb yeniRenk, QLabel *lblDoldur);
    void cizdir(QPoint ilk, QPoint son, QLabel *l);


    QRgb renksec();
    void dikdortgenciz(QLabel *label);


    void yerbelirle();
    void dondur();
private:
    Ui::mod3 *ui;

    QPoint ilkNokta , sonNokta;
    QImage res;
    QRgb renk;

    QList<ClickableLabel*> _nesneler;
    QList<ClickableLabel*> kuyruktaki_nesneler;
    QList<ClickableLabel*> silinen_nesneler;

    QList<ClickableLabel*> sagagidenler;
    QList<ClickableLabel*> solagidenler;
    QList<ClickableLabel*> yukarigidenler;
    QList<ClickableLabel*> asagigidenler;
    QList<ClickableLabel*> solyukarigidenler;
    QList<ClickableLabel*> solasagigidenler;
    QList<ClickableLabel*> sagyukarigidenler;
    QList<ClickableLabel*> sagasagigidenler;



    QTimer *zaman_sayac;
    QTimer *olusma_sayac;
    QTimer *yazma_sayac;


    QPoint Noktalar;
    QList<QPoint> Koseler;
};

#endif // MOD3_H
