//---------------------------------------------------------------------------

#ifndef FormCH341ComPortH
#define FormCH341ComPortH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmCH341Com : public TForm
{
__published:	// IDE-managed Components
	TButton *btnOpenClose;
	TLabel *lblStatus;
	TComboBox *cbComSelect;
	TLabel *lblCom;
	TMemo *memoWrite;
	TMemo *memoRead;
	TButton *btnSend;
	TCheckBox *chbHexWrite;
	TButton *btnClearRead;
	TComboBox *cbBaudSelect;
	TLabel *lblBaud;
	TCheckBox *chbHexRead;
	TButton *btnClearWrite;
	TLabel *lblByteCount;
	TTimer *tmrReadCheck;
	TCheckBox *chbAlignReadData;
	TCheckBox *chbPause;
	void __fastcall btnOpenCloseClick(TObject *Sender);
	void __fastcall cbComSelectChange(TObject *Sender);
	void __fastcall memoWriteChange(TObject *Sender);
	void __fastcall chbHexWriteClick(TObject *Sender);
	void __fastcall btnClearWriteClick(TObject *Sender);
	void __fastcall btnSendClick(TObject *Sender);
	void __fastcall tmrReadCheckTimer(TObject *Sender);
	void __fastcall btnClearReadClick(TObject *Sender);
	void __fastcall chbHexReadClick(TObject *Sender);
	void __fastcall chbAlignReadDataClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmCH341Com(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCH341Com *frmCH341Com;
//---------------------------------------------------------------------------
#endif