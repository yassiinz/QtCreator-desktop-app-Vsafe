#include "adminequipment.h"
#include "ui_adminequipment.h"

AdminEquipment::AdminEquipment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminEquipment)
{
    ui->setupUi(this);
}

AdminEquipment::~AdminEquipment()
{
    delete ui;
}
