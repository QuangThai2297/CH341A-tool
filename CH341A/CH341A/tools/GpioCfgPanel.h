//---------------------------------------------------------------------------

#ifndef GpioCfgPanelH
#define GpioCfgPanelH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

#include <stdint.h>

class PACKAGE TGpioCfgPanel : public TPanel
{
private:
	unsigned int id;
public:
	__fastcall TGpioCfgPanel(TComponent* Owner, unsigned int id, AnsiString description);
	bool GetDirection(void) {
		return chbDirection->Checked;
	}
	bool GetDataOut(void) {
		return chbDataOut->Checked;
	}
	void SetDataIn(bool val) {
		chbDataIn->Checked = val;
	}
__published:
	TLabel *label;
	TCheckBox *chbDirection;
	TCheckBox *chbDataOut;
	TCheckBox *chbDataIn;
};
//---------------------------------------------------------------------------
#endif
