//---------------------------------------------------------------------------

#ifndef FormCH341ComPortH
#define FormCH341ComPortH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
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
	TButton *btnClear;
	TComboBox *cbBaudSelect;
	TLabel *lblBaud;
	TCheckBox *chbHexRead;
	void __fastcall btnOpenCloseClick(TObject *Sender);
	void __fastcall cbComSelectChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmCH341Com(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmCH341Com *frmCH341Com;
//---------------------------------------------------------------------------
#endif
