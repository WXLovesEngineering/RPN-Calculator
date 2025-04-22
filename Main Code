// PROJECT  :RPNCalculator
// PURPOSE  :To create a calculator that performs calculations based on the postfix notation system
// COURSE   :ICS3U-E2
// AUTHOR   :William Xie
// DATE     :2025 04 21
// MCU      :328p (Nano)
// STATUS   :Working
// REFERENCE:http://darcy.rsgc.on.ca/ACES/TEI3M/Tasks.html#RPN

#include "Stack.h"          // Include the custom Stack library
#include <LiquidCrystal.h>  // Include the LCD library

Stack stack;  // Instance of the Stack Class

// LCD setups
uint8_t RS = 9, EN = 8, D4 = 7, D5 = 6, D6 = 5, D7 = 4;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Keypad setups
uint16_t maxThresholds[] = { 55, 59, 63, 67, 75, 81, 89, 97, 117, 132, 152, 179, 256, 341, 511, 1023 };  // adc values
char keys[] = { '+', 'E', '.', '0', '-', '3', '2', '1', '*', '6', '5', '4', '/', '9', '8', '7' };        // Corresponding keys

char operand[16] = "";  // String of the current operand

void setup() {
  lcd.begin(16, 2);             // Initialize the LCD
  lcd.clear();                  // Clear everything
  lcd.setCursor(0, 0);          // Set the cursor to the top left corner
  lcd.print("RPN Calculator");  // Display welcome texts
  delay(2000);                  // Wait for 2 seconds
  lcd.clear();                  // Clear everything
}

char getKey() {
  uint16_t adc = 0;        // Set the adc value to 0
  while (adc == 0) {       // Wait for a key to be pressed...
    adc = analogRead(A5);  // Read the analog value from the keypad
  }
  delay(500);                           // Debounce
  uint8_t index = 0;                    // Set the index value to 0
  while (adc > maxThresholds[index]) {  // Look for the matching adc value...
    index++;
  }
  return keys[index];  // Return the corresponding key
}

boolean isDigit(char ch) {
  return (ch >= '0' && ch <= '9');  // Return true if the entry is an integer between 0 and 9, inclusive
}

boolean isOperator(char ch) {
  return (ch == '+' || ch == '-' || ch == '*' || ch == '/');  // Return true if the entry is an operator
}

void append(char ch) {
  uint8_t length = strlen(operand);    // Set the length value to the length of the operand string
  if (length < sizeof(operand) - 1) {  // Ensure there is space in the string
    operand[length] = ch;              // Place the entry at the position corresponding to the length value
    operand[length + 1] = '\0';        // Terminate the string with null
  }
}

void displayEntry() {
  lcd.clear();          // Clear everything
  lcd.setCursor(0, 0);  // Set the cursor to the top left corner
  lcd.print(operand);   // Display the current operand
}

float evaluate(char op, float operand1, float operand2) {
  switch (op) {  // 4 cases for the operators...
    case '+':
      return operand1 + operand2;
    case '-':
      return operand1 - operand2;
    case '*':
      return operand1 * operand2;
    case '/':
      if (operand2 == 0) {                 // If divided by 0...
        lcd.clear();                       // Clear everything
        lcd.print("Error: Divided by 0");  // Display the error message
        delay(2000);                       // Wait for 2 seconds
        lcd.clear();                       // Clear everything
        return NAN;                        // Return Not-a-Number
      } else {
        return operand1 / operand2;
      }
  }
}

void displayEvaluate(float result) {
  lcd.clear();           // Clear everything
  lcd.setCursor(0, 1);   // Set the cursor to the bottom left corner
  lcd.print(result, 4);  // Display the result to 4 decimal places
  delay(2000);           // Wait for 2 seconds
  lcd.clear();           // Clear everything
}

void process(char ch) {
  if (isDigit(ch) || ch == '.') {  // If the entry is a digit or decimal point...
    append(ch);                    // Append the entry to the current operand
    displayEntry();                // Display the current operand
  } else if (ch == 'E') {          // If Enter is pressed...
    if (strlen(operand) > 0) {     // If the string is not empty...
      stack.push(atof(operand));   // Convert the operand to float and push it onto the stack
      operand[0] = '\0';           // Clear the operand
      lcd.clear();                 // Clear everything for the next entry
    }
  } else if (isOperator(ch)) {                            // If the entry is an operator...
    if (!stack.isEmpty()) {                               // If the stack is not empty...
      float operand2 = stack.pop();                       // Pop out the second operand
      if (!stack.isEmpty()) {                             // If the stack is still not empty...
        float operand1 = stack.pop();                     // Pop out the first operand
        float result = evaluate(ch, operand1, operand2);  // Perform the operation
        if (!isnan(result)) {                             // If the result is a valid number...
          stack.push(result);                             // Push the result back onto the stack
          displayEvaluate(result);                        // Display the result
        }
      } else {                               // If the stack is empty after popping out the second operand...
        stack.push(operand2);                // Push the second operand back onto the stack
        lcd.clear();                         // Clear everything
        lcd.print("Error: Only 1 Operand");  // Display the error message
        delay(2000);                         // Wait for 2 seconds
        lcd.clear();                         // Clear everything
      }
    } else {                            // If the stack is empty...
      lcd.clear();                      // Clear everything
      lcd.print("Error: Stack Empty");  // Display the error message
      delay(2000);                      // Wait for 2 seconds
      lcd.clear();                      // Clear everything
    }
  }
}

void loop() {
  char ch = getKey();  // Always get the entry
  process(ch);         // Always process the entry
}
