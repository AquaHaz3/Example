#include "CrackMe.h"
#include <iostream>
#include "CrackMeHelper.h"
#include "FormatUtil.h"

#pragma pack(1)
char __debug_addr = 0;
const char* UserName = "AAAABBBB\0";
const char* Serial__ = "12345\0";
int unknown_value_0 = 0x1;
int unknown_value = 0x10;
int unknown_values[]{ 0x03,0x03, 0x0c };

int ebx = 0;
int esi = 0;
int edi = 0;
int eax = 0;
int jmp = 0;

__int32 stack_dump[] =
{
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,
	0, // 22 (ebp-)
	0, // 21 (ebp-)
	0, // 20 (ebp-)
	5, // 19 (ebp-)
	1, // 18 (ebp-0x48)
	0, // 17 (ebp-0x44)
	0, // 16 (ebp-0x40)
	0, // 15 (ebp-0x3c)
	5, // 14 (ebp-0x38)
	0, // 13 (ebp-0x34)
	0, // 12 (ebp-0x30)
	0, // 11 (ebp-0x2c)
	0, // 10 (ebp-0x28)
	0, // 9  (ebp-0x24)
	0, // 8  (ebp-0x20)
	0, // 7  (ebp-0x1c)
	0, // 6  (ebp-0x18)
	0, // 5  (ebp-0x14)
	0, // 4  (ebp-0x10)
	0, // 3  (ebp-0xc)
	0, // 2  (ebp-0x8)
	0, // 1  (ebp-0x4)
	0xcc706265, // 0  (ebp)
	0xcccccccc,            // -1 (ebp+0x4)
	(int)((int*)commands), // -2 (ebp+0x8)  // arg1 ?
	(int)&UserName,        // -3 (ebp+0xc)  // ~arg2 
	(int)&Serial__,        // -4 (ebp+0x10) // ~arg3 
	(int)&unknown_value,   //               // ~arg4
	0,0,0,0
};

uint8_t* ebp = (uint8_t*)((int*)(&stack_dump) + 64 - 1 - 9);
void put_ebp(int offset, int value) { ((int*)((int)ebp + offset))[0] = value; }
#define get_ebp(index) ((int*)&ebp[index])[0]

#define _local(n) ((int*)&ebp[n * 4 - 0x48])[0] // local: ebp - 0x48

/* set stack value (ecx - stack pos, edx - value) */
void cmd_00(int ecx, int edx, int offset) {
	_local(ecx) = edx; // dst -18 + ecx
}

/* move local value (edx - from, ecx - to) */
void cmd_01(int ecx, int edx, int offset) {
	_local(ecx) = _local(edx);
}

/* copy args to stack local area {ecx - dst stack pos, edx - # of src arg} */
void cmd_02(int ecx, int edx, int offset) 
{
	int* dst_ptr = &_local(ecx); // dst args
	put_ebp(-0x4, (int)dst_ptr);

	int* src = (int*)&(ebp[0x8]); // src args
	*dst_ptr = src[edx + 1];
}

/* jump if condition (ecx - offset; edx - bitmask) */
void cmd_03(int ecx, int edx, int offset) 
{
	if ((edi & edx) != 0) {
		if (ecx < offset) {
			put_ebp(-0x4, (int) ((int*)commands));
		}
		if (ecx == offset) {
			return;
		}
		jmp = (ecx >> 8) - 1;
	}
};

void cmd_04(int ecx, int edx, int offset) {};

/* get next char from str {ecx - pos of local str, edx - local pos of dst} */
void cmd_05(int ecx, int edx, int offset)
{
	eax = ((int*)_local(ecx))[0];
	eax = ((char*)eax)[0]; // first byte of *local[ecx]

	_local(edx) = eax;
	((int*)_local(ecx))[0] = ((int*)_local(ecx))[0] + 1;
}

/* get ptr from local(ecx) and put to ptr EDX(dl) then inc ptr */
void cmd_06(int ecx, int edx, int offset) 
{
	int* ptr = (int*) _local(ecx);
	edx = _local(edx); // char
	ptr[0] = edx;
	ptr = (int*)((int)ptr + 1);
	_local(ecx) = (int) ptr;
};

void cmd_07(int ecx, int edx, int offset) {
	ecx = _local(ecx); // ecx = local[ecx]
	edi = 0;
	if (ecx != edx) edi = 2;
	else edi = 1;
	if (ecx >= edx) edi |= 4;
	if (ecx <= edx) edi |= 8;
};

/* compare values  {ecx - OP1, edx - OP2}
edi = 0101 : OP1 >= OP2
edi = 1001 : OP1 <= OP2
edi = 0110 : OP1 >  OP2
edi = 1010 : OP1 <  OP2; => edi = 1<2 : 1>2 : 1!=2 : 1==2
*/
void cmd_08(int ecx, int edx, int offset)
{
	edx = _local(edx); // edx = local[edx]
	ecx = _local(ecx); // ecx = local[ecx]
	edi = 0;
	if (ecx != edx) edi = 2;
	else edi = 1;
	if (ecx >= edx) edi |= 4;
	if (ecx <= edx) edi |= 8;
};

void cmd_09(int ecx, int edx, int offset) {
	edx = _local(edx);
	_local(ecx) = _local(ecx) + edx;
};

void cmd_0a(int ecx, int edx, int offset) {
	_local(ecx) ^= _local(edx);
};

void cmd_0b(int ecx, int edx, int offset) 
{
	int x = _local(ecx) & 1;
	x = -x;
	edi = x + 2;
	_local(ecx) = _local(ecx) >> 1;
};

void cmd_0c(int ecx, int edx, int offset) {
	_local(ecx) = _local(ecx) - edx;
};

/* local[ecx] |= edx */
void cmd_0d(int ecx, int edx, int offset) {
	((int*)&ebp[ecx * 4 - 0x48])[0] |= edx;
};

void cmd_0e(int ecx, int edx, int offset) {
	return;
};

unsigned int crc32b(unsigned char* message) {
	int i, j;
	unsigned int byte, crc;
	unsigned int mask;

	i = 0;
	crc = 0x9c3b248e;
	while (message[i] != 0) {
		byte = message[i];            // Get next byte.
		crc = crc ^ byte;
		for (j = 7; j >= 0; j--) {    // Do eight times.
			mask = crc & 1;
			crc = (crc >> 1);
			if ((mask) == 1) {
				crc ^= 0xc1a7f39a;
			}
			//printf("%x\n", crc);
		}
		i = i + 1;
	}
	return crc;
}

void CrackMe::Start()
{
	for (int i = 0; i < 3000; i++) {
		auto t = "User_"+std::to_string(i);
		int hash = crc32b((unsigned char*)t.c_str());
		printf("%d: %x\n", i, hash);
	}
	

	if (1) return;

	//PrintStackHash(true);
	//     cmd, ecx   edx, addr
	AddCMD(0x2, 0x0000, 0, 0x100); // copy arg#1 (UserName) -> local[0]
	AddCMD(0x2, 0x0001, 1, 0x200); // copy arg#2 (Serial) -> local[1]
	AddCMD(0x2, 0x0002, 2, 0x300); // copy arg#3 (SOMEPTR[0] = 0x10) -> local[2]
	AddCMD(0x0, 0x0003, 0, 0x400); // set local[3] = 0
	AddCMD(0x1, 0x0004, 1, 0x500); // move local[1](Serial) -> local[4] (copy: c_Serial)
	AddCMD(0x1, 0x0005, 2, 0x600); // move local[2](SOMEPTR) -> local[5]

	AddCMD(0x5, 0x0004, 6, 0x700); // local[6] = c_Serial[i]
	AddCMD(0x8, 0x0006, 3, 0x800); // 
	AddCMD(0x3, 0xd00,  1, 0x900); // while (Serial[i] != 0) {
	AddCMD(0xd, 0x6, 0x20, 0xa00); //    Serial[i] = Serial[i].lower() // lowercase
	AddCMD(0x6, 0x0005, 6, 0xb00); //    *SOMEPTR = Serial[i]; SOMEPTR++;
	AddCMD(0x3, 0x700,0xf, 0xc00); //    i++;
	//								  }
	AddCMD(0x6, 0x0005, 3, 0xd00); // *SOMEPTR = 0; SOMEPTR++;
	AddCMD(0x1, 0x04, 0x3, 0xe00); // int local_4 = 0;
	AddCMD(0x1, 0x5,  0x2, 0xf00); // move local[2](SOMEPTR) -> local[5]; "passw"
	AddCMD(0x5, 0x5, 0x6, 0x1000); // local[6] = "passw"[i]
	AddCMD(0x8, 0x6, 0x3, 0x1100); // 
	AddCMD(0x3, 0x2400, 1, 0x1200); // while(Serial[i] != 0) {
	AddCMD(0x7, 0x6, 0x30, 0x1300);  //  
	AddCMD(0x3, 0x3700, 8, 0x1400);  //   
	AddCMD(0x7, 0x6, 0x39, 0x1500);  //  if(Serial[i] >= '0' && Serial[i] <= '9')
	AddCMD(0x3, 0x1e00, 4, 0x1600);  //  {
	AddCMD(0xc, 0x6, 0x30, 0x1700);  //      int local_6 = Serial[i] - '0';
	AddCMD(0x9, 0x4, 0x4, 0x1800);   //      local_4 = local_4 << 4;
	AddCMD(0x9, 0x4, 0x4, 0x1900);   //      ...
	AddCMD(0x9, 0x4, 0x4, 0x1a00);   //      ...
	AddCMD(0x9, 0x4, 0x4, 0x1b00);   //      ...
	AddCMD(0x9, 0x4, 0x6, 0x1c00);   //      local_6 += local_4; i++;
	AddCMD(0x3, 0x1000, 0xf, 0x1d00);//  }
	AddCMD(0x7, 0x6, 0x61, 0x1e00);  //}
	AddCMD(0x3, 0x3700, 0x8, 0x1f00);//
	AddCMD(0x7, 0x6, 0x66, 0x2000);  //  ???
	AddCMD(0x3, 0x3700, 0x4, 0x2100);//  
	AddCMD(0xc, 0x6, 0x57, 0x2200);  //  
	AddCMD(0x3, 0x1800, 0xf, 0x2300);//  
								//	   }
	AddCMD(0x0, 5, 0x9c3b248e, 0x2400); // int local_5 = 0x9c3b248e
	AddCMD(0x0, 6, 0xc1a7f39a, 0x2500); // int local_6 = 0xc1a7f39a
	AddCMD(0x1, 0x7, 0x0, 0x2600);      // int local_7 = &<UserName>
	AddCMD(0x5, 0x7, 0x8, 0x2700);      // 
	AddCMD(0x8, 0x8, 0x3, 0x2800);      // while (UserName[i] != 0)  <-------- CRC32 or somthing ???
	AddCMD(0x3, 0x3300, 0x1, 0x2900);   // {
	AddCMD(0xa, 0x5, 0x8, 0x2a00);      //     local_5 ^= UserName[i];
	AddCMD(0x0, 0x9, 0x8, 0x2b00);      //     for (int j = 8; j > 0; j--) {
	AddCMD(0xb, 0x5, 0x1, 0x2c00);      //         local_5 = local_5 >> 1;
	AddCMD(0x3, 0x2f00, 0x2, 0x2d00);   //         if (local_5 & 1 == 1) {
	AddCMD(0xa, 0x5, 0x6, 0x2e00);      //	           local_5 ^= local_6; // (^= 0xc1a7f39a)
	AddCMD(0xc, 0x9, 0x1, 0x2f00);      //         }
	AddCMD(0x8, 0x9, 0x3, 0x3000);      //     }
	AddCMD(0x3, 0x2c00, 0x2, 0x3100);   //     ...
	AddCMD(0x3, 0x2700, 0xf, 0x3200);   // }
	AddCMD(0x8, 0x4, 0x5, 0x3300);      // 
	AddCMD(0x3, 0x3700, 0x2, 0x3400);   // if (local_4 == local_5) {
	AddCMD(0x0, 0x0, 0x1, 0x3500);      //     local_0 = 1
	AddCMD(0x3, 0x3900, 0xf, 0x3600);   // } else {
	AddCMD(0x0, 0x0, 0x0, 0x3700);      //     local_0 = 0
	AddCMD(0x3, 0x3900, 0xf, 0x3800);   // }
	AddCMD(0x1, 0x4, 0x2, 0x3900);      // local_4 = SOMEPTR ?
	AddCMD(0x0, 0x5, 0x10, 0x3a00);     // local_5 = 16;
	AddCMD(0x6, 0x4, 0x3, 0x3b00);      // local_3 = *SOMEPTR[0]
	AddCMD(0xc, 0x5, 0x1, 0x3c00);      // local_5 -= 1;
	AddCMD(0x8, 0x5, 0x3, 0x3d00);      // if (local_5 ? local_3)
	AddCMD(0x3, 0x3b00, 0x2, 0x3e00);   // ?
	AddCMD(0xe, 0x0, 0x0, 0x3f00);      // return local_0
	AddCMD(0xf, 0, 0, 0); // END
	Execute();
	PrintStackDump(true);
}

void CrackMe::AddCMD(int id, int cx, int dx, int offset)
{
	program.push_back(new s_command(id,cx,dx,offset));
}

_stack_cmd cmd_table[] = {
	cmd_00, cmd_01, cmd_02, cmd_03,
	cmd_04, cmd_05, cmd_06, cmd_07,
	cmd_08, cmd_09, cmd_0a, cmd_0b,
	cmd_0c, cmd_0d, cmd_0e, 0
};

void CrackMe::Execute()
{
	current_cmd = 0;
	//int trace = -1;
	while (1) {
		auto cmd = program[current_cmd];
		eax = cmd->id;
		if (eax > 0xe) {
			printf("[Execute] END\n\n");
			return;
		}
		if (1) {
			printf("[Execute#] cmd = %d : (%x, %x) {addr = %d}\n", cmd->id, cmd->ecx, cmd->edx, cmd->offset >> 8);
		}
		cmd_table[eax](cmd->ecx, cmd->edx, cmd->offset);
		current_cmd++;
		if(jmp > 0) {
			current_cmd = jmp;
			jmp = 0;
		}
		if (current_cmd == 15) break;
		//if (current_cmd >= trace) trace = current_cmd;
	}
}

void CrackMe::PrintStackDump(bool dump)
{
	if (dump) {
		for (int i = 38; i < (sizeof(stack_dump) / 4); i++) {
			int t = (int)ebp - (int)&stack_dump[i];
			auto printable = FormatUtil::DumpPrintableASCII((uint8_t*)&stack_dump[i], 4);
			if (t > 0) {
				printf("-0x%x :\t%08x\t| %s\n", t, stack_dump[i], printable.c_str());
			}
			else {
				printf("0x%x :\t%08x\t| %s\n", -t, stack_dump[i], printable.c_str());
			}
		}
		printf("\n");
		int* ptr = &unknown_value_0;
		for (int i = 0; i < (sizeof(unknown_values) / 4) + 2; i++) {
			auto printable = FormatUtil::DumpPrintableASCII((uint8_t*)&ptr[i], 4);
			printf("DATA :\t%08x| %s\n", ptr[i], printable.c_str());
		}
	}
	int size = sizeof(stack_dump);
	uint8_t* data = new uint8_t[size];
	memcpy(data, &stack_dump, size);
	int ctrl = 0;
	for (int i = 0; i < (sizeof(stack_dump) / 4); i++) {
		int z = ((int*)data)[i] - (int)&__debug_addr;
		if (abs(z) < 0x10000) {
			ctrl += z;
		}
		else {
			ctrl += ((int*)data)[i];
		}
	}
	int* ptr = &unknown_value_0;
	for (int i = 0; i < (sizeof(unknown_values) / 4) + 2; i++) {
		ctrl += ptr[i];
	}
	printf("\nStack control hash: %x\n", ctrl);
}