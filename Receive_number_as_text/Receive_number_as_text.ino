
// Example 4 - Receive a number as text and convert it to an int

const byte numChars = 32; //A byte stores an 8-bit unsigned number, from 0 to 255.

char receivedChars[numChars];   // an array to store the received data

boolean newData = false;  //initialised

long dataNumber = 0;             // new for this version

void setup() {
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
}

void loop() {
    recvWithEndMarker();
    showNewNumber();
}

void recvWithEndMarker() {
    static byte ndx = 0;  //The static keyword is used to create variables that are visible to only one function. 
    //However unlike local variables that get created and destroyed every time a function is called, static variables persist beyond the function call, 
    //preserving their data between function calls. Variables declared as static will only be created and initialized the first time a function is called.
    char endMarker = '\n';
    char rc;
   
    if (Serial.available() > 0) {
        rc = Serial.read();

        if (rc != endMarker) {  // the user can terminate the length of the string without reaching maximum
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx == (numChars - 2)) {
                //ndx = numChars - 1;
                receivedChars[(numChars - 1)] = '\0'; // terminate the string. equivalent to newline in IDE Serial Monitor.
                ndx = 0;  // reset for next string input
                newData = true;
            }
        }
        else {  //(rc == endMarker)
            receivedChars[ndx] = '\0'; // terminate the string. equivalent to newline in IDE Serial Monitor.
            ndx = 0;
            newData = true;
        }
    }
}

void showNewNumber() {
    if (newData == true) {
        dataNumber = 0;             // new for this version
        dataNumber = atol(receivedChars);   // converts a character string to a long integer value
        Serial.print("This just in ... ");
        Serial.println(receivedChars);
        Serial.print("Data as Number ... ");    // new for this version
        Serial.println(dataNumber);     // new for this version
        newData = false;
    }
}
