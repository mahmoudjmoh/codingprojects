/* 
Name: Mahmoud Mohammad
Class: CIS 160 M01
Due Date: November 16th, 2023
Date: October 31st, 2023
Program Name: PCCC Catering Project 
This program has been created to produce a catering bill for a customer for catering services that are provided to them.
*/

#include <iostream> 
#include <iomanip>  
#include <string>  
#include <cmath>
using namespace std;

// constants
const float DELUXE_MEAL = 29.95;
const float STANDARD_MEAL = 25.75;
const float HALL_A = 100.00;
const float HALL_B = 85.00;
const float HALL_C = 75.00;
const float HALL_D = 65.00;
const float HALL_H = 0.00; 
const float WEEKEND_SURCHARGE = .10;
const float DISCOUNT_ONE_PERCENT = .01;
const float DISCOUNT_TWO_PERCENT = .02;
const float DISCOUNT_FOUR_PERCENT = .04;
const float DISCOUNT_FIVE_PERCENT = .05;
const float DISCOUNT_SEVEN_PERCENT = .07;
const float COST_PER_CHILD_MEAL = .60;
const float GRATUITY = .20;
const float SALES_TAX = .07;

// function prototypes
// this function asks the user their meal choice which will determine the price of their meal depending on which meal they choose
void adjust_meal_cost_by_meal_choice(float &, int&);

// this function asks the user their hall choice which will determine the price added to their total depending on which hall they choose
void adjust_hall_cost_by_hall_choice(float &, int &);

// this function asks the user if their party will be on a weekend and to determine if there will be a weekend fee added
void ask_if_weekend(bool &);

// this function asks the user if their payment will be delivered within 10 days to determine if they get a discount
void ask_if_speedy(bool &);

// this function calculates the user's total meal cost based on previous selections
float pre_tax_total(float, float, bool, float, float &);

// this function collects user input
void collect_input(int &, int &, float &);

// this function calculates the total cost of all the meals
void calculate_total_meal_cost(float &, float &, float &, float &, float , float , int , int);

// this function calculates all the taxes, fees, and discounts as applicable to calculate the subtotal
void calculate_total_taxes_and_fees(float &, float &, float &, float &, float &,
float, float, float, float, bool, float, float &);

// this function is used to multiply multiple arguments
template <typename... T>
float multiply(T... args);

// this function is used to add multiple arguments
template <typename... T>
float add(T... args);

// this function is used to subtract multiple arguments
template <typename T, typename... Args> 
T subtract(T first, Args... args);

// this function is used to output a header on the bill
void caswell_catering_header();

// this function is used to output information on the bill which is the adult count, child count, gratuity percentage, and cost per meal for children and adults
void first_quarter_of_output(int, int, int, bool, float, float);

// this function is used to output information on the bill which is the total cost for adult and child meals, and total food cost
void second_quarter_of_output(float, float, float);

// this function is used to output information on the bill which is the gratuity fee, hall fee, weekend charge if applicable, and taxes
void third_quarter_of_output(float, float, float, float, bool, int, float);

// this function is used to output information on the bill which is the subtotal, less deposit, less speedy payment, and balance due
void fourth_quarter_of_output(float, float, float, float, bool);

// global declarations/definitions

void collect_input(int &adult_count, int &child_count, float &deposit_amount)
{
    cout << "How many adults will be attending?: "; cin >> adult_count;
    cout << "How many children will be attending?: "; cin >> child_count;
    cout << "How much are you depositing?: "; cin >> deposit_amount;
    cout << "\n";
}

void adjust_meal_cost_by_meal_choice(float &adult_meal_cost, int &meal_choice)
{
    cout << "\t\t\tSelect your Meal" << endl;
    cout << "\t\t\t________________" << endl;
    cout << "\t\t1 - Deluxe Meal - $29.95" << endl;
    cout << "\t\t2 - Standard Meal - $25.75" << endl;
    cout << "\t\tEnter Your Meal Choice: ";
    cin >> meal_choice;
    switch(meal_choice)
    {
        case 1:
            cout << "\t\tThank you for choosing the Deluxe Meal!" << endl << endl;
            adult_meal_cost += DELUXE_MEAL;
            break;
        case 2:
            cout << "\t\tThank you for choosing the Standard Meal!" << endl << endl;
            adult_meal_cost += STANDARD_MEAL;
            break;
    }
}

void adjust_hall_cost_by_hall_choice(float &hall_cost, int &hall_choice)
{
    cout << "\t\t\tSelect your Hall" << endl;
    cout << "\t\t\t________________" << endl;
    cout << "\t\t1. Hall - A: $100.00" << endl;
    cout << "\t\t2. Hall - B: $85.00" << endl;
    cout << "\t\t3. Hall - C: $75.00" << endl;
    cout << "\t\t4. Hall - D: $65.00" << endl;
    cout << "\t\t5. Hall - H: Home" << endl;
    cout << "\t\tEnter Your Hall Choice: ";
    cin >> hall_choice;
    switch(hall_choice)
        {
            case 1: 
                cout << "\t\tThank you for choosing Hall - A!" << endl << endl;
                hall_cost = HALL_A;
                break;
            case 2:
                cout << "\t\tThank you for choosing Hall - B!" << endl << endl;
                hall_cost = HALL_B;
                break;
            case 3: 
                cout << "\t\tThank you for choosing Hall - C!" << endl << endl;
                hall_cost = HALL_C;
                break;
            case 4: 
                cout << "\t\tThank you for choosing Hall - D!" << endl << endl;
                hall_cost = HALL_D;
                break;
            case 5: 
                cout << "\t\tThank you for choosing Hall - H!" << endl << endl;
                hall_cost = HALL_H;
                break;
        }
}

void ask_if_weekend(bool &is_weekend)
{
    cout << "\t\tWill your party be scheduled for a weekend?" << endl;
    cout << "\t1. Yes" << endl;
    cout << "\t2. No" << endl;
    cout << "\tEnter Here: ";
    int weekend_choice;
    cin >> weekend_choice;

    if (weekend_choice == 1)
    {
        cout << "\tSounds good! Weekends include a 10 percent surcharge fee." << endl << endl;
        is_weekend = true;
    }
    else
    {
        cout << "\tSounds good!" << endl << endl;
        is_weekend = false;
    }
}

void ask_if_speedy(bool &is_speedy)
{
    cout << "\t\tWill your payment be made within 10 days?" << endl;
    cout << "\t1. Yes" << endl;
    cout << "\t2. No" << endl;
    cout << "\tEnter Here: ";
    int speedy_choice;
    cin >> speedy_choice;

    if (speedy_choice == 1)
    {
        cout << "\tSounds good! You will be offered a discount based off your total." << endl << endl;
        is_speedy = true;
    }
    else
    {
        cout << "\tSounds good!" << endl << endl;
        is_speedy = false;
    }
}

template <typename... T>
float multiply(T... args)
{
float result = 1;
    (void)((result *= args), ...);
    return result;
}

template <typename... T>
float add(T... args)
{
float result = 0;
    (void)((result += args), ...);
    return result;
}

float pre_tax_total(float total_food_cost, float hall_cost, bool is_weekend, float gratuity_fee, float &total_weekend_surcharge)
{
    float total = total_food_cost + hall_cost + gratuity_fee;
    if (is_weekend)
    {
        total_weekend_surcharge = total * WEEKEND_SURCHARGE;
        total += (total_weekend_surcharge);
    }
    return total;
}

template <typename T, typename... Args>
T subtract(T first, Args... args) 
{
    // Subtract all arguments from the first
    ((first -= args), ...);
    return first;
}

void calculate_total_meal_cost(float &calculated_child_meal_cost, float &total_adult_meal_cost, float &total_child_meal_cost, float &total_food_cost,
 float COST_PER_CHILD_MEAL, float adult_meal_cost, int adult_count, int child_count)
{
    calculated_child_meal_cost = multiply(COST_PER_CHILD_MEAL, adult_meal_cost);
    total_adult_meal_cost = multiply(adult_count, adult_meal_cost);
    total_child_meal_cost = multiply(child_count, calculated_child_meal_cost);
    total_food_cost = add(total_adult_meal_cost, total_child_meal_cost);
}

void calculate_total_taxes_and_fees(float &gratuity_fee, float &total_tax, float &sub_total, float &balance_due, float &speedy_discount_rate,
float total_food_cost, float GRATUITY, float SALES_TAX, float hall_cost, bool is_weekend, float deposit_amount, float &total_weekend_surcharge)
{
    cout << fixed << setprecision(2);
    gratuity_fee = multiply(total_food_cost, GRATUITY);
    total_tax = multiply(total_food_cost, SALES_TAX);
    sub_total = add(pre_tax_total(total_food_cost, hall_cost, is_weekend, gratuity_fee, total_weekend_surcharge), total_tax);
    if (sub_total < 500.00)
    {
        speedy_discount_rate = DISCOUNT_ONE_PERCENT;
    }
    else if (sub_total >= 500.00 && sub_total <= 999.00)
    {
        speedy_discount_rate = DISCOUNT_TWO_PERCENT;
    }
    else if (sub_total >= 1000.00 && sub_total <= 4999.00)
    {
        speedy_discount_rate = DISCOUNT_FOUR_PERCENT;
    }
    else if (sub_total >= 5000.00 && sub_total <= 9999.00)
    {
        speedy_discount_rate = DISCOUNT_FIVE_PERCENT;
    }
    else if (sub_total >= 10000.00)
    {
        speedy_discount_rate = DISCOUNT_SEVEN_PERCENT;
    }
    balance_due = subtract(sub_total,deposit_amount, multiply(sub_total, speedy_discount_rate)); 
}

void caswell_catering_header()
{
    cout << "\tCaswell Catering and Convention Services" << endl;
    cout << "\t\t\tFinal Bill" << endl;
    cout << "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/--/-/-/-/-/-/-/-/-/-/-/" << endl;
}

void first_quarter_of_output(int adult_count, int child_count, int meal_choice, bool is_weekend, float adult_meal_cost, float calculated_child_meal_cost)
{
    cout << "Number of Adults: \t\t" << adult_count << endl;
    cout << "Number of Children: \t\t" << child_count << endl;
    cout << "Gratuity: \t\t\t20%" << endl;
    if (is_weekend == true)  
    {
        cout << "Weekend: \t\t\tYes" << endl;
    }
    else if (is_weekend == false)
    {
        cout << "Weekend: \t\t\tNo" << endl;
    }
    if (meal_choice == 1)
    {
        cout << "Cost Per Deluxe Meal for Adult: $" << adult_meal_cost << endl; 
        cout << "Cost Per Deluxe Meal for Child: $" << calculated_child_meal_cost << endl;
        cout << "-------------------------------------------------" << endl;
    }
    else if (meal_choice == 2)
    {
        cout << "Cost Per Standard Meal for Adult: $" << adult_meal_cost << endl; 
        cout << "Cost Per Standard Meal for Child: $" << calculated_child_meal_cost << endl;
        cout << "-------------------------------------------------" << endl;
    }
}

void second_quarter_of_output(float total_adult_meal_cost, float total_child_meal_cost, float total_food_cost)
{
    cout << "Total Cost for Adult Meals: \t$" << total_adult_meal_cost << endl;
    cout << "Total Cost for Child Meals: \t$" << total_child_meal_cost << endl << endl;
    cout << "Total Food Cost: \t\t$" << total_food_cost << endl;
    cout << "-------------------------------------------------" << endl;
}

void third_quarter_of_output(float gratuity_fee, float total_tax, float total_food_cost, float hall_cost, bool is_weekend, int hall_choice, float total_weekend_surcharge)
{
    cout << "Gratuity: \t$" << gratuity_fee << endl;
    if (hall_choice == 1)
    {
        cout << "Hall A - Room Fee: $" << HALL_A << endl;
    }
    else if (hall_choice == 2)
    {
        cout << "Hall B - Room Fee: $" << HALL_B << endl;
    }
      if (hall_choice == 3)
    {
        cout << "Hall C - Room Fee: $" << HALL_C << endl;
    }
    else if (hall_choice == 4)
    {
        cout << "Hall D - Room Fee: $" << HALL_D << endl;
    }
    else if (hall_choice == 5)
    {
        cout << "Hall H - Room Fee: $" << HALL_H << endl;
    }
    if (is_weekend == true)
    {
        cout << "Weekend Charge: $" << total_weekend_surcharge << endl;
    }
    cout << "Taxes: \t$" << total_tax << endl;
    cout << "-------------------------------------------------" << endl;
}

void fourth_quarter_of_output(float sub_total, float deposit_amount, float balance_due, float speedy_discount_rate, bool is_speedy)
{
    cout << "Subtotal: \t$" << sub_total << endl << endl;
    cout << "Less Deposit: $" << deposit_amount << endl;
    if (is_speedy == true)
    {
    cout << "Less Speedy Payment: $" << multiply(sub_total, speedy_discount_rate) << endl << endl;
    }
    cout << "Balance Due: $" << balance_due << endl;
    cout << "/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/--/-/-/-/-/-/-/-/-/-/-/" << endl;
}

int main()
{
// local declarations/definitions
int hall_choice, adult_count, child_count, meal_choice;
bool is_weekend, is_speedy;
float adult_meal_cost, total_adult_meal_cost, total_child_meal_cost, total_food_cost, calculated_child_meal_cost, total_weekend_surcharge,
gratuity_fee, total_tax, sub_total, deposit_amount, balance_due, hall_cost, speedy_discount_rate;

// input section
collect_input(adult_count, child_count, deposit_amount);
adjust_meal_cost_by_meal_choice(adult_meal_cost, meal_choice); 
adjust_hall_cost_by_hall_choice(hall_cost, hall_choice); 
ask_if_weekend(is_weekend); 
ask_if_speedy(is_speedy);

// proccessing section
calculate_total_meal_cost(calculated_child_meal_cost, total_adult_meal_cost, total_child_meal_cost, total_food_cost,
COST_PER_CHILD_MEAL, adult_meal_cost, adult_count, child_count);
calculate_total_taxes_and_fees(gratuity_fee, total_tax, sub_total, balance_due, speedy_discount_rate,
total_food_cost, GRATUITY, SALES_TAX, hall_cost, is_weekend, deposit_amount, total_weekend_surcharge);

// output section
caswell_catering_header();
first_quarter_of_output(adult_count, child_count, meal_choice, is_weekend, adult_meal_cost, calculated_child_meal_cost);
second_quarter_of_output(total_adult_meal_cost, total_child_meal_cost, total_food_cost);
third_quarter_of_output(gratuity_fee, total_tax, total_food_cost, hall_cost, is_weekend, hall_choice, total_weekend_surcharge);
fourth_quarter_of_output(sub_total, deposit_amount, balance_due, speedy_discount_rate, is_speedy);

return 0;
}
