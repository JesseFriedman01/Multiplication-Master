#ifndef SUBFORM_H
#define SUBFORM_H

#include <QWidget>
#include <settings.h>

namespace Ui {
class SubForm;
}

class SubForm : public QWidget
{
    Q_OBJECT

public:
    explicit SubForm(QWidget *parent = 0);
    ~SubForm();

private slots:
    void on_start_button_clicked();

    void on_settings_button_clicked();

private:
    Ui::SubForm *ui;
    settings settings_form;
};

#endif // SUBFORM_H
