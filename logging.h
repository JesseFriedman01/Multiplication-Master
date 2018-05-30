#ifndef LOGGING_H
#define LOGGING_H

#include <Multiplication.h>
#include <list>

using namespace std;

class Logging
{
public:

    // Default constructor for the Logging
    Logging();

    // Add the Multiplication object in the correct/incorrect list
    void list_include(Multiplication mult_object, const bool right_wrong);
    /*----------------------------------------------------------------------
      Precondition: mult_object is a valid Multiplication object and
                    right_wrong is 1 for a correct list object and 0
                    for an incorrect object
      Postcondition: None
    -----------------------------------------------------------------------*/


    // Return a list of incorrect/correct Multiplication objects
    list<Multiplication> list_return(int list_choice) const;
    /*----------------------------------------------------------------------
      Precondition: list_choice is 0 for correct_list and any other int
                    for incorrect list
      Postcondition: returns a list of Multiplication objects
                     correct/incorrect
    -----------------------------------------------------------------------*/

    //Return size of list
    int list_size(string list_choice) const;
    /*----------------------------------------------------------------------
      Precondition: list_choice is "correct" for correct list, "incorrect"
                    for incorrect list, and "both" for both combined
      Postcondition: returns an integer value reflecting the total number of
                     Multiplication objects in one/both lists
    -----------------------------------------------------------------------*/

    //Return the first Multiplication object in incorrect_list
    Multiplication return_incorrect() const;
    /*----------------------------------------------------------------------
      Precondition: incorrect_object is a valid Multiplication object
      Postcondition: returns first Multiplication object in incorrect_list.
    -----------------------------------------------------------------------*/

    // Transfer Multiplication object from from incorrect to correct list
    void incorrect_to_correct(Multiplication incorrect_object);
    /*----------------------------------------------------------------------
      Precondition: incorrect_object is a valid Multiplication object
      Postcondition: transfers Multiplication object from incorrect to correct
                     list
    -----------------------------------------------------------------------*/

    // Moves Incorrect object to back from list
    void incorrect_push_back (Multiplication incorrect_object);
    /*----------------------------------------------------------------------
      Precondition: incorrect_object is a valid Multiplication object
      Postcondition: removes incorrect_object from top of incorrect_list and
                     includes in the back
    -----------------------------------------------------------------------*/

    // Returns Qstring of correct list with/without total times a given equation was answered incorrectly
    QString return_correct_list_str( bool show_num_wrongs ) ;
    /*----------------------------------------------------------------------
      Precondition: show_num_wrongs is 1/true to show number of wrong attempts,
                    0/false to not show it
      Postcondition: Returns Qstring of correct list with/without total times a
                     given equation was answered incorrectly
    -----------------------------------------------------------------------*/

    // Returns Qstring of incorrect list with/without total times a given equation was answered incorrectly
    QString return_incorrect_list_str( bool show_num_wrongs );
    /*----------------------------------------------------------------------
      Precondition: show_num_wrongs is 1/true to show number of wrong attempts,
                    0/false to not show it
      Postcondition: Returns Qstring of correct list with/without total times a
                     given equation was answered incorrectly
    -----------------------------------------------------------------------*/

    // Returns total # of incorrect answers
    int return_incorrect_sum();
    /*----------------------------------------------------------------------
      Precondition: None
      Postcondition: Returns integer of total # of incorrect answers
    -----------------------------------------------------------------------*/

    // Returns total # of incorrect answers
    int return_correct_first_try();
    /*----------------------------------------------------------------------
      Precondition: None
      Postcondition: Returns integer of total # of incorrect answers
    -----------------------------------------------------------------------*/

private:

    list<Multiplication> correct_objects; // list of Multiplication objects for correct answers
    list<Multiplication> incorrect_objects; // list of Multiplication objects for incorrect answers

    list<Multiplication>::iterator it; // iterator for list of Multiplication objects
};

#endif // LOGGING_H
