object frmMD5: TfrmMD5
  Left = 0
  Top = 0
  Align = alClient
  BorderStyle = bsNone
  Caption = 'frmMD5'
  ClientHeight = 542
  ClientWidth = 800
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
    Width = 800
    Height = 97
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
      Width = 589
      Height = 23
      TabOrder = 0
      TextHint = #36755#20837#30340#25991#26412#65292#20250#20808#36716#25104'UTF-8'#30340#25991#26412#65292#20877#29983#25104'MD5'
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
    object Button1: TButton
      Left = 695
      Top = 17
      Width = 75
      Height = 25
      Caption = #29983#25104'MD5'
      TabOrder = 3
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 432
      Top = 64
      Width = 90
      Height = 25
      Caption = #28165#31354
      TabOrder = 4
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 552
      Top = 64
      Width = 81
      Height = 25
      Caption = #20840#37096#22797#21046
      TabOrder = 5
      OnClick = Button3Click
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 97
    Width = 800
    Height = 445
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object Memo1: TMemo
      Left = 0
      Top = 0
      Width = 800
      Height = 445
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
