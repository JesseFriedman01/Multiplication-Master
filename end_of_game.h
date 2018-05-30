#ifndef END_OF_GAME_H
#define END_OF_GAME_H

#include <QWidget>

namespace Ui {
class end_of_game;
}

class end_of_game : public QWidget
{
    Q_OBJECT

public:

    /***** Class constructor *****/
    explicit end_of_game(QWidget *parent = 0);
    /*----------------------------------------------------------------------
      Construct an end_of_game object.
    -----------------------------------------------------------------------*/

    /***** Class destructor *****/
    ~end_of_game(); // destructor
    /*----------------------------------------------------------------------
      Deallocates the memory of an end_of_game object.
     ------------------------------------------------------------------*/

    int total_questions; // data member for total number of (unique) questions asked
    int total_correct_answers; // data member for total number of correct answers
    int total_incorrect_answers; // data member for total number of incorrect answers
    int total_incorrect_sum;

    QString total_correct_list; // string representation of the correct list
    QString total_incorrect_list; // string representation of the incorrect list

    int total_first_attempt; // data member for total number of questions answered correctly on first attempt

    int total_score; // data member for total score

    void set_data() const;
    /*----------------------------------------------------------------------
      Sets data members for output
    -----------------------------------------------------------------------*/

private slots:
    void on_continueButton_clicked();
    /*----------------------------------------------------------------------
      Behavior if continue button is clicked
    -----------------------------------------------------------------------*/

    void on_quitButton_clicked();
    /*----------------------------------------------------------------------
      Behavior if quit button is clicked
    -----------------------------------------------------------------------*/

private:
    Ui::end_of_game *ui;
};

#endif // END_OF_GAME_H
