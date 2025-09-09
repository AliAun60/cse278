# Customer Orders App

A lightweight web + C++ application for **managing customer orders, payments, and products** using a MySQL backend.  
It provides a simple HTML interface connected to C++ CGI programs that query and display results dynamically.

---

## 🔎 Overview
- Query **orders by country** (date, number, customer name, status, address).
- Retrieve **customer payments and products** filtered by office code.
- View structured results in clean HTML tables.
- Backend powered by **C++** + **MySQL++** library.  
- Frontend built with **HTML + CSS** for navigation and forms.

---

## 🗂️ Features
- **Orders Inquiry**: Enter a country to view orders placed, customer names, and order statuses.  
- **Payments Query**: Select an office code to get customer payments, dates, and product details.  
- **About Page**: Explains the objectives and tables used in the system.  
- **Home Page**: Simple navigation with links to all queries.

---

## 🚀 How to Run

### Requirements
- A web server that supports **CGI** (e.g., Apache with CGI enabled).  
- **MySQL** database with tables: Offices, Employees, Customers, Payments, Orders, OrderDetails, Products.  
- **mysql++** C++ connector installed.  
- C++17 or newer compiler.

### Setup
1. Clone this repo:
   ```bash
   git clone https://github.com/AliAun60/customer-orders-app.git
   cd customer-orders-app

Configure your database connection inside the C++ files (getTotalOrders.cpp, totalPayments.cpp, OfficeCode.cpp) if needed.
g++ -o cgi-bin/getTotalOrders.cgi getTotalOrders.cpp -lmysqlpp
g++ -o cgi-bin/totalPayments.cgi totalPayments.cpp -lmysqlpp
g++ -o cgi-bin/OfficeCode.cgi OfficeCode.cpp -lmysqlpp


Place the compiled .cgi files in your server’s cgi-bin directory.

Serve the .html files (index.html, customersList.html, customerCode.html, about.html) via your web server.

Open index.html in your browser and start querying 🎉.
