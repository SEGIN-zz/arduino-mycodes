#### is the output of incremental encodes 90degree outof pahse

Incremental encoders are devices that convert mechanical motion into digital signals. They typically generate two square wave signals that are 90 degrees out of phase with each other. These signals are called "A" and "B," and they are used to determine the direction and speed of rotation of the encoder.

For example, consider an incremental encoder that is attached to a rotating shaft. As the shaft rotates, the encoder generates two square wave signals that are 90 degrees out of phase with each other. If the shaft is rotating in a clockwise direction, the A signal will lead the B signal by 90 degrees. If the shaft is rotating in a counterclockwise direction, the B signal will lead the A signal by 90 degrees.

So, in general, the output of an incremental encoder is a pair of square wave signals that are 90 degrees out of phase with each other. These signals can be used to determine the direction and speed of rotation of the encoder.


### show me the signal in .md
```
       _______     _______
      /       \   /       \
     /         \ /         \
____/           X           \____
     \         / \         /
      \_______/   \_______/
          |       |
          A       B

```
In this representation, the A and B signals are shown as square waves that are 90 degrees out of phase with each other. The X indicates a transition point in the waveform, which corresponds to a rising edge or falling edge in the signal.


Here is a visual representation of the A and B signals produced by an incremental encoder in Markdown, when the shaft is rotating in a clockwise direction:
```
       _______     _______
      /       \   /       \
     /         \ /         \
____/           X           \____
     \         / \         /
      \_______/   \_______/
          |       |
          A       B

```

In this case, the A signal leads the B signal by 90 degrees, indicating that the shaft is rotating in a clockwise direction.

Here is a visual representation of the A and B signals produced by an incremental encoder in Markdown, when the shaft is rotating in a counterclockwise direction:

```
       _______     _______
      /       \   /       \
     /         \ /         \
____/           X           \____
     \         / \         /
      \_______/   \_______/
          |       |
          B       A

```
In this case, the B signal leads the A signal by 90 degrees, indicating that the shaft is rotating in a counterclockwise direction.

It's important to note that these are just visual representations of the signals, and they may not be displayed accurately in all Markdown viewers. To generate actual incremental encoder signals, you will need to use a programming language or specialized software.

### then which point in this wave is used to count

In an incremental encoder, the transitions between the high and low states of the A and B signals are used to determine the position and speed of the encoder. These transitions, known as "edges," can be either rising or falling, depending on the direction of the signal.

For example, consider an incremental encoder that is attached to a rotating shaft. As the shaft rotates, the encoder generates two square wave signals that are 90 degrees out of phase with each other. The transitions between the high and low states of these signals, known as edges, can be used to determine the position and speed of the encoder.

To count the number of edges, you can use a counter that increments or decrements every time an edge is detected. The direction of the count depends on the order in which the A and B signals are detected. For example, if the A signal is detected before the B signal, the counter will increment. If the B signal is detected before the A signal, the counter will decrement.

By counting the number of edges, you can determine the position of the encoder relative to a reference point. You can also use the time between edges to determine the speed of the encoder.


Here is a sample Arduino code that you can use to interface with an incremental encoder, without using the `Encoder` library:
```
int A_pin = 2;  // Pin connected to A signal
int B_pin = 3;  // Pin connected to B signal

long position = 0;  // Variable to store encoder position

void setup() {
  pinMode(A_pin, INPUT);  // Set A pin as input
  pinMode(B_pin, INPUT);  // Set B pin as input
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  // Read A and B signals
  int A_state = digitalRead(A_pin);
  int B_state = digitalRead(B_pin);

  // Check for transitions and update position
  if (A_state == HIGH && B_state == LOW) {
    // A signal detected first, increment position
    position++;
  }
  else if (A_state == LOW && B_state == HIGH) {
    // B signal detected first, decrement position
    position--;
  }

  // Print position to serial monitor
  Serial.println(position);
}

```
In this code, the A and B signals of the incremental encoder are read using the `digitalRead()` function, which returns the state of the signal as a HIGH or LOW value. The code then checks for transitions between the A and B signals, and updates the position of the encoder accordingly. The direction of the count (clockwise or counterclockwise) is determined by the order in which the A and B signals are detected.

You will need to modify the code to match the pin numbers and other hardware details of your specific setup. You may also need to add additional logic to handle other aspects of the encoder, such as determining the speed of the encoder or filtering out noise from the signals.

To determine the direction of rotation of an incremental encoder, you can use the order in which the A and B signals are detected. For example, if the A signal is detected before the B signal, the encoder is rotating in a clockwise direction. If the B signal is detected before the A signal, the encoder is rotating in a counterclockwise direction.

Here is a modified version of the previous Arduino code that includes logic to determine the direction of rotation:
```
int A_pin = 2;  // Pin connected to A signal
int B_pin = 3;  // Pin connected to B signal

long position = 0;  // Variable to store encoder position

void setup() {
  pinMode(A_pin, INPUT);  // Set A pin as input
  pinMode(B_pin, INPUT);  // Set B pin as input
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  // Read A and B signals
  int A_state = digitalRead(A_pin);
  int B_state = digitalRead(B_pin);

  // Check for transitions and update position
  if (A_state == HIGH && B_state == LOW) {
    // A signal detected first, increment position
    position++;
    Serial.println("Clockwise");
  }
  else if (A_state == LOW && B_state == HIGH) {
    // B signal detected first, decrement position
    position--;
    Serial.println("Counterclockwise");
  }

  // Print position to serial monitor
  Serial.println(position);
}
```

In this code, the direction of rotation is printed to the serial monitor along with the position of the encoder. You can modify the code to suit your specific needs, such as adding additional logic to handle other cases or performing other actions based on the direction of rotation.

### how much degree of rotation will it be if it moves one possition ?

The number of degrees of rotation per position of an incremental encoder depends on the resolution of the encoder and the mechanical configuration of the system it is attached to.

Incremental encoders typically have a certain number of counts or "ticks" per revolution, which is a measure of their resolution. For example, an encoder with 1000 counts per revolution will generate 1000 ticks per complete revolution of the shaft.

To determine the number of degrees of rotation per position, you will need to know the resolution of the encoder and the mechanical configuration of the system it is attached to. For example, if the encoder is attached to a shaft that has a 10:1 reduction ratio, the number of degrees of rotation per position will be 360/1000 * 10 = 3.6 degrees per position.

It's important to note that this is just a general example, and the actual number of degrees of rotation per position will depend on the specific details of your setup.
