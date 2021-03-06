#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Multiplication.h"
#include "logging.h"
#include "QTimer"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /***** Class constructor *****/
    explicit MainWindow(QWidget *parent = 0);
    /*----------------------------------------------------------------------
      Construct a MainWindow object.
    -----------------------------------------------------------------------*/

    /***** Class destructor *****/
    ~MainWindow();
    /*----------------------------------------------------------------------
      Deallocates the memory of a MainWindow object.
      ------------------------------------------------------------------*/

    // Generate new (not necessarily unique) operands
    void gen_new_ops();

    // Set data to display
    void display( int problem_type );
    /*----------------------------------------------------------------------
      Precondition: problem_type is 0 for unseen equation and 1 for already
                    answered but incorrect equation
      Postcondition: none
    -----------------------------------------------------------------------*/

    // Determine what type of equation to generate (new and unique or old and incorrect)
    void problem_type_router();

    // Sets max limit for op1 and op2
    void set_max_limit( int max_limit_from_user ) const;
    /*----------------------------------------------------------------------
      Precondition: max_limit_from_user is a positive integer
      Postcondition: none
    -----------------------------------------------------------------------*/

    // Initializes timer for the countdown feature
    void initialize_timer();

    // Set the amount of time for the countdown (e.g. 10 seconds)
    void set_timer_amount( int timer_amount_from_user );
    /*----------------------------------------------------------------------
      Precondition: set_timer_amount is a positive integer
      Postcondition: none
    -----------------------------------------------------------------------*/

    // Sends relevant data to end_of_game class (window)
    void game_over( bool out_of_nums_bool );
    /*----------------------------------------------------------------------
      Precondition: out_of_nums_bool is a flag for whether or not there are
                    any equations left to display.
      Postcondition: none
    -----------------------------------------------------------------------*/

    // Disables the timer
    void disable_timer() const;

private slots:

    // Function for behavior of Skip button
    void on_pushButton_clicked();

    // Function for behavior of Check Answer button
    void on_check_answer_button_clicked();

    // Function for behavior of Quit button
    void on_quit_button_clicked();

    // Function for behavior of countdown timer
    void myTimerHandler();

private:

    Ui::MainWindow *ui; // pointer of type MainWindow

    Multiplication *pointer_Mult; // pointer of type Multiplication
    Logging *pointer_Logging; // pointer of type Logging
    list<Multiplication> mult_objects; // list of Multiplication objects
    bool is_new_problem;

    Multiplication incorrect_object;

    int problem_type;

    int temp_incorrect_wrong_count;

    QTimer *timer;

    int countdown;

    int score;

    int countdown_from_user;
};

#endif // MAINWINDOW_H
