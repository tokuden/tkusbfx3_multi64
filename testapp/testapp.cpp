#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#include "tkusbfx3.h"
CCyUSBDevice* hDevice;

bool UsbOpen(int num)
{
	char DeviceName[100];
	char Serial[20];
	unsigned short pid, vid;

	for (int timeout = 0; timeout < 3; timeout++)
	{
		hDevice = TKUSBFX3OpenEx(num, &vid, &pid, DeviceName, sizeof(DeviceName), Serial, 20);

		if (hDevice)
		{
			printf("USB open success. VID=%04x PID=%04x DeviceName=\"%s\" Serial=\"%s\"\n", vid, pid, DeviceName, Serial);
		}
		else
		{
			printf("USB open failed.");
			return false;
		}

		if ((vid == 0x2129) && (pid == 0x0520))
		{
			printf("NP1053(特電FX3ボード)を発見しました\n");
			return true;
		}
		else if ((vid == 0x2129) && (pid == 0x0640))
		{
			printf("NP1064(特電Artix-7ボード)を発見しました\n");
			return true;
		}
		else
		{
			char ErrorReason[100];
			printf("異なるVID,PIDのデバイスが見つかったので、ファームウェアを書き込みます。\n");
			/*
						if(TKUSBFX3WriteToRAM("SlaveFifoNP1064.img",ErrorReason,100))
						{
							printf("ファームウェアを書き込みました\n");
							Sleep(1000);
						}
						else
						{
							printf("ファームウェアの転送に失敗しました 理由:%s\n",ErrorReason);
							return false;
						}
			*/
		}
	}
	return false;
}

LONGLONG get_current_time()
{
	LONGLONG count, freq;
	if (!QueryPerformanceFrequency((LARGE_INTEGER*)& freq))
	{
		return 0;
	}
	QueryPerformanceCounter((LARGE_INTEGER*)& count);
	return count * 1000000 / freq;
}

typedef unsigned long uint32_t;

static uint32_t xs_x = 123456789;
static uint32_t xs_y = 362436069;
static uint32_t xs_z = 521288629;
static uint32_t xs_w = 88675123;

uint32_t xor128_reset(void)
{
	xs_x = 123456789;
	xs_y = 362436069;
	xs_z = 521288629;
	xs_w = 88675123;
	return xs_w;
}

uint32_t xor128(void) {
	uint32_t t;

	t = xs_x ^ (xs_x << 11);
	xs_x = xs_y; xs_y = xs_z; xs_z = xs_w;
	return xs_w = (xs_w ^ (xs_w >> 19)) ^ (t ^ (t >> 8));
}

typedef enum { XOR128, SEQ8, SEQ16, SEQ32 } DATAMODE;
typedef enum { IREG = 0, BRAM = 1, SDRAM = 2, TESTPTN = 3 } TARGET;

struct
{
	int len;
	BOOL write;
	BOOL read;
	BOOL loop;
	BOOL wait;
	BOOL nocomp;
	BOOL save;
	unsigned long addr;
	DATAMODE mode;
	TARGET target;
	int ndevice;
} flags;

int main(int argc, char* argv[])
{
	//	if(!UsbOpen()) return 0;

	int len = 128;

	LONGLONG start, end;
	int elapse;
	int rlen;
	double speed;

	flags.len = 128;
	flags.write = FALSE;
	flags.read = FALSE;
	flags.loop = FALSE;
	flags.wait = FALSE;
	flags.nocomp = FALSE;
	flags.addr = 0;
	flags.save = FALSE;
	flags.target = SDRAM;
	flags.mode = XOR128;
	flags.ndevice = 0;

	if (argc == 1)
	{
		printf("np1064test.exe cmd [option]\n");
		printf("cmd   : r             Read \n");
		printf("        w             Write\n");
		printf("        rw            Read-write and compare\n");
		printf("\n");
		printf("option: rand          Write random number by XorShift128 (*default) \n");
		printf("        seq8          Write sequential number (8bit)\n");
		printf("        seq16         Write sequential number (16bit)\n");
		printf("        seq32         Write sequential number (32bit)\n");
		printf("        #num#         Specify read write length\n");
		printf("        loop          Enable wait test\n");
		printf("        nocomp        No compare after read-write\n");
		printf("        wait          Enable wait test\n");
		printf("        sdram         Read/write SDRAM (default)\n");
		printf("        bram          Read/write BRAM\n");
		printf("        ireg          Read/write internal register \n");
		printf("        tptn          Read test pattern\n");
		printf("        save          Save read data to file\n");
		printf("        addr {offset} Specify read write start address\n");
	}
	for (int i = 1; i < argc; i++)
	{
		if (!strncmp(argv[i], "-n", 2))
		{
			flags.ndevice = atoi(argv[i] + 2);
			printf("dev=%d\n", flags.ndevice);
			continue;
		}
		if (!strcmp(argv[i], "r"))
		{
			flags.read = TRUE;
			continue;
		}
		if (!strcmp(argv[i], "w"))
		{
			flags.write = TRUE;
			continue;
		}
		if (!strcmp(argv[i], "rw"))
		{
			flags.read = TRUE;
			flags.write = TRUE;
			continue;
		}
		if (!strcmp(argv[i], "rand"))
		{
			flags.mode = XOR128;
			continue;
		}
		if (!strcmp(argv[i], "seq8"))
		{
			flags.mode = SEQ8;
			continue;
		}
		if (!strcmp(argv[i], "seq16"))
		{
			flags.mode = SEQ16;
			continue;
		}
		if (!strcmp(argv[i], "seq32"))
		{
			flags.mode = SEQ32;
			continue;
		}
		if (!strcmp(argv[i], "loop"))
		{
			flags.loop = TRUE;
			continue;
		}
		if (!strcmp(argv[i], "nocomp"))
		{
			flags.nocomp = TRUE;
			continue;
		}
		if (!strcmp(argv[i], "wait"))
		{
			flags.wait = TRUE;
			continue;
		}
		if (!strcmp(argv[i], "sdram"))
		{
			flags.target = SDRAM;
			continue;
		}
		if (!strcmp(argv[i], "bram"))
		{
			flags.target = BRAM;
			continue;
		}
		if (!strcmp(argv[i], "ireg"))
		{
			flags.target = IREG;
			continue;
		}
		if (!strcmp(argv[i], "tptn"))
		{
			flags.target = TESTPTN;
			continue;
		}
		if (!strcmp(argv[i], "save"))
		{
			flags.save = TRUE;
			continue;
		}
		if (!strcmp(argv[i], "addr"))
		{
			if (argc <= i + 1)
			{
				printf("missing parameter\n");
				return 0;
			}
			i++;
			int retval = sscanf_s(argv[i], "%x", &flags.addr);
			continue;
		}
		if (atoi(argv[i]) > 0)
		{
			len = atoi(argv[i]);
			continue;
		}
		printf_s("Unknown command or option [%s]\n", argv[i]);
		return 0;
	}

	if (!UsbOpen(flags.ndevice)) return 0;

	unsigned char* wdata = new unsigned char[len];
	unsigned char* rdata = new unsigned char[len];
	LONGLONG total_bytes = 0;
	int loop = 1;

	if (flags.mode == XOR128)
	{
		unsigned long* tmp = (unsigned long*)wdata;
		for (int i = 0; i < len / 4; i++)
		{
			*tmp++ = xor128();
		}
	}
	if (flags.mode == SEQ8)
	{
		for (int i = 0; i < len; i++)
		{
			wdata[i] = i;
		}
	}
	if (flags.mode == SEQ16)
	{
		unsigned short* tmp = (unsigned short*)wdata;
		for (int i = 0; i < len / 2; i++)
		{
			*tmp++ = i;
		}
	}
	if (flags.mode == SEQ32)
	{
		unsigned long* tmp = (unsigned long*)wdata;
		for (int i = 0; i < len / 4; i++)
		{
			*tmp++ = i;
		}
	}

	int orglen = len;
	while (1)
	{
		len = orglen;
		if (flags.loop)
		{
			int total_mb = total_bytes / 1000000;
			printf("%d回目 Total %d MBytes\n", loop++, total_mb);
		}

		if (flags.write)
		{
			start = get_current_time();
			USBWriteDataEx(hDevice, flags.addr, wdata, len, flags.target | (flags.wait ? 0x80 : 0));
			end = get_current_time();
			printf("%d Byteを送信, ", len);
			elapse = end - start;
			speed = (double)len / (double)elapse;
			printf("実行時間 %d us. 転送速度 %f MBytes/sec\n", elapse, speed);
			if (!flags.read)
			{
				total_bytes += len;
			}
		}
		if (flags.read)
		{
			memset(rdata, 0, len);
			start = get_current_time();
			rlen = USBReadDataEx(hDevice, flags.addr, rdata, len, flags.target | (flags.wait ? 0x80 : 0));
			end = get_current_time();
			printf("%d Byteを受信, ", rlen);
			elapse = end - start;
			speed = (double)rlen / (double)elapse;
			printf("実行時間 %d us. 転送速度 %f MBytes/sec\n", elapse, speed);

			if (flags.save)
			{
				FILE* fp;
				fopen_s(&fp, "read.bin", "wb");
				fwrite(rdata, 1, rlen, fp);
				fclose(fp);
			}
			if (!flags.nocomp && flags.write)
			{
				printf("比較します  ");
				if (memcmp(wdata, rdata, rlen))
				{
					printf("相違あり！\n");
					FILE* fp;
					fopen_s(&fp, "read.bin", "wb");
					fwrite(rdata, 1, rlen, fp);
					fclose(fp);
					fopen_s(&fp, "write.bin", "wb");
					fwrite(wdata, 1, rlen, fp);
					fclose(fp);
					break;
				}
				else
				{
					printf("相違なし\n");
				}
			}
			if (rlen != 4 * (int)((len + 3) / 4))
			{
				printf("短いパケット\n");
				break;
			}

			total_bytes += rlen;
		}
		if (flags.loop)
		{
			if (_kbhit()) break;
			continue;
		}
		break;
	}
	delete[] wdata;
	delete[] rdata;
}

