object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 441
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Button1: TButton
    Left = 112
    Top = 264
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 40
    Top = 8
    Width = 433
    Height = 185
    Lines.Strings = (
      'Memo1')
    TabOrder = 1
  end
  object NetHTTPRequest1: TNetHTTPRequest
    ConnectionTimeout = 0
    SendTimeout = 0
    ResponseTimeout = 0
    Left = 456
    Top = 304
  end
end
