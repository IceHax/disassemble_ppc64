// Copyright 2012       Grazioli Giovanni <wargio@libero.it>
// Licensed under the terms of the GNU GPL, version 2
// http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt

#ifndef _ENDIANESS_TOOLS_H__
#define _ENDIANESS_TOOLS_H__

static inline uint8_t le8(uint8_t *p)
{
	return *p;
}

static inline uint16_t le16(uint8_t *p)
{
	uint16_t a;

	a  = p[0] << 8;
	a |= p[1];

	return a;
}

static inline uint32_t le32(uint8_t *p)
{
	uint32_t a;

	a  = p[0] << 24;
	a |= p[1] << 16;
	a |= p[2] <<  8;
	a |= p[3] <<  0;

	return a;
}

static inline uint64_t le64(uint8_t *p)
{
	uint32_t a, b;

	a = le32(p + 4);
	b = le32(p);

	return ((uint64_t)b<<32) | a;
}

#endif
