#include "admininvoice.h"
#include "ui_admininvoice.h"

AdminInvoice::AdminInvoice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminInvoice)
{
    ui->setupUi(this);
}

AdminInvoice::~AdminInvoice()
{
    delete ui;
}
