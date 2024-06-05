#ifndef ADMINEQUIPMENT_H
#define ADMINEQUIPMENT_H

#include <QWidget>

namespace Ui {
class AdminEquipment;
}

class AdminEquipment : public QWidget
{
    Q_OBJECT

public:
    explicit AdminEquipment(QWidget *parent = nullptr);
    ~AdminEquipment();

private:
    Ui::AdminEquipment *ui;
};

#endif // ADMINEQUIPMENT_H
