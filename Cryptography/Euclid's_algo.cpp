#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <xlsxwriter.h>

// Function to compute GCD using Euclid's algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to count number of iterations
int gcd_iterations(int a, int b) {
    int count = 0;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
        count++;
    }
    return count;
}

// Function to generate a random number with the specified number of digits
int random_number(int digits) {
    int low = pow(10, digits - 1);
    int high = pow(10, digits) - 1;
    return rand() % (high - low + 1) + low;
}

int main() {
    srand(time(0)); // Seed for random number generation

    // Create a new Excel workbook and worksheet
    lxw_workbook  *workbook  = workbook_new("GCD_results.xlsx");
    lxw_worksheet *worksheet = workbook_add_worksheet(workbook, NULL);

    // Write headers to the Excel sheet
    worksheet_write_string(worksheet, 0, 0, "Number A", NULL);
    worksheet_write_string(worksheet, 0, 1, "Number B", NULL);
    worksheet_write_string(worksheet, 0, 2, "GCD", NULL);
    worksheet_write_string(worksheet, 0, 3, "Iterations", NULL);

    int row = 1; // Start writing from the second row

    // Test multiple pairs of random numbers
    for (int i = 0; i < 10; ++i) {
        // Generate two random numbers with 3 digits
        int a = random_number(3);
        int b = random_number(3);

        // Calculate the GCD and iterations
        int result = gcd(a, b);
        int iterations = gcd_iterations(a, b);

        // Write the input numbers, GCD, and iterations to the Excel sheet
        worksheet_write_number(worksheet, row, 0, a, NULL);
        worksheet_write_number(worksheet, row, 1, b, NULL);
        worksheet_write_number(worksheet, row, 2, result, NULL);
        worksheet_write_number(worksheet, row, 3, iterations, NULL);

        // Increment row to write the next set of results
        row++;
    }

    // Close the workbook
    workbook_close(workbook);

    std::cout << "Results have been saved to 'GCD_results.xlsx'." << std::endl;

    return 0;
}
