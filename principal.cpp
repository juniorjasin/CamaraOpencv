#include "principal.h"
#include "ui_principal.h"

principal::principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::principal)
{
    ui->setupUi(this);


    ui->SceneCamara->showMaximized();

    //ui->SceneCamara->setFixedSize(300,300);
}

principal::~principal()
{
    delete ui;
}
