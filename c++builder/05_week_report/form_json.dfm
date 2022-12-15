object frmJSON: TfrmJSON
  Left = 0
  Top = 0
  Align = alClient
  BorderStyle = bsNone
  Caption = 'frmJSON'
  ClientHeight = 680
  ClientWidth = 957
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Splitter1: TSplitter
    Left = 481
    Top = 0
    Width = 8
    Height = 680
    ExplicitLeft = 205
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 481
    Height = 680
    Align = alLeft
    BevelOuter = bvNone
    TabOrder = 0
    object Panel3: TPanel
      Left = 0
      Top = 0
      Width = 481
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object Button1: TButton
        Left = 24
        Top = 8
        Width = 153
        Height = 25
        Caption = #36873#25321#25110#25302#20837'JSON'#25991#20214
        TabOrder = 0
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 192
        Top = 8
        Width = 89
        Height = 25
        Caption = #31896#36148
        TabOrder = 1
        OnClick = Button2Click
      end
    end
    object Panel5: TPanel
      Left = 0
      Top = 41
      Width = 481
      Height = 639
      Align = alClient
      BevelOuter = bvNone
      Caption = 'Panel5'
      TabOrder = 1
      object Memo1: TMemo
        Left = 0
        Top = 0
        Width = 481
        Height = 639
        Align = alClient
        BorderStyle = bsNone
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -14
        Font.Name = 'Consolas'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
  end
  object Panel2: TPanel
    Left = 489
    Top = 0
    Width = 468
    Height = 680
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object Panel4: TPanel
      Left = 0
      Top = 0
      Width = 468
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object Button3: TButton
        Left = 16
        Top = 10
        Width = 89
        Height = 25
        Caption = #22797#21046#32467#26524
        TabOrder = 0
      end
    end
    object Panel6: TPanel
      Left = 0
      Top = 41
      Width = 468
      Height = 639
      Align = alClient
      BevelOuter = bvNone
      Caption = 'Panel6'
      TabOrder = 1
      object Memo2: TMemo
        Left = 0
        Top = 0
        Width = 468
        Height = 639
        Align = alClient
        BorderStyle = bsNone
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Consolas'
        Font.Style = []
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
      end
    end
  end
  object OpenTextFileDialog1: TOpenTextFileDialog
    DefaultExt = '.json'
    FileName = 'D:\work\lr\contract_export\package.json'
    Filter = 'JSON|*.json|'#25152#26377#25991#20214'|*.*'
    Options = [ofReadOnly, ofHideReadOnly, ofExtensionDifferent, ofEnableSizing]
    Encodings.Strings = (
      'ANSI'
      'UTF-8')
    EncodingIndex = 1
    Left = 368
    Top = 32
  end
end
