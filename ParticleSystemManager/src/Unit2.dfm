object Form2: TForm2
  Left = 676
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Params'
  ClientHeight = 665
  ClientWidth = 201
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 0
    Top = 4
    Width = 28
    Height = 13
    Caption = 'Name'
  end
  object Label2: TLabel
    Left = 0
    Top = 28
    Width = 73
    Height = 13
    Caption = 'Texture FName'
  end
  object Label3: TLabel
    Left = 0
    Top = 68
    Width = 51
    Height = 13
    Caption = 'Start frame'
  end
  object Label4: TLabel
    Left = 0
    Top = 132
    Width = 50
    Height = 13
    Caption = 'Blend kind'
  end
  object Label5: TLabel
    Left = 0
    Top = 180
    Width = 51
    Height = 13
    Caption = 'Particle life'
  end
  object Label6: TLabel
    Left = 0
    Top = 204
    Width = 72
    Height = 13
    Caption = 'Particle life var.'
  end
  object Label7: TLabel
    Left = 0
    Top = 228
    Width = 48
    Height = 13
    Caption = 'Emitter life'
  end
  object Label8: TLabel
    Left = 0
    Top = 252
    Width = 54
    Height = 13
    Caption = 'Start speed'
  end
  object Label9: TLabel
    Left = 0
    Top = 276
    Width = 51
    Height = 13
    Caption = 'End speed'
  end
  object Label10: TLabel
    Left = 0
    Top = 300
    Width = 51
    Height = 13
    Caption = 'Var. speed'
  end
  object Label11: TLabel
    Left = 0
    Top = 324
    Width = 24
    Height = 13
    Caption = 'Dir. x'
  end
  object Label12: TLabel
    Left = 0
    Top = 348
    Width = 24
    Height = 13
    Caption = 'Dir. y'
  end
  object Label13: TLabel
    Left = 0
    Top = 372
    Width = 24
    Height = 13
    Caption = 'Dir. z'
  end
  object Label14: TLabel
    Left = 0
    Top = 396
    Width = 48
    Height = 13
    Caption = 'Start color'
  end
  object Label15: TLabel
    Left = 56
    Top = 420
    Width = 8
    Height = 13
    Caption = 'R'
  end
  object Label16: TLabel
    Left = 104
    Top = 420
    Width = 8
    Height = 13
    Caption = 'G'
  end
  object Label17: TLabel
    Left = 152
    Top = 420
    Width = 7
    Height = 13
    Caption = 'B'
  end
  object Label18: TLabel
    Left = 0
    Top = 444
    Width = 45
    Height = 13
    Caption = 'End color'
  end
  object Label19: TLabel
    Left = 104
    Top = 468
    Width = 8
    Height = 13
    Caption = 'G'
  end
  object Label20: TLabel
    Left = 152
    Top = 468
    Width = 7
    Height = 13
    Caption = 'B'
  end
  object Label21: TLabel
    Left = 0
    Top = 492
    Width = 45
    Height = 13
    Caption = 'Var. color'
  end
  object Label22: TLabel
    Left = 104
    Top = 516
    Width = 8
    Height = 13
    Caption = 'G'
  end
  object Label23: TLabel
    Left = 152
    Top = 516
    Width = 7
    Height = 13
    Caption = 'B'
  end
  object Label24: TLabel
    Left = 56
    Top = 468
    Width = 8
    Height = 13
    Caption = 'R'
  end
  object Label25: TLabel
    Left = 56
    Top = 516
    Width = 8
    Height = 13
    Caption = 'R'
  end
  object Shape1: TShape
    Left = 0
    Top = 536
    Width = 65
    Height = 25
    OnMouseDown = Shape1MouseDown
  end
  object Shape2: TShape
    Left = 72
    Top = 536
    Width = 65
    Height = 25
    OnMouseDown = Shape2MouseDown
  end
  object Shape3: TShape
    Left = 144
    Top = 536
    Width = 57
    Height = 25
    OnMouseDown = Shape3MouseDown
  end
  object Label26: TLabel
    Left = 0
    Top = 572
    Width = 43
    Height = 13
    Caption = 'Start size'
  end
  object Label27: TLabel
    Left = 0
    Top = 596
    Width = 40
    Height = 13
    Caption = 'End size'
  end
  object Label28: TLabel
    Left = 0
    Top = 620
    Width = 40
    Height = 13
    Caption = 'Var. size'
  end
  object Label29: TLabel
    Left = 0
    Top = 420
    Width = 7
    Height = 13
    Caption = 'A'
  end
  object Label30: TLabel
    Left = 0
    Top = 468
    Width = 7
    Height = 13
    Caption = 'A'
  end
  object Label32: TLabel
    Left = 0
    Top = 156
    Width = 41
    Height = 13
    Caption = 'Emission'
  end
  object Label33: TLabel
    Left = 0
    Top = 92
    Width = 59
    Height = 13
    Caption = 'Frame count'
  end
  object Label31: TLabel
    Left = 0
    Top = 516
    Width = 7
    Height = 13
    Caption = 'A'
  end
  object Edit1: TEdit
    Left = 80
    Top = 0
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object Edit2: TEdit
    Left = 80
    Top = 24
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object CheckBox1: TCheckBox
    Left = 80
    Top = 48
    Width = 97
    Height = 17
    Caption = 'Animated'
    Checked = True
    State = cbChecked
    TabOrder = 2
  end
  object SpinEdit1: TSpinEdit
    Left = 80
    Top = 64
    Width = 121
    Height = 22
    MaxValue = 1000000
    MinValue = -1
    TabOrder = 3
    Value = 0
  end
  object CheckBox2: TCheckBox
    Left = 80
    Top = 112
    Width = 97
    Height = 17
    Caption = 'Normal emission'
    Checked = True
    State = cbChecked
    TabOrder = 4
  end
  object SpinEdit2: TSpinEdit
    Left = 80
    Top = 128
    Width = 121
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 5
    Value = 0
  end
  object Edit3: TEdit
    Left = 80
    Top = 176
    Width = 121
    Height = 21
    TabOrder = 6
  end
  object Edit4: TEdit
    Left = 80
    Top = 200
    Width = 121
    Height = 21
    TabOrder = 7
  end
  object Edit5: TEdit
    Left = 80
    Top = 224
    Width = 121
    Height = 21
    TabOrder = 8
  end
  object Edit6: TEdit
    Left = 80
    Top = 248
    Width = 121
    Height = 21
    TabOrder = 9
  end
  object Edit7: TEdit
    Left = 80
    Top = 272
    Width = 121
    Height = 21
    TabOrder = 10
  end
  object Edit8: TEdit
    Left = 80
    Top = 296
    Width = 121
    Height = 21
    TabOrder = 11
  end
  object Edit9: TEdit
    Left = 80
    Top = 320
    Width = 121
    Height = 21
    TabOrder = 12
  end
  object Edit10: TEdit
    Left = 80
    Top = 344
    Width = 121
    Height = 21
    TabOrder = 13
  end
  object Edit11: TEdit
    Left = 80
    Top = 368
    Width = 121
    Height = 21
    TabOrder = 14
  end
  object SpinEdit3: TSpinEdit
    Left = 64
    Top = 416
    Width = 41
    Height = 22
    MaxValue = 255
    MinValue = 0
    TabOrder = 15
    Value = 4
    OnChange = SpinEdit3Change
  end
  object SpinEdit4: TSpinEdit
    Left = 112
    Top = 416
    Width = 41
    Height = 22
    MaxValue = 255
    MinValue = 0
    TabOrder = 16
    Value = 5
    OnChange = SpinEdit3Change
  end
  object SpinEdit5: TSpinEdit
    Left = 160
    Top = 416
    Width = 41
    Height = 22
    MaxValue = 255
    MinValue = 0
    TabOrder = 17
    Value = 2
    OnChange = SpinEdit3Change
  end
  object SpinEdit6: TSpinEdit
    Left = 64
    Top = 464
    Width = 41
    Height = 22
    MaxValue = 255
    MinValue = 0
    TabOrder = 18
    Value = 2
    OnChange = SpinEdit6Change
  end
  object SpinEdit7: TSpinEdit
    Left = 112
    Top = 464
    Width = 41
    Height = 22
    MaxValue = 255
    MinValue = 0
    TabOrder = 19
    Value = 1
    OnChange = SpinEdit6Change
  end
  object SpinEdit8: TSpinEdit
    Left = 160
    Top = 464
    Width = 41
    Height = 22
    MaxValue = 255
    MinValue = 0
    TabOrder = 20
    Value = 255
    OnChange = SpinEdit6Change
  end
  object SpinEdit9: TSpinEdit
    Left = 64
    Top = 512
    Width = 41
    Height = 22
    MaxValue = 255
    MinValue = 0
    TabOrder = 21
    Value = 1
    OnChange = SpinEdit9Change
  end
  object SpinEdit10: TSpinEdit
    Left = 112
    Top = 512
    Width = 41
    Height = 22
    MaxValue = 255
    MinValue = 0
    TabOrder = 22
    Value = 7
    OnChange = SpinEdit9Change
  end
  object SpinEdit11: TSpinEdit
    Left = 160
    Top = 512
    Width = 41
    Height = 22
    MaxValue = 255
    MinValue = 0
    TabOrder = 23
    Value = 2
    OnChange = SpinEdit9Change
  end
  object Edit12: TEdit
    Left = 80
    Top = 568
    Width = 121
    Height = 21
    TabOrder = 24
  end
  object Edit13: TEdit
    Left = 80
    Top = 592
    Width = 121
    Height = 21
    TabOrder = 25
  end
  object Edit14: TEdit
    Left = 80
    Top = 616
    Width = 121
    Height = 21
    TabOrder = 26
  end
  object Button1: TButton
    Left = 0
    Top = 640
    Width = 97
    Height = 25
    Caption = 'OK'
    TabOrder = 27
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 104
    Top = 640
    Width = 97
    Height = 25
    Caption = 'Cancel'
    TabOrder = 28
    OnClick = Button2Click
  end
  object SpinEdit12: TSpinEdit
    Left = 16
    Top = 416
    Width = 41
    Height = 22
    MaxValue = 255
    MinValue = 0
    TabOrder = 29
    Value = 0
  end
  object SpinEdit13: TSpinEdit
    Left = 16
    Top = 464
    Width = 41
    Height = 22
    MaxValue = 255
    MinValue = 0
    TabOrder = 30
    Value = 0
  end
  object SpinEdit14: TSpinEdit
    Left = 16
    Top = 512
    Width = 41
    Height = 22
    MaxValue = 255
    MinValue = 0
    TabOrder = 31
    Value = 0
  end
  object SpinEdit15: TSpinEdit
    Left = 80
    Top = 152
    Width = 121
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 32
    Value = 0
  end
  object SpinEdit16: TSpinEdit
    Left = 80
    Top = 88
    Width = 121
    Height = 22
    MaxValue = 1000000
    MinValue = 0
    TabOrder = 33
    Value = 1
  end
  object ColorDialog1: TColorDialog
  end
end
