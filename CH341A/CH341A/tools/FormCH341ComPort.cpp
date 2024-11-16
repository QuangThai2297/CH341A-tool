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
	#define ARDUINO_WAIT_TIME 1000
	SerialPort(char *portName);
    ~SerialPort();

    int readSerialPort(char *buffer, unsigned int buf_size);
    bool writeSerialPort(char *buffer, unsigned int buf_size);
 bool isConnected();

};

SerialPort::SerialPort(char *portName)
{
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
            dcbSerialParameters.BaudRate = CBR_9600;
            dcbSerialParameters.ByteSize = 8;
            dcbSerialParameters.StopBits = ONESTOPBIT;
            dcbSerialParameters.Parity = NOPARITY;
            dcbSerialParameters.fDtrControl = DTR_CONTROL_ENABLE;

            if (!SetCommState(handler, &dcbSerialParameters))
            {
                log_info("ALERT: could not set Serial port parameters\n");
            }
            else {
                this->connected = true;
                PurgeComm(this->handler, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(ARDUINO_WAIT_TIME);
            }
        }
    }
}

SerialPort::~SerialPort()
{
    if (this->connected){
        this->connected = false;
        CloseHandle(this->handler);
    }
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
	log_info("open com\n");
	lblStatus->Caption = "";
	SerialPort comport("\\\\.\\COM10");
	if(comport.isConnected())
	{
		log_info("open com ok\n");
		lblStatus->Caption = "Open com success";
	}
	else {
		  log_info("open com fail\n");
		  lblStatus->Caption = "Open com fail";
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmCH341Com::cbComSelectChange(TObject *Sender)
{
	//GetCommPorts
}
//---------------------------------------------------------------------------

