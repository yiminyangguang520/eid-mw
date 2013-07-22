/* ****************************************************************************

 * eID Middleware Project.
 * Copyright (C) 2008-2009 FedICT.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License version
 * 3.0 as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this software; if not, see
 * http://www.gnu.org/licenses/.

**************************************************************************** */
#include "UnitTest++/src/UnitTest++.h"
#include "../applayer/CardFile.h"

using namespace eIDMW;

static const unsigned char _root[] = 
{
        0X30,0x82,0x03,0x94,0x30,0x82,0x02,0x7C,0xA0,0x03,0x02,0x01,0x02,0x02,0x10,0x58,
		0x0B,0x05,0x6C,0x53,0x24,0xDB,0xB2,0x50,0x57,0x18,0x5F,0xF9,0xE5,0xA6,0x50,0x30,
		0x0D,0x06,0x09,0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,0x05,0x05,0x00,0x30,0x27,
		0x31,0x0B,0x30,0x09,0x06,0x03,0x55,0x04,0x06,0x13,0x02,0x42,0x45,0x31,0x18,0x30,
		0x16,0x06,0x03,0x55,0x04,0x03,0x13,0x0F,0x42,0x65,0x6C,0x67,0x69,0x75,0x6D,0x20,
		0x52,0x6F,0x6F,0x74,0x20,0x43,0x41,0x30,0x1E,0x17,0x0D,0x30,0x33,0x30,0x31,0x32,
		0x36,0x32,0x33,0x30,0x30,0x30,0x30,0x5A,0x17,0x0D,0x31,0x34,0x30,0x31,0x32,0x36,
		0x32,0x33,0x30,0x30,0x30,0x30,0x5A,0x30,0x27,0x31,0x0B,0x30,0x09,0x06,0x03,0x55,
		0x04,0x06,0x13,0x02,0x42,0x45,0x31,0x18,0x30,0x16,0x06,0x03,0x55,0x04,0x03,0x13,
        0x0F,0x42,0x65,0x6C,0x67,0x69,0x75,0x6D,0x20,0x52,0x6F,0x6F,0x74,0x20,0x43,0x41,
		0x30,0x82,0x01,0x22,0x30,0x0D,0x06,0x09,0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,
		0x01,0x05,0x00,0x03,0x82,0x01,0x0F,0x00,0x30,0x82,0x01,0x0A,0x02,0x82,0x01,0x01,
		0x00,0xC8,0xA1,0x71,0xE9,0x1C,0x46,0x42,0x79,0x78,0x71,0x6F,0x9D,0xAE,0xA9,0xA8,
		0xAB,0x28,0xB7,0x4D,0xC7,0x20,0xEB,0x30,0x91,0x5A,0x75,0xF5,0xE2,0xD2,0xCF,0xC8,
		0x4C,0x14,0x98,0x42,0x58,0xAD,0xC7,0x11,0xC5,0x40,0x40,0x6A,0x5A,0xF9,0x74,0x12,
		0x27,0x87,0xE9,0x9C,0xE5,0x71,0x4E,0x22,0x2C,0xD1,0x12,0x18,0xAA,0x30,0x5E,0xA2,

		0x21,0xB9,0xD9,0xBB,0xFF,0xF6,0x74,0xEB,0x31,0x01,0xE7,0x3B,0x7E,0x58,0x0F,0x91,
		0x16,0x4D,0x76,0x89,0xA8,0x01,0x4F,0xAD,0x22,0x66,0x70,0xFA,0x4B,0x1D,0x95,0xC1,
        0x30,0x58,0xEA,0xBC,0xD9,0x65,0xD8,0x9A,0xB4,0x88,0xEB,0x49,0x46,0x52,0xDF,0xD2,
		0x53,0x15,0x76,0xCB,0x14,0x5D,0x19,0x49,0xB1,0x6F,0x6A,0xD3,0xD3,0xFD,0xBC,0xC2,
		0x2D,0xEC,0x45,0x3F,0x09,0x3F,0x58,0xBE,0xFC,0xD4,0xEF,0x00,0x8C,0x81,0x35,0x72,
		0xBF,0xF7,0x18,0xEA,0x96,0x62,0x7D,0x2B,0x28,0x7F,0x15,0x6C,0x63,0xD2,0xCA,0xCA,
		0x7D,0x05,0xAC,0xC8,0x6D,0x07,0x6D,0x32,0xBE,0x68,0xB8,0x05,0x40,0xAE,0x54,0x98,
		0x56,0x3E,0x66,0xF1,0x30,0xE8,0xEF,0xC4,0xAB,0x93,0x5E,0x07,0xDE,0x32,0x8F,0x12,
		0x74,0xAA,0x5B,0x34,0x23,0x54,0xC0,0xEA,0x6C,0xCE,0xFE,0x36,0x92,0xA8,0x09,0x17,
		0xEA,0xA1,0x2D,0xCF,0x6C,0xE3,0x84,0x1D,0xDE,0x87,0x2E,0x33,0x0B,0x3C,0x74,0xE2,
		0x21,0x50,0x38,0x95,0x2E,0x5C,0xE0,0xE5,0xC6,0x31,0xF9,0xDB,0x40,0xFA,0x6A,0xA1,
		0xA4,0x8A,0x93,0x9B,0xA7,0x21,0x06,0x87,0x1D,0x27,0xD3,0xC4,0xA1,0xC9,0x4C,0xB0,
		0x6F,0x02,0x03,0x01,0x00,0x01,0xA3,0x81,0xBB,0x30,0x81,0xB8,0x30,0x0E,0x06,0x03,
		0x55,0x1D,0x0F,0x01,0x01,0xFF,0x04,0x04,0x03,0x02,0x01,0x06,0x30,0x0F,0x06,0x03,
		0x55,0x1D,0x13,0x01,0x01,0xFF,0x04,0x05,0x30,0x03,0x01,0x01,0xFF,0x30,0x42,0x06,
		0x03,0x55,0x1D,0x20,0x04,0x3B,0x30,0x39,0x30,0x37,0x06,0x05,0x60,0x38,0x01,0x01,

		0x01,0x30,0x2E,0x30,0x2C,0x06,0x08,0x2B,0x06,0x01,0x05,0x05,0x07,0x02,0x01,0x16,
		0x20,0x68,0x74,0x74,0x70,0x3A,0x2F,0x2F,0x72,0x65,0x70,0x6F,0x73,0x69,0x74,0x6F,
		0x72,0x79,0x2E,0x65,0x69,0x64,0x2E,0x62,0x65,0x6C,0x67,0x69,0x75,0x6D,0x2E,0x62,
		0x65,0x30,0x1D,0x06,0x03,0x55,0x1D,0x0E,0x04,0x16,0x04,0x14,0x10,0xF0,0x0C,0x56,
		0x9B,0x61,0xEA,0x57,0x3A,0xB6,0x35,0x97,0x6D,0x9F,0xDD,0xB9,0x14,0x8E,0xDB,0xE6,
		0x30,0x11,0x06,0x09,0x60,0x86,0x48,0x01,0x86,0xF8,0x42,0x01,0x01,0x04,0x04,0x03,
		0x02,0x00,0x07,0x30,0x1F,0x06,0x03,0x55,0x1D,0x23,0x04,0x18,0x30,0x16,0x80,0x14,
		0x10,0xF0,0x0C,0x56,0x9B,0x61,0xEA,0x57,0x3A,0xB6,0x35,0x97,0x6D,0x9F,0xDD,0xB9,
		0x14,0x8E,0xDB,0xE6,0x30,0x0D,0x06,0x09,0x2A,0x86,0x48,0x86,0xF7,0x0D,0x01,0x01,
		0x05,0x05,0x00,0x03,0x82,0x01,0x01,0x00,0xC8,0x6D,0x22,0x51,0x8A,0x61,0xF8,0x0F,
		0x96,0x6E,0xD5,0x20,0xB2,0x81,0xF8,0xC6,0xDC,0xA3,0x16,0x00,0xDA,0xCD,0x6A,0xE7,
		0x6B,0x2A,0xFA,0x59,0x48,0xA7,0x4C,0x49,0x37,0xD7,0x73,0xA1,0x6A,0x01,0x65,0x5E,
		0x32,0xBD,0xE7,0x97,0xD3,0xD0,0x2E,0x3C,0x73,0xD3,0x8C,0x7B,0x83,0xEF,0xD6,0x42,
		0xC1,0x3F,0xA8,0xA9,0x5D,0x0F,0x37,0xBA,0x76,0xD2,0x40,0xBD,0xCC,0x2D,0x3F,0xD3,
		0x44,0x41,0x49,0x9C,0xFD,0x5B,0x29,0xF4,0x02,0x23,0x22,0x5B,0x71,0x1B,0xBF,0x58,
		0xD9,0x28,0x4E,0x2D,0x45,0xF4,0xDA,0xE7,0xB5,0x63,0x45,0x44,0x11,0x0D,0x2A,0x7F,

		0x33,0x7F,0x36,0x49,0xB4,0xCE,0x6E,0xA9,0x02,0x31,0xAE,0x5C,0xFD,0xC8,0x89,0xBF,
		0x42,0x7B,0xD7,0xF1,0x60,0xF2,0xD7,0x87,0xF6,0x57,0x2E,0x7A,0x7E,0x6A,0x13,0x80,
		0x1D,0xDC,0xE3,0xD0,0x63,0x1E,0x3D,0x71,0x31,0xB1,0x60,0xD4,0x9E,0x08,0xCA,0xAB,
		0xF0,0x94,0xC7,0x48,0x75,0x54,0x81,0xF3,0x1B,0xAD,0x77,0x9C,0xE8,0xB2,0x8F,0xDB,
		0x83,0xAC,0x8F,0x34,0x6B,0xE8,0xBF,0xC3,0xD9,0xF5,0x43,0xC3,0x64,0x55,0xEB,0x1A,
		0xBD,0x36,0x86,0x36,0xBA,0x21,0x8C,0x97,0x1A,0x21,0xD4,0xEA,0x2D,0x3B,0xAC,0xBA,
		0xEC,0xA7,0x1D,0xAB,0xBE,0xB9,0x4A,0x9B,0x35,0x2F,0x1C,0x5C,0x1D,0x51,0xA7,0x1F,
		0x54,0xED,0x12,0x97,0xFF,0xF2,0x6E,0x87,0x7D,0x46,0xC9,0x74,0xD6,0xEF,0xEB,0x3D,
		0x7D,0xE6,0x59,0x6E,0x06,0x94,0x04,0xE4,0xA2,0x55,0x87,0x38,0x28,0x6A,0x22,0x5E,
		0xE2,0xBE,0x74,0x12,0xB0,0x04,0x43,0x2A
};

TEST(CardFile_Certificate)
{
	CByteArray root(_root,sizeof(_root));

	APL_CardFile_Certificate rootfile(NULL,"",&root);

	CHECK_EQUAL(1061707343,rootfile.getUniqueId());
}
