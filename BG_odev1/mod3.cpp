#include "mod3.h"
#include "ui_mod3.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "nesneler.h"
#include "QRandomGenerator"
#include "QDebug"
#include "clickablelabel.h"

mod3::mod3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mod3)
{
    ui->setupUi(this);

    ui->setupUi(this);
    zaman_sayac = new QTimer(this);
    connect(zaman_sayac, SIGNAL(timeout()), this, SLOT(sureYaz()));
    zaman_sayac->start(1000);

    olusma_sayac = new QTimer(this);
    connect(olusma_sayac,SIGNAL(timeout()),this,SLOT(balonuret()));
    olusma_sayac->start(3000);

    yazma_sayac = new QTimer(this);
    connect(yazma_sayac,SIGNAL(timeout()),this,SLOT(dondur()));
    yazma_sayac->start(500);


    yazma_sayac = new QTimer(this);
    connect(yazma_sayac,SIGNAL(timeout()),this,SLOT(yerdegistir()));
    yazma_sayac->start(10);

    QTimer *timer=new QTimer(this);
    timer->start(50);
    connect(timer,&QTimer::timeout,this,&mod3::patlat);

    renk=qRgb(255,255,255);

}
int hareket ;
int sure3 = 0;
void mod3::sureYaz()
{
    if(sure3 == 60){
            QMessageBox::critical(this,"Uyarı","Süreniz sona ermiştir","Tamam");
            close();
            sure3 = 0 ;


        }
    QString format("Sure : <font color='blue'>%1</font>");
    ui->lbl_sure->setText(format.arg(QString::number(sure3)));
    sure3 +=1;
}

void mod3::balonuret()
{
    renk = renksec();
    Koseler.clear();
    int x = 900;
    int y = 450;


    ClickableLabel *l = new ClickableLabel(this);
    l->setGeometry(x,y,100,50);
    l->show();
    QImage arkaplan(100,100,QImage::Format_RGB32);
    arkaplan.fill(renk);
    l->setPixmap(QPixmap::fromImage(arkaplan));
    res = arkaplan;

   // renksec();

    //dikdortgenciz(l);
    yerbelirle();

    connect(l, SIGNAL(clicked()), this, SLOT(patlat()));

    _nesneler.push_back(l);


}
void mod3::dikdortgenciz(QLabel * label){
    Noktalar.setX(0);
    Noktalar.setY(0);
    Koseler.append(Noktalar);
    Noktalar.setX(100);
    Noktalar.setY(0);
    Koseler.append(Noktalar);
    Noktalar.setX(100);
    Noktalar.setY(50);
    Koseler.append(Noktalar);
    Noktalar.setX(0);
    Noktalar.setY(50);
    Koseler.append(Noktalar);
    Noktalar.setX(0);
    Noktalar.setY(0);
    Koseler.append(Noktalar);

    for(int i=0; i<Koseler.length()-1; i++)
    {
        cizdir(Koseler[i],Koseler[i+1], label);
    }
    double ortaX = (Koseler[0].x() + Koseler[1].x()+ Koseler[2].x() +Koseler[3].x())/4 ;
    double ortaY = (Koseler[0].y() + Koseler[1].y()+ Koseler[2].y() + Koseler[3].y())/4 ;
    doldur(ortaX,ortaY,res.pixel(ortaX,ortaY),renk,label);

}

QRgb mod3::renksec(){

    int random = QRandomGenerator::global()->bounded(0, 14);

    if(random == 0){
        return  renk = qRgb(255,0,0); // kırmızı
    }else if(random == 1){
       return renk = qRgb(139, 0, 0); // koyu kırmızı
    }
    else if(random == 2){
       return renk = qRgb (255, 255, 0); // sarı
    }
    else if(random == 3){
       return renk = qRgb (210 ,105, 30);// chocolate
    }
    else if(random == 4){
           return renk = qRgb(0, 255, 0); // yesil
        }
    else if(random == 5){
           return renk = qRgb  (50 ,205, 50); // lime yesil
        }
    else if(random == 6){
           return renk = qRgb (0, 206, 209); //koyu turkuaz
        }
        else if(random == 7){
           return renk = qRgb (0 ,191 ,255); // deep sky blue
        }
    else if(random == 8){
           return renk = qRgb(30 ,144 ,255); // dodger mavi
        }
        else if(random == 9){
          return  renk = qRgb (128, 0, 255); // mor
        }
    else if(random == 10){
           return renk = qRgb(132 ,112, 255); //light state blue
        }
    else if(random == 11){
            renk = qRgb(153 ,50 ,204); // medium orchid
        }
    else if(random == 12){
          return  renk = qRgb(255 ,140, 0); // dark orange
        }
    else{
       return renk = qRgb (151, 255, 255); // koyu barut grisi
    }


}

void mod3::cizdir(QPoint ilk, QPoint son, QLabel *l)
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

void mod3::doldur(int x, int y, QRgb zemin, QRgb yeniRenk, QLabel *lblDoldur)
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
void mod3::gizle(){

    if(kuyruktaki_nesneler.count()!=0){

        kuyruktaki_nesneler.at(0)->hide();
        delete kuyruktaki_nesneler.at(0);
        kuyruktaki_nesneler.removeAt(0);
    }


}

void mod3::yerbelirle(){


    int yer = QRandomGenerator::global()->bounded(0, 8);


        if(yer == 0){
            hareket = 0;
        }
        else if (yer == 1 ){
            hareket = 1;
        }
        else if (yer == 2 ){
            hareket = 2;
        }
        else if (yer == 3 ){
            hareket = 3;
        }
        else if (yer == 4 ){
            hareket = 4;
        }
        else if (yer == 5 ){
            hareket = 5;
        }
        else if (yer == 6 ){
            hareket = 6;
        }
        else {
            hareket = 7;
        }

    qDebug() << "yer:" << yer ;
}

int kacan3 = 0;
void mod3::yerdegistir()
{
    int sayisi = _nesneler.size();

    if(hareket == 0 ){

        for (int x = 0; x < sayisi; x++) {
            if(_nesneler[x]->y()< 990) {

                _nesneler[x]->setGeometry(_nesneler[x]->x(),
                                 _nesneler[x]->y() + 3,
                                 _nesneler[x]->width(),
                                 _nesneler[x]->height());

        }
        else{
            kacan3 = silinen_nesneler.size()+1;
            QString format("Kacanlar : <font color='red'>%1</font>");
            ui->lbl_kacanlar->setText(format.arg(QString::number(kacan3)));

            _nesneler.at(x)->hide();
            silinen_nesneler.append(_nesneler.at(x));
            silinen_nesneler.removeAt(x);

        }
    }
    }
    if (hareket == 1){
        for (int x = 0; x < sayisi; x++) {
            if(_nesneler[x]->x()< 1700) {
                _nesneler[x]->setGeometry(_nesneler[x]->x() +3,
                                     _nesneler[x]->y() ,
                                     _nesneler[x]->width(),
                                     _nesneler[x]->height());
            }
            else{
                kacan3 = silinen_nesneler.size()+1;
                QString format("Kacanlar : <font color='red'>%1</font>");
                ui->lbl_kacanlar->setText(format.arg(QString::number(kacan3)));

                _nesneler.at(x)->hide();
                silinen_nesneler.append(_nesneler.at(x));
                silinen_nesneler.removeAt(x);

            }
        }
    }
    if (hareket == 2){
        for (int x = 0; x < sayisi; x++) {
            if(_nesneler[x]->y() > 120) {
                _nesneler[x]->setGeometry(_nesneler[x]->x(),
                                     _nesneler[x]->y() - 3,
                                     _nesneler[x]->width(),
                                     _nesneler[x]->height());
            }
            else{
                kacan3 = silinen_nesneler.size()+1;
                QString format("Kacanlar : <font color='red'>%1</font>");
                ui->lbl_kacanlar->setText(format.arg(QString::number(kacan3)));

                _nesneler.at(x)->hide();
                silinen_nesneler.append(_nesneler.at(x));
                silinen_nesneler.removeAt(x);

            }
        }
    }
    if (hareket == 3){

        for (int x = 0; x < sayisi; x++) {
            if(_nesneler[x]->x() > 120) {
                _nesneler[x]->setGeometry(_nesneler[x]->x() -3,
                                     _nesneler[x]->y() ,
                                     _nesneler[x]->width(),
                                     _nesneler[x]->height());
            }
            else{
                kacan3 = silinen_nesneler.size()+1;
                QString format("Kacanlar : <font color='red'>%1</font>");
                ui->lbl_kacanlar->setText(format.arg(QString::number(kacan3)));

                _nesneler.at(x)->hide();
                silinen_nesneler.append(_nesneler.at(x));
                silinen_nesneler.removeAt(x);

            }
        }
    }
    if (hareket == 4){
        for (int x = 0; x < sayisi; x++) {
            if(_nesneler[x]->y()< 900 && _nesneler[x]->x() < 1400 ) {
                _nesneler[x]->setGeometry(_nesneler[x]->x() +3,
                                     _nesneler[x]->y() + 3,
                                     _nesneler[x]->width(),
                                     _nesneler[x]->height());
            }
            else{
                kacan3 = silinen_nesneler.size()+1;
                QString format("Kacanlar : <font color='red'>%1</font>");
                ui->lbl_kacanlar->setText(format.arg(QString::number(kacan3)));

                _nesneler.at(x)->hide();
                silinen_nesneler.append(_nesneler.at(x));
                silinen_nesneler.removeAt(x);

            }
        }
    }
    if (hareket == 5){
        for (int x = 0; x < sayisi; x++) {
            if(_nesneler[x]->y() > 120 && _nesneler[x]->x() < 1400) {
                _nesneler[x]->setGeometry(_nesneler[x]->x()+3,
                                     _nesneler[x]->y() - 3,
                                     _nesneler[x]->width(),
                                     _nesneler[x]->height());
            }
            else{
                kacan3 = silinen_nesneler.size()+1;
                QString format("Kacanlar : <font color='red'>%1</font>");
                ui->lbl_kacanlar->setText(format.arg(QString::number(kacan3)));

                _nesneler.at(x)->hide();
                silinen_nesneler.append(_nesneler.at(x));
                silinen_nesneler.removeAt(x);

            }
        }
    }

     if (hareket == 6){
        for (int x = 0; x < sayisi; x++) {
            if(_nesneler[x]->y()> 120 && _nesneler[x]->x() > 120) {
                _nesneler[x]->setGeometry(_nesneler[x]->x() -3,
                                     _nesneler[x]->y() + 3,
                                     _nesneler[x]->width(),
                                     _nesneler[x]->height());
            }
            else{
                kacan3 = silinen_nesneler.size()+1;
                QString format("Kacanlar : <font color='red'>%1</font>");
                ui->lbl_kacanlar->setText(format.arg(QString::number(kacan3)));

                _nesneler.at(x)->hide();
                silinen_nesneler.append(_nesneler.at(x));
                silinen_nesneler.removeAt(x);

            }
        }
    }
    if (hareket == 7){
        for (int x = 0; x < sayisi; x++) {
            if(_nesneler[x]->y() > 120 && _nesneler[x]->x() < 1400) {
                _nesneler[x]->setGeometry(_nesneler[x]->x() - 3,
                                     _nesneler[x]->y() - 3,
                                     _nesneler[x]->width(),
                                     _nesneler[x]->height());
            }
            else{
                kacan3 = silinen_nesneler.size()+1;
                QString format("Kacanlar : <font color='red'>%1</font>");
                ui->lbl_kacanlar->setText(format.arg(QString::number(kacan3)));

                _nesneler.at(x)->hide();
                silinen_nesneler.append(_nesneler.at(x));
                silinen_nesneler.removeAt(x);

            }
        }
    }

}

void mod3::dondur()
{


    for(int i=0;i<_nesneler.size();i++){
        double centerx = (_nesneler[i]->x()+ _nesneler[i]->x() +_nesneler[i]->width()) / 2;
        double centery = (_nesneler[i]->y()+ _nesneler[i]->height()+_nesneler[i]->y() ) /2 ;

        int sonx,sony;
        QList<QPoint> Yeniler;

        QPoint ilkX,sonX,ilkY,sonY;
        ilkX.setX(_nesneler[i]->x() - centerx);
        ilkX.setY(_nesneler[i]->y() - centery);
        Yeniler.append(ilkX);

        sonX.setX((_nesneler[i]->x()+ _nesneler[i]->width()) - centerx );
        sonX.setY(_nesneler[i]->y() - centery);
        Yeniler.append(sonX);

        ilkY.setX((_nesneler[i]->x()+_nesneler[i]->width()) - centerx);
        ilkY.setY((_nesneler[i]->y()+_nesneler[i]->height() ) - centery);
        Yeniler.append(ilkY);

        sonY.setX(_nesneler[i]->x() - centerx);
        sonY.setY((_nesneler[i]->y()+_nesneler[i]->height() ) - centery);
        Yeniler.append(sonY);

         for(int i = 0; i<4; i++){
             sonx = ((Yeniler[i].x()*0) - (Yeniler[i].y()*1)) + centerx;
             sony = ((Yeniler[i].x()*-1) + (Yeniler[i].y()*0)) + centery;
             Yeniler[i].setX(sonx);
             Yeniler[i].setY(sony);
         }

        double enbuyukX=  Yeniler[0].x(),enbuyukY = Yeniler[0].y(),enkucukX = Yeniler[0].x(),enkucukY =  Yeniler[0].y();
        for(int i = 1; i<4; i++){
            if( Yeniler[i].x() > enbuyukX){
                enbuyukX = Yeniler[i].x();
            }
            if( Yeniler[i].x() < enkucukX){
                enkucukX = Yeniler[i].x();
            }
            if( Yeniler[i].y() > enbuyukY){
                enbuyukY = Yeniler[i].y();
            }
            if( Yeniler[i].y() < enkucukY){
                enkucukY = Yeniler[i].y();
            }
        }

        _nesneler[i]->setGeometry(enkucukX,enkucukY,enbuyukX - enkucukX, enbuyukY - enkucukY);
    }


}

int vurulan3 = 0;
void mod3::patlat()
{
    QObject *balon_label = QObject::sender();
    int i;
    for(i=0;i<_nesneler.size();i++){
        if(_nesneler[i] == balon_label){
            vurulan3 = vurulan3+1;
            QString format("Vurulanlar : <font color='green'>%1</font>");
            ui->lbl_vurulanlar->setText(format.arg(QString::number(vurulan3)));
           // QString temp = "p";

           // _nesneler[i]->setIcon(QIcon(temp));
           // _nesneler[i]->setIconSize(QSize(50,50));

            kuyruktaki_nesneler.append(_nesneler.at(i));

            _nesneler.removeAt(i);

            QTimer::singleShot(2500, this, SLOT(gizle()));

        }
    }
}
mod3::~mod3()
{
    delete ui;
}
