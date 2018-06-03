#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include <cstdlib>
#include <ctime>
#include <QDateTime>
#include "end_of_game.h"
#include "out_of_nums.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    pointer_Mult = new Multiplication();
    pointer_Logging = new Logging();

    srand ( time(NULL) );

    ui->hint->hide();

    is_new_problem = true;

    problem_type = 0;

    QPixmap blackboard(":/files/images/blackboard5.jpg");
    QPixmap qmark(":/files/images/questionmark.png");

    ui->label_3->setPixmap(blackboard);
    ui->label_14->setPixmap(qmark);

    score = 0;

    connect(ui->lineEdit, SIGNAL(returnPressed()), ui->check_answer_button, SIGNAL(clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_max_limit(int max_limit_from_user) const
{
    pointer_Mult->set_max_limit( max_limit_from_user );
}

void MainWindow::initialize_timer()
{
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this ,SLOT(myTimerHandler()));
    timer->start(1000);  // 100 nanoseconds or 1 second interval
}

void MainWindow::myTimerHandler()
{
    if ( countdown > 0 )
       {
        countdown--;
        ui->lcdTimer->setEnabled(true);
        ui->lcdTimer->show();
        ui->lcdTimer->display(  QString::number( countdown) );
        }

    else if (countdown == 0)
    {
        if ( problem_type == 0)
            {
            pointer_Mult->set_wrong_count( 1 );
            pointer_Logging->list_include(*pointer_Mult, 0);
            }
        else
            {
            incorrect_object.set_wrong_count( 1 );
            pointer_Logging->incorrect_push_back( incorrect_object );
            }

        ui->lineEdit->setText("");

        problem_type_router();
     }

    else if ( countdown == -1 )
         ui->lcdTimer->setEnabled(false);
}

void MainWindow::disable_timer() const
{
    ui->lcdTimer->setDisabled(true);
    ui->lcdTimer->display(99);
}

void MainWindow::set_timer_amount(int timer_amount_from_user)
{
    countdown_from_user = timer_amount_from_user;
}

void MainWindow::problem_type_router()
{
    ui->result_label->hide();
    ui->hint->hide();
    ui->label_9->hide();
    ui->lineEdit->setText("");

    ui->label_12->setText(  QString::number (pointer_Mult->num_unique_pairs() - pointer_Logging->list_size("both") ) );

    ui->scoreLabel->setText(QString::number(score));

    countdown = countdown_from_user;

    int rand_num = rand() % (10 + 1);
    int probability = 7;

    ui->correctTextEdit->setText( pointer_Logging->return_correct_list_str( false ) );
    ui->incorrectTextEdit->setText( pointer_Logging->return_incorrect_list_str( false ) );

    if ( pointer_Logging->list_size("both")  == 0 )     // first problem of game
        {
        problem_type = 0;
        gen_new_ops();
        }

    else if (  rand_num <= probability )
        {
        if ( pointer_Logging->list_size("both") < pointer_Mult->num_unique_pairs()   )  // there are still unique pairs to generate
            {
            problem_type = 0;
            gen_new_ops();
            }

        else if ( ( pointer_Logging->list_size("both")  >= pointer_Mult->num_unique_pairs() ) && pointer_Logging->list_size("incorrect") > 0 )
            {
            problem_type = 1;
            incorrect_object = pointer_Logging->return_incorrect();
            temp_incorrect_wrong_count = incorrect_object.get_wrong_count();
            display( problem_type );
            }

        else
            {
            countdown = -1;
            game_over(true);
            }
        }

     else if ( rand_num > probability )
            {
            if ( pointer_Logging->list_size("incorrect") > 0 )
                {
                problem_type = 1;
                incorrect_object = pointer_Logging->return_incorrect();
                temp_incorrect_wrong_count = incorrect_object.get_wrong_count();
                display( problem_type );
                }
            else if ( pointer_Logging->list_size("incorrect") == 0 && ( pointer_Logging->list_size("both") < pointer_Mult->num_unique_pairs() ) )
                {
                problem_type = 0;
                gen_new_ops();
                }
            else
                {
                countdown = -1;
                game_over(true);
                }
            }

    if ( problem_type == 0 )
        ui->questiontypeLabel->setText( "New" );
    else
        ui->questiontypeLabel->setText( "Old" );
}

void MainWindow::display( int problem_type )
{
    QString op1_string;
    QString op2_string;

    if ( problem_type == 0 )
        {
        op1_string = QString::number(pointer_Mult->return_operands(1));
        op2_string = QString::number(pointer_Mult->return_operands(2));
        }
    else
        {
        op1_string = QString::number(incorrect_object.return_operands(1));
        op2_string = QString::number(incorrect_object.return_operands(2));
        }

    ui->label->setText(op1_string);
    ui->label_2->setText(op2_string);
 }

void MainWindow::gen_new_ops()
{
    pointer_Mult->set_wrong_count( 0 );

    pointer_Mult->new_operands();

    if ( pointer_Mult->unique_ops( pointer_Logging->list_return(0)) == true && pointer_Mult->unique_ops( pointer_Logging->list_return(1)) == true )
        display( 0 );
    else
        {
        while ( pointer_Mult->unique_ops( pointer_Logging->list_return(0)) == false || pointer_Mult->unique_ops( pointer_Logging->list_return(1)) == false )
            {
            if ( ( pointer_Logging->list_size("both") ) < pointer_Mult->num_unique_pairs() )
                {
                pointer_Mult->new_operands();
                display( 0 );
                }
            }
        }
}

void MainWindow::on_pushButton_clicked()
{
    if ( problem_type == 0 )
        {
        pointer_Mult->set_wrong_count( 1 );
        pointer_Logging->list_include(*pointer_Mult, 0);
        }
    else
        {
        incorrect_object.set_wrong_count( 1 );
        pointer_Logging->incorrect_push_back( incorrect_object );
        }

    ui->lineEdit->setText("");

    problem_type_router();
}

void MainWindow::on_check_answer_button_clicked()
{
    int guess = -1;

    if ( ui->lineEdit->text() != "" )
        guess =  ui->lineEdit->text().toInt();

    bool check_answer;

    check_answer = pointer_Mult->check_result(guess);

    if ( problem_type == 0 )
       check_answer = pointer_Mult->check_result(guess);
    else
       check_answer = incorrect_object.check_result(guess);

    if ( check_answer && problem_type == 0 )
    {

        if ( pointer_Mult->get_wrong_count() == 0 )
              {
               pointer_Logging->list_include(*pointer_Mult, 1);
               score += 5;
              }
        else
              pointer_Logging->list_include(*pointer_Mult, 0);

        problem_type_router();
     }

    else if ( check_answer && problem_type == 1 )
    {

        if ( temp_incorrect_wrong_count == incorrect_object.get_wrong_count() )
            {
            score += 1;
            pointer_Logging->incorrect_to_correct( incorrect_object );
            }
        else
            pointer_Logging->incorrect_push_back( incorrect_object );

        problem_type_router();
     }

    else if ( check_answer == false && problem_type == 0 )
        {
        pointer_Mult->set_wrong_count( 1 );

        if ( pointer_Mult->get_wrong_count() == 3 )
            {
            ui->hint->setText( pointer_Mult->hint() );
            ui->label_9->show();
            ui->hint->show();
            }

        ui->result_label->setText( QChar(0x2718) );
        ui->result_label->show();

        if ( pointer_Mult->get_wrong_count() > 3)
            {
             pointer_Logging->list_include(*pointer_Mult, 0);
             problem_type_router();
            }
        }
    else
        {
        incorrect_object.set_wrong_count( 1 );

        if ( incorrect_object.get_wrong_count() % 3 == 0 )
            {
            ui->hint->setText( incorrect_object.hint() );
            ui->label_9->show();
            ui->hint->show();
            }

        ui->result_label->setText( QChar(0x2718) );
        ui->result_label->show();

        if ( incorrect_object.get_wrong_count() % 4 == 0 )
            {
            pointer_Logging->incorrect_push_back( incorrect_object );
            problem_type_router();
            }
        }
}

void MainWindow::on_quit_button_clicked()
{
    game_over(false);
}

void MainWindow::game_over(bool out_of_nums_bool)
{
    end_of_game *pointer_end_of_game = new end_of_game();

    pointer_end_of_game->total_questions = pointer_Logging->list_size("both");

    pointer_end_of_game->total_correct_answers = pointer_Logging->list_size("correct");
    pointer_end_of_game->total_incorrect_answers = pointer_Logging->list_size("incorrect");

    pointer_end_of_game->total_correct_list = pointer_Logging->return_correct_list_str( true );
    pointer_end_of_game->total_incorrect_list = pointer_Logging->return_incorrect_list_str( true );

    pointer_end_of_game->total_incorrect_sum = pointer_Logging->return_incorrect_sum();

    pointer_end_of_game->total_first_attempt = pointer_Logging->return_correct_first_try();

    pointer_end_of_game->total_score = score;

    pointer_end_of_game->set_data();

    if ( out_of_nums_bool )
        {
        out_of_nums *pointer_out_of_nums = new out_of_nums;
        pointer_out_of_nums->set_end_game(pointer_end_of_game);
        pointer_out_of_nums->show();
        }
    else
        pointer_end_of_game->show();

    this->close();
}
