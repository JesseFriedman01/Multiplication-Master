#include "settings.h"
#include "ui_settings.h"
#include "QDebug"

settings::settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    user_max_limit = 9;
    user_seconds = 10;

    timer_enabled = true;
}

settings::~settings()
{
    delete ui;
}

int settings::get_user_max_limit() const
{
    return ui->max_limit_textbox->text().toInt();
}

int settings::get_user_timer_amount() const
{
    if ( ui->timer_checkbox->isChecked() )
        return ui->seconds_textbox->text().toInt();
    else
        return -1;
}

bool settings::return_timer_enabled()
{
    return timer_enabled;
}

void settings::on_timer_checkbox_stateChanged()
{
    if ( ui->timer_checkbox->isChecked() )
        {
        ui->seconds_textbox->setEnabled(true);
        timer_enabled = true;
        }
    else
        {
        ui->seconds_textbox->setDisabled(true);
        timer_enabled = false;
        }
}

void settings::on_done_button_clicked()
{
    this->hide();
}

void settings::on_default_button_clicked()
{
    ui->seconds_textbox->setEnabled(true);
    ui->timer_checkbox->setChecked(true);
    ui->max_limit_textbox->setText("9");
}
