#include "nesneler.h"
#include "QDebug"


nesneler::nesneler(QWidget *parrent):QPushButton(parrent)
{
    tiklandimi=false;
    connect(this,&QPushButton::clicked,this,&nesneler::tikla);
}

void nesneler::tikla()
{

    tiklandimi = true;

}
