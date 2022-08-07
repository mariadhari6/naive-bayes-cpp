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
void drawFrequencyDays(frequency days_frequency);
void drawFrequencyDelivery(frequency delivery_frequency);
void drawFrequencyDiscount(frequency discount_frequency);
void drawLikeHoodDays(frequency days_frequency);
void drawLikeHoodDelivery(frequency delivery_frequency);
void drawLikeHoodDiscount(frequency discount_frequency);
int main(int argc, char const *argv[])
{
    const string dates[] = {"Mondays", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    const string months[] = {
        "January", "February", "March", "April", "Mei",
        "June", "July", "August", "September", "October",
        "Novenber", "December"};
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

    /**
     * Let us calculate some conditional probabilities:
     * P(B) = P(Weekday)
     * = total daily customers / total data
     *
     * The probability of purchasing on the weekday = total customers on weekday / total customers
     * The probability of purchasing on the holiday = total customers on holiday / total customers
     * The probability of purchasing on the weekend = total customers on weekend / total customers
     */
    double days_probabilities[3] = {0, 0, 0};
    double totalDailyCustomers[3] = {0, 0, 0};
    for (int i = 0; i < sizeof(totalDailyCustomers) / sizeof(*totalDailyCustomers); i++)
    {
        totalDailyCustomers[i] = days_frequency.events[i].buys.yes + days_frequency.events[i].buys.no;
    }
    cout << "\n....:: Days Frequency Probabilities ::....\n";
    for (int i = 0; i < sizeof(totalDailyCustomers) / sizeof(*totalDailyCustomers); i++)
    {
        days_probabilities[i] = totalDailyCustomers[i] / (double(sizeof(shoppings_sheet) / sizeof(*shoppings_sheet)) - 1);
        cout << days_frequency.events[i].name << "\t\t=> " << days_probabilities[i] << endl;
    }

    /**
     * P(A) = P(No Buy)
     * = total no buys / total data
     */
    double noBuyDays = 0;
    for (int i = 0; i < sizeof(days) / sizeof(*days); i++)
    {
        noBuyDays += days_frequency.events[i].buys.no;
    }
    double daysNoBuyProbablility = noBuyDays / (double(sizeof(shoppings_sheet) / sizeof(*shoppings_sheet)) - 1);
    cout << "\nDidn't Buy\t=> " << daysNoBuyProbablility << endl;

    /**
     * P(B | A)
     * P(Weekday | No Buy)
     * P(Holiday | No Buy)
     * P(Weekend | No Buy)
     * = Didn't buy on weekday / Total didn't buy
     * => Calculate the probability of not buying on all days
     */

    double probNoBuyDays[3];
    for (int i = 0; i < sizeof(probNoBuyDays) / sizeof(*probNoBuyDays); i++)
    {
        probNoBuyDays[i] = days_frequency.events[i].buys.no / noBuyDays;
        cout << "Probabilities of not buying on " << days_frequency.events[i].name << "\t: " << probNoBuyDays[i] << endl;
    }

    /**
     * P(A | B)
     *
     * = P(No Buy | Weekday)
     * = P(Weekday | No Buy) * P(No Buy) / P(Weekday)
     * Calculate probability of not buying on every weekday
     *
     * = P(No Buy | Holiday)
     * = P(Holiday | No Buy) * P(No Buy) / P(Holiday)
     * Calculate probability of not buying on every holiday
     *
     * = P(No Buy | Weekend) * P(No Buy) / P(Weekend)
     * = P(Weekend | No Buy) * P(No Buy) / P(Weekend)
     * Calculate probability of not buying on every weekend
     *
     * => Calculate probability of not buying on a daily basis
     */
    double probNoBuyDaily[3];
    cout << endl
         << "....:: Probabilities of not buying on a daily basis ::....\n";
    for (int i = 0; i < sizeof(probNoBuyDaily) / sizeof(*probNoBuyDaily); i++)
    {
        probNoBuyDaily[i] = (probNoBuyDays[i] * daysNoBuyProbablility) / days_probabilities[i];
        cout << days_frequency.events[i].name << "\t=> " << probNoBuyDaily[i] << endl;
    }

    /**
     * Finally, we look at the probability of B (i.e., weekdays) when no purchase occurs.
     * If the probability of the weekday without a purchase less or 50%, the customer will most likely buy the product on a weekday.
     * We have the frequency tables of all three independent variables, and we can construct the tables for all the three variables.
     * See the likelihood tables for the three variables below:
     *
     */
    cout << endl
         << "....:: Draw Likehood Table Probabilities ::....\n";
    drawLikeHoodDays(days_frequency);
    drawLikeHoodDelivery(delivery_frequency);
    drawLikeHoodDiscount(discount_frequency);
    return 0;
}

void drawFrequencyDays(frequency days_frequency)
{
    cout << "____________________________________" << endl;
    cout << "|         |             |           " << endl;
    cout << "| " << days_frequency.label << "    |  Buy\t|   No" << endl;
    cout << "|_________|_____________|___________" << endl;
    cout << "|         |             |           " << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "| " << days_frequency.events[i].name << " |  "
             << days_frequency.events[i].buys.yes << "\t|  "
             << days_frequency.events[i].buys.no << " " << endl;
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
        cout << "| " << delivery_frequency.events[i].name << "\t\t|  "
             << delivery_frequency.events[i].buys.yes << "\t\t|  "
             << delivery_frequency.events[i].buys.no << " " << endl;
    }
    cout << "|_______________|_______________|___________" << endl;
}
void drawFrequencyDiscount(frequency discount_frequency)
{
    cout << "____________________________________" << endl;
    cout << "|          |            |           " << endl;
    cout << "| " << discount_frequency.label << " |  Buy\t|   No" << endl;
    cout << "|__________|____________|___________" << endl;
    cout << "|          |            |           " << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << "| " << discount_frequency.events[i].name << "\t   |  "
             << discount_frequency.events[i].buys.yes << "\t|  "
             << discount_frequency.events[i].buys.no << " " << endl;
    }
    cout << "|__________|____________|___________" << endl;
}
void drawLikeHoodDays(frequency days_frequency)
{
    int totalBuys = 0, totalNoBuys = 0;
    for (int i = 0; i < 3; i++)
    {
        totalBuys += days_frequency.events[i].buys.yes;
        totalNoBuys += days_frequency.events[i].buys.no;
    }

    cout << "______________________________________________________" << endl;
    cout << "|         |             |               |             " << endl;
    cout << "| " << days_frequency.label << "    |  Buy\t|  No\t\t|" << endl;
    cout << "|_________|_____________|_______________|_____________" << endl;
    cout << "|         |             |               |             " << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "| " << days_frequency.events[i].name << " |  "
             << days_frequency.events[i].buys.yes << "/" << totalBuys
             << "\t|  " << days_frequency.events[i].buys.no << "/" << totalNoBuys << "\t|  "
             << days_frequency.events[i].buys.yes + days_frequency.events[i].buys.no
             << "/" << totalBuys + totalNoBuys << endl;
    }
    cout << "|_________|_____________|_______________|_____________" << endl;
    cout << "|         |             |               |             " << endl;
    cout << "|         |  " << totalBuys << "/" << totalBuys + totalNoBuys
         << "\t|  " << totalNoBuys << "/" << totalBuys + totalNoBuys
         << "\t|             " << endl;
    cout << "|_________|_____________|_______________|_____________" << endl;
}
void drawLikeHoodDelivery(frequency delivery_frequency)
{
    int totalBuys = 0, totalNoBuys = 0;
    for (int i = 0; i < 2; i++)
    {
        totalBuys += delivery_frequency.events[i].buys.yes;
        totalNoBuys += delivery_frequency.events[i].buys.no;
    }

    cout << "______________________________________________________________" << endl;
    cout << "|               |               |               |" << endl;
    cout << "| " << delivery_frequency.label << "\t|  Buy\t\t|  No\t\t|" << endl;
    cout << "|_______________|_______________|_______________|_____________" << endl;
    cout << "|               |               |               |" << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << "| " << delivery_frequency.events[i].name << "\t\t|  "
             << delivery_frequency.events[i].buys.yes << "/" << totalBuys
             << "\t|  " << delivery_frequency.events[i].buys.no << "/" << totalNoBuys << "\t|  "
             << delivery_frequency.events[i].buys.yes + delivery_frequency.events[i].buys.no
             << "/" << totalBuys + totalNoBuys << endl;
    }
    cout << "|_______________|_______________|_______________|_____________" << endl;
    cout << "|               |               |               |             " << endl;
    cout << "|               |  " << totalBuys << "/" << totalBuys + totalNoBuys << "\t|  "
         << totalNoBuys << "/" << totalBuys + totalNoBuys << "\t|             " << endl;
    cout << "|_______________|_______________|_______________|_____________" << endl;
}
void drawLikeHoodDiscount(frequency discount_frequency)
{
    int totalBuys = 0, totalNoBuys = 0;
    for (int i = 0; i < 2; i++)
    {
        totalBuys += discount_frequency.events[i].buys.yes;
        totalNoBuys += discount_frequency.events[i].buys.no;
    }

    cout << "_____________________________________________________" << endl;
    cout << "|          |              |             |            " << endl;
    cout << "| " << discount_frequency.label << " |  Buy\t  |   No\t|" << endl;
    cout << "|__________|______________|_____________|____________" << endl;
    cout << "|          |              |             |            " << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << "| " << discount_frequency.events[i].name << "\t   |  "
             << discount_frequency.events[i].buys.yes << "/" << totalBuys
             << "\t  |  " << discount_frequency.events[i].buys.no << "/" << totalNoBuys << "\t|  "
             << discount_frequency.events[i].buys.yes + discount_frequency.events[i].buys.no
             << "/" << totalBuys + totalNoBuys << endl;
    }
    cout << "|__________|______________|_____________|_____________" << endl;
    cout << "|          |              |             |             " << endl;
    cout << "|          |  " << totalBuys << "/" << totalBuys + totalNoBuys << "\t  |  "
         << totalNoBuys << "/" << totalBuys + totalNoBuys << "\t|             " << endl;
    cout << "|__________|______________|_____________|_____________" << endl;
}