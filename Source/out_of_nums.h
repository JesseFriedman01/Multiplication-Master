#ifndef OUT_OF_NUMS_H
#define OUT_OF_NUMS_H

#include <QWidget>
#include "end_of_game.h"

namespace Ui {
class out_of_nums;
}

class out_of_nums : public QWidget
{
    Q_OBJECT

public:
    explicit out_of_nums(QWidget *parent = 0);
    ~out_of_nums();

public slots:

    void on_click();

    void set_end_game(end_of_game *end_game);

private:
    Ui::out_of_nums *ui;
    end_of_game *pointer_end_game;

};

#endif // OUT_OF_NUMS_H
