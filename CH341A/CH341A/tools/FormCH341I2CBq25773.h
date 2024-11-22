//---------------------------------------------------------------------------

#ifndef FormCH341I2CBq25773H
#define FormCH341I2CBq25773H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmBQ25773 : public TForm
{
__published:	// IDE-managed Components
	TShape *Shape1;
	TShape *Shape2;
	TShape *Shape3;
	TShape *Shape4;
	TShape *Shape5;
	TLabel *lblLevel;
	TShape *Shape6;
	TLabel *lblCharging;
	TEdit *edVoltageInput;
	TLabel *lblVol;
	TLabel *lblStatus;
	TCheckBox *chbSetVol;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TLabel *lblThresh;
	TTimer *tmrSystem;
	TButton *btnSaveThresh;
	TCheckBox *chbSetCharging;
	TCheckBox *chbSetError;
	void __fastcall btnSaveThreshClick(TObject *Sender);
	void __fastcall tmrSystemTimer(TObject *Sender);
	void __fastcall chbSetVolClick(TObject *Sender);
	void __fastcall chbSetChargingClick(TObject *Sender);
	void __fastcall chbSetErrorClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmBQ25773(TComponent* Owner);
	void displayThresh(float* thresh, int num);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBQ25773 *frmBQ25773;
//---------------------------------------------------------------------------
#endif
