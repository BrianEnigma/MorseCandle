/*
 * Morse Candle v1.0
 * Copyright © 2012, Brian Enigma <brian@netninja.com>, <http://nja.me/candle>
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 
 * 3.0 Unported License. To view a copy of this license, visit 
 * <http://creativecommons.org/licenses/by-nc-sa/3.0/>.
 *
 * If you like this project, you may also be interested in Puzzled Pint <http://puzzledpint.com/>.
 */
const int ANALOG_PIN = 9;
const int DIGITAL_PIN = 13;

//#define DEBUG_SERIAL      // output characters over the USB/Serial port
//#define ALSO_DIGITAL      // also blink dots/dashes to the on-board green LED

#define DOT_DURATION               500                  // 0.5s
#define DASH_DURATION             (DOT_DURATION * 3)    // 1.5s
#define PIP_BREAK_DURATION         DOT_DURATION         // 0.5s
#define CHARACTER_BREAK_DURATION  (DOT_DURATION * 4)    // 2s
#define WORD_BREAK_DURATION       (DOT_DURATION * 6)    // 3s
#define MESSAGE_BREAK_DURATION    (10 * 1000)           // 10s

#define ANALOG_LOW_VARIANCE    20
#define ANALOG_LOW             (50 - ANALOG_LOW_VARIANCE)
#define ANALOG_HIGH_VARIANCE   100
#define ANALOG_HIGH            (200 - ANALOG_HIGH_VARIANCE)

void tapCharacter(char c);
void tapString(const char *s);
void space(int duration);
void pip(int duration);

// Lookup table for all 26 letters.  Upper 5 bits are the pulses
// to send (MSB first), and the lower 3 bits are the number of
// bits to send for this letter.
// This table came from the Teensy 3.0 "blinky" example @ http://www.pjrc.com/teensy/gcc.html
const unsigned char morse_code_table[] = 
{
    0x40 + 2,   // A: .-
    0x80 + 4,   // B: -...
    0xA0 + 4,   // C: -.-.
    0x80 + 3,   // D: -..
    0x00 + 1,   // E: .
    0x20 + 4,   // F: ..-.
    0xC0 + 3,   // G: --.
    0x00 + 4,   // H: ....
    0x00 + 2,   // I: ..
    0x70 + 4,   // J: .---
    0xA0 + 3,   // K: -.-
    0x40 + 4,   // L: .-..
    0xC0 + 2,   // M: --
    0x80 + 2,   // N: -.
    0xE0 + 3,   // O: ---
    0x60 + 4,   // P: .--.
    0xD0 + 4,   // Q: --.-
    0x40 + 3,   // R: .-.
    0x00 + 3,   // S: ...
    0x80 + 1,   // T: -
    0x20 + 3,   // U: ..-
    0x10 + 4,   // V: ...-
    0x60 + 3,   // W: .--
    0x90 + 4,   // X: -..-
    0xB0 + 4,   // Y: -.--
    0xC0 + 4    // Z: --..
};

void setup() 
{
    // initialize the digital pin as an output.
    pinMode(ANALOG_PIN, OUTPUT);
    pinMode(DIGITAL_PIN, OUTPUT);
#ifdef DEBUG_SERIAL
    Serial.begin(9600); // USB is always 12 Mbit/sec
#endif
}

void loop() 
{
    // Identify that we're online, test the peripherals @ boot
    digitalWrite(DIGITAL_PIN, HIGH);
    analogWrite(ANALOG_PIN, 255);
    delay(1000);
    digitalWrite(DIGITAL_PIN, LOW);
    analogWrite(ANALOG_PIN, 0);
    // Run the program
    while (1) 
    {
        space(MESSAGE_BREAK_DURATION);
        tapString("PUZZLED PINT");
    }
}

void pip(int duration)
{
    int timeRemaining = duration;
    int delayTime;
#ifdef ALSO_DIGITAL
    digitalWrite(DIGITAL_PIN, HIGH);
#endif
    // Smooth out flicker transition here from low-to-high?
    while (timeRemaining > 0)
    {
        analogWrite(ANALOG_PIN, random(ANALOG_HIGH_VARIANCE / 10) * 10 + ANALOG_HIGH);
        if (timeRemaining > 100)
        {
            delayTime = random(90) + 10;
            delay(delayTime);
            timeRemaining -= delayTime;
        } else {
            delay(timeRemaining);
            timeRemaining = 0;
        }
    }
    // Smooth out flicker transition here from high-to-low?
    digitalWrite(DIGITAL_PIN, LOW);
}

void dot()
{
#ifdef DEBUG_SERIAL
    Serial.print(" dit");
#endif
    pip(DOT_DURATION); 
}

void dash()
{
#ifdef DEBUG_SERIAL
    Serial.print(" dah");
#endif
    pip(DASH_DURATION); 
}

void space(int duration)
{
    int timeRemaining = duration;
    int delayTime;
#ifdef DEBUG_SERIAL
    Serial.println("Space");
#endif
    digitalWrite(DIGITAL_PIN, LOW);
    while (timeRemaining > 0)
    {
        analogWrite(ANALOG_PIN, random(ANALOG_LOW_VARIANCE / 10) * 10 + ANALOG_LOW);
        if (timeRemaining > 100)
        {
            delayTime = random(90) + 10;
            delay(delayTime);
            timeRemaining -= delayTime;
        } else {
            delay(timeRemaining);
            timeRemaining = 0;
        }
    }
}

// blink a single character in Morse code
void tapCharacter(char c)
{
    unsigned char code, count;

    if (c == ' ') 
    {  
        space(WORD_BREAK_DURATION);
        return;
    }
    if (c < 'A' || c > 'Z') 
    {
        return; 
    }
#ifdef DEBUG_SERIAL
    Serial.print("Char ");
    Serial.print(c);
    Serial.print(':');
#endif  
    code = *(morse_code_table + (c - 'A'));
    for (count = code & 0x07; count > 0; count--) 
    {
        if (code & 0x80) 
        {
            dash();
        } else {
            dot();
        }
        space(PIP_BREAK_DURATION);
        code = code << 1;
    }
#ifdef DEBUG_SERIAL  
    Serial.println("");
#endif
    space(CHARACTER_BREAK_DURATION);
}

void tapString(const char *s)
{
    char c;

    while (1) 
    {
        c = *s++;
        if (!c) 
            break;
        tapCharacter(c);
    }
#ifdef DEBUG_SERIAL  
    Serial.print("");
#endif
}



