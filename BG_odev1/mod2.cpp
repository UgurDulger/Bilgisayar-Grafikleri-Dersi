#include "mod2.h"
#include "ui_mod2.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "nesneler.h"
#include "QRandomGenerator"
#include "QDebug"
#include "clickablelabel.h"

mod2::mod2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mod2)
{
    ui->setupUi(this);
    zaman_sayac = new QTimer(this);
    connect(zaman_sayac, SIGNAL(timeout()), this, SLOT(sureYaz()));
    zaman_sayac->start(1000);

    olusma_sayac = new QTimer(this);
    connect(olusma_sayac,SIGNAL(timeout()),this,SLOT(balonuret()));
    olusma_sayac->start(800);

   yazma_sayac = new QTimer(this);
   connect(yazma_sayac,SIGNAL(timeout()),this,SLOT(yerdegistir()));
   yazma_sayac->start(10);

   //yazma_sayac = new QTimer(this);
   //connect(yazma_sayac,SIGNAL(timeout()),this,SLOT(olceklendir()));
  // yazma_sayac->start(500);

    QTimer *timer=new QTimer(this);
    timer->start(50);
    connect(timer,&QTimer::timeout,this,&mod2::patlat);

    uzunluk =2000;
    genislik = 2000;

    renk=qRgb(255 ,255, 255);
}
int sure1 = 0;
void mod2::sureYaz()

{

    if(sure1 == 60){
            QMessageBox::critical(this,"Uyarı","Süreniz sona ermiştir","Tamam");
            close();
            sure1 = 0 ;


        }
    QString format("Sure : <font color='blue'>%1</font>");
    ui->lbl_sure->setText(format.arg(QString::number(sure1)));
    sure1 +=1;

}

void mod2::balonuret()
{
    Koseler.clear();
    int x = 0;
    int y = 120 + rand() % 800;

    if(_nesneler1.size() > 1){
        int sayisi = _nesneler1.size();
        for (int i = 0; i < sayisi-1 ; i++){
            if( x >_nesneler1[i]->x()+ 82 || x + 82 < _nesneler1[i]->x() || y > _nesneler1[i]->y()+ 82 || y +82 < _nesneler1[i]->y() ){
                 x = 0;
                 y = 120 + rand() % 800;
            }
       }
    }
    ClickableLabel *l = new ClickableLabel(this);
    l->setGeometry(x,y,82,82);
    l->show();
    QImage arkaplan(82,82,QImage::Format_RGB32);
    arkaplan.fill(qRgb(192 ,255, 62));
    l->setPixmap(QPixmap::fromImage(arkaplan));
    res = arkaplan;


    int random1 = QRandomGenerator::global()->bounded(0, 7);

    renksec();

    if(random1 == 0){

        eskenarkareciz(l);
    }
    else if( random1 == 1 ){
        ucgenciz(l);
    }
    else if(random1 == 2 ){
        kareciz(l);
    }
    else if(random1 == 3 ){
        dikdortgenciz(l);
    }
    else if(random1 == 4 ){
            besgenciz(l);
    }
    else if(random1 == 5 ){
            altigencizdir(l);
    }
    else{
        Noktalar.setX(40);
        Noktalar.setY(40);
        Koseler.append(Noktalar);

    }


    if( random1 != 6){

    }else{
        int x = 40;
        int y = 0;
        int hata = 0;
        int hata1; // x, y+1
        int hata2; //
        simetriBul(x, y);
        while(x >= y) {
            //QApplication::processEvents();
            hata1 = hata + 2*y + 1;
            hata2 = hata + 2*y + 1 - 2*x + 1;
            if (abs(hata1) < abs(hata2)) {
                y++;
                hata = hata1;
            } else {
                x--;
                y++;
                hata = hata2;
            }
            simetriBul(x, y);
            l->setPixmap(QPixmap::fromImage(res));
        }

        doldur(40,40,res.pixel(40,40),renk,l);
    }

    connect(l, SIGNAL(clicked()), this, SLOT(patlat()));

    _nesneler1.push_back(l);



}

void mod2::simetriBul(int X, int Y)
{
    res.setPixel(40 + X, 40 + Y, renk);
    res.setPixel(40 + Y, 40 + X, renk);
    res.setPixel(40 - Y, 40 + X, renk);
    res.setPixel(40 - X, 40 + Y, renk);
    res.setPixel(40 - X, 40 - Y, renk);
    res.setPixel(40 - Y, 40 - X, renk);
    res.setPixel(40 + Y, 40 - X, renk);
    res.setPixel(40 + X, 40 - Y, renk);
}
void mod2::ucgenciz(QLabel * label){
    Noktalar.setX(41);
    Noktalar.setY(1);
    Koseler.append(Noktalar);
    Noktalar.setX(81);
    Noktalar.setY(81);
    Koseler.append(Noktalar);
    Noktalar.setX(1);
    Noktalar.setY(81);
    Koseler.append(Noktalar);
    Noktalar.setX(41);
    Noktalar.setY(1);
    Koseler.append(Noktalar);

    for(int i=0; i<Koseler.length()-1; i++)
    {
        cizdir(Koseler[i],Koseler[i+1], label);
    }
    double ortaX = (Koseler[0].x() + Koseler[1].x()+ Koseler[2].x())/3 ;
    double ortaY = (Koseler[0].y() + Koseler[1].y()+ Koseler[2].y())/3 ;
    doldur(ortaX,ortaY,res.pixel(ortaX,ortaY),renk,label);


}
void mod2::altigencizdir(QLabel * label) {
    Noktalar.setX(41);
    Noktalar.setY(1);
    Koseler.append(Noktalar);
    Noktalar.setX(81);
    Noktalar.setY(27);
    Koseler.append(Noktalar);
    Noktalar.setX(81);
    Noktalar.setY(54);
    Koseler.append(Noktalar);
    Noktalar.setX(41);
    Noktalar.setY(81);
    Koseler.append(Noktalar);
    Noktalar.setX(1);
    Noktalar.setY(54);
    Koseler.append(Noktalar);
    Noktalar.setX(1);
    Noktalar.setY(27);
    Koseler.append(Noktalar);
    Noktalar.setX(41);
    Noktalar.setY(1);
    Koseler.append(Noktalar);

    for(int i=0; i<Koseler.length()-1; i++)
    {
        cizdir(Koseler[i],Koseler[i+1], label);
    }
    double ortaX = (Koseler[0].x() + Koseler[1].x()+ Koseler[2].x())/3 ;
    double ortaY = (Koseler[0].y() + Koseler[1].y()+ Koseler[2].y())/3 ;
    doldur(ortaX,ortaY,res.pixel(ortaX,ortaY),renk,label);
}
void mod2::eskenarkareciz(QLabel * label) {
    Noktalar.setX(41);
    Noktalar.setY(81);
    Koseler.append(Noktalar);
    Noktalar.setX(81);
    Noktalar.setY(41);
    Koseler.append(Noktalar);
    Noktalar.setX(41);
    Noktalar.setY(0);
    Koseler.append(Noktalar);
    Noktalar.setX(0);
    Noktalar.setY(41);
    Koseler.append(Noktalar);
    Noktalar.setX(41);
    Noktalar.setY(81);
    Koseler.append(Noktalar);

    for(int i=0; i<Koseler.length()-1; i++)
    {
        cizdir(Koseler[i],Koseler[i+1], label);
    }
    double ortaX = (Koseler[0].x() + Koseler[1].x()+ Koseler[2].x()+ Koseler[3].x() )/4 ;
    double ortaY = (Koseler[0].y() + Koseler[1].y()+ Koseler[2].y()+ Koseler[3].y() )/4 ;
    doldur(ortaX,ortaY,res.pixel(ortaX,ortaY),renk,label);

}
void mod2::dikdortgenciz(QLabel * label) {
    Noktalar.setX(1);
    Noktalar.setY(1);
    Koseler.append(Noktalar);
    Noktalar.setX(81);
    Noktalar.setY(1);
    Koseler.append(Noktalar);
    Noktalar.setX(81);
    Noktalar.setY(41);
    Koseler.append(Noktalar);
    Noktalar.setX(1);
    Noktalar.setY(41);
    Koseler.append(Noktalar);
    Noktalar.setX(1);
    Noktalar.setY(1);
    Koseler.append(Noktalar);

    for(int i=0; i<Koseler.length()-1; i++)
    {
        cizdir(Koseler[i],Koseler[i+1], label);
    }
    double ortaX = (Koseler[0].x() + Koseler[1].x()+ Koseler[2].x() +Koseler[3].x())/4 ;
    double ortaY = (Koseler[0].y() + Koseler[1].y()+ Koseler[2].y() + Koseler[3].y())/4 ;
    doldur(ortaX,ortaY,res.pixel(ortaX,ortaY),renk,label);
}
void mod2::besgenciz(QLabel * label) {
    Noktalar.setX(41);
    Noktalar.setY(1);
    Koseler.append(Noktalar);
    Noktalar.setX(81);
    Noktalar.setY(32);
    Koseler.append(Noktalar);
    Noktalar.setX(62);
    Noktalar.setY(81);
    Koseler.append(Noktalar);
    Noktalar.setX(22);
    Noktalar.setY(81);
    Koseler.append(Noktalar);
    Noktalar.setX(1);
    Noktalar.setY(32);
    Koseler.append(Noktalar);
    Noktalar.setX(41);
    Noktalar.setY(1);
    Koseler.append(Noktalar);

    for(int i=0; i<Koseler.length()-1; i++)
    {
        cizdir(Koseler[i],Koseler[i+1], label);
    }
    double ortaX = (Koseler[0].x() + Koseler[1].x()+ Koseler[2].x()+ Koseler[3].x() +Koseler[4].x())/5 ;
    double ortaY = (Koseler[0].y() + Koseler[1].y()+ Koseler[2].y()+ Koseler[3].y() +Koseler[4].y())/5 ;
    doldur(ortaX,ortaY,res.pixel(ortaX,ortaY),renk,label);
}
void mod2::kareciz(QLabel * label){
    Noktalar.setX(0);
    Noktalar.setY(0);
    Koseler.append(Noktalar);
    Noktalar.setX(82);
    Noktalar.setY(0);
    Koseler.append(Noktalar);
    Noktalar.setX(82);
    Noktalar.setY(82);
    Koseler.append(Noktalar);
    Noktalar.setX(0);
    Noktalar.setY(82);
    Koseler.append(Noktalar);
    Noktalar.setX(0);
    Noktalar.setY(0);
    Koseler.append(Noktalar);

    for(int i=0; i<Koseler.length()-1; i++)
    {
        cizdir(Koseler[i],Koseler[i+1], label);
    }
    double ortaX = (Koseler[0].x() + Koseler[1].x()+ Koseler[2].x()+ Koseler[3].x())/4 ;
    double ortaY = (Koseler[0].y() + Koseler[1].y()+ Koseler[2].y()+ Koseler[3].y())/4 ;
    doldur(ortaX,ortaY,res.pixel(ortaX,ortaY),renk,label);
}
void mod2::renksec(){

    int random = QRandomGenerator::global()->bounded(-1, 14);

    if(random == 0){
        renk = qRgb(255,0,0); // kırmızı
    }else if(random == 1){
        renk = qRgb(139, 0, 0); // koyu kırmızı
    }
    else if(random == 2){
        renk = qRgb (255, 255, 0); // sarı
    }
    else if(random == 3){
        renk = qRgb (210 ,105, 30);// chocolate
    }
    else if(random == 4){
            renk = qRgb(0, 255, 0); // yesil
        }
    else if(random == 5){
            renk = qRgb  (50 ,205, 50); // lime yesil
        }
    else if(random == 6){
            renk = qRgb (0, 206, 209); //koyu turkuaz
        }
        else if(random == 7){
            renk = qRgb (0 ,191 ,255); // deep sky blue
        }
    else if(random == 8){
            renk = qRgb(30 ,144 ,255); // dodger mavi
        }
        else if(random == 9){
            renk = qRgb (128, 0, 255); // mor
        }
    else if(random == 10){
            renk = qRgb(132 ,112, 255); //light state blue
        }
    else if(random == 11){
            renk = qRgb(153 ,50 ,204); // medium orchid
        }
    else if(random == 12){
            renk = qRgb(255 ,140, 0); // dark orange
        }
    else{
        renk = qRgb (151, 255, 255); // koyu barut grisi
    }


}
void mod2::cizdir(QPoint ilk, QPoint son, QLabel *l)
{
    double dx=son.x()-ilk.x();
    double dy=son.y()-ilk.y();
    double Xartim, Yartim;
    double adim;
    double x,y;
    if(fabs(dx)>fabs(dy))
    {
        adim=fabs(dx);
    }
    else
    {
        adim=fabs(dy);
    }
    Xartim=dx/adim;
    Yartim=dy/adim;
    x=ilk.x();
    y=ilk.y();
    for(int i=0; i<adim; i++)
    {

        x+=Xartim;
        y+=Yartim;
        res.setPixel(round(x),round(y),renk);
        l->setPixmap(QPixmap::fromImage(res));
    }

}

void mod2::doldur(int x, int y, QRgb zemin, QRgb yeniRenk, QLabel *lblDoldur)
{

    if(res.pixel(x,y)==zemin)
    {
        res.setPixel(x,y,yeniRenk);
        lblDoldur->setPixmap(QPixmap::fromImage(res));
        doldur(x+1,y,zemin,yeniRenk,lblDoldur);
        doldur(x-1,y,zemin,yeniRenk,lblDoldur);
        doldur(x,y+1,zemin,yeniRenk,lblDoldur);
        doldur(x,y-1,zemin,yeniRenk,lblDoldur);
    }
}
void mod2::gizle(){

    if(kuyruktaki_nesneler.count()!=0){

        kuyruktaki_nesneler.at(0)->hide();
        delete kuyruktaki_nesneler.at(0);
        kuyruktaki_nesneler.removeAt(0);
    }


}
int kacan1 = 0;

void mod2::yerdegistir()
{
    int sayisi = _nesneler1.size()-1;
    for (int y = 0; y < sayisi; y++) {
        if(_nesneler1[y]->x()< 1800) {
            _nesneler1[y]->setGeometry(_nesneler1[y]->x()+3,
                                 _nesneler1[y]->y(),
                                 _nesneler1[y]->width(),
                                 _nesneler1[y]->height());
        }
        else{
            kacan1 = silinen_nesneler.size()+1;
            QString format("Kacanlar : <font color='red'>%1</font>");
            ui->lbl_kacanlar->setText(format.arg(QString::number(kacan1)));

            _nesneler1.at(y)->hide();
            silinen_nesneler.append(_nesneler1.at(y));
            silinen_nesneler.removeAt(y);

        }
    }
}
int vurulan1 = 0;
void mod2::patlat()
{
    QObject *balon_label = QObject::sender();
    int i;
    for(i=0;i<_nesneler1.size();i++){
        if(_nesneler1[i] == balon_label){
            vurulan1 = vurulan1+1;
            QString format("Vurulanlar : <font color='green'>%1</font>");
            ui->lbl_vurulanlar->setText(format.arg(QString::number(vurulan1)));
           // QString temp = "p";

           // _nesneler[i]->setIcon(QIcon(temp));
           // _nesneler[i]->setIconSize(QSize(50,50));

            kuyruktaki_nesneler.append(_nesneler1.at(i));

            _nesneler1.removeAt(i);

            QTimer::singleShot(2500, this, SLOT(gizle()));

        }
    }
}


mod2::~mod2()
{
    delete ui;
}

