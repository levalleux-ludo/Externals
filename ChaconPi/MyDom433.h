#ifndef MyDom433_h
#define MyDom433_h

#include <wiringPi.h>
#include <cstdlib>

class MyDom433
{
	public:
		MyDom433(int tx_pin, int led_pin);

		// bool controller_id[] = {1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
		MyDom433(int tx_pin, int led_pin, const bool* controller_id);

		void deviceOn();
		void deviceOff();

		// bool device_code[] = {0, 0, 0, 0};
		void deviceOn(const bool* device_code);
		void deviceOff(const bool* device_code);

		void groupOn();
		void groupOff();

	private:
		int _tx_pin;
		int _led_pin;
		bool* _controller_id;

		int* _low_pulse_array;

		const static int _pulse_high;
		const static int _pulse_low0;
		const static int _pulse_low1;

		const static int _low_pulse_length;

		const static int _controller_id_offset;
		const static int _controller_id_length;
		const static int _group_flag_offset;
		const static int _on_flag_offset;
		const static int _device_code_offset;
		const static int _device_code_length;

		void setControllerId(const bool* controller_id);
		void setDeviceCode(const bool* device_code);

		void setBit(int bit_index, bool value);

		void xmit(void);
		void xmitLatch1(void);
		void xmitLatch2(void);
};

#endif /* MyDom433_h */
