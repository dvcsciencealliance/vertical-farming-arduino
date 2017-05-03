// Constants
const int BaudRate = 9600; // Transfer rate in bits per second 

void setup()
{
    // Open serial connection
    Serial.begin(BaudRate);
}

void loop() 
{
    // Check to see if RPI is asking for data; if not, return
    if (Serial.available() <= 0)
        return;

    // Send data to RPI
    sendData();

        // Flush serial buffer  
    while (Serial.available() > 0)
        Serial.read();
}

void sendData()
{
    // Send readings on all analog pins to RPI
    for (int i = 0; i < 6; ++i)
        Serial.write((byte)analogRead(i));
}





