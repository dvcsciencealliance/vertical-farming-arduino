// Constants
const int BaudRate = 9600; // Transfer rate in bits per second
const int ledPin = 13; 

void setup()
{
    pinMode(ledPin, OUTPUT);

    // Open serial connection
    Serial.begin(BaudRate);
}

void loop() 
{
    // Check to see if RPI is asking for data; if not, return
    if (Serial.available() <= 0)
        return;

    // Read command
    int command = Serial.read();    // read the next byte avilable; -1 if no data
    
    // Send data to RPI
    sendData();

    // Flush serial buffer  
    while (Serial.available() > 0)
        Serial.read();
}

void parseCommand(int command)
{
    digitalWrite(ledPin, command ? HIGH : LOW);   // sets the LED on or off   
}

void sendData()
{
    // Send readings on all analog pins to RPI
    String result;
    for (int i = 0; i < 6; ++i)
    {
        result += String(analogRead(i)) + ' ';
    }
    Serial.println(result);     
}






