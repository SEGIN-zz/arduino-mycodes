#include <Arduino.h>
#include <PID_v1.h>
#include <Wire.h>
#include <stdlib.h>

// Constants for pin numbers
const int SIGNAL_A_PIN = 2;   // pin connected to A signal 
const int SIGNAL_B_PIN = 3;   // pin connected to B signal
const int DIR_PIN = 4;
const int PWM_PIN = 5;

// Constant for I2C address of this Arduino
const int MY_ADDRESS = 0x04;

// Variable to store current position of encoder
long currentPositionEncoder = 0;

// Variables for PID control
double setpoint, input, output;
double kp = 2, ki = 5, kd = 1;
PID motorPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

// Task to read encoder position
void readEncoder(void *args)
{
    int signalAState = digitalRead(SIGNAL_A_PIN);
    int signalBState = digitalRead(SIGNAL_B_PIN);

    // clockwise
    if (signalAState == HIGH && signalBState == LOW)
        ++currentPositionEncoder;

    // counterclockwise
    else if (signalAState == LOW && signalAState == HIGH)
        --currentPositionEncoder;

    vTaskDelay(10 / portTICK_PERIOD_MS);
}

// Task to write to motor based on PID control output
void writeToMotor(void *args)
{
    // Update input for PID control
    input = currentPositionEncoder;
    // Compute output based on PID control algorithm
    motorPID.Compute();

    // Set direction and write output to motor
    if (output > 0)
    {
        digitalWrite(DIR_PIN, HIGH);
        analogWrite(PWM_PIN, output);
    }
    else if (output < 0)
    {
        digitalWrite(DIR_PIN, LOW);
        analogWrite(PWM_PIN, -output);
    }
    else
    {
        analogWrite(PWM_PIN, 0);
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
}

// Function to receive data from I2C bus
void receiveData(int byteCount)
{
    // Loop through all received bytes
    while (Wire.available())
    {
        // Read a byte as a character
        char c = '5';
        c = Wire.read();

        // Convert character to integer and update setpoint
        setpoint = atoi(&c);

        Serial.print(c);
    }

    Serial.println();
}

void setup()
{
    // Set pin modes
    pinMode(SIGNAL_A_PIN, INPUT);
    pinMode(SIGNAL_B_PIN, INPUT);

    // Initialize serial communication
    Serial.begin(9600);

    // Initialize PID control
    setpoint = 0;
    motorPID.SetMode(AUTOMATIC);

    // Initialize I2C communication as a slave and set function to call when data is
    Wire.begin(MY_ADDRESS);
    Wire.onReceive(receiveData);

    // Create tasks to read encoder position and write to motor
    xTaskCreatePinnedToCore(
        readEncoder,
        "readEncoder",
        2048,
        NULL,
        2,
        NULL,
        APP_CPU_NUM);

    xTaskCreatePinnedToCore(
        writeToMotor,
        "writeToMotor",
        2048,
        NULL,
        2,
        NULL,
        PRO_CPU_NUM);
}

void loop()
{
    // do nothing
}