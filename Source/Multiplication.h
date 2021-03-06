#ifndef MULTIPLICATION
#define MULTIPLICATION

#include <QString>
#include<list>

using namespace std;

class Multiplication
{
	private:  // declare data members
		   
		int op1,
			op2,
            max_limit,    // maximum value for the operands; minimum value = 0
            wrong_counter;

	public:   // declare function members

		Multiplication();  					// default constructor
		Multiplication(int new_max_limit); 	// specific constructor
		
		// accessor functions: access the data members, don't modify it 
		
		void display() const;    // displays the data of a Multiplication object
		int  get_result() const; // returns the result of the multiplication 
        QString hint() const;       // display hint
		bool check_result(int user_result) const;
					// if user_result == op1* op2 return true
        bool is_bigger(const Multiplication &other) const; // other's data members cannot be changed because of const
        //int factorial_calc (int val) const;
        int num_unique_pairs() const;
					
		// mutator functions: change data members 
		void set_max_limit(int new_max_limit);  // changes the value of max_limit
		void new_operands();  // assign new, random values to op1 and op2 between 0 and max_limit

        void set_operands (Multiplication mult_object);

        int return_operands (int op_choice) const;

        void set_wrong_count(int num_wrongs);
        int get_wrong_count() const;

        bool unique_ops(list<Multiplication> list_name);
};

#endif
