//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormCH341I2CDS1307.h"
#include "TabManager.h"
#include "Log.h"
#include "CH341A.h"
#include "common/BtnController.h"
#include "stdint.h"
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
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
	//check format hh:mm:ss
	bool setTimeFromString(AnsiString str)
	{
		int hh,mm,ss;   //should be type int
		hh = _raw[2]; mm = _raw[1]; ss = _raw[0];
		if(str == "") {
			log_info("text time NULL!!!\n");
			return false;
        }
		if(sscanf(str.c_str(), "%02X : %02X : %02X", &hh, &mm, &ss) == 0)
		{
			log_info("convert time FAIL!!!\n");
			return false;
        }
		_raw[0] = ss;
		_raw[1] = mm;
		_raw[2] = hh;
		String log;
		log.sprintf("%02X : %02X : %02X", _raw[2], _raw[1], _raw[0]) ;
		log_info("Set Time BCD: "); log_info(log);
		return writeDateTimeRaw();
    }
    //check format date:month:year
	bool setDateFromString(AnsiString str)
	{
		int day,date,month,year;
		day = _raw[3], date = _raw[4]; month = _raw[5]; year = _raw[6];
		if(str == "") {
			log_info("text date NULL!!!\n");
			return false;
        }
		if(sscanf(str.c_str(), "%X : %X : 20%X", &date, &month, &year) == 0)
		{
			log_info("convert date FAIL!!!\n");
			return false;
		}
		_raw[3] = day;
		_raw[4] = date;
		_raw[5] = month;
		_raw[6] = year;
		String log;
		log.sprintf("%02X : %02X : %02X", _raw[4], _raw[5], _raw[6]) ;
		log_info("Date BCD: "); log_info(log);
		//write to ds1307
		return writeDateTimeRaw();
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
RTC_DS1307 rtc(0x05, 0x31, 0x14, 1,1,1,1);
void TfrmCH341I2CDS1307::Clear(void)
{
	edTime->Text = "";
	edDate->Text = "";
}

bool TfrmCH341I2CDS1307::CheckBus(void)
{
	if (!ch341a.IsOpened())
	{
		lblStatus->Caption = "CH341 is not opened!";
		Clear();
		return false;
	}

	int status = ch341a.I2CCheckDev(RTC_DS1307::ADDRESS);
	if (status != 0)
	{
		lblStatus->Caption = "No ACK after sending expected I2C address!";
		Clear();
		return false;
	}

	return true;
}
void TfrmCH341I2CDS1307::Read(void)
{
   BtnController btnCtrl(btnRead);

	if(CheckBus() == false)
	{
        return;
    }
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
void TfrmCH341I2CDS1307::WriteTime(void)
{
	if(CheckBus() == false)
	{
        return;
    }
   if(rtc.setTimeFromString(edTime->Text)) {
	lblStatus->Caption = "Set Time OK";
   }
   else {
   	lblStatus->Caption = "Set Time Error";
   }
}
void TfrmCH341I2CDS1307::WriteDate(void)
{
	if(CheckBus() == false)
	{
        return;
    }
   if(rtc.setDateFromString(edDate->Text)) {
	lblStatus->Caption = "Set Date OK";
   }
   else {
   	lblStatus->Caption = "Set Date Error";
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
	{
		log_info("New Read\n");
		Read();
    }
	tmrAutoRead->Enabled = true;	
}
//---------------------------------------------------------------------------


void __fastcall TfrmCH341I2CDS1307::chbEnableWriteClick(TObject *Sender)
{
	if(chbEnableWrite->Checked)
	{
		log_info("enable write\n");
		chbAutoRead->Checked = false;
		edTime->Enabled = true;
		edDate->Enabled = true;
		btnTimeWrite->Enabled = true;
		btnDateWrite->Enabled = true;
	}
	else {
		log_info("disable write\n");
		edTime->Enabled = false;
		edDate->Enabled = false;
		btnTimeWrite->Enabled = false;
		btnDateWrite->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmCH341I2CDS1307::chbAutoReadClick(TObject *Sender)
{
	if (chbAutoRead->Checked)
		chbEnableWrite->Checked = false;	
}
//---------------------------------------------------------------------------

void __fastcall TfrmCH341I2CDS1307::btnTimeWriteClick(TObject *Sender)
{
	if(chbEnableWrite->Checked)
	{
		 WriteTime();
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmCH341I2CDS1307::btnDateWriteClick(TObject *Sender)
{
	if(chbEnableWrite->Checked)
	{
		WriteDate();
	}
}
//---------------------------------------------------------------------------

