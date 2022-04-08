object frmWeek: TfrmWeek
  Left = 0
  Top = 0
  Align = alClient
  BorderStyle = bsNone
  Caption = 'frmWeek'
  ClientHeight = 480
  ClientWidth = 912
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  TextHeight = 21
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 912
    Height = 81
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 16
      Width = 48
      Height = 21
      Caption = #36335#24452#65306
    end
    object Edit1: TEdit
      Left = 70
      Top = 12
      Width = 811
      Height = 29
      TabOrder = 0
      Text = 'D:\work\svn_doc\lr\02-'#39033#30446#31649#29702'\02-'#31649#29702#25253#34920'\02-'#20010#20154#25253#34920'\'#20010#20154#21608#25253'2022'
    end
    object Button1: TButton
      Left = 16
      Top = 43
      Width = 97
      Height = 33
      Caption = #36873#25321#30446#24405
      TabOrder = 1
      OnClick = Button1Click
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 81
    Width = 912
    Height = 399
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitLeft = 368
    ExplicitTop = 224
    ExplicitWidth = 185
    ExplicitHeight = 41
    object ListBox1: TListBox
      Left = 0
      Top = 0
      Width = 249
      Height = 399
      Align = alLeft
      ItemHeight = 21
      TabOrder = 0
    end
  end
  object FileOpenDialog1: TFileOpenDialog
    FavoriteLinks = <>
    FileTypes = <>
    Options = [fdoPickFolders]
    Left = 720
    Top = 152
  end
end
