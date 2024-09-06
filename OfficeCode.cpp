/* This file contains the Availible Attributes for the Product And Payment Query.
 * Contains a form to select an office code and submit a query.
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

// Function to output HTML header with embedded CSS
void PageHTMLHeader() {
    cout << "Content-type: text/html" << endl << endl;
    cout << "<html> <head> <meta charset=\"UTF-8\">" << endl;
    cout << "<style>"
         << "/* General styling for the body */"
         << "body {"
         << "    font-family: 'Arial', sans-serif;"
         << "    background-color: #f7f7f7;"
         << "    max-width: 800pt;"
         << "    padding: 72pt;"
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
    cout << "<body>" << endl;
    cout << "<table> "
         << "<tr>"
         << "<td>"
         << "<p class=\"title\">A Customer Application</p>"
         << "<p class=\"nav-links\">"
         << "<a href=\"./customerCode.html\"> QueryPage </a>"
         << " | <a href=\"/OfficeCode.cgi\"> GoBack </a> </p>"
         << "</td>"
         << "</tr>"
         << "</table>" << endl;
}

int main(int argc, char *argv[]) {
    // Output the HTML header with CSS
    PageHTMLHeader();

    // create a map object to access form objects with their names
    std::map<std::string, std::string> Get;
    // call the following methods from getpost.h to initialize the map object.
    initializePost(Get);
    //initializeGet(Get);

    // Connect to the database with: database, server, userID, password
    mysqlpp::Connection conn; // Exceptions suppressed to keep code simple
    if (conn.connect("cse278_Fall2023", "localhost", "cse278_Fall2023", "rubrikPenguin")) {

        // Create a query to retrieve distinct office codes from the Offices table
        mysqlpp::Query query = conn.query();
        query << "SELECT DISTINCT officeCode FROM Offices ORDER BY officeCode;";

        // Check the query for correctness
        query.parse();

        // Run the query and get the result
        mysqlpp::StoreQueryResult result = query.store();

        // Always check for errors
        if (result.num_rows() > 0) {
            // Output HTML content for the dropdown and form
            cout << "<form action=\"totalPayments.cgi\" method=\"POST\">" << endl;
            cout << "<fieldset> <legend>Available Attributes</legend> " << endl;
            cout << "  <label for=\"dropdown\">Select an Office Code: </label>\n";
            cout << "  <select id=\"dropdown\" name=\"dropdown\">\n";

            // Populate the dropdown menu with options from the database
            for (size_t i = 0; i < result.num_rows(); ++i) {
                cout << " <option value='" << result[i]["officeCode"] << "'>" << result[i]["officeCode"] << "</option>\n";
            }

            cout << "  </select>\n";
            cout << "  <input type=\"submit\" value=\"Submit\">\n";
            cout << "</fieldset>" << endl;
            cout << "</form>" << endl;
        } else {
            cerr << "Error: Query does not return any records" << query.error() << endl;
        }

        // Ensure you close the HTML document properly
        cout << "</body></html>" << endl;
        return 0;
    } else {
        cerr << "Error: Connection failed: " << conn.error() << endl;
        // Ensure you close the HTML document properly
        cout << "</body></html>" << endl;
        return 1;
    }
}
