#include <Arduino.h>
#include <PID_v1.h>
#include <Wire.h>
#include <stdlib.h>

const uint8_t SIGNAL_A_PIN_1 = 2; // pin connected to A signal of motor 1
const uint8_t SIGNAL_B_PIN_1 = 3; // pin connected to B signal of motor 1
const uint8_t DIR_PIN_1 = 4;
const uint8_t PWM_PIN_1 = 5;

const uint8_t SIGNAL_A_PIN_2 = 6; // pin connected to A signal of motor 2
const uint8_t SIGNAL_B_PIN_2 = 7; // pin connected to B signal of motor 2
const uint8_t DIR_PIN_2 = 8;
const uint8_t PWM_PIN_2 = 9;

// Constant for I2C address of this Arduino
const uint8_t MY_ADDRESS = 0x04;

// Variables to store current position of encoders
long currentPositionEncoder1 = 0;
long currentPositionEncoder2 = 0;

// Variables for PID control
double setpoint1, setpoint2, input1, input2, output1, output2;
double kp = 2, ki = 5, kd = 1;
PID motorPID1(&input1, &output1, &setpoint1, kp, ki, kd, DIRECT);
PID motorPID2(&input2, &output2, &setpoint2, kp, ki, kd, DIRECT);

// Task to read encoder position
void readEncoder(void *args)
{
    // Read encoder 1
    int signalAState1 = digitalRead(SIGNAL_A_PIN_1);
    int signalBState1 = digitalRead(SIGNAL_B_PIN_1);

    // clockwise
    if (signalAState1 == HIGH && signalBState1 == LOW)
        ++currentPositionEncoder1;

    // counterclockwise
    else if (signalAState1 == LOW && signalAState1 == HIGH)
        --currentPositionEncoder1;

    // Read encoder 2
    int signalAState2 = digitalRead(SIGNAL_A_PIN_2);
    int signalBState2 = digitalRead(SIGNAL_B_PIN_2);

    // clockwise
    if (signalAState2 == HIGH && signalBState2 == LOW)
        ++currentPositionEncoder2;

    // counterclockwise
    else if (signalAState2 == LOW && signalAState2 == HIGH)
        --currentPositionEncoder2;

    vTaskDelay(10 / portTICK_PERIOD_MS);
}

void writeToMotor(void *args)
{
    // Update input for PID control of motor 1
    input1 = currentPositionEncoder1;

    // Compute output based on PID control algorithm
    motorPID1.Compute();

    // Set direction and write output to motor 1
    if (output1 > 0)
    {
        digitalWrite(DIR_PIN_1, HIGH);
        analogWrite(PWM_PIN_1, output1);
    }
    else if (output1 < 0)
    {
        digitalWrite(DIR_PIN_1, LOW);
        analogWrite(PWM_PIN_1, -output1);
    }
    else
        analogWrite(PWM_PIN_1, 0);

    // Update input for PID control of motor 2
    input2 = currentPositionEncoder2;
    // Compute output based on PID control algorithm
    motorPID2.Compute();

    // Set direction and write output to motor 2
    if (output2 > 0)
    {
        digitalWrite(DIR_PIN_2, HIGH);
        analogWrite(PWM_PIN_2, output2);
    }
    else if (output2 < 0)
    {
        digitalWrite(DIR_PIN_2, LOW);
        analogWrite(PWM_PIN_2, -output2);
    }
    else
        analogWrite(PWM_PIN_2, 0);

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
        // Convert character to integer and update setpoint for motor 1
        setpoint1 = atoi(&c);

        // Read a byte as a character
        c = Wire.read();
        // Convert character to integer and update setpoint for motor 2
        setpoint2 = atoi(&c);
    }
}

void setup()
{
    // Set pin modes
    pinMode(SIGNAL_A_PIN_1, INPUT);
    pinMode(SIGNAL_B_PIN_1, INPUT);
    pinMode(SIGNAL_A_PIN_2, INPUT);
    pinMode(SIGNAL_B_PIN_2, INPUT);
    pinMode(DIR_PIN_1, OUTPUT);
    pinMode(PWM_PIN_1, OUTPUT);
    pinMode(DIR_PIN_2, OUTPUT);
    pinMode(PWM_PIN_2, OUTPUT);

    // Initialize serial communication
    Serial.begin(9600);

    // Initialize PID control
    setpoint1 = 0;
    setpoint2 = 0;
    motorPID1.SetMode(AUTOMATIC);
    motorPID2.SetMode(AUTOMATIC);

    // Initialize I2C communication as a slave and set function to call when data is received
    Wire.begin(MY_ADDRESS);
    Wire.onReceive(receiveData);

    // Create tasks to read encoder position
    xTaskCreatePinnedToCore(
        readEncoder,
        "readEncoder",
        2048,
        NULL,
        2,
        NULL,
        APP_CPU_NUM);

    // Create task to write to motor
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