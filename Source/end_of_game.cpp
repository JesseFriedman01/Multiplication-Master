#include "end_of_game.h"
#include "ui_end_of_game.h"
#include "subform.h"
#include "iomanip"

// default constructor for end_of_game
end_of_game::end_of_game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::end_of_game)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

// destructor for end_of_game
end_of_game::~end_of_game()
{
    delete ui;
}

// sets the data for the end_of_game window
void end_of_game::set_data() const
{
    double pct_correct = 0;
    double pct_incorrect = 0;
    double incorrect_avg = 0;

    if ( total_questions != 0 ) // check if there were actually questions asked (avoid a divide by 0 error)
        {
        pct_correct = ( (double) total_correct_answers/total_questions ) * 100;
        pct_incorrect = ( (double) total_incorrect_answers/total_questions ) * 100;
        }

    pct_correct = (int)(pct_correct/.01) * .01; // round decimal (i.e. XX.XX)
    pct_incorrect = (int)(pct_incorrect/.01) * .01; // round decimal (i.e. XX.XX)

    if ( total_incorrect_sum != 0 ) // check if there were any questions answered incorrectly
        incorrect_avg = (double)total_incorrect_sum/total_questions;

    incorrect_avg = (int)(incorrect_avg/.01) * .01; // round decimal (i.e. XX.XX)

    QString correct_text_str = QString::number ( total_correct_answers ) + " (" + QString::number( pct_correct ) + "%)"; // string for %
    QString incorrect_text_str = QString::number ( total_incorrect_answers ) + " (" + QString::number( pct_incorrect ) + "%)"; // string for %

    ui->totalText->setText( QString::number (total_questions ) ); // set output to window
    ui->correctText->setText ( correct_text_str ); // set output to window
    ui->incorrectText->setText ( incorrect_text_str ); // set output to window
    ui->correctTextEdit->setText( total_correct_list ); // set output to window
    ui->incorrectTextEdit->setText( total_incorrect_list ); // set output to window
    ui->incorrectAvgText->setText( QString::number( incorrect_avg ) ); // set output to window
    ui->correctFirstTryText->setText( QString::number ( total_first_attempt ) ); // set output to window
    ui->scoreText->setText(QString::number( total_score ) ); // set output to window
}

// continue button click behavior
void end_of_game::on_continueButton_clicked()
{
    SubForm *pointer_subform = new SubForm(); // create a pointer to a dynamically allocated SubForm object (SubForm is the initial window that you see)
    pointer_subform->show(); // show the SubForm
    this->close(); // close this window (as opposed to hide)
}

// quit button click behavior
void end_of_game::on_quitButton_clicked()
{
    this->close(); // close this window
}
