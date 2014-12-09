object Form2: TForm2
  Left = 191
  Top = 109
  BorderStyle = bsDialog
  Caption = 'New map'
  ClientHeight = 73
  ClientWidth = 250
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 0
    Top = 8
    Width = 28
    Height = 13
    Caption = 'Name'
  end
  object Label2: TLabel
    Left = 0
    Top = 32
    Width = 64
    Height = 13
    Caption = 'Width/Height'
  end
  object Edit1: TEdit
    Left = 88
    Top = 0
    Width = 161
    Height = 21
    TabOrder = 0
  end
  object ComboBox1: TComboBox
    Left = 88
    Top = 24
    Width = 81
    Height = 21
    ItemHeight = 13
    ItemIndex = 4
    TabOrder = 1
    Text = '256'
    Items.Strings = (
      '16'
      '32'
      '64'
      '128'
      '256'
      '512')
  end
  object ComboBox2: TComboBox
    Left = 168
    Top = 24
    Width = 81
    Height = 21
    ItemHeight = 13
    ItemIndex = 4
    TabOrder = 2
    Text = '256'
    Items.Strings = (
      '16'
      '32'
      '64'
      '128'
      '256'
      '512')
  end
  object Button1: TButton
    Left = 24
    Top = 48
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 120
    Top = 48
    Width = 73
    Height = 25
    Caption = 'Cancel'
    TabOrder = 4
    OnClick = Button2Click
  end
end
