/* Allows users to inquire about orders by entering a country name.
 * Includes a form with a text input for the country name and a submit button.
 * JavaScript is used to perform an AJAX request to get results without a page reload.
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
         << "    color: #333;"
         << "    margin: 0;"
         << "    padding: 20px;"
         << "    display: flex;"
         << "    flex-direction: column;"
         << "    align-items: center;"
         << "}"
         << "/* Styling for tables */"
         << "table {"
         << "    background-color: #fff;"
         << "    border-spacing: 2px;"
         << "    border-collapse: collapse;"
         << "    width: 80%;"
         << "    border-radius: 5px;"
         << "    box-shadow: 0 0 20px rgba(0, 0, 0, 0.1);"
         << "    margin-bottom: 20px;"
         << "}"
         << "table, th, td {"
         << "    border: 1px solid #ddd;"
         << "}"
         << "th, td {"
         << "    padding: 15px;"
         << "    text-align: left;"
         << "}"
         << "th {"
         << "    background-color: #3498db;"
         << "    color: #fff;"
         << "    font-weight: bold;"
         << "}"
         << "/* Styling for title */"
         << ".title {"
         << "    color: #3498db;"
         << "    text-align: center;"
         << "    font-size: 36px;"
         << "    font-weight: 700;"
         << "    margin-bottom: 20px;"
         << "}"
         << "</style></head>"
         << endl;
    html << "<body>" << endl;

    cout << html.str();
}



int main(int argc, char *argv[]) {
    // Output the HTML header with CSS
    PageHTMLHeader();

    // create a map object to access form objects with their names
    std::map<std::string, std::string> Get;
    // call the following methods from getpost.h to initialize the map object.
    initializePost(Get);
    // initializeGet(Get);

    std::string column;
    if (Get.find("search_text") != Get.end()) {
        column = Get["search_text"];
    }

    // Connect to the database with: database, server, userID, password
    mysqlpp::Connection conn; // Exceptions suppressed to keep code simple
    if (conn.connect("cse278_Fall2023", "localhost", "cse278_Fall2023", "rubrikPenguin")) {

        // Create a query
        mysqlpp::Query query = conn.query();
        query << "SELECT  Orders.orderDate AS 'Order Date', Customers.customerName AS 'Customer Name', Orders.orderNumber AS 'Order Number', Customers.addressLine1 AS 'Address', Customers.city AS 'City', Customers.country AS 'Country', Orders.status AS 'Status' FROM Customers, Orders  WHERE Customers.country = '"
              << column << "' AND Customers.customerNumber = Orders.customerNumber GROUP BY Customers.customerName, Orders.orderNumber;";

        // Check the query for correctness
        query.parse();

        // Run the query and get the result
        mysqlpp::StoreQueryResult result = query.store();

        // Always check for errors
        if (result.num_rows() > 0) {
            // display result in table
            cout << "<table border='2' width='1000'>" << endl;

            cout << "<tr><th>Order Date</th>"
                 << "<th>Customer Name</th>"
                 << "<th>Order Number</th>"
                 << "<th>Address</th>"
                 << "<th>City</th>"
                 << "<th>Country</th>"
                 << "<th>Status</th></tr>" << endl;

            // Get each row in the result set and print its contents
            for (int i = 0; i < result.num_rows(); ++i) {
                cout << "<tr><td>" << result[i]["Order Date"] << "</td><td>" << result[i]["Customer Name"] << "</td><td>" 
                << result[i]["Order Number"] << "</td><td>" << result[i]["Address"] << "</td><td>" << result[i]["City"] 
                << "</td><td>" << result[i]["Country"] << "</td><td>" << result[i]["Status"] << "</td></tr>" << endl;
            }

            cout << "</table>" << endl;
        } else {
            cout << "<p>Query does not return any records" << query.error() << "</p>" << endl;
        }

        // Ensure you close the HTML document properly
        cout << "</body></html>" << endl;
        return 0;
    } else {
        cout << "<p>Connection failed: " << conn.error() << "</p>" << endl;
        // Ensure you close the HTML document properly
        cout << "</body></html>" << endl;
        return 1;
    }
}
