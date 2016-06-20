/***************************************************

Pet-box

Most useless box with multiple behaviours and
multiple faces using small TFT display, inspired by
Don't touch box by Sally from Florence
https://www.youtube.com/watch?v=tGCW8xftdOA

***************************************************/



#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>
//#include <Servo.h>
#include <Adafruit_SoftServo.h>

#include "LimitedServo.h"
#include "Strategy.h"
#include "SimpleBehaviour.h"
#include "FastBehaviour.h"
#include "AngryBehaviour.h"
#include "SlowFastBehaviour.h"
#include "SuspiciousBehaviour.h"

// TFT display and SD card will share the hardware SPI interface.
// Hardware SPI pins are specific to the Arduino board type and
// cannot be remapped to alternate pins.  For Arduino Uno,
// Duemilanove, etc., pin 11 = MOSI, pin 12 = MISO, pin 13 = SCK.
#define TFT_CS  10  // Chip select line for TFT display
#define TFT_RST  9  // Reset line for TFT (or see below...)
#define TFT_DC   8  // Data/command line for TFT
#define TFT_WIDTH 128
#define TFT_HEIGHT 128
#define SD_CS    4  // Chip select line for SD card

#define LED_PWM  3 // pin for TFT backlight control

#define LID_SERVO  5 // pin for lid opening servo
#define ARM_SERVO  6 // pin for switch arm servo

#define SWITCH     7 // pin for switch input

#define LOOP_DELAY 20 // loop time for servo refresh
#define SERVO_COOL_TIME 50 // number of loops to bring servos home



void bmpDraw(char *filename, uint8_t x, uint8_t y);
void bmpDraw(File &bmpFile, uint8_t x, uint8_t y);
uint16_t read16(File f);
uint32_t read32(File f);

int readBitmapCount();
boolean selectBitmap(int index);


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

Adafruit_SoftServo lid, arm;


File root;
File bitmap;
int bitmapCount = 0;
int currentBitmap = 0;

SimpleBehaviour simple = SimpleBehaviour();
FastBehaviour fast = FastBehaviour();
AngryBehaviour angry = AngryBehaviour();
SlowFastBehaviour sf = SlowFastBehaviour();
SuspiciousBehaviour suspicious = SuspiciousBehaviour();

Strategy *strategy = NULL;
Strategy *strategies[] = { &fast, &simple, &angry, &sf, &suspicious };
int numStrategies = sizeof(strategies) / sizeof(strategies[0]);
int currentStrategy = 0;

int servoCoolTime = SERVO_COOL_TIME;


void setup(void) {
	Serial.begin(115200);

	Serial.println(F("Useless don't touch box"));
	Serial.println();
	Serial.print(F("with "));
	Serial.print(numStrategies);
	Serial.println(F(" behaviours"));
	Serial.println();

	delay(500);

	// Pin setup
	pinMode(LED_PWM, OUTPUT);
	analogWrite(LED_PWM, 0);

	pinMode(SWITCH, INPUT);
	digitalWrite(SWITCH, HIGH);

	// Servo setup
	lid.attach(LID_SERVO);
	arm.attach(ARM_SERVO);
	// cooling will drive servos home
	lid.write(LID_MIN_VALUE);
	arm.write(ARM_MIN_VALUE);

	// TFT setup
	tft.initR(INITR_144GREENTAB);

	// SD setup
	Serial.print(F("Initializing SD card..."));
	if (!SD.begin(SD_CS)) {
		Serial.println(F("failed!"));
		return;
	}
	Serial.println(F("OK!"));

	// Random seeding
	uint32_t seed = 0;
	for (uint8_t i = 0 ; i < 10 ; i++) {
		seed = (seed << 5) + (analogRead(0) * 3);
	}
	Serial.print(F("Random seed="));
	Serial.println(seed);
	randomSeed(seed);

	// Bitmaps setup
	// open SD and read number of bitmap files
	root = SD.open("/");
	bitmapCount = readBitmapCount();
	Serial.print(bitmapCount);
	Serial.println(F(" bitmap files found"));
	if (bitmapCount == 0) {
		Serial.println(F("failed!"));
		return;
	}
	// load first bitmap so that it is ready
	currentBitmap = random(bitmapCount);
	Serial.print(F("Next bitmap: "));
	Serial.println(currentBitmap);
	if (selectBitmap(currentBitmap)) {
		Serial.println(bitmap.name());
		bmpDraw(bitmap, 0, 0);
		bitmap.close();
	}
}



void loop() {
	unsigned long start = millis();

	if (strategy == NULL) {
		if (digitalRead(SWITCH) == 0) {
			Serial.print(F("Starting sequence "));
			Serial.print(currentStrategy);
			Serial.println();
			// Start sequence
			strategy = strategies[currentStrategy];
			// next strategy is random
			currentStrategy = random(numStrategies);

			strategy->setServos(&lid, &arm);
			strategy->setPwmPin(LED_PWM);
			strategy->execute(false);
		} else if (servoCoolTime > 0) {
			servoCoolTime--;
			lid.refresh();
			arm.refresh();
		}
	} else {
		bool abort = false;
		// Run untill finished, then stop
		if (strategy->execute(abort) == true) {
			strategy = NULL;
			Serial.println();
			Serial.print(F("Next sequence: "));
			Serial.println(currentStrategy);
			// load next bitmap
			currentBitmap = random(bitmapCount);
			Serial.print(F("Next bitmap: "));
			Serial.println(currentBitmap);
			if (selectBitmap(currentBitmap)) {
				bmpDraw(bitmap, 0, 0);
				bitmap.close();
			}
		}
	}

	unsigned long end = millis();

	if ((start > end) && (LOOP_DELAY + end < 20)) {
		delay(LOOP_DELAY);
	} else {
		delay(LOOP_DELAY + end - start);
	}
}


bool isBmpFile(File &file) {
	if (!file.isDirectory()) {
		char *name = file.name();
		int8_t len = strlen(name);
		if (strstr(strlwr(name + (len - 4)), ".bmp")) {
			return true;
		}
	}
	return false;
}

int readBitmapCount() {
	int count = 0;
	root.rewindDirectory();
	while (true) {
		File entry = root.openNextFile();
		if (!entry) {
			break;
		}
		if (isBmpFile(entry)){
			count++;
		}
		entry.close();
	}

	return count;
}

boolean selectBitmap(int index) {
	root.rewindDirectory();
	while (true) {
		bitmap = root.openNextFile();
		if (!bitmap) {
			break;
		}
		if (isBmpFile(bitmap)){
			if (index == 0) {
				return true;
			} else {
				index--;
				bitmap.close();
			}
		} else {
			bitmap.close();
		}
	}

	return false;
}

// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.

#define BUFFPIXEL 20

void bmpDraw(char *filename, uint8_t x, uint8_t y) {

	File bmpFile;


	Serial.println();
	Serial.print(F("Loading image '"));
	Serial.print(filename);
	Serial.println('\'');

	// Open requested file on SD card
	if ((bmpFile = SD.open(filename)) == NULL) {
		Serial.print(F("File not found"));
		return;
	}

	bmpDraw(bmpFile, x, y);

	bmpFile.close();
}

void bmpDraw(File &bmpFile, uint8_t x, uint8_t y) {
	int bmpWidth, bmpHeight;   // W+H in pixels
	uint8_t bmpDepth;              // Bit depth (currently must be 24)
	uint32_t bmpImageoffset;        // Start of image data in file
	uint32_t rowSize;               // Not always = bmpWidth; may have padding
	uint8_t sdbuffer[3 * BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
	uint8_t buffidx = sizeof(sdbuffer); // Current position in sdbuffer
	boolean goodBmp = false;       // Set to true on valid header parse
	boolean flip = true;        // BMP is stored bottom-to-top
	int w, h, row, col;
	uint8_t r, g, b;
	uint32_t pos = 0, startTime = millis();

	if ((x >= TFT_WIDTH) || (y >= TFT_HEIGHT))
		return;

	// Parse BMP header
	if (read16(bmpFile) == 0x4D42) { // BMP signature
		Serial.print(F("File size: "));
		Serial.println(read32(bmpFile));
		(void) read32(bmpFile); // Read & ignore creator bytes
		bmpImageoffset = read32(bmpFile); // Start of image data
		Serial.print(F("Image Offset: "));
		Serial.println(bmpImageoffset, DEC);
		// Read DIB header
		Serial.print(F("Header size: "));
		Serial.println(read32(bmpFile));
		bmpWidth = read32(bmpFile);
		bmpHeight = read32(bmpFile);
		if (read16(bmpFile) == 1) { // # planes -- must be '1'
			bmpDepth = read16(bmpFile); // bits per pixel
			Serial.print(F("Bit Depth: "));
			Serial.println(bmpDepth);
			if ((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

				goodBmp = true; // Supported BMP format -- proceed!
				Serial.print(F("Image size: "));
				Serial.print(bmpWidth);
				Serial.print('x');
				Serial.println(bmpHeight);

				// BMP rows are padded (if needed) to 4-byte boundary
				rowSize = (bmpWidth * 3 + 3) & ~3;

				// If bmpHeight is negative, image is in top-down order.
				// This is not canon but has been observed in the wild.
				if (bmpHeight < 0) {
					bmpHeight = -bmpHeight;
					flip = false;
				}

				// Crop area to be loaded
				w = bmpWidth;
				h = bmpHeight;
				if ((x + w - 1) >= TFT_WIDTH)
					w = TFT_WIDTH - x;
				if ((y + h - 1) >= TFT_HEIGHT)
					h = TFT_HEIGHT - y;

				// Set TFT address window to clipped image bounds
				tft.setAddrWindow(x, y, x + w - 1, y + h - 1);

				for (row = 0; row < h; row++) { // For each scanline...

					// Seek to start of scan line.  It might seem labor-
					// intensive to be doing this on every line, but this
					// method covers a lot of gritty details like cropping
					// and scanline padding.  Also, the seek only takes
					// place if the file position actually needs to change
					// (avoids a lot of cluster math in SD library).
					if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
						pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
					else
						// Bitmap is stored top-to-bottom
						pos = bmpImageoffset + row * rowSize;
					if (bmpFile.position() != pos) { // Need seek?
						bmpFile.seek(pos);
						buffidx = sizeof(sdbuffer); // Force buffer reload
					}

					for (col = 0; col < w; col++) { // For each pixel...
						// Time to read more pixel data?
						if (buffidx >= sizeof(sdbuffer)) { // Indeed
							bmpFile.read(sdbuffer, sizeof(sdbuffer));
							buffidx = 0; // Set index to beginning
						}

						// Convert pixel from BMP to TFT format, push to display
						b = sdbuffer[buffidx++];
						g = sdbuffer[buffidx++];
						r = sdbuffer[buffidx++];
						tft.pushColor(tft.Color565(r, g, b));
					} // end pixel
				} // end scanline
				Serial.print(F("Loaded in "));
				Serial.print(millis() - startTime);
				Serial.println(F(" ms"));
			} // end goodBmp
		}
	}

	if (!goodBmp)
		Serial.println(F("BMP format not recognized."));
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File f) {
	uint16_t result;
	((uint8_t *) &result)[0] = f.read(); // LSB
	((uint8_t *) &result)[1] = f.read(); // MSB
	return result;
}

uint32_t read32(File f) {
	uint32_t result;
	((uint8_t *) &result)[0] = f.read(); // LSB
	((uint8_t *) &result)[1] = f.read();
	((uint8_t *) &result)[2] = f.read();
	((uint8_t *) &result)[3] = f.read(); // MSB
	return result;
}
