object Form2: TForm2
  Left = 335
  Top = 151
  BorderStyle = bsDialog
  Caption = 'Tileset properties'
  ClientHeight = 81
  ClientWidth = 193
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
  object Label1: TLabel
    Left = 0
    Top = 5
    Width = 28
    Height = 13
    Caption = 'Name'
  end
  object Label2: TLabel
    Left = 0
    Top = 29
    Width = 38
    Height = 13
    Caption = 'Tile size'
  end
  object Edit1: TEdit
    Left = 72
    Top = 0
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object SpinEdit1: TSpinEdit
    Left = 72
    Top = 24
    Width = 121
    Height = 22
    MaxValue = 256
    MinValue = 16
    TabOrder = 1
    Value = 64
  end
  object Button1: TButton
    Left = 0
    Top = 56
    Width = 97
    Height = 25
    Caption = 'OK'
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 96
    Top = 56
    Width = 97
    Height = 25
    Caption = 'Cancel'
    TabOrder = 3
    OnClick = Button2Click
  end
end
