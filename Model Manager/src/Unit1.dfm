object Form1: TForm1
  Left = 809
  Top = 341
  Width = 265
  Height = 355
  Caption = 'Model Manager'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label11: TLabel
    Left = 200
    Top = 304
    Width = 52
    Height = 13
    Caption = 'PIE engine'
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 257
    Height = 289
    ActivePage = Model
    Style = tsFlatButtons
    TabOrder = 0
    object Model: TTabSheet
      Caption = 'Model'
      object Label1: TLabel
        Left = 8
        Top = 12
        Width = 28
        Height = 13
        Caption = 'Name'
      end
      object Edit1: TEdit
        Left = 96
        Top = 8
        Width = 153
        Height = 21
        TabOrder = 0
      end
    end
    object Mesh: TTabSheet
      Caption = 'Mesh'
      ImageIndex = 1
      object Label2: TLabel
        Left = 8
        Top = 12
        Width = 28
        Height = 13
        Caption = 'Name'
      end
      object Label3: TLabel
        Left = 8
        Top = 36
        Width = 42
        Height = 13
        Caption = 'Filename'
      end
      object Label4: TLabel
        Left = 8
        Top = 140
        Width = 73
        Height = 13
        Caption = 'Angle threshold'
      end
      object Label5: TLabel
        Left = 8
        Top = 164
        Width = 76
        Height = 13
        Caption = 'Vertex threshold'
      end
      object Label6: TLabel
        Left = 8
        Top = 188
        Width = 82
        Height = 13
        Caption = 'Texture threshold'
      end
      object Label9: TLabel
        Left = 8
        Top = 60
        Width = 72
        Height = 13
        Caption = 'Ph. m. filename'
      end
      object Edit2: TEdit
        Left = 96
        Top = 8
        Width = 153
        Height = 21
        TabOrder = 0
      end
      object Edit3: TEdit
        Left = 96
        Top = 32
        Width = 153
        Height = 21
        TabOrder = 1
      end
      object CheckBox1: TCheckBox
        Left = 8
        Top = 88
        Width = 97
        Height = 17
        Caption = 'Draw mesh'
        Checked = True
        State = cbChecked
        TabOrder = 2
      end
      object CheckBox2: TCheckBox
        Left = 8
        Top = 112
        Width = 97
        Height = 17
        Caption = 'Create buffers'
        Checked = True
        State = cbChecked
        TabOrder = 3
      end
      object Edit4: TEdit
        Left = 96
        Top = 136
        Width = 145
        Height = 21
        TabOrder = 4
        Text = '60,0'
      end
      object Edit5: TEdit
        Left = 96
        Top = 160
        Width = 145
        Height = 21
        TabOrder = 5
        Text = '0,01'
      end
      object Edit6: TEdit
        Left = 96
        Top = 184
        Width = 145
        Height = 21
        TabOrder = 6
        Text = '0,0'
      end
      object CheckBox3: TCheckBox
        Left = 8
        Top = 240
        Width = 97
        Height = 17
        Caption = 'Self illumination'
        TabOrder = 7
      end
      object CheckBox4: TCheckBox
        Left = 8
        Top = 216
        Width = 97
        Height = 17
        Caption = 'Invert normals'
        TabOrder = 8
      end
      object Edit9: TEdit
        Left = 96
        Top = 56
        Width = 153
        Height = 21
        TabOrder = 9
      end
    end
    object Texture: TTabSheet
      Caption = 'Texture'
      ImageIndex = 2
      object Label7: TLabel
        Left = 0
        Top = 60
        Width = 42
        Height = 13
        Caption = 'Filename'
      end
      object Label8: TLabel
        Left = 0
        Top = 28
        Width = 28
        Height = 13
        Caption = 'Name'
      end
      object CheckBox5: TCheckBox
        Left = 0
        Top = 0
        Width = 97
        Height = 17
        Caption = 'Use texture'
        Checked = True
        State = cbChecked
        TabOrder = 0
      end
      object Edit7: TEdit
        Left = 96
        Top = 24
        Width = 145
        Height = 21
        TabOrder = 1
      end
      object Edit8: TEdit
        Left = 96
        Top = 56
        Width = 145
        Height = 21
        TabOrder = 2
      end
    end
    object PS: TTabSheet
      Caption = 'Particle System'
      ImageIndex = 3
      object Label10: TLabel
        Left = 0
        Top = 12
        Width = 59
        Height = 13
        Caption = 'Preset name'
      end
      object Edit10: TEdit
        Left = 96
        Top = 8
        Width = 145
        Height = 21
        TabOrder = 0
      end
    end
  end
  object Button1: TButton
    Left = 0
    Top = 296
    Width = 97
    Height = 25
    Caption = 'Save'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 96
    Top = 296
    Width = 97
    Height = 25
    Caption = 'Load'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = Button2Click
  end
  object OpenDialog1: TOpenDialog
    Filter = 'PIE model|*.pmd'
    Left = 164
    Top = 275
  end
  object SaveDialog1: TSaveDialog
    Filter = 'PIE model|*.pmd'
    Left = 196
    Top = 275
  end
end
