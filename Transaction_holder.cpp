#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct node
{
    string transctionID;
    long long amountPaid;
    string paymnetMethod;
    int date, month, year;
    node *next;

    node(string tI, long long aP, string pM, int d, int m, int y)
    {
        transctionID = tI;
        amountPaid = aP;
        paymnetMethod = pM;
        date = d;
        month = m;
        year = y;
        next = nullptr;
    }
};

node *head = NULL;
node *tail = NULL;

void addTransaction(string tI, long long aP, string pM, int d, int m, int y)
{
    node *newnode = new node(tI, aP, pM, d, m, y);
    if (head == nullptr)
        head = newnode, tail = newnode;
    else
    {
        tail->next = newnode;
        tail = tail->next;
    }
}

void transactionOfTheMonth(int m, int y)
{
    vector<node *> vec;

    node *temp = head;
    while (temp != nullptr)
    {
        if ((temp->month) == m && (temp->year) == y)
            vec.push_back(temp);
        temp = temp->next;
    }

    if (vec.empty())
    {
        cout << "No Transactions found in the data for the month " << m << " in the year " << y << endl
             << endl;
        return;
    }

    int n = vec.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if ((vec[j]->date) > (vec[j + 1]->date))
            {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
    cout << endl;
    cout << left << setw(15) << "Date" << setw(18) << "Transaction ID" << setw(15) << "Amount Paid" << setw(15) << "Payment Method" << endl;
    for (int i = 0; i < vec.size(); i++)
    {
        string a = "";
        a += to_string(vec[i]->date);
        a += "/";
        a += to_string(vec[i]->month);
        a += "/";
        a += to_string(vec[i]->year);
        cout << left << setw(15) << a << setw(18) << vec[i]->transctionID << setw(15) << vec[i]->amountPaid << setw(15) << vec[i]->paymnetMethod << endl;
    }
    cout << endl;
}

void monthWiseTotalSales(int y)
{
    map<int, int> mp1;

    node *temp = head;
    while (temp != nullptr)
    {
        if ((temp->year) == y)
        {
            mp1[temp->month] += temp->amountPaid;
        }
        temp = temp->next;
    }

    if (mp1.empty())
    {
        cout << "No transactions found for the year " << y << endl
             << endl;
        return;
    }
    cout << endl;
    cout << left << setw(10) << "Month" << "Total Sale" << endl;
    for (auto &value : mp1)
    {
        cout << left << setw(10) << value.first << value.second << endl;
    }
    cout << endl;
}

void displayPaymentMethodWiseSales(int y, string payMethod)
{
    map<int, int> mp2;

    node *temp = head;
    while (temp != nullptr)
    {
        if ((temp->year) == y && (temp->paymnetMethod == payMethod))
        {
            mp2[temp->month] += temp->amountPaid;
        }
        temp = temp->next;
    }

    if (mp2.empty())
    {
        cout << "No Transactions found in the data for the payment method " << payMethod << " in the year " << y << endl
             << endl;
        return;
    }

    cout << endl;
    cout << left << setw(13) << "Month" << "Total Sale" << endl;
    for (auto &value : mp2)
    {
        cout << left << setw(13) << value.first << value.second << endl;
    }
    cout << endl;
}

set<string> validPaymentMethods = {"paytm", "gpay", "cash", "card"};
bool isValidPaymentMethod(const string &paymentMethod)
{
    return validPaymentMethods.find(paymentMethod) != validPaymentMethods.end();
}

bool isValidDate(int d, int m, int y)
{
    if (y < 1900 || y > 2024)
        return false;
    if (m < 1 || m > 12)
        return false;
    if (d < 1)
        return false;

    vector<int> dayInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)))
        dayInMonth[1] = 29;
    return d <= dayInMonth[m - 1];
}

int main()
{
    bool flag = false;
    int n;
    while (!flag)
    {
        cout << "1. to Add Transaction" << endl;
        cout << "2. to Display transactions of a specific month in Ascending Order" << endl;
        cout << "3. to Display month-wise total sales of a specific year" << endl;
        cout << "4. to Display payment method-wise total sales of a specific year" << endl;
        cout << "5. to Exit!" << endl;
        cout << "Enter the task no. you want to perform : ";
        cin >> n;
        cout << endl;
        switch (n)
        {
        case 1:
        {
            long long aP;
            int d, m, y;
            string t, p;
            cout << "Enter Transaction ID :- ";
            cin >> t;
            cout << "Enter Amount Paid :- ";
            cin >> aP;
            while (aP < 0)
            {
                cout << "Enter a valid amount paid : ";
                cin >> aP;
            }
            while (true)
            {
                cout << "Enter Payment Method (e.g., paytm, gpay, cash, card) :- ";
                cin >> p;
                transform(p.begin(), p.end(), p.begin(), ::tolower);
                if (isValidPaymentMethod(p))
                    break;
                cout << "Please try again. Invalid Payment Method!" << endl;
            }

            while (true)
            {
                cout << "Enter Date of Transaction :- ";
                cin >> d;
                cout << "Enter Month of Transaction :- ";
                cin >> m;
                cout << "Enter Year of Transaction :- ";
                cin >> y;

                if (isValidDate(d, m, y))
                    break;

                cout << "Invalid Date! Please enter a valid date." << endl;
            }
            addTransaction(t, aP, p, d, m, y);
            cout << "TRANSACTION ADDED SUCCESSFULLY !" << endl
                 << endl;
            break;
        }

        case 2:
        {
            int month, year;
            cout << "Enter the Month and the year of which you want the transactions details :- ";
            cin >> month >> year;
            transactionOfTheMonth(month, year);
            break;
        }

        case 3:
        {
            int year;
            cout << "Enter the year to get month-wise Total Sales :- ";
            cin >> year;
            monthWiseTotalSales(year);
            break;
        }

        case 4:
        {
            int year;
            string payMethod;
            cout << "Enter year :- ";
            cin >> year;
            while (true)
            {
                cout << "Enter Payment Method (e.g., paytm, gpay, cash, card) :- ";
                cin >> payMethod;
                transform(payMethod.begin(), payMethod.end(), payMethod.begin(), ::tolower);
                if (isValidPaymentMethod(payMethod))
                    break;
                cout << "Please try again. Invalid Payment Method!" << endl;
            }
            displayPaymentMethodWiseSales(year, payMethod);
            break;
        }

        case 5:
        {
            flag = true;
            break;
        }

        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    }

    return 0;
}
