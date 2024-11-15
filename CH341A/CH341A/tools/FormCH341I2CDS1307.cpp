//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormCH341I2CDS1307.h"
#include "TabManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmCH341I2CDS1307 *frmCH341I2CDS1307;
//---------------------------------------------------------------------------
__fastcall TfrmCH341I2CDS1307::TfrmCH341I2CDS1307(TComponent* Owner)
	: TForm(Owner)
{
	TabManager::Instance().Register(this);
}
//---------------------------------------------------------------------------
