#include <Arduino.h>
 /* =========================
      Structure Constants
   ========================= */


/* For ROTJ:
   - Change NUM_STEPS to 8
   - Copy and paste the following into char_sequence below:

const byte char_sequence[NUM_STEPS][NUM_DIGITS + 1] =
{
  //  DIGIT 1     DIGIT 2     DIGIT 3     DIGIT 4     DIGIT 5  BAR (0-4)        DISPLAY BARGRAPH
  //  GFEDCBA     GFEDCBA     GFEDCBA     GFEDCBA     GFEDCBA                     12345   01234
  {0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0x03},  //Seq 1  - 88888  |   = |
  {0b10111101, 0b11011011, 0b11110110, 0b11001111, 0b10111110, 0xFF},  //Seq 2  - '.=¦=  |     |
  {0b10100001, 0b11000001, 0b10000110, 0b10001100, 0b11111101, 0x02},  //Seq 3  - dUEP'  |  =  |
  {0b10001001, 0b11000010, 0b10100100, 0b10000000, 0b11001110, 0xFF},  //Seq 4  - HG28r  |     |
  {0b10001001, 0b10010010, 0b10100100, 0b10011000, 0b11111001, 0x00},  //Seq 5  - H5291  |=    |
  {0b10111101, 0b11011011, 0b11110110, 0b11001111, 0b10111110, 0xFF},  //Seq 6  - '.=¦=  |     |
  {0b10001011, 0b10000110, 0b10001000, 0b10100001, 0b10001001, 0x04},  //Seq 7 -  hEADH  |    =|
  {0b10001001, 0b11000010, 0b10100100, 0b10000000, 0b11001110, 0xFF},  //Seq 8  - HG28r  |     |
};
  
  For ESB:
  - Change NUM_STEPS to 11
  - Copy and paste the following into char_sequence below
  
const byte char_sequence[NUM_STEPS][NUM_DIGITS + 1] =
{
  //  DIGIT 1     DIGIT 2     DIGIT 3     DIGIT 4     DIGIT 5  BAR (0-4)        DISPLAY BARGRAPH
  //  GFEDCBA     GFEDCBA     GFEDCBA     GFEDCBA     GFEDCBA                     12345   01234
  {0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0xFF},  //Seq 1  -        |     |
  {0b10100001, 0b11000001, 0b10000110, 0b10001100, 0b11111101, 0x01},  //Seq 2  - dUEP'  | =   |
  {0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0x03},  //Seq 3  - 88888  |   = |
  {0b10100001, 0b11000001, 0b10000110, 0b10001100, 0b11111101, 0x02},  //Seq 4  - dUEP'  |  =  |
  {0b10001011, 0b10000110, 0b10001000, 0b10100001, 0b10001001, 0x04},  //Seq 5  - hEADH  |    =|
  {0b10111101, 0b11011011, 0b11110110, 0b11001111, 0b10111110, 0xFF},  //Seq 6  - '.=¦=  |     |
  {0b10100001, 0b11000001, 0b10000110, 0b10001100, 0b11111101, 0x01},  //Seq 7  - dUEP'  | =   |
  {0b10001001, 0b10010010, 0b10100100, 0b10011000, 0b11111001, 0x00},  //Seq 8  - H5291  |=    |
  {0b10111101, 0b11011011, 0b11110110, 0b11001111, 0b10111110, 0xFF},  //Seq 9  - '.=¦=  |     |
  {0b10100001, 0b11000001, 0b10000110, 0b10001100, 0b11111101, 0x01},  //Seq 10 - dUEP'  | =   |
  {0b10001001, 0b11000010, 0b10100100, 0b10000000, 0b11001110, 0xFF},  //Seq 11 - H{E8¬  |     |
};

*/
#define NUM_STEPS 11

#define UPDATE_FREQUENCY 2000 //approx 2 seconds

#define NUM_BARS       5
#define NUM_DIGITS     5
#define NUM_SEGMENTS   7

//this structure holds the entire sequence of characters to display
const byte char_sequence[NUM_STEPS][NUM_DIGITS + 1] =
{
  //  DIGIT 1     DIGIT 2     DIGIT 3     DIGIT 4     DIGIT 5  BAR (0-4)        DISPLAY BARGRAPH
  //  GFEDCBA     GFEDCBA     GFEDCBA     GFEDCBA     GFEDCBA                     12345   01234
  {0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0xFF},  //Seq 1  -        |     |
  {0b10100001, 0b11000001, 0b10000110, 0b10001100, 0b11111101, 0x01},  //Seq 2  - dUEP'  | =   |
  {0b10000000, 0b10000000, 0b10000000, 0b10000000, 0b10000000, 0x03},  //Seq 3  - 88888  |   = |
  {0b10100001, 0b11000001, 0b10000110, 0b10001100, 0b11111101, 0x02},  //Seq 4  - dUEP'  |  =  |
  {0b10001011, 0b10000110, 0b10001000, 0b10100001, 0b10001001, 0x04},  //Seq 5  - hEADH  |    =|
  {0b10111101, 0b11011011, 0b11110110, 0b11001111, 0b10111110, 0xFF},  //Seq 6  - '.=¦=  |     |
  {0b10100001, 0b11000001, 0b10000110, 0b10001100, 0b11111101, 0x01},  //Seq 7  - dUEP'  | =   |
  {0b10001001, 0b10010010, 0b10100100, 0b10011000, 0b11111001, 0x00},  //Seq 8  - H5291  |=    |
  {0b10111101, 0b11011011, 0b11110110, 0b11001111, 0b10111110, 0xFF},  //Seq 9  - '.=¦=  |     |
  {0b10100001, 0b11000001, 0b10000110, 0b10001100, 0b11111101, 0x01},  //Seq 10 - dUEP'  | =   |
  {0b10001001, 0b11000010, 0b10100100, 0b10000000, 0b11001110, 0xFF},  //Seq 11 - H{E8¬  |     |
};

#define BAR_DATA    NUM_DIGITS
#define BAR_ON      LOW
#define BAR_OFF     HIGH

// Setup PinMap for bars at the top of the kit 
const byte pinmap_bars[5] =
{
	6,   // Bar 1
	5,   // Bar 2
	4,   // Bar 3
	3,    // Bar 4
	2,    // Bar 5
};


//  AAAA
// F    B
// F    B
// F    B
//  GGGG
// E    C
// E    C
// E    C
//  DDDD

// Setup PinMap for the individual segements in each Character in the Kit
const byte pinmap_segments[7] =
{
	7,   // Segment A 7
	9,   // Segment B
	11,   // Segment C 11
	14,   // Segment D 14
	12,   // Segment E 12
	8,   // Segment F
	10,   // Segment G 10
};

// Setup PinMap that controls the selection of each Character in the Kit
const byte pinmap_digits[5] =
{
	19,    // Digit 1
	18,   // Digit 2
	17,   // Digit 3
	16,   // Digit 4
	15,   // Digit 5
};


// Walks through each character in the specified word index, delaying
//   only 1/10th of a second between characters as to allow the mind
//   to see the letter even though it's on only 1/5 of the time.
void word_test(int idxWord ) 
{
  // Turn on the correct bar
  digitalWrite( pinmap_bars[char_sequence[idxWord][BAR_DATA]], BAR_ON ) ;

  // Now, let's work on the word we would like to display  
  for( int character = 0 ; character < NUM_DIGITS; character++ )
  {
    int charValue = char_sequence[idxWord][character] ;
    
    // Setup the character on the data lines first 
    for( int segment = 0 ; segment < NUM_SEGMENTS; segment++ )
      digitalWrite( pinmap_segments[segment], ( charValue >> segment ) & 1 ) ;
    
    // Turn the character on
    digitalWrite( pinmap_digits[character],   HIGH);
    
    delay(0);
    
    // Turn the character off
    digitalWrite( pinmap_digits[character],   LOW);
  }
  
  // Turn the correct bar off
  digitalWrite( pinmap_bars[char_sequence[idxWord][BAR_DATA]], BAR_OFF );
}

// Walks through the entire sentence, word by word, repeating each word
//   multiple times so that they mind perceives a roughly two second delay
//   between each new word before the loop starts again.
void sentence_test()
{
  // Move through the words in the sentence one at a time
  for ( int idxWord = 0; idxWord < NUM_STEPS; idxWord++)
  {
    // Repeat each word to meet the desired update frequency (300 = ~2 seconds)
    for ( int idxDelay = 0; idxDelay < UPDATE_FREQUENCY; idxDelay++)
    {
      word_test( idxWord ) ;
    }
  }
}

// the setup routine runs once when you press reset:
void setup() 
{
  // Setup external pins for the BARs across the top  
  for (int i = 0; i < 5; i++)
  {
    pinMode( pinmap_bars[i], OUTPUT);
    digitalWrite(pinmap_bars[i], HIGH);
  }
  
  // Setup external pins for the segemnt data
  for (int i = 0; i < 7; i++)
  {
    pinMode( pinmap_segments[i], OUTPUT);
    digitalWrite(pinmap_segments[i], HIGH);
  }
  
  // Setup external pins for the segment selector
  for (int i = 0; i < 5; i++)
  {
    pinMode( pinmap_digits[i], OUTPUT);
    digitalWrite(pinmap_digits[i], LOW);
  }
}

// the loop routine runs over and over again forever:
void loop()
{
  sentence_test();
}

