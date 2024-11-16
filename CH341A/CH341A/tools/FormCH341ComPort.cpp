//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormCH341ComPort.h"
#include "TabManager.h"
#include "stdio.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCH341Com *frmCH341Com;
//---------------------------------------------------------------------------
__fastcall TfrmCH341Com::TfrmCH341Com(TComponent* Owner)
	: TForm(Owner)
{
	TabManager::Instance().Register(this);
	for (unsigned int i=0; i< 100; i++)
	{
		AnsiString text;
		text.sprintf("COM%u",i+1);
		cbComSelect->Items->Add(text);
	}
	cbComSelect->ItemIndex = 0;
}
static void	log_info(String text)
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


//https://forum.arduino.cc/t/vcl-c-builder-serial-communication/587947/10

class SerialPort
{
private:
    HANDLE handler;
    bool connected;
    COMSTAT status;
	DWORD errors;
public:
	#define WAIT_TIME 10
	SerialPort();
    ~SerialPort();
	 bool Open(char *portName, int baudrate);
	 bool Close();                            	
    int readSerialPort(char *buffer, unsigned int buf_size);
    bool writeSerialPort(char *buffer, unsigned int buf_size);
 bool isConnected();

};
SerialPort ser;
SerialPort::SerialPort()
{
   this->handler = NULL;
   this->connected = false;
}
SerialPort::~SerialPort()
{
    if (this->connected){
        this->connected = false;
		CloseHandle(this->handler);
		this->handler = NULL;
    }
}
bool SerialPort::Close()
{
    if (this->connected){
        this->connected = false;
		CloseHandle(this->handler);
		this->handler = NULL;
		 log_info("closed port\n");
	}else {
		if(this->handler)
		{
           CloseHandle(this->handler);
		   this->handler = NULL;
		   log_info("closed port\n");
		}
		else {
            log_info("not open before\n");
        }
	}
	return true;
}
bool SerialPort::Open(char *portName, int baudrate)
{
	if(this->handler)
	{
		if(this->connected)
		{
			log_info("ready openned\n");
			return true;
        }
	}
	String log;
	log.sprintf("open with COM: %s, baud: %d", portName, baudrate);
	log_info(log);
	this->connected = false;

	this->handler = CreateFileA(static_cast<LPCSTR>(portName),
                                GENERIC_READ | GENERIC_WRITE,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);
    if (this->handler == INVALID_HANDLE_VALUE){
        if (GetLastError() == ERROR_FILE_NOT_FOUND){
			printf("ERROR: Handle was not attached. Reason: %s not available\n", portName);
			log_info("error!!!\n");
        }
    else
        {
			log_info("ERROR!!!");
        }
    }
    else {
        DCB dcbSerialParameters = {0};

        if (!GetCommState(this->handler, &dcbSerialParameters)) {
			log_info("failed to get current serial parameters");
        }
        else {
            dcbSerialParameters.BaudRate = baudrate;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_DISABLE;

            if (!SetCommState(handler, &dcbSerialParameters))
            {
                log_info("ALERT: could not set Serial port parameters\n");
            }
            else {
                this->connected = true;
                PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
				Sleep(WAIT_TIME);
				return true;
            }
        }
	}
	return false;
}


int SerialPort::readSerialPort(char *buffer, unsigned int buf_size)
{
    DWORD bytesRead;
    unsigned int toRead;

    ClearCommError(this->handler, &this->errors, &this->status);

	if (this->status.cbInQue > 0){
        if (this->status.cbInQue > buf_size){
            toRead = buf_size;
        }
        else toRead = this->status.cbInQue;
    }

	if (ReadFile(this->handler, buffer, toRead, &bytesRead, NULL)) return bytesRead;

    return 0;
}

bool SerialPort::writeSerialPort(char *buffer, unsigned int buf_size)
{
    DWORD bytesSend;

	if (!WriteFile(this->handler, (void*) buffer, buf_size, &bytesSend, 0)){
 ClearCommError(this->handler, &this->errors, &this->status);
        return false;
    }
    else return true;
}

bool SerialPort::isConnected()
{
 return this->connected;
}

//---------------------------------------------------------------------------
void __fastcall TfrmCH341Com::btnOpenCloseClick(TObject *Sender)
{
	if(ser.isConnected())
	{
		log_info("close com\n");
		if(!ser.Close())
		{
             log_info("close fail\n");
		}
		if(!ser.isConnected())
		{
			log_info("close com ok\n");
			btnOpenClose->Caption = "Open";
			lblStatus->Caption = "Close com success";
		}
		else {
			log_info("close com fail\n");
		  	lblStatus->Caption = "Close com fail";
		}
	}
	else {
		log_info("open com\n");
		lblStatus->Caption = "";
		String s = "\\\\.\\" + cbComSelect->Items->Strings[cbComSelect->ItemIndex];
		if(!ser.Open(s.c_str(),
					cbBaudSelect->Items->Strings[cbBaudSelect->ItemIndex].ToInt()))
					{
                         log_info("open fail\n");
                    }
		if(ser.isConnected())
		{
			log_info("open com ok\n");
			btnOpenClose->Caption = "Close";
			lblStatus->Caption = "Open com success";
		}
		else {
			log_info("open com fail\n");
		  	lblStatus->Caption = "Open com fail";
		}
    }

}
//---------------------------------------------------------------------------


void __fastcall TfrmCH341Com::cbComSelectChange(TObject *Sender)
{
	//GetCommPorts
}
//---------------------------------------------------------------------------

