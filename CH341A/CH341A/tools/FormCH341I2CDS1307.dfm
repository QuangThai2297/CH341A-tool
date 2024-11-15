object frmCH341I2CDS1307: TfrmCH341I2CDS1307
  Left = 0
  Top = 0
  Caption = 'RTC DS1307'
  ClientHeight = 231
  ClientWidth = 505
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object lblDate: TLabel
    Left = 50
    Top = 107
    Width = 23
    Height = 13
    Caption = 'Date'
  end
  object lblTime: TLabel
    Left = 50
    Top = 76
    Width = 25
    Height = 13
    Caption = 'Time '
  end
  object lblStatus: TLabel
    Left = 97
    Top = 144
    Width = 3
    Height = 13
  end
  object btnRead: TButton
    Left = 97
    Top = 31
    Width = 75
    Height = 25
    Caption = 'Read'
    TabOrder = 0
    OnClick = btnReadClick
  end
  object chbAutoRead: TCheckBox
    Left = 97
    Top = 8
    Width = 264
    Height = 17
    Caption = 'auto refresh (repeat reading every second)'
    TabOrder = 1
    OnClick = chbAutoReadClick
  end
  object edTime: TEdit
    Left = 97
    Top = 73
    Width = 121
    Height = 21
    Enabled = False
    TabOrder = 2
  end
  object edDate: TEdit
    Left = 97
    Top = 104
    Width = 121
    Height = 21
    Enabled = False
    TabOrder = 3
  end
  object btnTimeWrite: TButton
    Left = 264
    Top = 71
    Width = 81
    Height = 25
    Caption = 'Write'
    Enabled = False
    TabOrder = 4
    OnClick = btnTimeWriteClick
  end
  object btnDateWrite: TButton
    Left = 264
    Top = 102
    Width = 81
    Height = 25
    Caption = 'Write'
    Enabled = False
    TabOrder = 5
    OnClick = btnDateWriteClick
  end
  object chbEnableWrite: TCheckBox
    Left = 264
    Top = 48
    Width = 81
    Height = 17
    Caption = 'Enable Write'
    TabOrder = 6
    OnClick = chbEnableWriteClick
  end
  object tmrAutoRead: TTimer
    OnTimer = tmrAutoReadTimer
    Left = 384
    Top = 8
  end
end
