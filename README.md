# US Taxation System

![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)
![Platform](https://img.shields.io/badge/Platform-Console-lightgrey)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen)
![University](https://img.shields.io/badge/University-Superior%20University%20Lahore-red)

A comprehensive **C++ console-based tax estimation platform** that calculates federal and state-specific tax liabilities for all **50 US states + District of Columbia**. The system supports both **Individual** (Single/Married) and **Organization** taxpayers with detailed tax summaries, personalized suggestions, and CSV data export.

---

## Team Members

| # | Name | Role |
|---|------|------|
| 1 | M. Ahmad Subhani | Team Leader & Developer |
| 2 | Saad Ali | Developer |
| 3 | Asadullah Baig | Developer |
| 4 | Uzair Alam | Tester |
| 5 | Abdullah Khan | Documentation & Research |

**Submitted to:** Sir Asad Ali  
**Department:** Software Engineering  
**University:** Superior University, Lahore  
**Date:** November 24, 2025

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [System Roles](#system-roles)
- [Tax Calculation Workflow](#tax-calculation-workflow)
- [Technical Architecture](#technical-architecture)
- [How to Run](#how-to-run)
- [Modes of Operation](#modes-of-operation)
- [Sample Output](#sample-output)
- [Future Improvements](#future-improvements)

---

## Overview

The **US Taxation System** is built to simplify one of the most complex processes a citizen faces — tax filing. By centralizing tax logic and presenting a clean interface, the system minimizes confusion and delivers an instant breakdown of estimated taxes.

It supports:
- All **50 US states** plus the **District of Columbia**
- **Federal tax** brackets for Individuals (2024 IRS rates)
- **Flat 21% corporate tax** for Organizations
- **Standard deductions** ($14,600 for Single, $29,200 for Married)
- **State income tax** rates for each state
- **Personalized tax-saving suggestions**
- **CSV export** of all customer records

---

## Features

- **Multi-State Support** — Tax rules for all 50 states and DC integrated
- **Individual Taxpayer** — Single and Married filing status with correct brackets
- **Organization Taxpayer** — Flat 21% federal corporate tax rate
- **Standard Deduction** — Automatically applied for individual filers
- **Detailed Tax Summary** — Shows Gross Income, Taxable Income, Federal Tax, State Tax, Total Tax, and Net Income
- **Personalized Suggestions** — Smart tips for 401(k), IRA, filing jointly, and state-specific credits
- **Admin Dashboard** — View all entered customer records
- **CSV Export** — Export all records to `customerdata.csv`
- **Input Validation** — Handles invalid entries gracefully

---

## System Roles

### Individual Taxpayer
Users can choose between **Single** or **Married** filing status. Each triggers different federal tax brackets and a standard deduction:
- Single: $14,600 deduction
- Married: $29,200 deduction

### Organization
Organizations are taxed at a flat **21% federal rate** on gross income. State tax is also applied based on selected state.

### State Selection
All 50 US states are available. States with **no income tax** (e.g., Texas, Florida, Wyoming) return $0 state tax automatically.

---

## Tax Calculation Workflow

```
1. Select Taxpayer Type  →  Individual or Organization
2. Select Filing Status  →  Single or Married (Individual only)
3. Select State          →  Any of the 50 US states or DC
4. Enter Annual Income   →  Gross income in USD
5. System Computes       →  Taxable income, federal tax, state tax
6. Summary Displayed     →  Full tax breakdown shown
7. Suggestions Given     →  Personalized tax-saving tips
```

---

## Technical Architecture

- **Language:** C++
- **UI:** Console-based (Qt-compatible design structure)
- **Data Storage:** In-memory `vector<Customer>` with CSV export
- **Modules:**
  - `federalTaxIndividual()` — Progressive bracket calculation
  - `federalTaxOrganization()` — Flat 21% rate
  - `stateTax()` — Full 50-state + DC mapping
  - `giveSuggestions()` — Personalized financial advice
  - `addCustomer()` — Input handling and tax computation
  - `displayAdminDashboard()` — View all records
  - `exportData()` — CSV export

### Federal Tax Brackets (Individual - 2024)

| Rate | Single Filers | Married Filing Jointly |
|------|--------------|------------------------|
| 10% | Up to $11,000 | Up to $22,000 |
| 12% | $11,001 – $44,725 | $22,001 – $89,450 |
| 22% | $44,726 – $95,375 | $89,451 – $190,750 |
| 24% | $95,376 – $182,100 | $190,751 – $364,200 |
| 32% | $182,101 – $231,250 | $364,201 – $462,500 |
| 35% | $231,251 – $578,125 | $462,501 – $693,750 |
| 37% | Over $578,125 | Over $693,750 |

---

## How to Run

### Prerequisites
- A C++ compiler (GCC / MinGW / MSVC)
- Terminal or Command Prompt

### Compilation
```bash
g++ tax3.cpp -o tax_system
```

### Run
```bash
./tax_system
```
*(On Windows: `tax_system.exe`)*

---

## Modes of Operation

When the program starts, enter one of the following modes:

| Mode | Description |
|------|-------------|
| `customer` | Add a new taxpayer and compute taxes |
| `admin` | View all stored customer records |
| `export` | Export all records to `customerdata.csv` |
| `exit` | Exit the program |

---

## Sample Output

```
===== TAX SUMMARY =====
Taxpayer Type   : Individual
Marital Status  : Single
State           : California
Annual Income   : $85,000.00
Taxable Income  : $70,400.00
Federal Tax     : $11,554.00
State Tax       : $11,305.00
Total Tax       : $22,859.00
Net Income      : $62,141.00

--- PERSONALIZED TAX SUGGESTIONS ---
1. Max out your 401k contributions! Save up to $8,500.00
2. Contribute to an IRA. Putting aside $4,250.00 could reduce federal tax.
4. Check if you qualify for California renters credit.
```

---

## Future Improvements

- [ ] Automatic federal tax rule updates (IRS annual sync)
- [ ] Federal tax integrated with state tax in one unified flow
- [ ] Online filing compatibility
- [ ] Multi-year tax projections
- [ ] AI-assisted tax planning features
- [ ] Graphical User Interface (Qt-based)
- [ ] Support for additional filing statuses (Head of Household)

---

## License

This project was developed as an academic assignment at **Superior University, Lahore**. All rights reserved by the team.
