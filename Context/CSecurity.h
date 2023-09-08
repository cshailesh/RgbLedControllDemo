/*
 * CSecurity.h
 *
 *  Created on: 21 Jan 2019
 *      Author: Shailesh
 */

#ifndef CSECURITY_H_
#define CSECURITY_H_

#define MMIO16(addr)  (*(volatile uint16_t *)(addr))
#define MMIO32(addr)  (*(volatile uint32_t *)(addr))
#define U_ID          0x1ffff7e8
#define UID_Base 	  0x1FFFF7E8

struct UID_t
{
	uint16_t off0;
	uint16_t off2;
	uint32_t off4;
	uint32_t off8;
};

void UID_Read(struct UID_t *id)
{
	id->off0 = MMIO16(U_ID + 0x0);
	id->off2 = MMIO16(U_ID + 0x2);
	id->off4 = MMIO32(U_ID + 0x4);
	id->off8 = MMIO32(U_ID + 0x8);
}

uint8_t UID_CMP(struct UID_t *id1, struct UID_t *id2)
{
	return id1->off0 == id2->off0 && id1->off2 == id2->off2
			&& id1->off4 == id2->off4 && id1->off8 == id2->off8;
}


uint8_t ContextPin()
{
	struct UID_t codedID =
	{ 0x0, 0x1, 0x2, 0x3 };

	struct UID_t chipID;
	uint8_t same_id;

	UID_Read(&chipID);
	same_id = UID_CMP(&codedID, &chipID);
	return 1;
	//return same_id;

}

void UIDTest()
{
	struct UID_t codedID =
	{ 0x0, 0x1, 0x2, 0x3 };

	struct UID_t chipID;
	uint8_t same_id;

	UID_Read(&chipID);
	same_id = UID_CMP(&codedID, &chipID);
}


#endif /* CSECURITY_H_ */
