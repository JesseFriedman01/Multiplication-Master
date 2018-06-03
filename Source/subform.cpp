#include "subform.h"
#include "ui_subform.h"
#include "mainwindow.h"

SubForm::SubForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubForm)
{
    ui->setupUi(this);

    QPixmap pix(":/files/images/logo.png");

    ui->label->setPixmap(pix);
}

SubForm::~SubForm()
{
    delete ui;
}

void SubForm::on_start_button_clicked()
{
    MainWindow *pointer_mainwindow = new MainWindow();

    pointer_mainwindow->set_max_limit( settings_form.get_user_max_limit() );

    if ( settings_form.return_timer_enabled() == true )
        {
        pointer_mainwindow->initialize_timer();
        pointer_mainwindow->set_timer_amount( settings_form.get_user_timer_amount() );
        }
    else
        pointer_mainwindow->disable_timer();

    pointer_mainwindow->problem_type_router();
    pointer_mainwindow->show();

    settings_form.close();
    this->close();
}

void SubForm::on_settings_button_clicked()
{
    settings_form.show();
}
