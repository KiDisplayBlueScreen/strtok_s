#include <iostream>
#include <Windows.h>
using namespace std;

char String[] =
".A string\tof ,,tokens\nand some  more tokens";
char seps[] = ".";
char* token = NULL;
char* next_token = NULL;


_Check_return_ char* __cdecl Mystrtok_s(char* _String, char const* _Delimiter, char** _Context)
{
	if (_Context == NULL || _Delimiter == NULL || ((_String == NULL) && *_Context == 0)) return 0;

	char** Temp = _Context;//[EBP-0x28]
	char const* TempESI = _Delimiter;
	char* TempEDI = _String;
	DWORD EDX, ECX = 0;
	DWORD TempEAX = 0;
	BYTE Buffer[0x20] = { 0 };

	while (1)
	{
		BYTE BL= *(PBYTE)TempESI;
		EDX = (DWORD) * (PBYTE)TempESI;
		ECX = EDX;
		EDX &= 7;
		ECX >>= 3;
		TempEAX = Buffer[ECX];
		TempEAX |= (1 << EDX);
		TempESI++;
		Buffer[ECX] = (BYTE)(TempEAX &= 0xFF);
		if (BL == 0) break;
	}
	if (TempEDI == 0)
	{
		TempEDI = *Temp;
	}
	EDX = (DWORD) * (PBYTE)TempEDI;
	TempEAX = 0;
	ECX = EDX;
	TempEAX++;
	ECX &= 7;
	EDX >>= 3;
	TempEAX <<= (BYTE)(ECX & 0xFF);

	if ( (Buffer[EDX] & (BYTE)(TempEAX & 0xFF) )!= 0)
	{
		TempESI = TempEDI;
		if (*(PBYTE)TempEDI == 0)
		{
			goto label;
		}

	}

label:
	char* TempEBX = TempEDI;
	TempESI = TempEBX;


	if (*TempEDI == 0)
	{
		goto End;
	}
	else
	{
		while (1)
		{
			EDX = (DWORD) * (PBYTE)TempESI;
			TempEAX = 0;
			ECX = EDX;
			TempEAX++;
			ECX &= 7;
			EDX >>= 3;
			TempEAX <<= (BYTE)(ECX & 0xFF);
			TempESI++;
			if ((Buffer[EDX] & (BYTE)(TempEAX & 0xFF) )== 0)
			{
				TempEDI = (char*)TempESI;
				if (*TempEDI != 0) continue;
				else 
				{
					goto End;
				}
			}
			else
			{
				*TempEDI = 0;
				TempEDI =(char*)TempESI;
				goto End;
			}
		}
	}

    End:
	TempESI =(const char*)( (char*)TempESI - TempEBX);

	TempESI=(char*)(((DWORD)TempESI ^ 0xFFFFFFFF) + 1);
	if (TempESI == 0)
	{
		TempESI = (char*)(TempESI - TempESI);
	}
	else
	{
		TempESI = (char*)(TempESI - TempESI-1);
	}
	TempESI =(char*) ((DWORD)TempESI&(DWORD)TempEBX);
	*Temp = TempEDI;
	return (char*)TempESI;

}

int main()
{

	token = Mystrtok_s(String, seps, &next_token);

	while (token != NULL)
	{
		// Get next token: 
		if (token != NULL)
		{
			printf(" %s\n", token);
			token = Mystrtok_s(NULL, seps, &next_token);
		}
	}
	printf("the rest token1:\n");
	printf("%d", token);
	system("pause");
}


