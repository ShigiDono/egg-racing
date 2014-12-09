object Form4: TForm4
  Left = 190
  Top = 111
  BorderStyle = bsDialog
  ClientHeight = 81
  ClientWidth = 113
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 0
    Top = 56
    Width = 57
    Height = 25
    Caption = 'OK'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 56
    Top = 56
    Width = 57
    Height = 25
    Caption = 'Cancel'
    TabOrder = 1
    OnClick = Button2Click
  end
  object CheckBox1: TCheckBox
    Left = 8
    Top = 8
    Width = 17
    Height = 17
    TabOrder = 2
  end
  object CheckBox2: TCheckBox
    Left = 8
    Top = 32
    Width = 17
    Height = 17
    TabOrder = 3
  end
  object CheckBox3: TCheckBox
    Left = 40
    Top = 8
    Width = 17
    Height = 17
    TabOrder = 4
  end
  object CheckBox4: TCheckBox
    Left = 40
    Top = 32
    Width = 17
    Height = 17
    TabOrder = 5
  end
  object Button3: TButton
    Left = 64
    Top = 8
    Width = 33
    Height = 33
    Caption = 'All'
    TabOrder = 6
    OnClick = Button3Click
  end
end
