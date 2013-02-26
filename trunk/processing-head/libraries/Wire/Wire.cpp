/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 *  @brief Wire library, ported from Arduino. Provides a simplistic
 *  interface to i2c.
 */

#include "Wire.h"
#include "wirish.h"

/* low level conventions:
 * - SDA/SCL idle high (expected high)
 * - always start with i2c_delay rather than end
 */
uint32 i2c_delay = 1;

void i2c_start(Port port) {
    I2C_DELAY;
    digitalWrite(port.sda,LOW);
    I2C_DELAY;
    digitalWrite(port.scl,LOW);
}

void i2c_stop(Port port) {
    I2C_DELAY;
    digitalWrite(port.scl,HIGH);
    I2C_DELAY;
    digitalWrite(port.sda,HIGH);
}

boolean i2c_get_ack(Port port) {
    I2C_DELAY;
    digitalWrite(port.scl,LOW);
    I2C_DELAY;
    digitalWrite(port.sda,HIGH);
    I2C_DELAY;
    digitalWrite(port.scl,HIGH);
    I2C_DELAY;

    if (!digitalRead(port.sda)) {
      I2C_DELAY;
      digitalWrite(port.scl,LOW);
      return true;
    } else {
      I2C_DELAY;
      digitalWrite(port.scl,LOW);
      return false;
    }
}

void i2c_send_ack(Port port) {
    I2C_DELAY;
    digitalWrite(port.sda,LOW);
    I2C_DELAY;
    digitalWrite(port.scl,HIGH);
    I2C_DELAY;
    digitalWrite(port.scl,LOW);
}

void i2c_send_nack(Port port) {
    I2C_DELAY;
    digitalWrite(port.sda,HIGH);
    I2C_DELAY;
    digitalWrite(port.scl,HIGH);
}

uint8 i2c_shift_in(Port port) {
    uint8 data = 0;

    int i;
    for (i=0;i<8;i++) {
        I2C_DELAY;
        digitalWrite(port.scl,HIGH);
        I2C_DELAY;
        data += digitalRead(port.sda) << (7-i);
        I2C_DELAY;
        digitalWrite(port.scl,LOW);
    }

    return data;
}

void i2c_shift_out(Port port, uint8 val) {
    int i;
    for (i=0;i<8;i++) {
        I2C_DELAY;
        digitalWrite(port.sda, !!(val & (1 << (7 - i))));
        I2C_DELAY;
        digitalWrite(port.scl, HIGH);
        I2C_DELAY;
        digitalWrite(port.scl, LOW);
    }
}

TwoWire::TwoWire() {
    i2c_delay = 0;
    rx_buf_idx = 0;
    rx_buf_len = 0;
    tx_addr = 0;
    tx_buf_idx = 0;
    tx_buf_overflow = false;
}

/*
 * Sets pins SDA and SCL to OUPTUT_OPEN_DRAIN, joining I2C bus as
 * master.  If you want them to be some other pins, use begin(uint8,
 * uint8);
 */
void TwoWire::begin() {
    begin(SDA, SCL);
}

/*
 * Joins I2C bus as master on given SDA and SCL pins.
 */
void TwoWire::begin(uint8 sda, uint8 scl) {
    port.sda = sda;
    port.scl = scl;
    pinMode(scl, OUTPUT_OPEN_DRAIN);
    pinMode(sda, OUTPUT_OPEN_DRAIN);
    digitalWrite(scl, HIGH);
    digitalWrite(sda, HIGH);
}

void TwoWire::beginTransmission(uint8 slave_address) {
    tx_addr = slave_address;
    tx_buf_idx = 0;
    tx_buf_overflow = false;
    rx_buf_idx = 0;
    rx_buf_len = 0;
}

void TwoWire::beginTransmission(int slave_address) {
    beginTransmission((uint8)slave_address);
}

uint8 TwoWire::endTransmission(void) {
    if (tx_buf_overflow) return EDATA;

    i2c_start(port);

    i2c_shift_out(port, (tx_addr << 1) | I2C_WRITE);
    if (!i2c_get_ack(port)) return ENACKADDR;

    // shift out the address we're transmitting to
    for (uint8 i = 0; i < tx_buf_idx; i++) {
        uint8 ret = writeOneByte(tx_buf[i]);
        if (ret) return ret;    // SUCCESS is 0
    }

    i2c_stop(port);

    tx_buf_idx = 0;
    tx_buf_overflow = false;
    return SUCCESS;
}

uint8 TwoWire::requestFrom(uint8 address, int num_bytes) {
    if (num_bytes > WIRE_BUFSIZ) num_bytes = WIRE_BUFSIZ;

    rx_buf_idx = 0;
    rx_buf_len = 0;
    while (rx_buf_len < num_bytes) {
        if(!readOneByte(address, rx_buf + rx_buf_len)) rx_buf_len++;
        else break;
    }
    return rx_buf_len;
}

uint8 TwoWire::requestFrom(int address, int numBytes) {
    return TwoWire::requestFrom((uint8)address, (uint8) numBytes);
}

void TwoWire::send(uint8 value) {
    if (tx_buf_idx == WIRE_BUFSIZ) {
        tx_buf_overflow = true;
        return;
    }

    tx_buf[tx_buf_idx++] = value;
}

void TwoWire::send(uint8* buf, int len) {
    for (uint8 i = 0; i < len; i++) send(buf[i]);
}

void TwoWire::send(int value) {
    send((uint8)value);
}

void TwoWire::send(int* buf, int len) {
    send((uint8*)buf, (uint8)len);
}

void TwoWire::send(char* buf) {
    uint8 *ptr = (uint8*)buf;
    while(*ptr) {
        send(*ptr);
        ptr++;
    }
}

uint8 TwoWire::available() {
    return rx_buf_len - rx_buf_idx;
}

uint8 TwoWire::receive() {
    if (rx_buf_idx == rx_buf_len) return 0;
    return rx_buf[rx_buf_idx++];
}

// private methods

uint8 TwoWire::writeOneByte(uint8 byte) {
    i2c_shift_out(port, byte);
    if (!i2c_get_ack(port)) return ENACKTRNS;

    return SUCCESS;
}

uint8 TwoWire::readOneByte(uint8 address, uint8 *byte) {
    i2c_start(port);

    i2c_shift_out(port, (address << 1) | I2C_READ);
    if (!i2c_get_ack(port)) return ENACKADDR;

    *byte = i2c_shift_in(port);

    i2c_send_nack(port);
    i2c_stop(port);

    return SUCCESS;      // no real way of knowing, but be optimistic!
}

// Declare the instance that the users of the library can use
TwoWire Wire;

