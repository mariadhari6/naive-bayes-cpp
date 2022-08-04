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
void drawFrequencyDays(frequency days_frequency)
{
    cout << "____________________________________" << endl;
    cout << "|         |             |           " << endl;
    cout << "| " << days_frequency.label << "    |  Buy\t|   No" << endl;
    cout << "|_________|_____________|___________" << endl;
    cout << "|         |             |           " << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "| " << days_frequency.events[i].name << " |  " << days_frequency.events[i].buys.yes << "\t|  " << days_frequency.events[i].buys.no << " " << endl;
    }
    cout << "|_________|_____________|___________" << endl;
}
void drawFrequencyDelivery(frequency delivery_frequency)
{

    cout << "____________________________________________" << endl;
    cout << "|               |               |           " << endl;
    cout << "| " << delivery_frequency.label << "\t|  Buy\t\t|  No" << endl;
    cout << "|_______________|_______________|___________" << endl;
    cout << "|               |               |           " << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << "| " << delivery_frequency.events[i].name << "\t\t|  " << delivery_frequency.events[i].buys.yes << "\t\t|  " << delivery_frequency.events[i].buys.no << " " << endl;
    }
    cout << "|_______________|_______________|___________" << endl;
}
void drawFrequencyDiscount(frequency discount_frequency) {
     cout << "____________________________________" << endl;
    cout << "|          |            |           " << endl;
    cout << "| " << discount_frequency.label << " |  Buy\t|   No" << endl;
    cout << "|__________|____________|___________" << endl;
    cout << "|          |            |           " << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << "| " << discount_frequency.events[i].name << "\t   |  " << discount_frequency.events[i].buys.yes << "\t|  " << discount_frequency.events[i].buys.no << " " << endl;
    }
    cout << "|__________|____________|___________" << endl;
}
int main(int argc, char const *argv[])
{
    const string dates[] = {"Mondays", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    const string months[] = {"January", "February", "March", "April", "Mei", "June", "July", "August", "September", "October", "Novenber", "December"};
    const string days[] = {"Weekday", "Holiday", "Weekend"};
    shopping shoppings_sheet[10000];

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

    // Create Free Delivery Frequency
    frequency delivery_frequency;
    delivery_frequency.label = "Free Delivery";
    delivery_frequency.events[0].name = "yes";
    delivery_frequency.events[1].name = "no";
    for (int i = 0; i < (sizeof(shoppings_sheet) / sizeof(*shoppings_sheet)) - 1; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (delivery_frequency.events[j].name.compare(shoppings_sheet[i].free_delivery) == 0)
            {
                if (shoppings_sheet[i].buy.compare("yes") == 0)
                {
                    delivery_frequency.events[j].buys.yes++;
                }
                else
                {
                    delivery_frequency.events[j].buys.no++;
                }
            }
        }
    }

    // Create Days Frequency
    frequency days_frequency;
    days_frequency.label = "Days";
    for (int i = 0; i < sizeof(days) / sizeof(*days); i++)
    {
        days_frequency.events[i].name = days[i];
    }
    for (int i = 0; i < (sizeof(shoppings_sheet) / sizeof(*shoppings_sheet)) - 1; i++)
    {
        for (int j = 0; j < sizeof(days) / sizeof(*days); j++)
        {
            if (days_frequency.events[j].name.compare(shoppings_sheet[i].day) == 0)
            {
                if (shoppings_sheet[i].buy.compare("yes") == 0)
                {
                    days_frequency.events[j].buys.yes++;
                }
                else
                {
                    days_frequency.events[j].buys.no++;
                }
            }
        }
    }
    // Draw Discount Frequency Table
    drawFrequencyDiscount(discount_frequency);
    // Draw Days Frequency Table
    drawFrequencyDays(days_frequency);
    // Draw Free Delivery Frequency Table
    drawFrequencyDelivery(delivery_frequency);

    return 0;
}
