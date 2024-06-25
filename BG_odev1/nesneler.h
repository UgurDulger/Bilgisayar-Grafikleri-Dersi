#ifndef BALON_H
#define BALON_H
#include <QPushButton>

class nesneler : public QPushButton
{
    Q_OBJECT
public:
    nesneler(QWidget *parrent=0);
    bool tiklandimi;
public slots:
    void tikla();
};

#endif // YENIBTN_H
