#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	MontiCompiler::MyForm form;
	Application::Run(%form);
}

void MontiCompiler::MyForm::UpdateLine()
{
	//we get index of first visible char and 
	//number of first visible line
	Point pos = Point(0, 0);
	int firstIndex = richTextBox1->GetCharIndexFromPosition(pos);
	int firstLine = richTextBox1->GetLineFromCharIndex(firstIndex);

	//now we get index of last visible char 
	//and number of last visible line
	pos.X = ClientRectangle.Width;
	pos.Y = ClientRectangle.Height;
	int lastIndex = richTextBox1->GetCharIndexFromPosition(pos);
	int lastLine = richTextBox1->GetLineFromCharIndex(lastIndex);

	//this is point position of last visible char, we'll 
	//use its Y value for calculating numberLabel size
	pos = richTextBox1->GetPositionFromCharIndex(lastIndex);

	//finally, renumber label
	label1->Text = "";
	for (int i = firstLine; i <= lastLine + 1; i++)
	{
		label1->Text += i + 1 + "\n";
	}
}
