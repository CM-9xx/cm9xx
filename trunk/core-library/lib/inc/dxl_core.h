// Dynamixel SDK platform independent header
#ifndef _DYNAMIXEL_HEADER
#define _DYNAMIXEL_HEADER


#ifdef __cplusplus
extern "C" {
#endif

#include "dxl_hal.h"
#include "dxl_constants.h"


///////////// device control methods ////////////////////////
int dxl_initialize( int devIndex, int baudnum );
void dxl_terminate(void);


// functions for making a packet
void dxl_set_txpacket_id( int id );
void dxl_set_txpacket_instruction( int instruction );
void dxl_set_txpacket_parameter( int index, int value );
void dxl_set_txpacket_length( int length );

int dxl_get_rxpacket_parameter( int index );
int dxl_get_rxpacket_length(void);
int dxl_get_rxpacket_error( int errbit );

// utility for value
int dxl_makeword( int lowbyte, int highbyte );
int dxl_get_lowbyte( int word );
int dxl_get_highbyte( int word );

////////// packet communication methods ///////////////////////
void dxl_tx_packet(void);
void dxl_rx_packet(void);
void dxl_txrx_packet(void);

void dxl_SetPosition(int ServoID, int Position, int Speed);
int dxl_get_result(void);

//////////// high communication methods ///////////////////////
void dxl_ping( int id );
int dxl_read_byte( int id, int address );
void dxl_write_byte( int id, int address, int value );
int dxl_read_word( int id, int address );
void dxl_write_word( int id, int address, int value );

// 2012-03-14 jason
void dxl_reset( int id );


#ifdef __cplusplus
}
#endif

#endif
