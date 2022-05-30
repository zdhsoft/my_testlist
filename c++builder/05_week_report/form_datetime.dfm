object frmDateTime: TfrmDateTime
  Left = 0
  Top = 0
  Align = alClient
  BorderStyle = bsNone
  Caption = 'frmDateTime'
  ClientHeight = 757
  ClientWidth = 944
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = #24494#36719#38597#40657
  Font.Style = []
  TextHeight = 21
  object Label1: TLabel
    Left = 24
    Top = 16
    Width = 96
    Height = 21
    Caption = #26102#38388#25139#36716#25442#65306
  end
  object Label2: TLabel
    Left = 24
    Top = 56
    Width = 128
    Height = 21
    Caption = #29616#22312#30340#26102#38388#25139#26159#65306
  end
  object LabelTimestamp: TLabel
    Left = 158
    Top = 56
    Width = 124
    Height = 21
    Caption = 'LabelTimestamp'
    Color = clBtnFace
    Font.Charset = ANSI_CHARSET
    Font.Color = clRed
    Font.Height = -16
    Font.Name = #24494#36719#38597#40657
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object Label3: TLabel
    Left = 24
    Top = 104
    Width = 130
    Height = 21
    Caption = 'Unix'#26102#38388#25139#65288#31186#65289
  end
  object Label4: TLabel
    Left = 24
    Top = 152
    Width = 146
    Height = 21
    Caption = 'Unix'#26102#38388#25139#65288#27627#31186#65289
  end
  object Label5: TLabel
    Left = 24
    Top = 208
    Width = 133
    Height = 21
    Caption = #26412#22320#26102#38388#65306'('#31186#65289#65306
  end
  object Label6: TLabel
    Left = 24
    Top = 248
    Width = 149
    Height = 21
    Caption = #26412#22320#26102#38388#65306'('#27627#31186#65289#65306
  end
  object btnStartTimestamp: TButton
    Left = 304
    Top = 51
    Width = 75
    Height = 33
    Caption = #24320#22987
    TabOrder = 0
    OnClick = btnStartTimestampClick
  end
  object btnStopTimestamp: TButton
    Left = 385
    Top = 51
    Width = 75
    Height = 33
    Caption = #20572#27490
    TabOrder = 1
    OnClick = btnStopTimestampClick
  end
  object btnCopyTimestamp: TButton
    Left = 466
    Top = 51
    Width = 75
    Height = 33
    Caption = #22797#21046
    TabOrder = 2
    OnClick = btnCopyTimestampClick
  end
  object edTimestampSecond: TEdit
    Left = 176
    Top = 101
    Width = 161
    Height = 29
    TabOrder = 3
    TextHint = #36755#20837#26102#38388#25139
    OnChange = edTimestampSecondChange
  end
  object btnConvertSecond: TButton
    Left = 343
    Top = 99
    Width = 75
    Height = 33
    Caption = '>>'
    TabOrder = 4
    OnClick = edTimestampSecondChange
  end
  object edTimestampResultSecond: TEdit
    Left = 424
    Top = 101
    Width = 313
    Height = 29
    TabOrder = 5
  end
  object edTimestampMillis: TEdit
    Left = 176
    Top = 149
    Width = 161
    Height = 29
    TabOrder = 6
    TextHint = #36755#20837#26102#38388#25139
    OnChange = edTimestampMillisChange
  end
  object btnConvertMillis: TButton
    Left = 343
    Top = 147
    Width = 75
    Height = 33
    Caption = '>>'
    TabOrder = 7
    OnClick = edTimestampMillisChange
  end
  object edTimestampResultMillis: TEdit
    Left = 424
    Top = 149
    Width = 313
    Height = 29
    TabOrder = 8
  end
  object btTimestampResultCopy: TButton
    Left = 743
    Top = 99
    Width = 75
    Height = 33
    Caption = #22797#21046
    TabOrder = 9
    OnClick = btTimestampResultCopyClick
  end
  object btTimestampMillisResultCopy: TButton
    Left = 743
    Top = 147
    Width = 75
    Height = 33
    Caption = #22797#21046
    TabOrder = 10
    OnClick = btTimestampMillisResultCopyClick
  end
  object edDateTimeSecond: TEdit
    Left = 176
    Top = 205
    Width = 284
    Height = 29
    TabOrder = 11
    TextHint = #31034#20363': 2022-05-18 22:00:00'
    OnChange = edDateTimeSecondChange
  end
  object edDateTimeMillis: TEdit
    Left = 176
    Top = 240
    Width = 284
    Height = 29
    TabOrder = 12
    TextHint = #31034#20363': 2022-05-18 22:00:00.999'
    OnChange = edDateTimeMillisChange
  end
  object Button1: TButton
    Left = 466
    Top = 203
    Width = 75
    Height = 33
    Caption = '>>'
    TabOrder = 13
    OnClick = edDateTimeSecondChange
  end
  object Button2: TButton
    Left = 466
    Top = 238
    Width = 75
    Height = 33
    Caption = '>>'
    TabOrder = 14
    OnClick = edDateTimeMillisChange
  end
  object edDTResultSecond: TEdit
    Left = 547
    Top = 205
    Width = 190
    Height = 29
    TabOrder = 15
  end
  object edDTResultMillis: TEdit
    Left = 547
    Top = 240
    Width = 190
    Height = 29
    TabOrder = 16
  end
  object btDTResultSecondCopy: TButton
    Left = 743
    Top = 201
    Width = 75
    Height = 33
    Caption = #22797#21046
    TabOrder = 17
    OnClick = btTimestampResultCopyClick
  end
  object btDTResultMillisCopy: TButton
    Left = 743
    Top = 240
    Width = 75
    Height = 33
    Caption = #22797#21046
    TabOrder = 18
    OnClick = btTimestampMillisResultCopyClick
  end
  object Timer1: TTimer
    Interval = 200
    OnTimer = Timer1Timer
    Left = 680
    Top = 304
  end
end
