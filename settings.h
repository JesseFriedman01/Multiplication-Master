#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

namespace Ui {
class settings;
}

class settings : public QWidget
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();

    int get_user_max_limit() const;
    int get_user_timer_amount() const;
    bool return_timer_enabled();

private slots:
    void on_timer_checkbox_stateChanged();

    void on_done_button_clicked();

    void on_default_button_clicked();

private:
    Ui::settings *ui;

    QString user_max_limit;
    QString user_seconds;

    bool timer_enabled;
};

#endif // SETTINGS_H
