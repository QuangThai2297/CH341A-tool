//---------------------------------------------------------------------------

#ifndef FormCH341I2CDS1307H
#define FormCH341I2CDS1307H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmCH341I2CDS1307 : public TForm
{
__published:	// IDE-managed Components
	TButton *btnRead;
	TCheckBox *chbAutoRead;
	TTimer *tmrAutoRead;
	TLabel *lblDate;
	TLabel *lblTime;
	TEdit *edTime;
	TEdit *edDate;
	TButton *btnTimeWrite;
	TButton *btnDateWrite;
	TCheckBox *chbEnableWrite;
	TLabel *lblStatus;
	void __fastcall lblStatusClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmCH341I2CDS1307(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCH341I2CDS1307 *frmCH341I2CDS1307;
//---------------------------------------------------------------------------
#endif
