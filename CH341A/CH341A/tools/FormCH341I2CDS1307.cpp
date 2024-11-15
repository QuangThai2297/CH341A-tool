//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormCH341I2CDS1307.h"
#include "TabManager.h"
#include "Log.h"
#include "CH341A.h"
#include "common/BtnController.h"
#include "stdint.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCH341I2CDS1307 *frmCH341I2CDS1307;
 void	log_info(String text)
	{
	// fprintf(stderr, "%s\n", text.c_str());
		static HANDLE handle;
		if (!handle) {
			AllocConsole();
			handle = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		text += "\n";
		WriteConsole(handle, text.c_str(), text.Length(), 0, 0);
	}
class RTC_DS1307
{
private:

	/* data */
	// Convert normal decimal numbers to binary coded decimal
	uint8_t decToBcd(uint8_t val)
	{
		return ( (val/10*16) + (val%10) );
	}
	// Convert binary coded decimal to normal decimal numbers
	uint8_t bcdToDec(uint8_t val)
	{
		return ( (val/16*10) + (val%16) );
	}
	#define MAX_REG_NUM 7

	enum {
		ADDR_SEC = 0x00,
		ADDR_MIN,
		ADDR_HOUR,
		ADDR_DY,
		ADDR_DT,
		ADDR_MONTH,
		ADDR_YEAR
	};
	uint8_t _raw[MAX_REG_NUM];
public:
	enum { ADDRESS = 0x38 };
	RTC_DS1307::RTC_DS1307(int ss, int mm, int hh, int day, int date, int month, int year)
	{                
		_raw[0] = ss;
		_raw[1] = mm;
		_raw[2] = hh;
		_raw[3] = day;
		_raw[4] = date;
		_raw[5] = month;
		_raw[6] = year;
	}
	RTC_DS1307::RTC_DS1307()
	{               

	}
	RTC_DS1307::~RTC_DS1307()
	{
	}

	bool readReg(uint8_t reg, uint8_t* value) {
		int status;
		uint8_t data;
		status = ch341a.I2CWriteCommandReadByte(ADDRESS, reg, data);
		if (status != 0)
				return false;
		*value = data;
		return true;
	}
	bool writeReg(uint8_t reg, uint8_t value)
	{
		int status;
		status = ch341a.I2CWriteCommandWriteByte(ADDRESS, reg, value);
		if (status != 0)
				return false;
		return true;
	}
	bool readDateTimeRaw()
	{
		int status;
		status = ch341a.I2CWriteCommandReadBytes(ADDRESS, ADDR_SEC, _raw, MAX_REG_NUM);
		if (status != 0)
				return false;
		return true;
	}
	bool writeDateTimeRaw()
	{
		int status;
		status = ch341a.I2CWriteCommandWriteBytes(ADDRESS, ADDR_SEC, _raw, MAX_REG_NUM);
		if (status != 0)
				return false;
		return true;
	}
	AnsiString getTimeInString()
	{
		AnsiString str;
		str.sprintf("%02X : %02X : %02X", _raw[2], _raw[1], _raw[0]) ;
		log_info("Time BCD: "); log_info(str);
		str.sprintf("%02d : %02d : %02d", bcdToDec(_raw[2]), bcdToDec(_raw[1]), bcdToDec(_raw[0])) ;
		log_info("Time DEC: "); log_info(str);
		return str;
	}
	AnsiString getDateInString()
	{
		AnsiString str;
		str.sprintf("%02X : %02X : %02X", _raw[4], _raw[5], _raw[6]) ;
		log_info("Date BCD: "); log_info(str);
		str.sprintf("%02d : %02d : 20%02d", bcdToDec(_raw[4]), bcdToDec(_raw[5]), bcdToDec(_raw[6])) ;
		log_info("Date DEC: "); log_info(str);
		return str;
	}
	void init()
	{
		uint8_t chByte = 0;
		if(readReg(ADDR_SEC,&chByte))
		{
			if((chByte & 0x80) == 0x80)
			{
				log_info("start counter rtc\n");
				if(writeReg(ADDR_SEC,chByte & 0x7F)) // start counter
				{
					log_info("Inited rtc\n");
				}
			}
			else {
				log_info("Inited rtc\n");
			}
		}
	}
};
void TfrmCH341I2CDS1307::Clear(void)
{
	edTime->Text = "";
	edDate->Text = "";
}

void TfrmCH341I2CDS1307::Read(void)
{
   BtnController btnCtrl(btnRead);

	if (!ch341a.IsOpened())
	{
		lblStatus->Caption = "CH341 is not opened!";
		Clear();
		return;
	}

	int status = ch341a.I2CCheckDev(RTC_DS1307::ADDRESS);
	if (status != 0)
	{
		lblStatus->Caption = "No ACK after sending expected I2C address!";
		Clear();
		return;
	}

	RTC_DS1307 rtc(0x05, 0x31, 0x14, 1,1,1,1);

	if (rtc.readDateTimeRaw() == 0)
	{
		lblStatus->Caption = "Read OK";
		AnsiString str;
		edTime->Text = rtc.getTimeInString();
		edDate->Text = rtc.getDateInString();
	}
	else
	{
		lblStatus->Caption = "Read error";
		Clear();
	}
}
//---------------------------------------------------------------------------
__fastcall TfrmCH341I2CDS1307::TfrmCH341I2CDS1307(TComponent* Owner)
	: TForm(Owner)
{
	TabManager::Instance().Register(this);
}
//---------------------------------------------------------------------------


void __fastcall TfrmCH341I2CDS1307::btnReadClick(TObject *Sender)
{
	log_info("New Read\n");
	Read();	
}
//---------------------------------------------------------------------------

void __fastcall TfrmCH341I2CDS1307::tmrAutoReadTimer(TObject *Sender)
{
	tmrAutoRead->Enabled = false;
	if (chbAutoRead->Checked)
		Read();
	tmrAutoRead->Enabled = true;	
}
//---------------------------------------------------------------------------

