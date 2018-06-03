#include "out_of_nums.h"
#include "ui_out_of_nums.h"


#include "QDebug"

out_of_nums::out_of_nums(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::out_of_nums)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    connect(ui->continue_button, SIGNAL (released()), this, SLOT (on_click( )));

}

out_of_nums::~out_of_nums()
{
    delete ui;
}

void out_of_nums::on_click()
{
    this->close();
    pointer_end_game->show();
}

void out_of_nums::set_end_game(end_of_game *end_game)
{
    pointer_end_game = end_game;
}


