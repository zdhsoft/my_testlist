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
  OnDestroy = FormDestroy
  TextHeight = 21
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 912
    Height = 119
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
    object Label5: TLabel
      Left = 143
      Top = 47
      Width = 82
      Height = 18
      Caption = #21608#25253#36335#24452':'
    end
    object Label6: TLabel
      Left = 240
      Top = 48
      Width = 49
      Height = 21
      Caption = 'Label6'
      Color = clRed
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -16
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
    object Label7: TLabel
      Left = 409
      Top = 87
      Width = 80
      Height = 21
      Caption = #36873#25321#26085#26399#65306
    end
    object Label8: TLabel
      Left = 752
      Top = 15
      Width = 84
      Height = 21
      Caption = #36873#25321#30340#26085#26399':'
    end
    object Label9: TLabel
      Left = 842
      Top = 15
      Width = 86
      Height = 21
      Caption = '2023-01-01'
      Font.Charset = ANSI_CHARSET
      Font.Color = clRed
      Font.Height = -16
      Font.Name = #24494#36719#38597#40657
      Font.Style = []
      ParentFont = False
    end
    object Edit1: TEdit
      Left = 70
      Top = 12
      Width = 676
      Height = 29
      TabOrder = 0
      Text = '.'
    end
    object Button1: TButton
      Left = 16
      Top = 43
      Width = 121
      Height = 33
      Caption = #36873#25321#26681#30446#24405
      TabOrder = 1
      OnClick = Button1Click
    end
    object DateTimePicker1: TDateTimePicker
      Left = 498
      Top = 84
      Width = 225
      Height = 29
      Date = 44936.000000000000000000
      Format = 'yyyy-MM-dd'
      Time = 0.741427037035464300
      TabOrder = 2
      OnChange = DateTimePicker1Change
    end
    object Button5: TButton
      Left = 16
      Top = 85
      Width = 121
      Height = 28
      Caption = #19978#21608#20116
      TabOrder = 3
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 143
      Top = 85
      Width = 122
      Height = 28
      Caption = #19979#21608#20116
      TabOrder = 4
      OnClick = Button6Click
    end
    object Button7: TButton
      Left = 271
      Top = 85
      Width = 114
      Height = 28
      Caption = #26412#21608#20116
      TabOrder = 5
      OnClick = Button7Click
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 119
    Width = 912
    Height = 361
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 249
      Top = 0
      Height = 361
      ExplicitLeft = 256
      ExplicitTop = 288
      ExplicitHeight = 100
    end
    object Splitter2: TSplitter
      Left = 489
      Top = 0
      Height = 361
      ExplicitLeft = 608
      ExplicitTop = 280
      ExplicitHeight = 100
    end
    object Splitter3: TSplitter
      Left = 705
      Top = 0
      Height = 361
      ExplicitLeft = 792
      ExplicitTop = 288
      ExplicitHeight = 100
    end
    object ListBox1: TListBox
      Left = 0
      Top = 0
      Width = 249
      Height = 361
      Align = alLeft
      ItemHeight = 21
      TabOrder = 0
    end
    object Panel3: TPanel
      Left = 252
      Top = 0
      Width = 237
      Height = 361
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 1
      object ListBoxCurr: TListBox
        Left = 0
        Top = 65
        Width = 237
        Height = 296
        Align = alClient
        ItemHeight = 21
        TabOrder = 0
      end
      object Panel5: TPanel
        Left = 0
        Top = 0
        Width = 237
        Height = 65
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 1
        object Label2: TLabel
          Left = 0
          Top = 44
          Width = 237
          Height = 21
          Align = alBottom
          Caption = #24403#21069#25104#21592#65306
          ExplicitWidth = 80
        end
        object Button2: TButton
          Left = 6
          Top = 13
          Width = 219
          Height = 25
          Caption = #35774#32622#25104#21592
          TabOrder = 0
        end
      end
    end
    object Panel4: TPanel
      Left = 492
      Top = 0
      Width = 213
      Height = 361
      Align = alLeft
      BevelOuter = bvNone
      TabOrder = 2
      object Panel7: TPanel
        Left = 0
        Top = 0
        Width = 213
        Height = 65
        Align = alTop
        TabOrder = 0
        object Label3: TLabel
          Left = 1
          Top = 43
          Width = 211
          Height = 21
          Align = alBottom
          Caption = #26410#22635#65306
          ExplicitWidth = 48
        end
        object Button4: TButton
          Left = 6
          Top = 12
          Width = 201
          Height = 25
          Caption = #22797#21046#21098#36148#26495
          TabOrder = 0
          OnClick = Button4Click
        end
      end
      object ListBoxNot: TListBox
        Left = 0
        Top = 65
        Width = 213
        Height = 296
        Align = alClient
        ItemHeight = 21
        TabOrder = 1
      end
    end
    object Panel6: TPanel
      Left = 708
      Top = 0
      Width = 204
      Height = 361
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 3
      object Panel8: TPanel
        Left = 0
        Top = 0
        Width = 204
        Height = 65
        Align = alTop
        TabOrder = 0
        object Label4: TLabel
          Left = 1
          Top = 43
          Width = 202
          Height = 21
          Align = alBottom
          Caption = #24050#22635#65306
          ExplicitWidth = 48
        end
      end
      object ListBoxGood: TListBox
        Left = 0
        Top = 65
        Width = 204
        Height = 296
        Align = alClient
        ItemHeight = 21
        TabOrder = 1
      end
      object Button3: TButton
        Left = 6
        Top = 12
        Width = 187
        Height = 25
        Caption = #22797#21046#21098#36148#26495
        TabOrder = 2
        OnClick = Button3Click
      end
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
