#include "logging.h"
#include <QDebug>

// Default constructor for Logging object
Logging::Logging()
{

}

// Add the Multiplication object in the correct/incorrect list
void Logging::list_include(Multiplication mult_object, const bool right_wrong)
{
    if (right_wrong)
        correct_objects.push_back(mult_object);  // if right, add the object to the correct_objects list
    else
        incorrect_objects.push_back(mult_object); // if right, add the object to the incorrect_objects list
}

// Return a list of incorrect/correct Multiplication objects
list<Multiplication> Logging::list_return(int list_choice) const
{
    if (list_choice == 0)
        return correct_objects;
    else
        return incorrect_objects;
}

//Return size of list
int Logging::list_size(string list_choice) const
{
    if ( list_choice == "correct" )
        return correct_objects.size();
    else if ( list_choice == "incorrect" )
        return incorrect_objects.size();
    else if ( list_choice == "both" )
        return correct_objects.size() + incorrect_objects.size();
}

//Return the first Multiplication object in incorrect list
Multiplication Logging::return_incorrect() const
{
    return incorrect_objects.front();
}

// Transfer Multiplication object from from incorrect to correct list
void Logging::incorrect_to_correct(Multiplication incorrect_object)
{
    for ( it = incorrect_objects.begin(); it != incorrect_objects.end(); it++ )  // iterate through the incorrect list
    {
        if ( it->return_operands( 1 ) == incorrect_object.return_operands( 1 ) && it->return_operands( 2 ) == incorrect_object.return_operands( 2 ) )  // find the object in the list that matches the current equation
            incorrect_objects.erase( it ); // erase the object from the list
    }

    correct_objects.push_back(incorrect_object); // add the object to the back of the correct_objects list
}

// Moves Incorrect object to back from list
void Logging::incorrect_push_back(Multiplication incorrect_object)
{
    incorrect_objects.push_back(incorrect_object);   // push the object to the back of the list before deleting (popping) it
    incorrect_objects.pop_front(); // remove it from the front
}

// Returns Qstring of correct list with/without total times a given equation was answered incorrectly
QString Logging::Logging::return_correct_list_str( bool show_num_wrongs)
{
    QString str_lst="";

    for ( it = correct_objects.begin(); it != correct_objects.end(); it++ )  // iterate through the correct list
        {
        if ( show_num_wrongs ) // include num wrongs in the string
            // "op1 * op2: # of wrong attempts"
            str_lst += QString::number( it->return_operands(1) ) + " * " + QString::number( it->return_operands(2) ) + ": " + QString::number( it->get_wrong_count() ) + " wrong attempt(s)";
        else
            // "op1 * op2"
            str_lst += QString::number( it->return_operands(1) ) + " * " + QString::number( it->return_operands(2) );
        str_lst += "\n";
        }

    return str_lst;
}

// Returns Qstring of incorrect list with/without total times a given equation was answered incorrectly
QString Logging::Logging::return_incorrect_list_str( bool show_num_wrongs )
{
    QString str_lst="";

    for ( it = incorrect_objects.begin(); it != incorrect_objects.end(); it++ ) // iterate through the incorrect list
        {
        if ( show_num_wrongs ) // include num wrongs in the string
            // "op1 * op2: # of wrong attempts"
            str_lst += QString::number( it->return_operands(1) ) + " * " + QString::number( it->return_operands(2) ) + ": " + QString::number( it->get_wrong_count() ) + " wrong attempt(s)";
        else
            // "op1 * op2"
            str_lst += QString::number( it->return_operands(1) ) + " * " + QString::number( it->return_operands(2) );
        str_lst += "\n";
        }

    return str_lst;
}

// Returns total # of incorrect answers
int Logging::return_incorrect_sum()
{
    int incorrect_sum = 0;

    for ( it = incorrect_objects.begin(); it != incorrect_objects.end(); it++ ) //iterate through incorrect list
        {
        incorrect_sum+=it->get_wrong_count(); // call get_wrong_count function of each Multiplication object in list and increment sum
        }

    for ( it = correct_objects.begin(); it != correct_objects.end(); it++ ) //iterate through correct list
        {
        incorrect_sum+=it->get_wrong_count(); // call get_wrong_count function of each Multiplication object in list and increment sum
        }

    return incorrect_sum;
}

int Logging::return_correct_first_try()
{
    int first_try_counter = 0;

    for ( it = correct_objects.begin(); it != correct_objects.end(); it++ ) // iterate through correct list
        {
        if ( it->get_wrong_count() == 0 ) // call get_wrong_count function of each Multiplication object and check if returned value is 0
            first_try_counter++; // increment counter
        }

    return first_try_counter;
}



