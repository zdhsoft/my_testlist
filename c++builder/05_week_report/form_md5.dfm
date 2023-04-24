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
    Height = 89
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
      Top = 47
      Width = 104
      Height = 15
      Caption = #27491#22312#22788#29702#30340#25991#20214#65306
    end
    object Label3: TLabel
      Left = 16
      Top = 68
      Width = 39
      Height = 15
      Caption = #32467#26524#65306
    end
    object Label4: TLabel
      Left = 126
      Top = 47
      Width = 3
      Height = 15
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
      Top = 68
      Width = 97
      Height = 17
      Caption = #36755#20986#32467#26524#22823#20889
      TabOrder = 1
    end
    object ProgressBar1: TProgressBar
      Left = 61
      Top = 66
      Width = 245
      Height = 17
      DoubleBuffered = True
      Max = 1000
      ParentDoubleBuffered = False
      Smooth = True
      MarqueeInterval = 0
      Step = 2
      TabOrder = 2
      StyleName = 'Windows10'
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 89
    Width = 748
    Height = 453
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitTop = 105
    ExplicitHeight = 437
    object Memo1: TMemo
      Left = 0
      Top = 0
      Width = 748
      Height = 453
      Align = alClient
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -14
      Font.Name = 'Consolas'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
end
