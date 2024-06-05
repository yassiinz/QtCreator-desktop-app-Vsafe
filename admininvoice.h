#ifndef ADMININVOICE_H
#define ADMININVOICE_H

#include <QWidget>

namespace Ui {
class AdminInvoice;
}

class AdminInvoice : public QWidget
{
    Q_OBJECT

public:
    explicit AdminInvoice(QWidget *parent = nullptr);
    ~AdminInvoice();

private:
    Ui::AdminInvoice *ui;
};

#endif // ADMININVOICE_H
