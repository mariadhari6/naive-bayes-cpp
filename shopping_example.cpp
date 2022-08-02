#include <iostream>
#include <string.h>

using namespace std;

struct shopping
{
    string date, day;
    string discount, free_delivery, buy;
};
struct buy
{
    int yes = 0;
    int no = 0;
};
struct event
{
    string name;
    buy buys;
};
struct frequency
{
    string label;
    event events[5];
};
int main(int argc, char const *argv[])
{
    const string dates[] = {"Mondays", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    const string months[] = {"January", "February", "March", "April", "Mei", "June", "July", "August", "September", "October", "Novenber", "December"};
    const string days[] = {"Weekdays", "Holiday", "Weekend"};
    shopping shoppings_sheet[10];

    // Create random datasheet
    for (int i = 0; i < (sizeof(shoppings_sheet) / sizeof(*shoppings_sheet)) - 1; i++)
    {
        shopping data;
        int indexDay = rand() % 7;
        data.date = dates[indexDay] + ", " + to_string(rand() % 31 + 1) + " " + months[rand() % 12] + " " + to_string(2000 + i);
        data.day = indexDay > 4 ? days[2] : days[rand() % 2];
        data.discount = rand() % 2 == 0 ? "yes" : "no";
        data.free_delivery = rand() % 2 == 0 ? "yes" : "no";
        data.buy = rand() % 2 == 0 ? "yes" : "no";
        shoppings_sheet[i] = data;
        cout << data.buy << endl;
    }

    // Create Discont Frequency
    frequency discount_frequency;
    discount_frequency.label = "Discount";
    discount_frequency.events[0].name = "yes";
    discount_frequency.events[1].name = "no";
    for (int i = 0; i < (sizeof(shoppings_sheet) / sizeof(*shoppings_sheet)) - 1; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (discount_frequency.events[j].name.compare(shoppings_sheet[i].discount) == 0)
            {
                if (shoppings_sheet[i].buy.compare("yes") == 0)
                {
                    discount_frequency.events[j].buys.yes++;
                }
                else
                {
                    discount_frequency.events[j].buys.no++;
                }
            }
        }
    }
    return 0;
}
