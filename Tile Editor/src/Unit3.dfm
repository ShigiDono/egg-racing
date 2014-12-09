object Form3: TForm3
  Left = 246
  Top = 456
  BorderStyle = bsDialog
  Caption = 'Form3'
  ClientHeight = 153
  ClientWidth = 217
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
    Width = 46
    Height = 13
    Caption = 'Tile name'
  end
  object Label2: TLabel
    Left = 0
    Top = 29
    Width = 78
    Height = 13
    Caption = 'Texture filename'
  end
  object Label3: TLabel
    Left = 0
    Top = 53
    Width = 87
    Height = 13
    Caption = 'Tile width X height'
  end
  object Label4: TLabel
    Left = 0
    Top = 77
    Width = 24
    Height = 13
    Caption = 'Color'
  end
  object Shape1: TShape
    Left = 104
    Top = 72
    Width = 113
    Height = 17
    OnMouseUp = Shape1MouseUp
  end
  object Label5: TLabel
    Left = 0
    Top = 104
    Width = 32
    Height = 13
    Caption = 'Label5'
  end
  object Edit1: TEdit
    Left = 104
    Top = 0
    Width = 113
    Height = 21
    TabOrder = 0
    Text = 'Edit1'
  end
  object Edit2: TEdit
    Left = 104
    Top = 24
    Width = 113
    Height = 21
    TabOrder = 1
    Text = 'Edit1'
  end
  object SpinEdit1: TSpinEdit
    Left = 104
    Top = 48
    Width = 57
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 2
    Value = 0
  end
  object SpinEdit2: TSpinEdit
    Left = 160
    Top = 48
    Width = 57
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 3
    Value = 0
  end
  object Button1: TButton
    Left = 192
    Top = 96
    Width = 25
    Height = 25
    Caption = '...'
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 0
    Top = 128
    Width = 105
    Height = 25
    Caption = 'OK'
    TabOrder = 5
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 112
    Top = 128
    Width = 105
    Height = 25
    Caption = 'Cancel'
    TabOrder = 6
    OnClick = Button3Click
  end
  object ColorDialog1: TColorDialog
  end
  object OpenDialog1: TOpenDialog
    Left = 32
  end
end
