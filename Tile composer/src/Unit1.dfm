object Form1: TForm1
  Left = 190
  Top = 105
  BorderStyle = bsDialog
  Caption = 'Tile ComPoser'
  ClientHeight = 191
  ClientWidth = 451
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 376
    Top = 0
    Width = 75
    Height = 33
    Caption = 'Add'
    TabOrder = 0
    OnClick = Button1Click
  end
  object ListBox1: TListBox
    Left = 0
    Top = 0
    Width = 377
    Height = 161
    ItemHeight = 13
    MultiSelect = True
    PopupMenu = PopupMenu1
    TabOrder = 1
  end
  object Button2: TButton
    Left = 376
    Top = 32
    Width = 75
    Height = 33
    Caption = 'Remove'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 376
    Top = 64
    Width = 75
    Height = 33
    Caption = 'Move Up'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 376
    Top = 96
    Width = 75
    Height = 33
    Caption = 'Move Down'
    TabOrder = 4
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 376
    Top = 128
    Width = 75
    Height = 33
    Caption = 'Do it!'
    TabOrder = 5
    OnClick = Button5Click
  end
  object SpinEdit1: TSpinEdit
    Left = 8
    Top = 168
    Width = 121
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 6
    Value = 0
  end
  object SpinEdit2: TSpinEdit
    Left = 136
    Top = 168
    Width = 121
    Height = 22
    MaxValue = 0
    MinValue = 0
    TabOrder = 7
    Value = 0
  end
  object OpenDialog1: TOpenDialog
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofEnableSizing]
  end
  object SaveDialog1: TSaveDialog
    Left = 128
    Top = 56
  end
  object PopupMenu1: TPopupMenu
    Left = 176
    Top = 80
    object Add1: TMenuItem
      Caption = 'Add'
      ShortCut = 16462
      OnClick = Button1Click
    end
    object Doit1: TMenuItem
      Caption = 'Do it'
      ShortCut = 113
      OnClick = Button5Click
    end
    object MoveDown1: TMenuItem
      Caption = 'Move Down'
      ShortCut = 16452
      OnClick = Button4Click
    end
    object MoveUp1: TMenuItem
      Caption = 'Move Up'
      ShortCut = 16469
      OnClick = Button3Click
    end
    object Remove1: TMenuItem
      Caption = 'Remove'
      ShortCut = 46
      OnClick = Button2Click
    end
    object Sort1: TMenuItem
      Caption = 'Sort'
      ShortCut = 16467
      OnClick = Sort1Click
    end
    object SelectAll1: TMenuItem
      Caption = 'Select All'
      ShortCut = 16449
      OnClick = SelectAll1Click
    end
  end
end
