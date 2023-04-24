object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 628
  ClientWidth = 983
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  OnCreate = FormCreate
  TextHeight = 15
  object Panel1: TPanel
    Left = 0
    Top = 65
    Width = 983
    Height = 563
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    ExplicitLeft = 160
    ExplicitTop = 128
    ExplicitWidth = 185
    ExplicitHeight = 41
    object Memo1: TMemo
      Left = 1
      Top = 1
      Width = 981
      Height = 561
      Align = alClient
      Lines.Strings = (
        'Memo1')
      TabOrder = 0
      ExplicitLeft = 0
      ExplicitTop = 232
      ExplicitWidth = 983
      ExplicitHeight = 396
    end
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 983
    Height = 65
    ButtonHeight = 54
    ButtonWidth = 48
    Caption = 'ToolBar1'
    Images = ImageList1
    ShowCaptions = True
    TabOrder = 1
    object ToolButton1: TToolButton
      Left = 0
      Top = 0
      Action = Action1
    end
    object ToolButton2: TToolButton
      Left = 48
      Top = 0
      Action = Action3
    end
    object ToolButton3: TToolButton
      Left = 96
      Top = 0
      Action = Action3
    end
  end
  object MainMenu1: TMainMenu
    Left = 608
    Top = 128
    object Action11: TMenuItem
      Action = Action1
      object Action21: TMenuItem
        Action = Action2
      end
      object Action31: TMenuItem
        Action = Action3
      end
    end
    object Bold1: TMenuItem
      Action = FormatRichEditBold1
      AutoCheck = True
    end
  end
  object ActionList1: TActionList
    Left = 720
    Top = 152
    object Action1: TAction
      Caption = 'Action1'
      OnExecute = Action1Execute
    end
    object Action2: TAction
      Caption = 'Action2'
      OnExecute = Action2Execute
    end
    object Action3: TAction
      Caption = 'Action3'
      OnExecute = Action3Execute
    end
    object FormatRichEditBold1: TRichEditBold
      Category = 'Format'
      AutoCheck = True
      Caption = '&Bold'
      Hint = 'Bold'
      ImageIndex = 31
      ShortCut = 16450
    end
  end
  object ImageList1: TImageList
    Height = 32
    Width = 32
    Left = 424
    Top = 80
  end
end
