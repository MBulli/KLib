/*
 * ByteArrayInOutStream.h
 *
 *  Created on: Dec 19, 2013
 *      Author: kazu
 */

#include "InputStream.h"
#include "OutputStream.h"
#include "Buffer.h"


namespace K {

/**
 * provides both, an input and an output stream
 * to write data to and read from.
 *
 * e.g. for testing purpose
 */
class ByteArrayInOutStream : virtual public InputStream, virtual public OutputStream {

public:

	/** ctor */
	ByteArrayInOutStream() {
		;
	}

	/** dtor */
	~ByteArrayInOutStream() {

	}


	int read() override {
		if (buffer.empty()) {return -1;}
		int ret = buffer.get();
		return ret;
	}

	int read(uint8_t* data, unsigned int len) override {
		if (buffer.empty()) {return -1;}
		int toRead = (buffer.getNumUsed() >= len) ? (len) : (buffer.getNumUsed());
		memcpy(data, buffer.getData(), toRead);
		buffer.remove(toRead);
		return toRead;
	}


	void write(uint8_t data) override {
		buffer.add(data);
	}

	void write(uint8_t* data, unsigned int len) override {
		buffer.add(data, len);
	}


	void close() override {;}

	void flush() override {;}

private:

	/** the internal buffer */
	Buffer<uint8_t> buffer;

};

}
