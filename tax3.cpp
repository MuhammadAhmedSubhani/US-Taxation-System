#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <fstream>
using namespace std;

// Helper: lowercase
string toLowerCase(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Customer struct to hold all data
struct Customer {
    string type;
    string maritalStatus;
    string state;
    double income;
    double taxableIncome;
    double fedTax;
    double stTax;
    double totalTax;
    double netIncome;
};

// Global vector to store all customers
vector<Customer> customers;

// Federal tax functions
double federalTaxIndividual(double taxableIncome, const string& status) {
    string st = toLowerCase(status);
    if (st == "single") {

        if (taxableIncome <= 0) 
        return 0; // No tax

        else if (taxableIncome <= 11000) 
        return taxableIncome * 0.10; // 10%

        else if (taxableIncome <= 44725) 
        return 1100 + (taxableIncome - 11000) * 0.12; // 12%

        else if (taxableIncome <= 95375) 
        return 5147 + (taxableIncome - 44725) * 0.22; // 22%

        else if (taxableIncome <= 182100) 
        return 16290 + (taxableIncome - 95375) * 0.24; // 24%
        
        else if (taxableIncome <= 231250) 
        return 37104 + (taxableIncome - 182100) * 0.32; // 32%
        
        else if (taxableIncome <= 578125) 
        return 52832 + (taxableIncome - 231250) * 0.35; // 35%

        else 
        return 174238 + (taxableIncome - 578125) * 0.37; // 37%
    } 
    else if (st == "married") {

        if (taxableIncome <= 0) 
        return 0; // No tax

        else if (taxableIncome <= 22000) 
        return taxableIncome * 0.10; // 10%

        else if (taxableIncome <= 89450) 
        return 2200 + (taxableIncome - 22000) * 0.12; // 12%

        else if (taxableIncome <= 190750) 
        return 10294 + (taxableIncome - 89450) * 0.22; // 22%

        else if (taxableIncome <= 364200) 
        return 32580 + (taxableIncome - 190750) * 0.24; // 24%

        else if (taxableIncome <= 462500) 
        return 74208 + (taxableIncome - 364200) * 0.32; // 32%

        else if (taxableIncome <= 693750) 
        return 105664 + (taxableIncome - 462500) * 0.35; // 35%

        else 
        return 186601 + (taxableIncome - 693750) * 0.37; // 37%

    } else {
        cout << "Unknown status, assuming Single.\n";
        return federalTaxIndividual(taxableIncome, "Single");
    }
}

double federalTaxOrganization(double income) {
    return income <= 0 ? 0 : income * 0.21; // Flat 21%
}

// State tax function (full 50 states + DC)
double stateTax(double income, const string& state, bool isIndividual) {
    if (income <= 0) 
    return 0; // No tax

    string st = toLowerCase(state);

    // No state income tax states
    if (st == "alaska" || st == "florida" || st == "nevada" ||
        st == "south dakota" || st == "texas" || st == "washington" ||
        st == "wyoming" || st == "tennessee" || st == "new hampshire") {
        return 0.0;
    }

    double rate = 0.05; // default

    // Full 50-state + DC mapping
    if (st == "alabama") 
    rate = 0.05;

    else if (st == "arkansas") 
    rate = 0.039;

    else if (st == "california") 
    rate = 0.133;

    else if (st == "connecticut") 
    rate = 0.0699;

    else if (st == "delaware") 
    rate = 0.066;

    else if (st == "hawaii") 
    rate = 0.11;

    else if (st == "iowa") 
    rate = 0.038;

    else if (st == "kansas") 
    rate = 0.0558;

    else if (st == "louisiana") 
    rate = 0.0425;

    else if (st == "maine") 
    rate = 0.0715;

    else if (st == "maryland") 
    rate = 0.0575;
    
    else if (st == "minnesota") 
    rate = 0.0985;

    else if (st == "missouri") 
    rate = 0.048;

    else if (st == "montana") 
    rate = 0.0675;

    else if (st == "nebraska") 
    rate = 0.0584;

    else if (st == "new jersey") 
    rate = 0.1075;

    else if (st == "new mexico") 
    rate = 0.059;

    else if (st == "new york") 
    rate = 0.109;

    else if (st == "north dakota") 
    rate = 0.025;

    else if (st == "ohio") 
    rate = 0.035;

    else if (st == "oklahoma") 
    rate = 0.0475;

    else if (st == "oregon") 
    rate = 0.099;

    else if (st == "rhode island") 
    rate = 0.0599;

    else if (st == "south carolina") 
    rate = 0.063;

    else if (st == "vermont") 
    rate = 0.0875;

    else if (st == "virginia") 
    rate = 0.0575;

    else if (st == "west virginia") 
    rate = 0.0482;

    else if (st == "wisconsin") 
    rate = 0.0765;

    else if (st == "district of columbia" || st == "dc") 
    rate = 0.1075;

    // Flat-tax states
    else if (st == "arizona") 
    rate = 0.025;

    else if (st == "colorado") 
    rate = 0.044;

    else if (st == "georgia") 
    rate = 0.0539;

    else if (st == "idaho") 
    rate = 0.05695;

    else if (st == "illinois") 
    rate = 0.0495;

    else if (st == "indiana") 
    rate = 0.03;

    else if (st == "kentucky") 
    rate = 0.04;

    else if (st == "massachusetts") 
    rate = 0.05;
    
    else if (st == "michigan") 
    rate = 0.0425;

    else if (st == "mississippi") 
    rate = 0.044;

    else if (st == "north carolina") 
    rate = 0.0425;

    else if (st == "pennsylvania") 
    rate = 0.0307;

    else if (st == "utah") 
    rate = 0.0455;

    return income * rate;
}

// Display reference data
void displayTaxStats() {
    cout << "\n======= 2024 TAX REFERENCE DATA =======\n";
    cout << "Federal Individual Rates: 10% to 37%\n";
    cout << "Standard Deduction: Single $14,600, Married $29,200\n";
    cout << "Corporate Federal Tax: 21% (flat)\n";
    cout << "State Income Tax: Varies by state\n";
    cout << "========================================\n\n";
}

// Personalized, lively suggestions
void giveSuggestions(const Customer& c) {
    cout << "\n--- PERSONALIZED TAX SUGGESTIONS ---\n";

    if (toLowerCase(c.type) == "individual") {
        double potential401k = min(22500.0, c.income * 0.10); // 401k contribution limit
        double potentialIRA = min(6500.0, c.income * 0.05); // Individual Retirement Account

        cout << "Hey! Based on your income of $" << c.income << ":\n";

        if (c.taxableIncome > 50000)
            cout << "1. Max out your 401k contributions! Save up to $" << potential401k << ".\n";
        else
            cout << "1. Even small 401k contributions reduce taxable income and save for retirement.\n";

        cout << "2. Contribute to an IRA. Putting aside $" << potentialIRA
             << " could reduce federal tax by approx $" << potentialIRA * 0.22 << ".\n";

        if (toLowerCase(c.maritalStatus) == "married")
            cout << "3. Filing jointly with your spouse may reduce taxes further!\n";

        if (c.state == "California" || c.state == "california")
            cout << "4. Check if you qualify for California renter's credit.\n";
        else if (c.state == "New York" || c.state == "new york")
            cout << "4. Explore New York's College Savings Program deductions.\n";
        else
            cout << "4. Check for state-specific deductions or credits.\n";

        if (c.income > 75000)
            cout << "5. Track eligible medical expenses above 7.5% of income for deductions.\n";

        cout << "Keep it up! Smart moves today mean more savings tomorrow!\n";
    } else {
        cout << "Business Owner Advice:\n";
        cout << "1. Deduct legitimate business expenses.\n";
        cout << "2. Use depreciation and investment credits.\n";
        cout << "3. Consider deferring some income.\n";
        cout << "4. Explore state-specific business credits in " << c.state << ".\n";
        cout << "5. Keep organized records for maximum deductions.\n";
    }

    cout << "---------------------------------\n";
}

// Add a customer and compute taxes
void addCustomer() {
    Customer c;
    string taxpayerType, maritalStatus, state;
    double income;

    cout << "\nEnter taxpayer type (Individual/Organization): ";
    getline(cin, taxpayerType);
    while (toLowerCase(taxpayerType) != "individual" && toLowerCase(taxpayerType) != "organization") {
        cout << "Invalid input. Enter 'Individual' or 'Organization': ";
        getline(cin, taxpayerType);
    }
    c.type = taxpayerType;
    bool isIndividual = toLowerCase(taxpayerType) == "individual";

    if (isIndividual) {
        cout << "Enter marital status (Single/Married): ";
        getline(cin, maritalStatus);
        while (toLowerCase(maritalStatus) != "single" && toLowerCase(maritalStatus) != "married") {
            cout << "Invalid input. Enter 'Single' or 'Married': ";
            getline(cin, maritalStatus);
        }
        c.maritalStatus = maritalStatus;
    } else {
        c.maritalStatus = "N/A";
    }

    cout << "Enter State (full name): ";
    getline(cin, state);
    c.state = state;

    cout << "Enter annual income (USD): $";
    while (!(cin >> income) || income < 0) {
        cout << "Invalid input. Enter non-negative numeric value: $";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    c.income = income;

    double taxableIncome = income;
    if (isIndividual) {
        
        if (toLowerCase(c.maritalStatus) == "single") 
        taxableIncome = max(0.0, income - 14600.0);

        else 
        taxableIncome = max(0.0, income - 29200.0);
    }
    c.taxableIncome = taxableIncome;

    c.fedTax = isIndividual ? federalTaxIndividual(taxableIncome, c.maritalStatus)
                            : federalTaxOrganization(income);
    c.stTax = stateTax(income, c.state, isIndividual);
    c.totalTax = c.fedTax + c.stTax;
    c.netIncome = income - c.totalTax;

    cout << "\n========== TAX SUMMARY ==========\n";
    cout << "Taxpayer Type: " << c.type << "\n";
    cout << "Marital Status: " << c.maritalStatus << "\n";
    cout << "State: " << c.state << "\n";
    cout << "Annual Income: $" << c.income << "\n";
    if (isIndividual)
        cout << "Taxable Income after Standard Deduction: $" << c.taxableIncome << "\n";
    cout << "Federal Tax: $" << c.fedTax << "\n";
    cout << "State Tax: $" << c.stTax << "\n";
    cout << "Total Tax: $" << c.totalTax << "\n";
    cout << "Net Income After Tax: $" << c.netIncome << "\n";
    cout << "=================================\n";

    giveSuggestions(c);

    customers.push_back(c);
}

// Admin dashboard
void displayAdminDashboard() {
    cout << "\n======= ADMIN DASHBOARD =======\n";
    cout << "Total customers: " << customers.size() << "\n";
    if (customers.empty()) {
        cout << "No customers yet.\n";
    } else {
        for (size_t i = 0; i < customers.size(); ++i) {
            const Customer& c = customers[i];
            cout << "\nCustomer #" << i + 1 << ":\n";
            cout << "Type: " << c.type << ", Marital Status: " << c.maritalStatus
                 << ", State: " << c.state << ", Income: $" << c.income
                 << ", Total Tax: $" << c.totalTax << "\n";
        }
    }
    cout << "================================\n";
}

// Export data to CSV
void exportData() {
    ofstream file("customer_data.csv");
    if (!file) {
        cout << "Error opening file for export!\n";
        return;
    }
    file << "Type,MaritalStatus,State,Income,TaxableIncome,FederalTax,StateTax,TotalTax,NetIncome\n";
    for (const auto& c : customers) {
        file << c.type << "," << c.maritalStatus << "," << c.state << "," << c.income
             << "," << c.taxableIncome << "," << c.fedTax << "," << c.stTax
             << "," << c.totalTax << "," << c.netIncome << "\n";
    }
    file.close();
    cout << "Customer data exported to customer_data.csv\n";
}

int main() {
    cout << fixed << setprecision(2);
    displayTaxStats();

    while (true) {
        string mode;
        cout << "\nSelect mode (Customer/Admin/Export/Exit): ";
        getline(cin, mode);
        string modeLower = toLowerCase(mode);

        if (modeLower == "customer") addCustomer();
        else if (modeLower == "admin") displayAdminDashboard();
        else if (modeLower == "export") exportData();
        else if (modeLower == "exit") {
            cout << "Exiting program. Goodbye!\n";
            break;
        } else {
            cout << "Invalid mode. Try again.\n";
        }
    }
    return 0;
}
