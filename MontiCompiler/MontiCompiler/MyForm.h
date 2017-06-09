#pragma once
#include "FSM.h"

namespace MontiCompiler {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	FSM Compiler;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  archivoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  guargarToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cargarToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  salirToolStripMenuItem;
	private: System::Windows::Forms::RichTextBox^  richTextBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  proyectoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  compilarToolStripMenuItem;

	private: System::Windows::Forms::RichTextBox^  richTextBox2;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;




	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->archivoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->guargarToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cargarToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->salirToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->proyectoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->compilarToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->menuStrip1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::Color::DimGray;
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(18, 18);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->archivoToolStripMenuItem,
					this->proyectoToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(782, 27);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// archivoToolStripMenuItem
			// 
			this->archivoToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->guargarToolStripMenuItem,
					this->cargarToolStripMenuItem, this->toolStripSeparator1, this->salirToolStripMenuItem
			});
			this->archivoToolStripMenuItem->Name = L"archivoToolStripMenuItem";
			this->archivoToolStripMenuItem->Size = System::Drawing::Size(67, 23);
			this->archivoToolStripMenuItem->Text = L"Archivo";
			// 
			// guargarToolStripMenuItem
			// 
			this->guargarToolStripMenuItem->Name = L"guargarToolStripMenuItem";
			this->guargarToolStripMenuItem->Size = System::Drawing::Size(132, 24);
			this->guargarToolStripMenuItem->Text = L"Guargar";
			this->guargarToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::guargarToolStripMenuItem_Click);
			// 
			// cargarToolStripMenuItem
			// 
			this->cargarToolStripMenuItem->Name = L"cargarToolStripMenuItem";
			this->cargarToolStripMenuItem->Size = System::Drawing::Size(132, 24);
			this->cargarToolStripMenuItem->Text = L"Cargar";
			this->cargarToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cargarToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(129, 6);
			// 
			// salirToolStripMenuItem
			// 
			this->salirToolStripMenuItem->Name = L"salirToolStripMenuItem";
			this->salirToolStripMenuItem->Size = System::Drawing::Size(132, 24);
			this->salirToolStripMenuItem->Text = L"Salir";
			this->salirToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::salirToolStripMenuItem_Click);
			// 
			// proyectoToolStripMenuItem
			// 
			this->proyectoToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->compilarToolStripMenuItem });
			this->proyectoToolStripMenuItem->Name = L"proyectoToolStripMenuItem";
			this->proyectoToolStripMenuItem->Size = System::Drawing::Size(75, 23);
			this->proyectoToolStripMenuItem->Text = L"Proyecto";
			// 
			// compilarToolStripMenuItem
			// 
			this->compilarToolStripMenuItem->Name = L"compilarToolStripMenuItem";
			this->compilarToolStripMenuItem->Size = System::Drawing::Size(137, 24);
			this->compilarToolStripMenuItem->Text = L"Compilar";
			this->compilarToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::compilarToolStripMenuItem_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::Color::White;
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.78182F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(12, 56);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(758, 334);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->Text = L"";
			// 
			// richTextBox2
			// 
			this->richTextBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.78182F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->richTextBox2->Location = System::Drawing::Point(13, 424);
			this->richTextBox2->Name = L"richTextBox2";
			this->richTextBox2->ReadOnly = true;
			this->richTextBox2->Size = System::Drawing::Size(757, 120);
			this->richTextBox2->TabIndex = 2;
			this->richTextBox2->Text = L"";
			// 
			// toolStrip1
			// 
			this->toolStrip1->BackColor = System::Drawing::SystemColors::WindowFrame;
			this->toolStrip1->ImageScalingSize = System::Drawing::Size(18, 18);
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripButton1 });
			this->toolStrip1->Location = System::Drawing::Point(0, 27);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(782, 25);
			this->toolStrip1->TabIndex = 3;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(23, 22);
			this->toolStripButton1->Text = L"toolStripButton1";
			this->toolStripButton1->Click += gcnew System::EventHandler(this, &MyForm::toolStripButton1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Gray;
			this->ClientSize = System::Drawing::Size(782, 556);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->richTextBox2);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"MontiCompiler";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void salirToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		Application::Exit();
	}

	private: System::Void compilarToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		Compiler.SetString((char*)(void*)Marshal::StringToHGlobalAnsi(this->richTextBox1->Text));
		Compiler.ErrorManagment.Clean();
		Compiler.TokenManagment.Clean();
		Compiler.LexicalAnalysis();
		Compiler.ErrorManagment.Save();
		Compiler.TokenManagment.Save();
		this->richTextBox2->Text = L"";
		for (auto &error : Compiler.ErrorManagment.m_lErrors)
		{
			std::string s = error.desc + " Line: " + std::to_string(error.line) + " " + error.text + " " + error.type + "\n";
			this->richTextBox2->Text += gcnew String(s.c_str());
		}
	}
	private: System::Void cargarToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		if (Compiler.Load("main"))
		{
			if (this->richTextBox1->Text == L"")
				this->richTextBox1->Text = gcnew String(Compiler.m_formatString.c_str());
			else
			{
				// Initializes the variables to pass to the MessageBox::Show method.
				String^ message = "Error al cargar";
				String^ caption = "El documento no esta limpio";
				MessageBoxButtons buttons = MessageBoxButtons::YesNo;
				System::Windows::Forms::DialogResult result;

				// Displays the MessageBox.
				result = MessageBox::Show(this, message, caption, buttons);
			}
			Compiler.SetString("");
		}
		else
		{
			// Initializes the variables to pass to the MessageBox::Show method.
			String^ message = "El archivo main.txt no existe";
			String^ caption = "Error al cargar el archivo";
			MessageBoxButtons buttons = MessageBoxButtons::YesNo;
			System::Windows::Forms::DialogResult result;

			// Displays the MessageBox.
			result = MessageBox::Show(this, message, caption, buttons);
		}

	}
	private: System::Void guargarToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		Compiler.SetString((char*)(void*)Marshal::StringToHGlobalAnsi(this->richTextBox1->Text));
		Compiler.Save("main");
	}
private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e) {
	Compiler.SetString((char*)(void*)Marshal::StringToHGlobalAnsi(this->richTextBox1->Text));
	Compiler.ErrorManagment.Clean();
	Compiler.TokenManagment.Clean();
	Compiler.LexicalAnalysis();
	Compiler.ErrorManagment.Save();
	Compiler.TokenManagment.Save();
	this->richTextBox2->Text = L"";
	for (auto &error : Compiler.ErrorManagment.m_lErrors)
	{
		std::string s = error.desc + " Line: " + std::to_string(error.line) + " " + error.text + " " + error.type + "\n";
		this->richTextBox2->Text += gcnew String(s.c_str());
	}
}
};
}
