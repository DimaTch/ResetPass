#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    btn1.setText("Генератор");
//        btn1.setDefault(true);
    btn2.setText("Выход");
    lbl.setFrameStyle(QFrame::Box);
    lbl.setAlignment(Qt::AlignCenter);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(&lbl);
    layout->addWidget(&le);
    QHBoxLayout *layout_h = new QHBoxLayout;
    layout_h->addWidget(&btn1);
    layout_h->addWidget(&btn2);
    layout->addLayout(layout_h);
    setLayout(layout);
    resize(150,150);
    connect(&btn1,SIGNAL(clicked()),this,SLOT(generate_btn()));
    connect(&btn2,SIGNAL(clicked(bool)),this,SLOT(close()));


}

Widget::~Widget()
{

}

void Widget::generate_btn(){
    QString str=le.text();
    QString str1("5412986453");
    str.append(str1);
    str=QString::number(Crc16(str.data(),str.length()));
    for(int i=6-str.length();i>0;i--){
        str.prepend('0');
    }
    lbl.setText(str);
}
void Widget::keyPressEvent(QKeyEvent* ev){
    switch (ev->key()){
    case Qt::Key_Enter:
        generate_btn();
        break;
    default:
        QWidget::keyPressEvent(ev);
    }



}

unsigned short Widget::Crc16(QChar* pcBlock, int len)
{
    unsigned short crc = 0x81A9;


    while (len--)
        crc = (crc << 8) ^ Crc16Table[(crc >> 8) ^ (*pcBlock++).unicode()];

    return crc;
}
