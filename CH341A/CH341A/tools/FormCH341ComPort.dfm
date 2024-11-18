object frmCH341Com: TfrmCH341Com
  Left = 0
  Top = 0
  Caption = 'COM'
  ClientHeight = 245
  ClientWidth = 511
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lblStatus: TLabel
    Left = 92
    Top = 53
    Width = 3
    Height = 13
  end
  object lblCom: TLabel
    Left = 59
    Top = 29
    Width = 23
    Height = 13
    Caption = 'COM'
  end
  object lblBaud: TLabel
    Left = 184
    Top = 29
    Width = 44
    Height = 13
    Caption = 'Baudrate'
  end
  object lblByteCount: TLabel
    Left = 377
    Top = 86
    Width = 47
    Height = 13
    Caption = '0 byte (s)'
  end
  object btnOpenClose: TButton
    Left = 322
    Top = 24
    Width = 75
    Height = 25
    Caption = 'Open'
    TabOrder = 0
    OnClick = btnOpenCloseClick
  end
  object cbComSelect: TComboBox
    Left = 88
    Top = 26
    Width = 81
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    OnChange = cbComSelectChange
  end
  object memoWrite: TMemo
    Left = 88
    Top = 74
    Width = 217
    Height = 60
    ScrollBars = ssVertical
    TabOrder = 2
    OnChange = memoWriteChange
  end
  object memoRead: TMemo
    Left = 88
    Top = 151
    Width = 217
    Height = 62
    Color = clMenu
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 3
  end
  object btnSend: TButton
    Left = 377
    Top = 109
    Width = 75
    Height = 25
    Caption = 'Send'
    TabOrder = 4
    OnClick = btnSendClick
  end
  object chbHexWrite: TCheckBox
    Left = 322
    Top = 86
    Width = 49
    Height = 17
    Caption = 'Hex'
    TabOrder = 5
    OnClick = chbHexWriteClick
  end
  object btnClearRead: TButton
    Left = 322
    Top = 184
    Width = 49
    Height = 25
    Caption = 'Clear'
    TabOrder = 6
  end
  object cbBaudSelect: TComboBox
    Left = 232
    Top = 26
    Width = 73
    Height = 21
    ItemHeight = 13
    ItemIndex = 2
    TabOrder = 7
    Text = '9600'
    Items.Strings = (
      '2400'
      '4800'
      '9600'
      '19200'
      '38400'
      '115200')
  end
  object chbHexRead: TCheckBox
    Left = 322
    Top = 161
    Width = 49
    Height = 17
    Caption = 'Hex'
    TabOrder = 8
  end
  object btnClearWrite: TButton
    Left = 322
    Top = 109
    Width = 49
    Height = 25
    Caption = 'Clear'
    TabOrder = 9
    OnClick = btnClearWriteClick
  end
end
