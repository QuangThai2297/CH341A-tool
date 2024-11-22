object frmBQ25773: TfrmBQ25773
  Left = 0
  Top = 0
  Caption = 'BQ25773 Charger'
  ClientHeight = 282
  ClientWidth = 557
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Shape1: TShape
    Left = 360
    Top = 168
    Width = 49
    Height = 25
    Brush.Color = clSilver
    Pen.Color = cl3DDkShadow
    Pen.Width = 2
  end
  object Shape2: TShape
    Left = 360
    Top = 137
    Width = 49
    Height = 25
    Brush.Color = clSilver
    Pen.Color = cl3DDkShadow
    Pen.Width = 2
  end
  object Shape3: TShape
    Left = 360
    Top = 106
    Width = 49
    Height = 25
    Brush.Color = clSilver
    Pen.Color = cl3DDkShadow
    Pen.Width = 2
  end
  object Shape4: TShape
    Left = 360
    Top = 75
    Width = 49
    Height = 25
    Brush.Color = clSilver
    Pen.Color = cl3DDkShadow
    Pen.Width = 2
  end
  object Shape5: TShape
    Left = 360
    Top = 44
    Width = 49
    Height = 25
    Brush.Color = clSilver
    Pen.Color = cl3DDkShadow
    Pen.Width = 2
  end
  object lblLevel: TLabel
    Left = 352
    Top = 25
    Width = 80
    Height = 13
    Caption = 'LEVEL (MAX = 5)'
  end
  object Shape6: TShape
    Left = 272
    Top = 44
    Width = 49
    Height = 25
    Brush.Color = clSilver
    Pen.Color = cl3DDkShadow
    Pen.Width = 2
  end
  object lblCharging: TLabel
    Left = 272
    Top = 24
    Width = 53
    Height = 13
    Caption = 'CHARGING'
  end
  object lblVol: TLabel
    Left = 80
    Top = 47
    Width = 19
    Height = 13
    Caption = 'VOL'
  end
  object lblStatus: TLabel
    Left = 112
    Top = 110
    Width = 71
    Height = 13
    Caption = 'Status: Normal'
  end
  object lblThresh: TLabel
    Left = 447
    Top = 25
    Width = 50
    Height = 13
    Caption = 'Thresh Vol'
  end
  object edVoltageInput: TEdit
    Left = 105
    Top = 44
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object chbSetVol: TCheckBox
    Left = 112
    Top = 71
    Width = 71
    Height = 17
    Caption = 'Set vol'
    TabOrder = 1
    OnClick = chbSetVolClick
  end
  object Edit1: TEdit
    Left = 447
    Top = 172
    Width = 59
    Height = 21
    TabOrder = 2
  end
  object Edit2: TEdit
    Left = 447
    Top = 141
    Width = 59
    Height = 21
    TabOrder = 3
  end
  object Edit3: TEdit
    Left = 447
    Top = 110
    Width = 59
    Height = 21
    TabOrder = 4
  end
  object Edit4: TEdit
    Left = 447
    Top = 75
    Width = 59
    Height = 21
    TabOrder = 5
  end
  object Edit5: TEdit
    Left = 447
    Top = 44
    Width = 59
    Height = 21
    TabOrder = 6
  end
  object btnSaveThresh: TButton
    Left = 447
    Top = 216
    Width = 59
    Height = 25
    Caption = 'Save'
    TabOrder = 7
    OnClick = btnSaveThreshClick
  end
  object chbSetCharging: TCheckBox
    Left = 272
    Top = 72
    Width = 82
    Height = 17
    Caption = 'Set charge'
    TabOrder = 8
    OnClick = chbSetChargingClick
  end
  object chbSetError: TCheckBox
    Left = 200
    Top = 71
    Width = 66
    Height = 17
    Caption = 'Set error'
    TabOrder = 9
    OnClick = chbSetErrorClick
  end
  object tmrSystem: TTimer
    Interval = 10
    OnTimer = tmrSystemTimer
    Left = 120
    Top = 160
  end
end
