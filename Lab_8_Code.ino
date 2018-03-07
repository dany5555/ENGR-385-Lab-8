/**
   ENGR 385 Microprocessor Systems
   Lab 8-Timers

   The following code uses inline assembly code to control a servo motor by using the internal timers of the motor
   and setting the pin where the motor is connected to high or low in the specified times inicated in the datasheet
   of the servo motor.

   Authors:

   Edy Gomez
   Kevin Gonzalez
*/


// Servo motor communication wire is connected to pin 9 on the Arduino board.
int servo = 9;

// Global variable that holds the psoition of the servo motor.
int pos = 0;

void setup() {

  // Start of assembly code.
  asm(
    //Set Bit in I/O Register as output.
    "sbi %0, %1 \n"   
    : : "I" ( _SFR_IO_ADDR(DDRB)), "I" (DDB1)
  );
}

void loop() {

  // This loop sweeps the servo motor from position 500 to 2500 in increments of 5.
  // Instead of using the position as the example code does, we used time.
  for (int i = 500; i < 2500; i += 5) {


    asm volatile(
      "sbi %0, %1 \n"     //Set Bit in I/O Register
      : : "I" ( _SFR_IO_ADDR(PORTB)), "I" (PORTB1)
    );

    delayMicroseconds(i);


    asm volatile(
      "cbi %0, %1 \n"     //Clear Bit in I/O Register
      : : "I" ( _SFR_IO_ADDR(PORTB)), "I" (PORTB1)
    );
    delay(5);
  }

  // This loop sweeps the servo motor from position 2500 to 500 in decrements of 5.
  // Instead of using the position as the example code does, we used time.
  for (int i = 2500; i > 500; i -= 5) {

    asm volatile(
      "sbi %0, %1 \n"     //Set Bit in I/O Register
      : : "I" ( _SFR_IO_ADDR(PORTB)), "I" (PORTB1)
    );

    delayMicroseconds(i);


    asm volatile(
      "cbi %0, %1 \n"     //Clear Bit in I/O Register
      : : "I" ( _SFR_IO_ADDR(PORTB)), "I" (PORTB1)
    );
    delay(5);
  }
}
