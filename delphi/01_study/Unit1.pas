unit Unit1;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    ListBox1: TListBox;
    Button1: TButton;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
const
  UserId: Integer = 1;
  Password: String = '123456';
  UserName: String = 'hello test';
  Num: array[0..9] of char = ('0','1','2','3','4','5','6','7','8','9');

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
var
  i: Integer;
begin
  Edit1.Text := IntToStr(UserId);
  Edit2.Text := Password;
  Edit3.Text := UserName;
  for i := 0 to high(Num) do
    begin
        // ListBox1.Items.Add('0');
        ListBox1.Items.Add(Num[i]);
    end;

end;

end.
