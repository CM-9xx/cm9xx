/*
 * dxl_constants.h
 *
 *  Created on: 2012. 12. 17.
 *      Author: in2storm(sm6787@robotis.com)
 */

#ifndef DXL_CONSTANTS_H_
#define DXL_CONSTANTS_H_


#define BROADCAST_ID		(254)
/*
 * Instruction command
 * */
#define INST_PING           0x01
#define INST_READ           0x02
#define INST_WRITE          0x03
#define INST_REG_WRITE      0x04
#define INST_ACTION         0x05
#define INST_RESET          0x06
#define INST_DIGITAL_RESET  0x07    //reset�� �����ѵ� id�� �����ϰ� ���������� reset����
#define INST_SYSTEM_READ    0x0C    //� �ּ���ġ�� 1 byte �� ������ ������ �ְ�. CT ������ �ʰ��ص� ����.
#define INST_SYSTEM_WRITE   0x0D    //� �ּ���ġ�� 1 byte �� ������ ���� �ְ�. CT ������ �ʰ��ص� ��.
#define INST_SYNC_WRITE     0x83
#define INST_SYNC_REG_WRITE 0x84    //action�� �����߸� ����. ���� ID dxl �� ��� ����.

/*
 * Index for packet instruction
 * */
#define ID					(2)
#define LENGTH				(3)
#define INSTRUCTION			(4)
#define ERRBIT				(4)
#define PARAMETER			(5)
#define DEFAULT_BAUDNUMBER	(1)

#define MAXNUM_RXPARAM		(60)
#define MAXNUM_TXPARAM		(150)


/*
 * defines for error message
 * */
#define ERRBIT_VOLTAGE		(1)
#define ERRBIT_ANGLE		(2)
#define ERRBIT_OVERHEAT		(4)
#define ERRBIT_RANGE		(8)
#define ERRBIT_CHECKSUM		(16)
#define ERRBIT_OVERLOAD		(32)
#define ERRBIT_INSTRUCTION	(64)

/*
 * defines message of communication
 * */
#define	COMM_TXSUCCESS		(0)
#define COMM_RXSUCCESS		(1)
#define COMM_TXFAIL			(2)
#define COMM_RXFAIL			(3)
#define COMM_TXERROR		(4)
#define COMM_RXWAITING		(5)
#define COMM_RXTIMEOUT		(6)
#define COMM_RXCORRUPT		(7)



#endif /* DXL_CONSTANTS_H_ */
