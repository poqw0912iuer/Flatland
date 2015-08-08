object Form1: TForm1
  Left = 858
  Top = 156
  BorderStyle = bsSingle
  Caption = 'Flatland Agent'
  ClientHeight = 698
  ClientWidth = 559
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 96
    Top = 168
    Width = 25
    Height = 13
    Caption = 'steps'
  end
  object Label6: TLabel
    Left = 448
    Top = 40
    Width = 50
    Height = 13
    Caption = 'Population'
  end
  object Label7: TLabel
    Left = 448
    Top = 64
    Width = 38
    Height = 13
    Caption = 'Cr. Porb'
  end
  object Label8: TLabel
    Left = 448
    Top = 88
    Width = 46
    Height = 13
    Caption = 'Mut. Prob'
  end
  object Label9: TLabel
    Left = 448
    Top = 112
    Width = 57
    Height = 13
    Caption = 'Gneerations'
  end
  object Label4: TLabel
    Left = 192
    Top = 168
    Width = 147
    Height = 23
    Caption = 'Scenario no. '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Neuropol'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 376
    Top = 168
    Width = 91
    Height = 23
    Caption = 'Fitnes = '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Neuropol'
    Font.Style = []
    ParentFont = False
  end
  object Edit2: TEdit
    Left = 512
    Top = 40
    Width = 41
    Height = 21
    TabOrder = 0
    Text = '40'
  end
  object Button2: TButton
    Left = 0
    Top = 168
    Width = 89
    Height = 25
    Caption = 'Visualise'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 448
    Top = 8
    Width = 105
    Height = 25
    Caption = 'Solve'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Edit3: TEdit
    Left = 512
    Top = 64
    Width = 41
    Height = 21
    TabOrder = 3
    Text = '0,80'
  end
  object Edit4: TEdit
    Left = 512
    Top = 88
    Width = 41
    Height = 21
    TabOrder = 4
    Text = '0,30'
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 257
    Height = 161
    Caption = 'Selection Mechanisms'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    object Label10: TLabel
      Left = 144
      Top = 64
      Width = 13
      Height = 13
      Caption = 'T='
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object RadioButton1: TRadioButton
      Left = 8
      Top = 128
      Width = 161
      Height = 17
      Caption = 'Fitness Proportionate scaling'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = RadioButton1Click
    end
    object RadioButton2: TRadioButton
      Left = 8
      Top = 32
      Width = 113
      Height = 17
      Caption = 'Sigma scaling'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      TabStop = True
      OnClick = RadioButton2Click
    end
    object RadioButton3: TRadioButton
      Left = 8
      Top = 64
      Width = 113
      Height = 17
      Caption = 'Boltzman scaling'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = RadioButton3Click
    end
    object RadioButton4: TRadioButton
      Left = 8
      Top = 96
      Width = 113
      Height = 17
      Caption = 'Rank selection'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = RadioButton4Click
    end
    object Edit5: TEdit
      Left = 160
      Top = 64
      Width = 33
      Height = 21
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      Text = '40'
    end
  end
  object GroupBox2: TGroupBox
    Left = 264
    Top = 0
    Width = 177
    Height = 81
    Caption = 'Selection Protocols'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    object RadioButton6: TRadioButton
      Left = 8
      Top = 24
      Width = 161
      Height = 17
      Caption = 'Full Generational replacement'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object RadioButton7: TRadioButton
      Left = 8
      Top = 48
      Width = 113
      Height = 17
      Caption = 'Over Production'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      TabStop = True
    end
  end
  object Edit8: TEdit
    Left = 512
    Top = 112
    Width = 41
    Height = 21
    TabOrder = 7
    Text = '20'
  end
  object Edit9: TEdit
    Left = 128
    Top = 168
    Width = 41
    Height = 21
    TabOrder = 8
    Text = '50'
  end
  object Button5: TButton
    Left = 448
    Top = 136
    Width = 105
    Height = 25
    Caption = 'Plot'
    Enabled = False
    TabOrder = 9
    OnClick = Button5Click
  end
  object GroupBox3: TGroupBox
    Left = 264
    Top = 88
    Width = 177
    Height = 73
    Caption = 'Type of run'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 10
    object RadioButton9: TRadioButton
      Left = 8
      Top = 24
      Width = 113
      Height = 17
      Caption = 'Dynamic'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      TabStop = True
    end
    object RadioButton10: TRadioButton
      Left = 8
      Top = 48
      Width = 113
      Height = 17
      Caption = 'Static'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
  end
  object TrackBar1: TTrackBar
    Left = 512
    Top = 208
    Width = 41
    Height = 361
    Max = 50
    Min = 1
    Orientation = trVertical
    ParentShowHint = False
    Frequency = 1
    Position = 1
    SelEnd = 0
    SelStart = 0
    ShowHint = False
    TabOrder = 11
    TickMarks = tmBoth
    TickStyle = tsAuto
    OnChange = TrackBar1Change
  end
end
