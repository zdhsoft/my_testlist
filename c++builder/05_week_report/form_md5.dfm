object frmMD5: TfrmMD5
  Left = 0
  Top = 0
  Align = alClient
  BorderStyle = bsNone
  Caption = 'frmMD5'
  ClientHeight = 542
  ClientWidth = 748
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 748
    Height = 105
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 21
      Width = 78
      Height = 15
      Caption = #21407#22987#23383#31526#20018#65306
    end
    object Label2: TLabel
      Left = 16
      Top = 55
      Width = 78
      Height = 15
      Caption = #36873#25321#30340#25991#20214#65306
    end
    object Label3: TLabel
      Left = 16
      Top = 84
      Width = 39
      Height = 15
      Caption = #32467#26524#65306
    end
    object Edit1: TEdit
      Left = 100
      Top = 18
      Width = 637
      Height = 23
      TabOrder = 0
      OnChange = Edit1Change
    end
    object cbCaption: TCheckBox
      Left = 312
      Top = 82
      Width = 97
      Height = 17
      Caption = #36755#20986#32467#26524#22823#20889
      TabOrder = 1
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 105
    Width = 748
    Height = 437
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitTop = 256
    ExplicitHeight = 286
    object Memo1: TMemo
      Left = 0
      Top = 0
      Width = 748
      Height = 437
      Align = alClient
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = 'Consolas'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      ExplicitLeft = 232
      ExplicitTop = 112
      ExplicitWidth = 185
      ExplicitHeight = 89
    end
  end
end
