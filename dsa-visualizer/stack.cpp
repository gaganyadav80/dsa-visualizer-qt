#include "stack.h"
#include "ui_stack.h"

stack::stack(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stack)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QRectF coords;
    coords.setX(0); coords.setY(0); //? -1000, -1000
    coords.setWidth(1000); coords.setHeight(350);   //? 2000, 2000
    tPoint.setX(0); //? -1000
    tPoint.setY(93);    //? -907
    tLine.setLine(20, 93, 20, 70);  //? -980,-907,-980,-930
    sList = new Ui::List(ui->graphicsView, scene, coords, tPoint, tLine, "Top");
}

stack::~stack()
{
    delete ui;
}

void stack::insertElem(QString val)
{
    sList->incrEntries(1);
    sList->setData(sList->getNumEntries()-1, val);

    sList->insertNode();
}

void stack::removeElem(int idx)
{
    sList->setData(idx-1, "0");
    sList->decrEntries(1);

    sList->removeNode();
}

// Push an element to the stack
void stack::on_pushButton_2_clicked()
{
    QString val;

    val = ui->lineEdit->text();
    if (val == "") {
        return; //Do Nothing
    }
    ui->lineEdit->setText("");

    insertElem(val);
}

// Pop an element from stack and cleanup.
void stack::on_pushButton_clicked()
{
    QString val;
    QRect rect;
    QFont font;
    std::map <int, Ui::RectElement>::iterator it;

    if (!sList->getNumEntries()) {
        return;
    }

    // Pop an element and clean up.
    removeElem(sList->getNumEntries());
}

//Clear stack
void stack::on_pushButton_3_clicked()
{
    sList->clearList();
}

//Add 10 random numbers to stack
void stack::on_pushButton_4_clicked()
{
    int randNum[10];

    Ui::genRand(randNum, 10);
    for (int i=0; i<10; i++) {
        insertElem(QString::number(randNum[i]));
    }
}
