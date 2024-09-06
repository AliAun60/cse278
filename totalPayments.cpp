/* Displays a form with a dropdown menu to select an office code.
 * Connects to a MySQL database and executes a query to populate the dropdown.
 * Allows users to select an office code and submit the form to perform a query.
 * Copyright (c) Ali Aun Haider, DEC 2023
 */ 

#define MYSQLPP_MYSQL_HEADERS_BURIED
#include <mysql++/mysql++.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <iomanip>
#include "getpost.h"

using std::cout;
using std::cerr;
using std::endl;
using std::stringstream;

// Function to output HTML header with embedded CSS
void PageHTMLHeader() {
    stringstream html;
    html << "Content-type: text/html" << endl << endl;
    html << "<html> <head> <meta charset=\"UTF-8\">" << endl;
    html << "<style>"
         << "/* General styling for the body */"
         << "body {"
         << "    font-family: 'Arial', sans-serif;"
         << "    background-color: #f7f7f7;"
         << "    max-width: 800pt;"
         << "    text-align: center;"
         << "    padding: 20pt;"
         << "}"
         << "/* Styling for tables */"
         << "table {"
         << "    margin: 0 auto;"
         << "    background-color: #fff;"
         << "    border-spacing: 0;"
         << "    border-collapse: collapse;"
         << "    width: 100%;"
         << "}"
         << "th, td {"
         << "    border: 1px solid #ddd;"
         << "    padding: 8px;"
         << "    text-align: left;"
         << "}"
         << "th {"
         << "    background-color: #3498db;"
         << "    color: white;"
         << "}"
         << "/* Styling for title */"
         << ".title {"
         << "    color: #3498db;"
         << "    text-align: center;"
         << "    font-size: 36px;"
         << "    font-weight: 700;"
         << "    margin-bottom: 20px;"
         << "}"
         << ".nav-links {"
         << "    color: #fff;"
         << "    font-weight: 700;"
         << "    text-decoration: none;"
         << "    text-align: center;"
         << "    display: inline-block;"
         << "    margin: 10px;"
         << "    padding: 10px 20px;"
         << "    border-radius: 5px;"
         << "    background-color: #3498db;"
         << "    transition: background-color 0.3s ease;"
         << "}"
         << ".nav-links:hover {"
         << "    background-color: #2980b9;"
         << "}"
         << "</style></head>"
         << endl;
    html << "<body>" << endl;
    html << "<table> "
         << "<tr>"
         << "<td>"
         << "<p class=\"title\">Customer and Order Management</p>"
         << "<p class=\"nav-links\">"
         << "<a href=\"http://os1.csi.miamioh.edu/~haidera/\" class=\"nav-links\"> QueryPage </a>"
         << " | <a href=\"http://os1.csi.miamioh.edu/~haidera/customerCode.html\" class=\"nav-links\"> GoBack </a> </p>"
         << "</td>"
         << "</tr>"
         << "</table>" << endl;

    cout << html.str();
}

int main(int argc, char *argv[]) {
    // Output the HTML header with CSS
    PageHTMLHeader();

    // create a map object to access form objects with their names
    std::map<std::string, std::string> Get;
    // call the following methods from getpost.h to initialize the map object.
    initializePost(Get);
    //initializeGet(Get);

    float OfficeCode;

    if (Get.find("dropdown") != Get.end()) {
        // Retrieve the selected office code from the form
        OfficeCode = std::stof(Get["dropdown"]);
    } else {
        // Display an error message if the form is not filled out
        cout << "<p>Fill out the form and press submit</p>" << endl;
        cout << "</body></html>" << endl;
        return 0;
    }

    // Connect to the database with: database, server, userID, password
    mysqlpp::Connection conn; // Exceptions suppressed to keep code simple
    if (conn.connect("cse278_Fall2023", "localhost", "cse278_Fall2023", "rubrikPenguin")) {

        // Create a query to retrieve customer and order information
        mysqlpp::Query query = conn.query();
        query << "SELECT Customers.customerNumber AS `Customer Number`, Customers.customerName AS `Customer Name`, Payments.amount AS `Amount Paid`, Payments.paymentDate AS `Payment Date`, Products.productName AS `Product Bought`, Offices.city AS `City`, Offices.country AS `Country` FROM Offices JOIN Employees ON Offices.officeCode = Employees.officeCode JOIN Customers ON Employees.employeeNumber = Customers.salesRepEmployeeNumber JOIN Payments ON Customers.customerNumber = Payments.customerNumber JOIN Orders ON Customers.customerNumber = Orders.customerNumber JOIN OrderDetails ON Orders.orderNumber = OrderDetails.orderNumber JOIN Products ON OrderDetails.productCode = Products.productCode WHERE Offices.officeCode = "
              << OfficeCode << " ORDER BY `Payment Date` DESC;";

        // Check the query for correctness
        query.parse();

        // Run the query and get the result
        mysqlpp::StoreQueryResult result = query.store();

        // Always check for errors
        if (result.num_rows() > 0) {
            // display result in table
            cout << "<table>" << endl;

            cout << "<tr>"
                 << "<th>Customer Number</th>"
                 << "<th>Customer Name</th>"
                 << "<th>Amount Paid</th>"
                 << "<th>Payment Date</th>"
                 << "<th>Product Bought</th>"
                 << "<th>City</th>"
                 << "<th>Country</th>"
                 << "</tr>" << endl;

            // Get each row in the result set and print its contents
            for (int i = 0; i < result.num_rows(); ++i) {
                cout << "<tr>"
                     << "<td>" << result[i]["Customer Number"] << "</td>"
                     << "<td>" << result[i]["Customer Name"] << "</td>"
                     << "<td>" << result[i]["Amount Paid"] << "</td>"
                     << "<td>" << result[i]["Payment Date"] << "</td>"
                     << "<td>" << result[i]["Product Bought"] << "</td>"
                     << "<td>" << result[i]["City"] << "</td>"
                     << "<td>" << result[i]["Country"] << "</td>"
                     << "</tr>" << endl;
            }

            cout << "</table>" << endl;

        } else {
            // Display an error message if the query does not return any records
            cout << "<p>Query does not return any records" << query.error() << "</p>" << endl;
        }

        // Ensure you close the HTML document properly
        cout << "</body></html>" << endl;
        return 0;
    } else {
        // Display an error message if the database connection fails
        cout << "<p>Connection failed: " << conn.error() << "</p>" << endl;
        // Ensure you close the HTML document properly
        cout << "</body></html>" << endl;
        return 1;
    }
}