#include "MyDom433.h"

const int MyDom433::_pulse_high = 275;
const int MyDom433::_pulse_low0 = 275;
const int MyDom433::_pulse_low1 = 1225;

const int MyDom433::_low_pulse_length = 64;

/* Structure du message :
	* The actual message is 32 bits of data:
	* bits 0-25: the group code - a 26bit number assigned to controllers.
	* bit 26: group flag
	* bit 27: on/off flag
	* bits 28-31: the device code - a 4bit number.
*/

const int MyDom433::_controller_id_offset = 0;
const int MyDom433::_controller_id_length = 26;
const int MyDom433::_group_flag_offset = 26;
const int MyDom433::_on_flag_offset = 27;
const int MyDom433::_device_code_offset = 28;
const int MyDom433::_device_code_length = 4;

MyDom433::MyDom433(int tx_pin, int led_pin)
{
	_tx_pin = tx_pin;
	_led_pin = led_pin;

	pinMode(_tx_pin, OUTPUT);
	pinMode(_led_pin, OUTPUT);

	_low_pulse_array = (int*)calloc(_low_pulse_length, sizeof(int));

	bool default_controller_id[] = {1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
	setControllerId(default_controller_id);
}

MyDom433::MyDom433(int tx_pin, int led_pin, const bool* controller_id)
{
	_tx_pin = tx_pin;
	_led_pin = led_pin;

	//  _controller_id = controller_id;
	_low_pulse_array = (int*)calloc(_low_pulse_length, sizeof(int));

	setControllerId(controller_id);
}

void MyDom433::deviceOn(void)
{
	bool default_device[] = {0, 0, 0, 0};
	setDeviceCode(default_device);
	setBit(_group_flag_offset, 0);
	setBit(_on_flag_offset, 1);
	xmit();
}

void MyDom433::deviceOn(const bool* device_code)
{
	setDeviceCode(device_code);
	setBit(_group_flag_offset, 0);
	setBit(_on_flag_offset, 1);
	xmit();
}

void MyDom433::deviceOff(void)
{
	bool default_device[] = {0, 0, 0, 0};
	setDeviceCode(default_device);
	setBit(_group_flag_offset, 0);
	setBit(_on_flag_offset, 0);
	xmit();
}

void MyDom433::deviceOff(const bool* device_code)
{
	setDeviceCode(device_code);
	setBit(_group_flag_offset, 0);
	setBit(_on_flag_offset, 0);
	xmit();
}

void MyDom433::groupOn(void)
{
	bool default_device[] = {0, 0, 0, 0};
	setDeviceCode(default_device);
	setBit(_group_flag_offset, 1);
	setBit(_on_flag_offset, 1);
	xmit();
}

void MyDom433::groupOff(void)
{
	bool default_device[] = {0, 0, 0, 0};
	setDeviceCode(default_device);
	setBit(_group_flag_offset, 1);
	setBit(_on_flag_offset, 0);
	xmit();
}

// Private methods
void MyDom433::setControllerId(const bool* controller_id)
{
	int bit_count;

	for (bit_count = 0; bit_count < _controller_id_length; bit_count++)
	{
		setBit(_controller_id_offset + bit_count, controller_id[bit_count]);
	}
}

void MyDom433::setDeviceCode(const bool* device_code)
{
	int bit_count;

	for (bit_count = 0; bit_count < _device_code_length; bit_count++)
	{
		setBit(_device_code_offset + bit_count, device_code[bit_count]);
	}
}

void MyDom433::setBit(int bit_index, bool value)
{
	// Each actual bit of data is encoded as two bits on the wire...
	if(!value)
	{
		// Data 0 = Wire 01
		_low_pulse_array[(bit_index*2)] = _pulse_low0;
		_low_pulse_array[(bit_index*2) + 1] = _pulse_low1;
	}
	else
	{
		// Data 1 = Wire 10
		_low_pulse_array[(bit_index*2)] = _pulse_low1;
		_low_pulse_array[(bit_index*2) + 1] = _pulse_low0;
	}
}

void MyDom433::xmit(void)
{
	int pulse_count;
	int xmit_count;

	for(xmit_count = 0; xmit_count < 3; xmit_count++)
	{
		digitalWrite(_led_pin, HIGH);
		xmitLatch1();
		xmitLatch2();

		/*
		* transmit the actual message
		* every wire bit starts with the same short high pulse, followed
		* by a short or long low pulse from an array of low pulse lengths
		*/
		for(pulse_count = 0; pulse_count < _low_pulse_length; pulse_count++)
		{
			digitalWrite(_tx_pin, HIGH);
			delayMicroseconds(_pulse_high);
			digitalWrite(_tx_pin, LOW);
			delayMicroseconds(_low_pulse_array[pulse_count]);
		}

		xmitLatch2();
		digitalWrite(_led_pin, LOW);

		delayMicroseconds(10000);
	}
}

void MyDom433::xmitLatch1(void)
{
	// bit of radio shouting before we start
	digitalWrite(_tx_pin, HIGH);
	delayMicroseconds(275);
	// low for 9900 for latch 1
	digitalWrite(_tx_pin, LOW);
	delayMicroseconds(9900);
}

void MyDom433::xmitLatch2(void)
{
	// high for a moment 275
	digitalWrite(_tx_pin, HIGH);
	delayMicroseconds(275);
	// low for 2675 for latch 2
	digitalWrite(_tx_pin, LOW);
	delayMicroseconds(2675);
}

