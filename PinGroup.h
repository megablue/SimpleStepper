/**
	@file PinGroup.h
	@author Alec Fenichel
	@brief Simultaneous operations on Arduino I/O pins
 */


#include "Pin.h"

#pragma once


/**
	Class for simultaneous operations on Arduino I/O pins

	@author Alec Fenichel
 */
class PinGroup {
	public:
		// ################################# Constructors #################################
		template<size_t N>
		PinGroup(Pin (&pins)[N]) {
			_offset = pins[0].getOffset();
			_PIN = pins[0].getPIN();
			_PORT = pins[0].getPORT();
			_DDR = pins[0].getDDR();
			_numbers[0] = pins[0].getNumber();
			_valid = true;

			for (int i = 1; i < N; i++) {
				if (_DDR != pins[i].getDDR()) {
					_valid = false;
				}
				_offset |= pins[i].getOffset();
				_numbers[i] = pins[i].getNumber();
			}
			_ioffset = ~_offset;
		}

		// ################################# Operators #################################

		/**
			Compare the value of the pin

			@param value the state of the pin (HIGH, LOW)

			@return true if the value of all of the pins are equal to the value passed in, false otherwise
		 */
		bool operator ==(uint8_t value) {
			uint8_t status = *_PIN;
			if ((status & _offset) == _offset) {
				return (value == HIGH);
			} else if ((status | _ioffset) == _ioffset) {
				return (value == LOW);
			} else {
				return false;
			}
		}

		/**
			Compare the value of the pin

			@param value the state of the pin (HIGH, LOW)

			@return true if the value of all of the pins are not equal to the value passed in, false otherwise
		 */
		bool operator !=(uint8_t value) {
			uint8_t status = *_PIN;
			if ((status & _offset) == _offset) {
				return (value == LOW);
			} else if ((status | _ioffset) == _ioffset) {
				return (value == HIGH);
			} else {
				return false;
			}
		}

		/**
			Set the pin state

			@param state the state of the pin (HIGH, LOW)
		 */
		PinGroup& operator =(uint8_t state) {
			uint8_t oldSREG = SREG;
			cli();
			if (state == LOW) {
				PORT_LOW;
			} else {
				PORT_HIGH;
			}
			SREG = oldSREG;

			return *this;
		}

		// ################################# Getters #################################

		/**
			Get the pin numbers

			@return array of pin numbers
		 */
		uint8_t* getNumbers() {
			return _numbers;
		}

		/**
			Get the pin offset

			@return pin offset
		 */
		uint8_t getOffset() {
			return _offset;
		}

		/**
			Get the inverse pin offset

			@return inverse pin offset
		 */
		uint8_t getInverseOffset() {
			return _ioffset;
		}

		/**
			Get a pointer to the PIN register

			@return pointer to the PIN register
		 */
		volatile uint8_t* getPIN() {
			return _PIN;
		}

		/**
			Get a pointer to the PORT register

			@return pointer to the PORT register
		 */
		volatile uint8_t* getPORT() {
			return _PORT;
		}

		/**
			Get a pointer to the DDR register

			@return pointer to the DDR register
		 */
		volatile uint8_t* getDDR() {
			return _DDR;
		}

		/**
			Get the mode of the pin from the DDR register

			@return mode of the pin (OUTPUT, INPUT, -1)
		 */
		uint8_t getMode() {
			uint8_t status = *_DDR;
			if ((status & _offset) == _offset) {
				return OUTPUT;
			} else if ((status | _ioffset) == _ioffset) {
				return INPUT;
			} else {
				return -1;
			}
		}

		/**
			Get the state of the pin from the PORT register

			@return state of the pin (HIGH, LOW, -1)
		 */
		uint8_t getState() {
			uint8_t status = *_PORT;
			if ((status & _offset) == _offset) {
				return HIGH;
			} else if ((status | _ioffset) == _ioffset) {
				return LOW;
			} else {
				return -1;
			}
		}

		/**
			Get the value of the pin from the PIN register

			@return value of the pin (HIGH, LOW, -1)
		 */
		uint8_t getValue() {
			uint8_t status = *_PIN;
			if ((status & _offset) == _offset) {
				return HIGH;
			} else if ((status | _ioffset) == _ioffset) {
				return LOW;
			} else {
				return -1;
			}
		}

		/**
			Check the group to ensure all pins use the same registers

			@return true if the pins in the group all use the same registers, false otherwise
		 */
		bool isValid() {
			return _valid;
		}


		// ################################# Setters #################################

		// #################### Generic ####################

		/**
			Set the pin mode and pin state

			@param mode the mode of the pin (OUTPUT, INPUT)
			@param state the state of the pin (HIGH, LOW)
		 */
		void set(uint8_t mode, uint8_t state) {
			uint8_t oldSREG = SREG;
			cli();
			if (mode == INPUT) {
				DDR_LOW;
			} else {
				DDR_HIGH;
			}
			if (state == LOW) {
				PORT_LOW;
			} else {
				PORT_HIGH;
			}
			SREG = oldSREG;
		}

		/**
			Set the pin mode

			@param mode the mode of the pin (OUTPUT, INPUT)
		 */
		void setMode(uint8_t mode) {
			uint8_t oldSREG = SREG;
			cli();
			if (mode == INPUT) {
				DDR_LOW;
			} else {
				DDR_HIGH;
			}
			SREG = oldSREG;
		}

		/**
			Set the pin state

			@param state the state of the pin (HIGH, LOW)
		 */
		void setState(uint8_t state) {
			uint8_t oldSREG = SREG;
			cli();
			if (state == LOW) {
				PORT_LOW;
			} else {
				PORT_HIGH;
			}
			SREG = oldSREG;
		}

		// #################### Input ####################

		/**
			Set the pin mode to input
		 */
		void setInput() {
			uint8_t oldSREG = SREG;
			cli();
			DDR_LOW;
			SREG = oldSREG;
		}

		/**
			Set the pin pullup resistor to on
		 */
		void setPullupOn() {
			uint8_t oldSREG = SREG;
			cli();
			PORT_HIGH;
			SREG = oldSREG;
		}

		/**
			Set the pin pullup resistor to off
		 */
		void setPullupOff() {
			uint8_t oldSREG = SREG;
			cli();
			PORT_LOW;
			SREG = oldSREG;
		}

		/**
			Set the pin mode to input and the pin pullup resistor to on
		 */
		void setInputPullupOn() {
			uint8_t oldSREG = SREG;
			cli();
			DDR_LOW;
			PORT_HIGH;
			SREG = oldSREG;
		}

		/**
			Set the pin mode to input and the pin pullup resistor to off
		 */
		void setInputPullupOff() {
			uint8_t oldSREG = SREG;
			cli();
			DDR_LOW;
			PORT_LOW;
			SREG = oldSREG;
		}

		// #################### Output ####################

		/**
			Set the pin mode to output
		 */
		void setOutput() {
			uint8_t oldSREG = SREG;
			cli();
			DDR_HIGH;
			SREG = oldSREG;
		}

		/**
			Set the pin output to HIGH
		 */
		void setHigh() {
			uint8_t oldSREG = SREG;
			cli();
			PORT_HIGH;
			SREG = oldSREG;
		}

		/**
			Set the pin output to LOW
		 */
		void setLow() {
			uint8_t oldSREG = SREG;
			cli();
			PORT_LOW;
			SREG = oldSREG;
		}

		/**
			Set the pin mode to output and the pin output to HIGH
		 */
		void setOutputHigh() {
			uint8_t oldSREG = SREG;
			cli();
			DDR_HIGH;
			PORT_HIGH;
			SREG = oldSREG;
		}

		/**
			Set the pin mode to output and the pin output to LOW
		 */
		void setOutputLow() {
			uint8_t oldSREG = SREG;
			cli();
			DDR_HIGH;
			PORT_LOW;
			SREG = oldSREG;
		}


		// ################################# Utilities #################################

		// #################### Toggle ####################

		/**
			Toggle the pin mode (OUTPUT -> INPUT, INPUT -> OUTPUT)
		 */
		void toggleMode() {
			uint8_t oldSREG = SREG;
			cli();
			DDR_TOGGLE;
			SREG = oldSREG;
		}

		/**
			Toggle the pin state (HIGH -> LOW, LOW -> HIGH)
		 */
		void toggleState() {
			uint8_t oldSREG = SREG;
			cli();
			PORT_TOGGLE;
			SREG = oldSREG;
		}

	private:
		// Variables
		uint8_t _numbers[8];
		uint8_t _offset;
		uint8_t _ioffset;
		bool _valid;
		volatile uint8_t* _PIN;
		volatile uint8_t* _PORT;
		volatile uint8_t* _DDR;
};
