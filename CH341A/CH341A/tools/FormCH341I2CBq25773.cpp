//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormCH341I2CBq25773.h"
#include "TabManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmBQ25773 *frmBQ25773;

//---------------------------------------------------------------------------
__fastcall TfrmBQ25773::TfrmBQ25773(TComponent* Owner)
	: TForm(Owner)
{
	TabManager::Instance().Register(this);
}
	#define MAX_LEVEL 5
class TChargerDisplay
{
private:
	float voltageCurrent;
	bool isCharging;
	bool isError;
	float voltageThres[MAX_LEVEL];
	int levelCurrent;
protected:


public:
	TChargerDisplay::TChargerDisplay() {
		for(int i = 0; i < MAX_LEVEL; i++)
		{
			voltageThres[i] = (i+1)*2;
		}
		voltageCurrent = 0;
		isCharging = false;
		isError = false;
	}
	TChargerDisplay::~TChargerDisplay(){}
	void setThreshVoltage(float* thresh, int editNum)
	{
		if(editNum > MAX_LEVEL)
		{
            return;
        }
		for(int i = 0; i < editNum; i++)
		{
			voltageThres[i] = thresh[i];
		}
	}
	void getThreshVoltage(float* thresh, int editNum)
	{
		if(editNum > MAX_LEVEL)
		{
            return;
        }
		for(int i = 0; i < editNum; i++)
		{
			thresh[i] = voltageThres[i];
		}
	}
	void setVoltageCurrent(float voltage)
	{
		voltageCurrent = voltage;
	}
	float getVoltageCurrent()
	{
        return voltageCurrent;
    }
	int getLevelCurrent()
	{
		 for(int i = MAX_LEVEL; i > 0; i--)
		 {
			 if(voltageCurrent >= voltageThres[i-1])
			 {
				 return i;
			 }
		 }
		 return 0;
	}
	bool isChargerCharging()
	{
		return isCharging;
	}
	void setCharging(bool ischarging)
	{
		isCharging =  ischarging;
	}
	bool isChargerError()
	{
		return isError;
	}
	void setError(bool iserror)
	{
		isError =  iserror;
	}
    
};
TChargerDisplay chargerDisplay;
void TfrmBQ25773::displayThresh(float* thresh, int num)
{
	TEdit* editList[5] = {Edit1, Edit2, Edit3, Edit4, Edit5};
	for(int i = 0; i < 5; i++)
	{
        editList[i]->Text = FloatToStr(thresh[i]);
	}
}
//---------------------------------------------------------------------------

void __fastcall TfrmBQ25773::btnSaveThreshClick(TObject *Sender)
{
	float thresh[5] = {0};
	TEdit* editList[5] = {Edit1, Edit2, Edit3, Edit4, Edit5};
	for(int i = 0; i < 5; i++)
	{
		try {

			thresh[i] = editList[i]->Text.ToDouble();
		} catch (...) {
			lblStatus->Caption = "Input wrong!";
			return;
		}
	}

	chargerDisplay.setThreshVoltage(thresh, 5);
	chargerDisplay.getThreshVoltage(thresh, 5);
	frmBQ25773->displayThresh(thresh, 5);
	lblStatus->Caption = "Save thresh ok";
}
//---------------------------------------------------------------------------

void __fastcall TfrmBQ25773::tmrSystemTimer(TObject *Sender)
{
	static int cnt500ms = 0;
	static bool tglColor = true;
	static int cnt100ms = 0;
	cnt100ms++;
	cnt500ms++;
	static bool isStart = true;
	if(isStart)
	{
    	float thresh[5] = {0};
    	chargerDisplay.getThreshVoltage(thresh, 5);
		frmBQ25773->displayThresh(thresh, 5);
		edVoltageInput->Text = FloatToStr(chargerDisplay.getVoltageCurrent());
		Shape6->Brush->Color =  chargerDisplay.isChargerCharging() ? clLime : clSilver;
        isStart = false;
	}
	if(isStart == true) return;
	if(cnt500ms == 5)
	{
		tglColor = !tglColor;
		cnt500ms = 0;
	}

	

	if(cnt100ms > 10)
	{
		cnt100ms = 0;
		TShape* shapeList[5] = {Shape1, Shape2, Shape3, Shape4, Shape5};
		int level =   chargerDisplay.getLevelCurrent();
		for(int i = 0; i < 5; i++)
		{
            if(chargerDisplay.isChargerError())
			{
            	 shapeList[i]->Brush->Color =  tglColor ? clSilver : clLime;
                 continue;
            }

			if(level == 0)
			{
               if(chargerDisplay.isChargerCharging())
				{
					shapeList[0]->Brush->Color =  tglColor ? clSilver : clLime;
				}
				else {
					 shapeList[0]->Brush->Color =   clLime;
				}
				if(i != 0)
				{
                     shapeList[i]->Brush->Color =   clSilver;
                }
            }
			else if(i < level - 1)
			{
			   shapeList[i]->Brush->Color =   clLime;
			}
			else if(i == level - 1)
			{
				if(chargerDisplay.isChargerCharging())
				{
					shapeList[i]->Brush->Color =  tglColor ? clSilver : clLime;
				}
				else {
                     shapeList[i]->Brush->Color =   clLime;
                }
            }
			else {
				shapeList[i]->Brush->Color =   clSilver;
			}
		}
    }	
}
//---------------------------------------------------------------------------


void __fastcall TfrmBQ25773::chbSetVolClick(TObject *Sender)
{
	if(chbSetVol->Checked)
	{
        edVoltageInput->Enabled = true;
	}
	else {
		chargerDisplay.setVoltageCurrent(edVoltageInput->Text.ToDouble());
		edVoltageInput->Enabled = false;

		lblStatus->Caption =  "Current voltage: " + FloatToStr(edVoltageInput->Text.ToDouble())
							+ ", Level: " + IntToStr(chargerDisplay.getLevelCurrent());


							
    }	
}
//---------------------------------------------------------------------------



void __fastcall TfrmBQ25773::chbSetChargingClick(TObject *Sender)
{
	chargerDisplay.setCharging(chbSetCharging->Checked);
	Shape6->Brush->Color =  chargerDisplay.isChargerCharging() ? clLime : clSilver;	
}
//---------------------------------------------------------------------------

void __fastcall TfrmBQ25773::chbSetErrorClick(TObject *Sender)
{
	chargerDisplay.setError(chbSetError->Checked);
}
//---------------------------------------------------------------------------

